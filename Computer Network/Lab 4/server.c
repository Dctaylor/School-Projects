
/********************
 * COEN 146, UDP example, server
 ********************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "tfv2.h"


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

/********************
 * main
 ********************/
int main (int argc, char *argv[])
{
	int sock, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	int i;
	FILE *fp;
	char *file;
	PACKET ack;
	PACKET p;
	PACKET namePack;
	int expectedSeq = 0;
	int checksum = 0;
	int fin = 0;
	int badPack = 0;

    if (argc != 2)
    {
        printf ("need the port number\n");
        return 1;
    }

	// init 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons ((short)atoi (argv[1]));
	serverAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	memset ((char *)serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));  
	addr_size = sizeof (serverStorage);

	// create socket
	if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf ("socket error\n");
		return 1;
	}

	// bind
	if (bind (sock, (struct sockaddr *)&serverAddr, sizeof (serverAddr)) != 0)
	{
		printf ("bind error\n");
		return 1;
	}

	//recieve filename
	nBytes = recvfrom (sock, &namePack, sizeof(namePack), 0, (struct sockaddr *)&serverStorage, &addr_size);
	//if partner needs ack for file name, uncomment line below
	//sendto (sock, &namePack, nBytes, 0, (struct sockaddr *)&serverStorage, addr_size);
	printf("Recieved: %s\n", namePack.data);
	fflush(stdout);
	fp = fopen(namePack.data,"w");
	fclose(fp);


	while (fin != 1){		
		// receive  datagrams
		nBytes = recvfrom (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverStorage, &addr_size);
		FILE *open = fopen(namePack.data,"a");
		printf("Recieved Seq# %i, Checksum: %d\n", p.header.seq,p.header.checksum);
		fflush(stdout);

		//check Checksum and Seq#
		char tempCheck = p.header.checksum;
		checksum = checksumCalc(p);
		printf("Calculated Checksum: %d\n", checksum);

		if(tempCheck != checksum) {
			printf("Incorrect Checksum\n");
			badPack = 1;
			//send back incorrect ack
			if(p.header.seq == 1)
				ack.header.seq = 0;
			else 
				ack.header.seq = 1;
			printf("Returning Seq #: %i\n\n", ack.header.seq);
			sendto (sock, &ack.header, sizeof(ack), 0, (struct sockaddr *)&serverStorage, addr_size);
		}

		//If Incorrect Sequence number received
		else if(p.header.seq != expectedSeq) {
			printf("Unexpected Seq Num\n");
			badPack = 1;

			//send back incorrect ack
			if(p.header.seq == 1)
				ack.header.seq = 0;
			else 
				ack.header.seq = 1;
			printf("Returning Seq #: %i\n\n", ack.header.seq);
			sendto (sock, &ack.header, sizeof(ack), 0, (struct sockaddr *)&serverStorage, addr_size);
		}

		//correct sequence and checksum recieved
		else {
			//Decide whether to send of skip and ack
			badPack = 0;
			srand(time(NULL));

			if((rand() % 10) != 1) {
				fwrite(p.data, 1, strlen(p.data), open);
				ack.header.seq = p.header.seq;
				printf("Setting ACK to: %i\n", p.header.seq);
				ack.header.len = 0;
				printf("Returning Seq #: %i\n\n", ack.header.seq);
				sendto (sock, &ack.header, sizeof(ack), 0, (struct sockaddr *)&serverStorage, addr_size);
				if(p.header.seq == 0)
					expectedSeq = 1;
				else
					expectedSeq = 0;
			}
		}

		memset(p.data, 0, sizeof(p.data));
		if(badPack == 0)
			fin = p.header.fin;
		fclose(open);	
	}
	
	return 0;
}
