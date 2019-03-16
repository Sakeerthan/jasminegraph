/**
Copyright 2018 JasminGraph Team
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

#include "JasmineGraphInstanceFileTransferService.h"
#include "../util/Utils.h"

using namespace std;

void *filetransferservicesession(void *dummyPt) {
    filetransferservicesessionargs *sessionargs = (filetransferservicesessionargs *) dummyPt;
    int connFd = sessionargs->connFd;
    Utils utils;

    char data[300];
    bzero(data, 301);
    read(connFd, data, 300);
    string fileName = (data);
    //fileName = utils.trim_copy(fileName, " \f\n\r\t\v");
    string filePathWithName =
            utils.getJasmineGraphProperty("org.jasminegraph.server.instance.datafolder") + "/" + fileName;

    write(connFd, JasmineGraphInstanceProtocol::SEND_FILE.c_str(), JasmineGraphInstanceProtocol::SEND_FILE.size());

    char recvBUFF[1024];
    int bytesReceived = 0;
    //memset(recvBUFF, '0', sizeof(recvBUFF));

    char buffer[1024];
    std::ofstream file(filePathWithName, std::ios::out|std::ios::binary);
    do
    {
        bytesReceived = recv(connFd, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            file.write(buffer, bytesReceived);
            printf("Buffer: %.*s\n", connFd, buffer);
            //or: printf("Buffer: %*.*s\n", bytes_read, bytes_read, buffer);
        }
    }
    while (bytesReceived > 0);
}

JasmineGraphInstanceFileTransferService::JasmineGraphInstanceFileTransferService() {
}

int JasmineGraphInstanceFileTransferService::run(int dataPort) {

    int listenFd;
    socklen_t len;
    struct sockaddr_in svrAdd;
    struct sockaddr_in clntAdd;

    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd < 0) {
        std::cerr << "Cannot open socket" << std::endl;
        return 0;
    }

    bzero((char *) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(dataPort);

    int yes = 1;

    if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    }

    //bind socket
    if (bind(listenFd, (struct sockaddr *) &svrAdd, sizeof(svrAdd)) < 0) {
        std::cerr << "Cannot bind" << std::endl;
        return 0;
    }
    int connFd;
    listen(listenFd, 5);

    len = sizeof(clntAdd);

    int connectionCounter = 0;
    pthread_t threadA[5];

    // TODO :: What is the maximum number of connections allowed??
    while (connectionCounter<5) {
        std::cout << "Worker FileTransfer Service listening on port " << dataPort << std::endl;
        connFd = accept(listenFd, (struct sockaddr *) &clntAdd, &len);

        if (connFd < 0) {
            std::cerr << "Cannot accept connection" << std::endl;
        } else {
            std::cout << "Connection successful" << std::endl;
            struct filetransferservicesessionargs filetransferservicesessionargs1;
            filetransferservicesessionargs1.connFd = connFd;

            pthread_create(&threadA[connectionCounter], NULL, filetransferservicesession,
                           &filetransferservicesessionargs1);
            connectionCounter++;
        }
    }

    for (int i = 0; i < connectionCounter; i++) {
        pthread_join(threadA[i], NULL);
        std::cout << "FT Threads joined" << std::endl;
    }
}