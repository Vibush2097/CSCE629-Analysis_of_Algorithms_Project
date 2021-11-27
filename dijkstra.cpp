// C / C++ program for Dijkstra's
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <vector>

using namespace std;
#define unseen 0
#define fringe 1
#define in_tree 2

struct Node {
    int dest;
    int weight;
    struct Node *next;
};

struct AdjList {
    struct Node *head;
};

struct Node *newNode(int dest, int weight) {
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

void addEdge(struct AdjList *adjList, int src, int dest, int weight) {
    struct Node *node = newNode(dest, weight);
    node->next = adjList[src].head;
    adjList[src].head = node;

    node = newNode(src, weight);
    node->next = adjList[dest].head;
    adjList[dest].head = node;
}

void Dijkstra(struct AdjList *adjList, int src, int dest) {
	cout<<"Source: "<<src<<endl;
    cout<<"Dest: "<<dest<<endl;

    int i, w, fringeCount=0, max=-1, index=-1;
    int status[9], bw[9], dad[9]; 

    for(i=0; i<9; i++) {
        status[i] = unseen;
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

    while(fringeCount>0) {
        max = -1; index=-1;
        for(i=0; i<9; i++) {
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
            }
            else if((status[w]==fringe) && (bw[w]<min(bw[v], cur->weight))) {
                bw[w] = min(bw[v], cur->weight);
                dad[w] = v;
            }
            cur = cur->next;
        }

        fringeCount = 0;
        for(i=0; i<9; i++) {
            if(status[i]==fringe)
                fringeCount++;
        }
    }

    if(status[dest]!=in_tree) 
        cout<<"No S-T path"<<endl;
    else    
        cout<<"Maximum bandwidth: "<<bw[dest]<<endl;
} 

int main()
{
    struct AdjList *adjList = (struct AdjList*) malloc(sizeof(struct Node)*9);    

    for(int i=0; i<9; i++) {
        adjList[i].head = NULL;
    }

    addEdge(adjList, 0, 1, 4);
    addEdge(adjList, 0, 7, 8);
    addEdge(adjList, 1, 7, 11);
    addEdge(adjList, 1, 2, 8);
    addEdge(adjList, 7, 8, 7);
    addEdge(adjList, 7, 6, 1);
    addEdge(adjList, 6, 8, 6);
    addEdge(adjList, 2, 8, 2);
    addEdge(adjList, 2, 5, 9);
    addEdge(adjList, 2, 3, 7);
    addEdge(adjList, 3, 5, 14);
    addEdge(adjList, 3, 4, 9);
    addEdge(adjList, 5, 4, 10);
    Dijkstra(adjList, 3, 5);
}  