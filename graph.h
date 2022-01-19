#ifndef GRAPH_
#define GRAPH_

#include <stdio.h>
#include <iostream>

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
#endif