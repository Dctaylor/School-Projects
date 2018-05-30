/*****************************
 * COEN 146, UDP, client
 *****************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include "tfv1.h"
/***********
 *  main
 ***********/
int main (int argc, char *argv[])
{
	int sock, portNum, nBytes;
	char buffer[10];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	FILE *fp = fopen(argv[1],"r");
	PACKET p;
	PACKET filePack;
	size_t datas;
	HEADER ack;
	p.header.seq_ack = 0;

	if (argc != 5)
	{
		printf ("Incorrect amount of arguements\n");
		return 1;
	}

	// configure address
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons (atoi (argv[4]));
	inet_pton (AF_INET, argv[3], &serverAddr.sin_addr.s_addr);
	memset (serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));  
	addr_size = sizeof serverAddr;

	/*Create UDP socket*/
	sock = socket (PF_INET, SOCK_DGRAM, 0);

	// send file name
	printf ("Sending File name: %s\n", argv[2]);
	strncpy(filePack.data, argv[2], 10);
	sendto (sock, &filePack, sizeof(filePack), 0, (struct sockaddr *)&serverAddr, addr_size);

	//create file data packet
	while((datas = fread(buffer, 1, 10, fp)) > 0) {
		memcpy(p.data, buffer, 10);
		printf("Sending Seq#: %i\n", p.header.seq_ack);
		sendto (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverAddr, addr_size);

		// receive ACK
		nBytes = recvfrom (sock, &ack, sizeof(ack), 0, NULL, NULL);
		printf ("Received Ack Seq#: %i\n", ack.seq_ack);

		//change seq #
		if(p.header.seq_ack == 0) {
			p.header.seq_ack = 1;
		}
		else {
			p.header.seq_ack = 0;
		}

		memset(p.data, 0, sizeof(p.data));
		memset(buffer, 0, sizeof(buffer));
	}

	
	fclose(fp);
	return 0;
}
