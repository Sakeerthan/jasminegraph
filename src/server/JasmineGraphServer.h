/**
Copyright 2019 JasmineGraph Team
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

#ifndef JASMINEGRAPH_JASMINEGRAPHSERVER_H
#define JASMINEGRAPH_JASMINEGRAPHSERVER_H

#include <iostream>
#include <map>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../frontend/JasmineGraphFrontEnd.h"
#include "../backend/JasmineGraphBackend.h"
#include "../metadb/SQLiteDBInterface.h"
#include "../performancedb/PerformanceSQLiteDBInterface.h"
#include "../util/Conts.h"
#include "../util/Utils.h"

using std::map;

class JasmineGraphServer {
private:
    map<std::string, long> hostPlaceMap;
    std::string profile;
    std::string workerHosts;
    int numberOfWorkers = -1;
    static const int BUFFER_SIZE = 128;
    int serverPort;
    int serverDataPort;
    std::map<std::string, std::vector<int>> workerPortsMap;
    std::map<std::string, std::vector<int>> workerDataPortsMap;

    static void startRemoteWorkers(std::vector<int> workerPortsVector, std::vector<int> workerDataPortsVector, std::string host, string profile, string masterHost);

    void addHostsToMetaDB(std::string host, std::vector<int> portVector, std::vector<int> dataPortVector);

    void updateOperationalGraphList();

    std::map<std::string, std::string> getLiveHostIDList();

    static void copyArtifactsToWorkers(std::string workerPath, std::string artifactLocation, std::string remoteWorker);
    static void createWorkerPath (std::string workerHost, std::string workerPath);
    static void createLogFilePath (std::string workerHost, std::string workerPath);
    static void deleteWorkerPath (std::string workerHost, std::string workerPath);

    static bool hasEnding(std::string const &fullString, std::string const &ending);
    std::vector<std::string> getWorkerVector(std::string workerList);
    void deleteNonOperationalGraphFragment(int graphID);
public:
    ~JasmineGraphServer();

    JasmineGraphServer();

    void init();

    void start_workers();

    void resolveOperationalGraphs();

    void backupPerformanceDB();

    void clearPerformanceDB();

    void addInstanceDetailsToPerformanceDB(std::string host, std::vector<int> portVector, std::string isMaster);

    int shutdown_workers();

    int run(std::string profile, std::string masterIp, int numberofWorkers, std::string workerIps);

    bool isRunning();

    void uploadGraphLocally(int graphID, const std::string graphType, std::vector<std::map<int,std::string>> fullFileList, std::string masterIP);

    void removeGraph(std::vector<std::pair<std::string, std::string>> hostHasPartition, std::string graphID, std::string masterIP);

    void assignPartitionsToWorkers(int numberOfWorkers);

    static bool batchUploadFile(std::string host, int port, int dataPort, int graphID, std::string filePath, std::string masterIP);

    static bool batchUploadCentralStore(std::string host, int port, int dataPort, int graphID, std::string filePath, std::string masterIP);

    static bool batchUploadAttributeFile(std::string host, int port, int dataPort, int graphID, std::string filePath, std::string masterIP);

    static bool batchUploadCentralAttributeFile(std::string host, int port, int dataPort, int graphID, std::string filePath, std::string masterIP);

    static int removePartitionThroughService(std::string host, int port, std::string graphID, std::string partitionID, std::string masterIP);

    static int removeFragmentThroughService(std::string host, int port, std::string graphID, std::string masterIP);

    static bool sendFileThroughService(std::string host, int dataPort, std::string fileName, std::string filePath, std::string masterIP);

    JasmineGraphFrontEnd *frontend;
    SQLiteDBInterface sqlite;
    PerformanceSQLiteDBInterface performanceSqlite;
    JasmineGraphBackend *backend;
    std::string masterHost;

    struct workers {
        std::string hostname;
        int port;
        int dataPort;
    };

    struct workerPartitions {
        int port;
        int dataPort;
        std::vector<std::string> partitionID;
    };

    static void updateMetaDB(std::vector<workers> hostWorkerMap,  std::map<int,std::string> partitionFileList, int graphID,
                 std::string uploadEndTime);

    //return hostWorkerMap
    static std::vector<JasmineGraphServer::workers> getHostWorkerMap();

    std::map<std::string, workerPartitions> getGraphPartitionedHosts(std::string graphID);

    void initiateFiles(std::string graphID, std::string trainingArgs);

    void initiateCommunication(std::string graphID, std::string trainingArgs, SQLiteDBInterface sqlite);

    void initiateOrgCommunication(std::string graphID, std::string trainingArgs, SQLiteDBInterface sqlite);

    void initiateMerge(std::string graphID, std::string trainingArgs,SQLiteDBInterface sqlite);

    static bool initiateTrain(std::string host, int port, int dataPort,std::string trainingArgs,int iteration, string partCount);

    static bool initiateServer(std::string host, int port, int dataPort,std::string trainingArgs,int iteration, string partCount);

    static bool initiateOrgServer(std::string host, int port, int dataPort,std::string trainingArgs,int iteration, string partCount);

    static bool initiateAggregator(std::string host, int port, int dataPort,std::string trainingArgs,int iteration, string partCount);

    static bool initiateClient(std::string host, int port, int dataPort,std::string trainingArgs,int iteration, string partCount);

    static bool mergeFiles(std::string host, int port, int dataPort,std::string trainingArgs,int iteration, string partCount);

    static bool receiveGlobalWeights(std::string host, int port, std::string trainingArgs, int iteration, std::string partCount);

    static bool sendTrainCommand(std::string host, int port, std::string trainingArgs);

};

#endif //JASMINEGRAPH_JASMINEGRAPHSERVER_H