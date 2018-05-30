
/********************
 * COEN 146, UDP example, server
 ********************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "tfv1.h"

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


	while (1){		
		// receive  datagrams
		nBytes = recvfrom (sock, &p, sizeof(p), 0, (struct sockaddr *)&serverStorage, &addr_size);
		FILE *open = fopen(namePack.data,"a");
		printf("Recieved Seq# %i\n", p.header.seq_ack);
		fflush(stdout);

		fwrite(p.data, 1, strlen(p.data), open);
		memset(p.data, 0, sizeof(p.data));

		fclose(open);

		ack.header.seq_ack = p.header.seq_ack;

		// send message back
		sendto (sock, &ack.header, nBytes, 0, (struct sockaddr *)&serverStorage, addr_size);
	}
	
	return 0;
}
