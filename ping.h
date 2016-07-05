#pragma comment( lib, "ws2_32.lib" )

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Record Route */
#define IP_RECORD_ROUTE  0x7

/* The default packet size */
#define DEF_PACKET_SIZE  32 

/* The maximum size of ICMP packets */
#define MAX_PACKET       1024    

/* The maximum IP header length */
#define MAX_IP_HDR_SIZE  60 

/* ICMP packet type, echo request */
#define ICMP_ECHO        8

/* ICMP packet type, echo reply */
#define ICMP_ECHOREPLY   0

/* The minimum size of ICMP packets */
#define ICMP_MIN         8

/* 
	IP header field data structure 
*/
typedef struct _iphdr
{
	unsigned int   len : 4;    	//  IP header length
	unsigned int   version : 4;  //  IP version number
	unsigned char  TOS;          //  Type of service
	unsigned short total_len;    //  The total length of the datagram
	unsigned short ident;        //  Unique identifier
	unsigned short frag_flags;   //  Segmentation flags
	unsigned char  TTL;          //  Lifetime
	unsigned char  proto;        //  Protocol type (TCP, UDP, etc.)
	unsigned short checksum;     //  Checksum
	unsigned int   sourceIP;     //  Source IP address
	unsigned int   destIP;       //  Destination IP address
} IPHeader;
