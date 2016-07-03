/*
    Author: Jason.Ghost
    Time: 2016/7/3
*/
#pragma comment( lib, "ws2_32.lib" )

#include <winsock2.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ws2tcpip.h>

#include <Windows.h>
#include "debug.h"

#ifndef ARCHER_BROADCAST
#define ARCHER_BROADCAST

#define MAXSIZE      65536
#define BCASTPORT     5050
#define BCOUNT        10

class Broadcast {
private:
    SOCKET             socketBro;
    SOCKET             socketRec;
    struct sockaddr_in addrBro;
    struct sockaddr_in addrRec;

    DWORD              bcastAddr;
    short              bPort;
    int addrBroLen;
    
public:
	volatile char * rev_buffer; // mutli-thread

    Broadcast(void) {
    	Inital();
	}
    void Inital(void);

    void SetAddress(char * address_) {
        bcastAddr = inet_addr(address_);
    }
    void SetPort(short port_) {
        bPort = port_;
    }

    BOOL InitalSendSocket(void);
    void CleanSendSocket(void);

    BOOL Send(const char * message, int count, int delay);

    BOOL InitalReceiveSocket(void);
    void CleanReceiveSocket(void);

    BOOL Receive(int count, int delay);
    char * Receive(void);

    ~Broadcast() {
        CleanSendSocket();
        CleanReceiveSocket();
    }
};

#endif