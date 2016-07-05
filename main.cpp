#include "broadcast.h"

Broadcast sendman;
int main(void) {
	sendman.InitalSendSocket();
	sendman.Send("Silly Vector", -1, 1000);
	sendman.CleanSendSocket();
	while (1);
	return 0;
}