#ifndef DIJKSTRA_
#define DIJKSTRA_
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <vector>
#include "./graph.h"
// #include <chrono>
// using namespace std::chrono;

using namespace std;

void printPath(int dad[], int src, int dest) {
    int w = dest;
    while(dad[w]!=-1) {
        cout<<w<<" <-- ";
    }
    cout<<endl;
}

void Dijkstra(struct AdjList *adjList, int src, int dest) {

    // auto start = high_resolution_clock::now();
    int i, w, fringeCount=0, max=-1, index=-1;
    int status[5000], bw[5000], dad[5000]; 

    for(i=0; i<5000; i++) {
        status[i] = unseen;
        dad[i] = -1;
    }
    status[src] = in_tree;

    struct Node *cur = adjList[src].head;
    while(cur != NULL) {
        w = cur->dest;
        status[w] = fringe;
        bw[w] = cur->weight;
        dad[w] = src;
        cur = cur->next;
        fringeCount++;
    }

    while(fringeCount-->0) {
        max = -1; index=-1;
        for(i=0; i<5000; i++) {
            if((status[i]==fringe) && (bw[i]>max)) {
                index = i;
                max = bw[i];
            }
        }

        int v = index;
        status[v] = in_tree;
        cur = adjList[v].head;

        while(cur!=NULL) {
            w = cur->dest;
            if(status[w]==unseen) {
                status[w] = fringe;
                bw[w] = min(bw[v], cur->weight);
                dad[w] = v;
                fringeCount++;
            }
            else if((status[w]==fringe) && (bw[w]<min(bw[v], cur->weight))) {
                bw[w] = min(bw[v], cur->weight);
                dad[w] = v;
            }
            cur = cur->next;
        }

    }

    if(status[dest]!=in_tree) 
        std::cout<<"No S-T path"<<endl;
    else    
        std::cout<<"Maximum bandwidth: "<<bw[dest]<<endl;
    
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(stop - start);

    // std::cout << "Time taken by Dijkstra without heap: "<< duration.count() << " milliseconds\n" << endl;
} 

#endif