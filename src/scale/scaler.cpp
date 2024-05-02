/**
Copyright 2024 JasmineGraph Team
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */

#include "scaler.h"

#include <unistd.h>

#include <map>
#include <thread>
#include <vector>

#include "../../globals.h"
#include "../k8s/K8sWorkerController.h"
#include "../metadb/SQLiteDBInterface.h"
#include "../util/Utils.h"

using namespace std;

std::mutex schedulerMutex;
static std::thread *scale_down_thread = nullptr;
static volatile bool running = false;
SQLiteDBInterface *sqlite = nullptr;
std::map<std::string, int> used_workers;

static void scale_down_thread_fn();

void start_scale_down(SQLiteDBInterface *sqliteInterface) {
    if (jasminegraph_profile != PROFILE_K8S) return;
    if (scale_down_thread) return;
    sqlite = sqliteInterface;
    running = true;
    scale_down_thread = new std::thread(scale_down_thread_fn);
}

void stop_scale_down() {
    if (jasminegraph_profile != PROFILE_K8S) return;
    if (!scale_down_thread) return;
    running = false;
    scale_down_thread->join();
    scale_down_thread = nullptr;
}

static void scale_down_thread_fn() {
    while (running) {
        sleep(30);
        if (!running) break;
        schedulerMutex.lock();
        vector<string> workers;  // id => "ip:port"
        const std::vector<vector<pair<string, string>>> &results =
            sqlite->runSelect("SELECT DISTINCT idworker FROM worker;");
        for (int i = 0; i < results.size(); i++) {
            string workerId = results[i][0].second;
            workers.push_back(workerId);
        }

        vector<int> removing;
        for (auto it = workers.begin(); it != workers.end(); it++) {
            const string &worker = *it;
            auto it_used = used_workers.find(worker);
            if (it_used != used_workers.end() && it_used->second > 0) continue;
            removing.push_back(stoi(worker));
        }

        // TODO(thevindu-w): Transfer partitions and spare 2 workers

        K8sWorkerController *k8s = K8sWorkerController::getInstance();
        k8s->scaleDown(removing);
        schedulerMutex.unlock();
    }
}
