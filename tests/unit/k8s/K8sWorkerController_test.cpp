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

#include "../../../src/k8s/K8sWorkerController.h"

#include <fstream>
#include <vector>

#include "gtest/gtest.h"

class K8sWorkerControllerTest : public ::testing::Test {
 public:
    static K8sWorkerController *controller;
    static SQLiteDBInterface *metadb;
    static K8sInterface *interface;

    static void SetUpTestSuite() {
        metadb = new SQLiteDBInterface(TEST_RESOURCE_DIR "temp/jasminegraph_meta.db");
        metadb->init();
        controller = K8sWorkerController::getInstance("10.43.0.1", 2, metadb);
        interface = new K8sInterface();
    }

    static void TearDownTestSuite() {
        delete controller;
        delete metadb;
        delete interface;
        remove(TEST_RESOURCE_DIR "temp/jasminegraph_meta.db");
    }
};

K8sWorkerController *K8sWorkerControllerTest::controller = nullptr;
SQLiteDBInterface *K8sWorkerControllerTest::metadb = nullptr;
K8sInterface *K8sWorkerControllerTest::interface = nullptr;

TEST_F(K8sWorkerControllerTest, TestConstructor) {
    ASSERT_EQ(controller->getMasterIp(), "10.43.0.1");
    ASSERT_EQ(controller->getNumberOfWorkers(), 2);
    auto result = metadb->runSelect("SELECT idworker FROM worker");
    ASSERT_EQ(result.size(), 2);

    v1_deployment_list_t *deployment_list = interface->getDeploymentList(strdup("deployment=jasminegraph-worker"));
    ASSERT_EQ(deployment_list->items->count, 2);
    v1_service_list_t *service_list = interface->getServiceList(strdup("service=jasminegraph-worker"));
    ASSERT_EQ(service_list->items->count, 2);
}

TEST_F(K8sWorkerControllerTest, TestScaleUp) {
    auto result = controller->scaleUp(2);
    ASSERT_EQ(result.size(), 2);
    v1_deployment_list_t *deployment_list = interface->getDeploymentList(strdup("deployment=jasminegraph-worker"));
    ASSERT_EQ(deployment_list->items->count, 4);
    v1_service_list_t *service_list = interface->getServiceList(strdup("service=jasminegraph-worker"));
    ASSERT_EQ(service_list->items->count, 4);
}

TEST_F(K8sWorkerControllerTest, TestScaleUpBeyondLimit) {
    auto result = controller->scaleUp(1);
    ASSERT_EQ(result.size(), 0);
    v1_deployment_list_t *deployment_list = interface->getDeploymentList(strdup("deployment=jasminegraph-worker"));
    ASSERT_EQ(deployment_list->items->count, 4);
    v1_service_list_t *service_list = interface->getServiceList(strdup("service=jasminegraph-worker"));
    ASSERT_EQ(service_list->items->count, 4);
}
