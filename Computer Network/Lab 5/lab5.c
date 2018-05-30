/*
 * lab5.c
 * Usage: ./lab5 <id> <total # of machines> <costs file> <hosts file>
 * This file acts as a pretend router in a network. It can communicate with
 * other routers to determine the best paths through the network. This is
 * done using the link state algorithm for routing the best path.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "utilities.h"

void * receive_info(void * arg) {
    struct message recv_msg;

    while(1) {
        // Receive messages from other nodes
        recvfrom(sockfd, &recv_msg, sizeof(recv_msg), 0, NULL, NULL);

        // Update and print the neighbor cost table
        pthread_mutex_lock(&lock);
        costs[recv_msg.routerID][recv_msg.neighborID] = recv_msg.newCost;
        costs[recv_msg.neighborID][recv_msg.routerID] = recv_msg.newCost;
        print_cost_table();
        printf("\n");
        pthread_mutex_unlock(&lock);
    }

}

void * link_state(void * arg) {
    while(1) {
        // Sleep_time between 0..10, then adjust to be between 10..20
        int sleep_time = (rand() % 11) + 10;

        // Sleep for sleep_time seconds
        sleep(sleep_time);

        // Run the link-state algorithm to update the least costs
        dijkstra();

        // Output the current least costs
        pthread_mutex_lock(&lock);
        print_least_costs();
        pthread_mutex_unlock(&lock);
    }

}

int main(int argc, char * argv[]) {
    // Check to make sure we have everything we need to get started
    if (argc != 5) {
        printf("ERROR: NEED THE FOLLOWING ARGUMENTS:\nargv[1]: id\nargv[2]: total # of machines\nargv[3]: costs file\nargv[4]: hosts file\n");
        return 1;
    }

    // Seed random and initialize the lock
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);

    // Initialize variables from utilities.h
    myID = atoi(argv[1]);
    numMachines = atoi(argv[2]);

    // Open the files
    FILE * costsFile = fopen(argv[3], "r");
    FILE * hostsFile = fopen(argv[4], "r");

    // Initialize dynamic arrays and tables from utilities.h
    leastCosts = (int *) malloc(numMachines * sizeof(int));
    costs = (int **) malloc(numMachines * sizeof(int *));
    myMachines = (struct machine *) malloc(numMachines * sizeof(struct machine));

    for (int i = 0; i < numMachines; ++i) {
        // Fill the hosts table with information from hostsFile
        fscanf(hostsFile, "%s%s%d", myMachines[i].name, myMachines[i].IP, &myMachines[i].port);
        costs[i] = (int *) malloc(numMachines * sizeof(int));
    }

    // Print the hosts table
    print_host_table();

    // Fill the costs table with data from costsFile
    for (int i = 0; i < numMachines; ++i) {
        for (int j = 0; j < numMachines; ++j) {
            int cost = 0;
            fscanf(costsFile, "%d", &cost);
            costs[i][j] = cost;
        }
    }

    // Print the costs table
    print_cost_table();

    // Set up self as server
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = htons(myMachines[myID].port);
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(myAddr.sin_zero, '\0', sizeof(myAddr.sin_zero));
    myAddrSize = sizeof(myAddr);

    // Create and bind socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    bind(sockfd, (struct sockaddr *)&myAddr, sizeof(myAddr));

    // Declare threads
    int t2, t3;
    pthread_t threads[NUM_THREADS];

    // Create receive_info thread and make sure it was created successfully
    t2 = pthread_create(threads, NULL, receive_info, NULL);
    if(t2) {
        printf("ERROR: Cannot create Thread 2\n");
        return 1;
    }

    // Create link state thread and make sure it was created successfully
    t3 = pthread_create(threads + 2, NULL, link_state, NULL);
    if(t3) {
        printf("ERROR: Cannot create Thread 3\n");
        return 1;
    }

    // Initialize int for number of cost table changes to perform
    int numChanges = 2;

    //Keyboard input to change distances (thread 1)
    for (int i = 0; i < numChanges; ++i) {
        // Buffer for reading keyboard input from terminal
        size_t n = 0;
        char * buffer = NULL;

        // Read keyboard input and write to buffer
        printf("Waiting for keyboard input %d/%d: <neighbor> <space> <new cost> <Enter Key>\n", (i + 1), numChanges);
        getline(&buffer, &n, stdin);
        buffer = strtok(buffer, " ");

        // Inputs array
        int inputs[2];
        int j = 0;

        // Parse input buffer for tokens
        while(buffer) {
            inputs[j++] = atoi(buffer);
            buffer = strtok(NULL, " ");
        }

        // Update the cost table (x -> y and y -> x)
        pthread_mutex_lock(&lock);
        costs[myID][inputs[0]] = inputs[1];
        costs[inputs[0]][myID] = inputs[1];
        print_cost_table();
        printf("\n");
        pthread_mutex_unlock(&lock);

        // Initialize a message to send to the other routers
        struct message send_msg = {
            myID,
            inputs[0],
            inputs[1],
        };

        // Send the initialized message to the other routers
        for (int j = 0; j < numMachines; ++j) {
            if (j != myID) {
                if (establishCommunication(myMachines[j].IP, myMachines[j].port)) {
                    sendto(sockfd, &send_msg, sizeof(send_msg), 0, (struct sockaddr *) &theirAddr, theirAddrSize);
                    printf("Message Sent\n");
                } else {
                    printf("ERROR: Failed to establish communication\n");
                    return 1;
                }
            }
        }
        sleep(10);
    }
    sleep(30);

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++ i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex lock
    pthread_mutex_destroy(&lock);


    // Free memory for heap-allocated arrays
    for (int i = 0; i < numMachines; ++i) {
        free(costs[i]);
    }

    free(myMachines);
    free(costs);
    free(leastCosts);

    // Close the files and return 0
    fclose(costsFile);
    fclose(hostsFile);

    return 0;
}