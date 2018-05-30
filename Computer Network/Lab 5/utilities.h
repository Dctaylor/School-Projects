

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

/* Definitions, structs, and variable declarations */

// Number of threads and our definition of infinite
#define NUM_THREADS 2
#define INFINITE 10000

// Message structure
struct message {
    int routerID;
    int neighborID;
    int newCost;
};

// Machine structure
struct machine {
    char name[50];
    char IP[50];
    int port;
};

// Declare mutex lock
pthread_mutex_t lock;

// Declare myID, numMachines, sockfd
int myID, numMachines, sockfd;

// Declare addrs, addrsizes
socklen_t myAddrSize, theirAddrSize;
struct sockaddr_in myAddr, theirAddr;

// Dynamically allocated arrays
int * leastCosts;
int ** costs;
struct machine * myMachines;

/* Helper functions */

// Print the cost table
void print_cost_table() {
    printf("COST TABLE\n");
    for(int i = 0; i < numMachines; ++i) {
        for(int j = 0; j < numMachines; ++j) {
            printf("%d\t", costs[i][j]);
        }
        printf("\n");
    }
}

// Print the host table
void print_host_table() {
    printf("HOST TABLE\n");
    for (int i = 0; i < numMachines; ++i) {
        printf("%s\t%s\t%d\n", myMachines[i].name, myMachines[i].IP, myMachines[i].port);
    }
}

// Print the least cost array
void print_least_costs() {
    printf("LEAST COST ARRAY\n");
    for (int i = 0; i < numMachines; ++i) {
        printf("Shortest distance to Machine %d: %d\n", i ,leastCosts[i]);
    }
    printf("\n\n");
}

// Min function
int min(int p1, int p2) {
    return p1 < p2 ? p1 : p2;
}

// Contains function
int contains(int A[], int n) {
    for (int i = 0; i < numMachines; ++i) {
        if (A[i] == n) {
            return 1;
        }
    }
    return 0;
}

// Dijkstra algorithm 
void dijkstra() {
    // Initialization
    int * N = (int *) malloc(numMachines * sizeof(int));

    // N' = {u}
    N[0] = myID;
    int knownCosts = 1;

    // For all nodes v
    for (int i = 0; i < numMachines; ++i) {
        // All nodes are adjacent to eachother, so D(v) = c(u,v)
        pthread_mutex_lock(&lock);
        leastCosts[i] = costs[myID][i];
        pthread_mutex_unlock(&lock);
    }

    /* Loop */

    while (knownCosts < numMachines) {
        // Find w not in N' such that D(w) is a minimum
        int minDw = INFINITE;
        int w = 0;
        for (int i = 0; i < numMachines; ++i) {
            pthread_mutex_lock(&lock);
            if (!contains(N, i) && leastCosts[i] < minDw) {
                minDw = leastCosts[i];
                w = i;
            }
            pthread_mutex_unlock(&lock);
        }
        // Add w to N'
        N[knownCosts++] = w;

        // Update D(v) for all v adjacent to w and not in N'
        for (int i = 0; i < numMachines; ++i) {
            pthread_mutex_lock(&lock);
            leastCosts[i] = min(leastCosts[i], leastCosts[w] + costs[w][i]);
            pthread_mutex_unlock(&lock);
        }
    }

    // Free int N array from memory
    free(N);
}


// Set up UDP connection to given IP and port
int establishCommunication(char IP[50], int port) {
    printf("Establishing connection to %s at port %d\n", IP, port);

    // Set their address
    theirAddr.sin_family = AF_INET;
    theirAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, IP, &theirAddr.sin_addr) <=0 ) {
        printf("ERROR: Failed to set address\n");
        return 0;
    }

    memset(theirAddr.sin_zero, '\0', sizeof(theirAddr.sin_zero));
    theirAddrSize = sizeof(theirAddr);

    return 1;
}