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
#include "tfv2.h"
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>


char checksumCalc(PACKET p) {
	p.header.checksum = 0;
	char check = 0;
	int i;
	char * p2 = &p;
	for(i = 0; i < sizeof(p); ++i) {
		check = check ^ *(p2+i);
	}
	return check;
}
	

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
	p.header.seq = 0;
	struct timeval tv; //timer
	int rv; //select returned value
	PACKET badPack;
	int counter = 0;
	

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

	//set it up, in the beginning of the function
	fd_set readfds;
	fcntl(sock,F_SETFL,O_NONBLOCK);


	// send file name
	printf ("Sending File name: %s\n", argv[2]);
	strncpy(filePack.data, argv[2], 10);
	sendto (sock, &filePack, sizeof(filePack), 0, (struct sockaddr *)&serverAddr, addr_size);


	//create file data packet
	while((datas = fread(buffer, 1, 10, fp)) > 0) {
		HEADER ack;
		memcpy(p.data, buffer, 10);

		if(feof(fp) != 0) {
			p.header.fin = 1;
		}
		else {
			p.header.fin = 0;
		}

		//calculate data length
		p.header.len = sizeof(p.data);

		//Decide whether to calculate checksum or just make it 0
		if((rand() % 10) != 1) 
			p.header.checksum = checksumCalc(p);
		else
			p.header.checksum = 0;

		srand(time(NULL));
		//Decide whether to send or skip a packet
		if((rand() % 10) != 1) {
			//send packet
			printf("Sending Seq#: %i, Checksum: %d\n", p.header.seq,p.header.checksum);
			sendto (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverAddr, addr_size);

		}

		//set the timer
		tv.tv_sec = 10;
		tv.tv_usec = 0;

		//call before select
		FD_ZERO (&readfds);
		FD_SET (sock, &readfds);

		//call select
		rv = select(sock + 1, &readfds, NULL, NULL, &tv);

		while(rv == 0 && counter != 3) {
			if(p.header.fin == 1)
				counter++;

			if((rand() % 10) != 1) 
				p.header.checksum = checksumCalc(p);
			else
				p.header.checksum = 0;

			printf("Timeout, Resending Seq#: %i, Checksum: %d\n", p.header.seq, p.header.checksum);
			sendto (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverAddr, addr_size);

			tv.tv_sec = 10;
			tv.tv_usec = 0;

			//call before select
			FD_ZERO (&readfds);
			FD_SET (sock, &readfds);
			rv = select(sock + 1, &readfds, NULL, NULL, &tv);
		} 

		// receive ACK
		nBytes = recvfrom (sock, &ack, sizeof(ack), 0, NULL, NULL);

		

		//check for correct ack
		while(ack.seq != p.header.seq) {

			if((rand() % 10) != 1) 
				p.header.checksum = checksumCalc(p);
			else
				p.header.checksum = 0;

			printf("Incorrect Ack, Resending Seq#: %i, Checksum: %d\n", p.header.seq, p.header.checksum);
			sendto (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverAddr, addr_size);

			//timeout
			while(rv == 0 && counter != 3) {
				if(p.header.fin == 1)
					counter++;

				printf("Timeout, Resending Seq#: %i, Checksum: %d\n", p.header.seq, p.header.checksum);
				sendto (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverAddr, addr_size);
				tv.tv_sec = 10;
				tv.tv_usec = 0;

				//call before select
				FD_ZERO (&readfds);
				FD_SET (sock, &readfds);
				rv = select(sock + 1, &readfds, NULL, NULL, &tv);
			}
			nBytes = recvfrom (sock, &ack, sizeof(ack), 0, NULL, NULL);
			printf ("Received Ack Seq#: %i\n\n", ack.seq);
		}

		//change seq #
		if(p.header.seq == 0) {
			p.header.seq = 1;
			printf("Packet SEQ# Set to: %i\n", p.header.seq);
		}
		else  {
			p.header.seq = 0;
			printf("Packet SEQ# Set to: %i\n", p.header.seq);
		}

		memset(p.data, 0, sizeof(p.data));
		memset(buffer, 0, sizeof(buffer));
	}

	
	fclose(fp);
	return 0;
}
