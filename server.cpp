#include "server.h"

ArcherServer :: ArcherServer(void) {
    WSADATA wsaData;
    if (!WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        // ...
    }

    listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_socket == INVALID_SOCKET) {
        // ...
    }
    
    // set server message
    address.sin_family = AF_INET;
    address.sin_port = htons( DEFAULTPORT );
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_socket, (LPSOCKADDR)&address, sizeof(address)) 
                == 
        SOCKET_ERROR) {
            // ...
        }
    if (listen(listen_socket, 5) == SOCKET_ERROR) {
        // ...
    }

    exist_pwd = false;

	memset(pwd, 0, sizeof(pwd));
    
    game_ID = -1, game_version = -1;

    server_info = game_world = (void *) NULL;


}