#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]) {
    // 1.create socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1) {
        cout << "create listen socket fail." << endl;
        return -1;
    }

    // 2.init server address
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if(bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1) {
        cout << "bind listen socket fail." << endl;
    }

    // 3.start listen
    if(listen(listenfd, SOMAXCONN) == -1) {
        cout << "listen error." << endl;
        return -1;
    }

    while(true) {
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        // 4.accept client
        int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
        if(clientfd != -1) {
            char recvbuf[32] = {0};
            // 5.start to receive data from client.
            int ret = recv(clientfd, recvbuf, 32, 0);
            if(ret > 0) {
                cout << "receive data from client, data:" << recvbuf << endl;
                // 6.respond to the client.
                string sendstr;
                cout << "please input the response:" << endl;
                cin >> sendstr;
                ret = send(clientfd, sendstr.c_str(), strlen(sendstr.c_str()), 0);
                if(ret != strlen(sendstr.c_str())) {
                    cout << "send data length not expected." << endl;
                } else {
                    cout << "send data sucessfully." << endl;
                }
            } else {
                cout << "receive data from client fail." << recvbuf << endl;
            }
        }
        close(clientfd);
    }

    close(listenfd);

    return 0;
}