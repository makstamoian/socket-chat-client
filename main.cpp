#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;
#define ADDRESS "127.0.0.1"
#define PORT 8228
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {

    int client;
    struct sockaddr_in serv_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        cerr << "SERVER: Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    int ADDR = inet_pton(AF_INET, ADDRESS, &serv_addr.sin_addr);

    if (ADDR <= 0) {
        cerr << "Invalid address / Address not supported" << endl;
        return -1;
    }

    if (connect(client, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "ERROR: Connection Failed" << endl;
        return -1;
    }

    char buffer[BUFFER_SIZE];
    cout << "Waiting for server confirmation..." << endl;
    cout << "Connection established..!" << endl << endl << "All messages are encrypting with Cesar cipher(not very secure)))))" << endl;
    cout << "You can close connection by stop running programm!)" << endl;

    while (true) {

        if (client < 0) {
            break;
        }

        cout << "You   " << " => ";
        cin.getline(buffer, BUFFER_SIZE);

        for(int i = 0; (i < 1024 && buffer[i] != '\0'); i++)
            buffer[i] = buffer[i] + 2;
        send(client, buffer, BUFFER_SIZE, 0);

        if (client < 0) {
            break;
        }

        recv(client, buffer, BUFFER_SIZE, 0);
        for(int i = 0; (i < 1024 && buffer[i] != '\0'); i++)
            buffer[i] = buffer[i] - 2;
        cout << "Server" << " => ";
        cout << buffer << endl;

        if (client < 0) {
            break;
        }
    }
    return 0;
}
