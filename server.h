#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Windows.h>
#include <string.h>

// default opening port
#define DEFAULTPORT 9800

#define VERSION 1

#define MAX_PASSWORD_LEN 16

#define MAX_PLAYER_NUM 10

/*
	Password Checker:							
	Unique = '$' : 4	Version : 4	Game ID : 4	Game Version : 4	Total Length (Byte count) : 16			
	Source Address (IPV4) : 32							
	Port : 16				Random Code : 16			
	Password : 128							
							
	More Infomaion (Such as 'Username(use to create long time server)')							

	always get these message when the client connecting the server, with data-package and the system.
*/
struct ClientInfo {

	SOCKET sock;

	/*
		client_info = 'Source Address'
	*/
	sockaddr_in client_info;
	short ID;
	DWORD thread_ID;
	bool active;

	/*
		player-info = 'More Infomation'
	*/
	void * player_info;
};

/*
	Broadcast Host Information:							
	Unique = '$' : 4	Version : 4	Game ID : 4	Game Version : 4	Total Length (Byte count) : 16			
	Source Address (IPV4) : 32							
	Port : 16				Random Code : 16			
	Host Name : 128							
							
	Host Description : 128							
							
	More Information (Such as 'Game Model', 'Total Num', 'Online Num', 'PWD')							

*/
class ArcherServer {
protected:
	bool exist_pwd;
	char pwd [MAX_PASSWORD_LEN];

	short game_ID, game_version;

	SOCKET listen_socket;
	sockaddr_in address;

	ClientInfo players [MAX_PLAYER_NUM];

public:

	ArcherServer(void);

	void * server_info;

	void * game_world;
};