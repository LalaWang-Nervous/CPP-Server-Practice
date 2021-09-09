#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 3000
#define SEND_DATA "Hello, chenfei!"

int main(int argc, char* argv[]) {
    // 1.create client socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1) {
        cout << "create client socket fail." << endl;
        return -1;
    }

    // 2.connect server
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if(connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        cout << "connect socket fail." << endl;
        return -1;
    }

    // 3.send server data
    while(true) {
        cout << "please input the message to send:" << endl;
        string sendbuf;
        cin >> sendbuf;
        int ret = send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
        if(ret != strlen(sendbuf.c_str())) {
            cout << "send data fail." << endl;
            return -1;
        }

        cout << "send data successfully, data:" << sendbuf << endl;

        // 4.receive data from server
        char recvbuf[32] = {0};
        ret = recv(clientfd, recvbuf, 32, 0);
        if(ret > 0) {
            cout << "receive data successfully, data:" << recvbuf << endl;
        } else {
            cout << "receive data error." << recvbuf << endl;
        }
    }
    
    // 5.close socket
    close(clientfd);

    return 0;
}