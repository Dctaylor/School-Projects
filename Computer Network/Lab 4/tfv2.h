#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define SIZE    10


typedef struct
{
    int	seq;	//sequence nu,ber for data and for acks
    int len;	//length of the data in bytes (zero for acks)
    char checksum;	//checksum calculated (by byte)
    int fin;	//1 for the last packet

} HEADER;

typedef struct
{
    HEADER	header;
    char	data[SIZE];
} PACKET;

