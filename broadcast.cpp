/*
    Author: Jason.Ghost
    Time: 2016/7/3
*/
#include "broadcast.h"

void Broadcast::Inital(void) {
	WSADATA wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);

    rev_buffer = NULL;
    bPort = BCASTPORT;
    bcastAddr = INADDR_BROADCAST;
}


// Please use this function when all about-sending-message settings have done.
BOOL Broadcast::InitalSendSocket(void) {
    BOOL opt = TRUE;

    // create UDP socket
    socketBro 
    = 
    WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

    if (socketBro == INVALID_SOCKET) {
        // create failed...
        DEBUG_ERROR("Create UDP socket failed. (%d)", WSAGetLastError());
    }

    // set broadcast option
    addrBro.sin_family = AF_INET;
    addrBro.sin_addr.s_addr = bcastAddr;
    addrBro.sin_port = htons(bPort);

    // set SOCKET to BROADCAST type
    if (setsockopt(socketBro, SOL_SOCKET, SO_BROADCAST, 
        (char FAR *)&opt, sizeof(opt))
        == SOCKET_ERROR
        ) {
            // set failed ...
            DEBUG_ERROR("\"setsockopt\" Runtime error! (%d)", WSAGetLastError());
        }
    return TRUE;
}

// if count == -1, means send forever
BOOL Broadcast::Send(const char * message, int count, int delay) {
	DEBUG_MESSAGE("Starting Send Message...");
    int NLEN = sizeof(addrBro), ret = 0;
    int i = 0;
    
    // send Message
    while (!(~count) || i < count) {
        Sleep(delay);

        ret = 
        sendto(socketBro, 
        message, sizeof(message), 
        0, (struct sockaddr*)&addrBro, NLEN
        );

        if (ret == SOCKET_ERROR) {
            //...
            DEBUG_WARNING("Send message(%d) failed... continue. (%d)", i, WSAGetLastError());
        } else {
            // ...
            DEBUG_MESSAGE("Send message(%d) is OK", i);
        }
        ++i;
    }
    return TRUE;
}

// Please use this function when you sent all messages and you want to stop
void Broadcast::CleanSendSocket(void) {
    closesocket (socketBro);
    WSACleanup();
}

// Please use this function when all about-receiving-message settings have done.
BOOL Broadcast::InitalReceiveSocket(void) {
    BOOL optval = TRUE;

    // use to connect socket
    addrRec.sin_family = AF_INET;
    addrRec.sin_addr.s_addr = 0;
    addrRec.sin_port = htons(bPort);

    // use to receive message
    addrBro.sin_family = AF_INET;
    addrBro.sin_addr.s_addr = bcastAddr;
    addrBro.sin_port = htons(bPort);
    
    addrBroLen = sizeof(addrBro);
    // create socket
    socketRec = socket(AF_INET,SOCK_DGRAM,0);

    if (socketRec == INVALID_SOCKET) {
        // failed ...
        DEBUG_ERROR("Create UDP socket failed. (%d)", WSAGetLastError());
    }

    // set it to be can-reused
    if (setsockopt(socketRec, SOL_SOCKET, SO_REUSEADDR, (char FAR *)&optval, 
                                                			sizeof(optval)) == SOCKET_ERROR) {
        // set failed...
        DEBUG_ERROR("\"setsockopt\" Runtime error! (%d)", WSAGetLastError());
    }
    
    // bind socket and address
    if (bind(socketRec, (struct sockaddr *)&addrRec, 
                                sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        // bind failed...
        DEBUG_ERROR("bind\" Runtime error! (%d)", WSAGetLastError());
    }
    return TRUE;
}

// if count == -1 means receive all-times
BOOL Broadcast::Receive(int count, int delay) {
    int i = 0;
    static char * buf = new char[MAXSIZE];

	while (!(~count) || i < count) {
        recvfrom(socketRec, buf, MAXSIZE, 0, 
        (struct sockaddr FAR *)&addrBro, (int FAR *)&addrBroLen);

        Sleep(delay);

        rev_buffer = buf;

        //DEBUG_MESSAGE("Receive message(%d): %s", i, rev_buffer);

        ZeroMemory(buf, MAXSIZE);
        i++;
    }
    return TRUE;
}
char * Broadcast::Receive(void) {
    static char * buf = new char[MAXSIZE];

    recvfrom(socketRec, buf, MAXSIZE, 0, 
        (struct sockaddr FAR *)&addrBro, (int FAR *)&addrBroLen);

    //DEBUG_MESSAGE("Receive message(%d): %s", i, rev_buffer);
    ZeroMemory(buf, MAXSIZE);

    return buf;
}

void Broadcast::CleanReceiveSocket(void) {
    closesocket(socketRec);
    WSACleanup();
}
