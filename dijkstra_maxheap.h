// C++ program for Dijsktra maximum bandwidth problem with heap
#ifndef DIJKSTRA_MAXHEAP_
#define DIJKSTRA_MAXHEAP_
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <vector>
#include "./graph.h"
// #include <chrono>
// using namespace std::chrono;

using namespace std;
#define unseen 0
#define fringe 1
#define in_tree 2

void heapify_insert(int heap[], int dist[], int pos[], int n, int i)
{
	int parent;
	parent = (i-1)/2;
	if(parent>=0) 
	{
		if(dist[heap[parent]]<dist[heap[i]])
		{
            pos[heap[parent]] = i;
            pos[heap[i]] = parent;
            swap(heap[parent], heap[i]);
			heapify_insert(heap, dist, pos, n, parent); 
		}
	}
}

void heapify_delete(int heap[], int dist[], int pos[], int n, int i)
{
    int largest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l < n && dist[heap[l]] > dist[heap[largest]])
        largest = l;
 
    if (r < n && dist[heap[r]] > dist[heap[largest]])
        largest = r;
 
    if (largest != i) {
        pos[heap[i]] = largest;
        pos[heap[largest]] = i;
        swap(heap[i], heap[largest]);
        heapify_delete(heap, dist, pos, n, largest);
    }
}

void insert(int heap[], int dist[], int pos[], int &n, int vertex)
{
	n=n+1;
	heap[n-1]=vertex;
    pos[heap[n-1]] = n-1;

	heapify_insert(heap, dist, pos, n, n-1);
}

void deleteElement(int heap[], int dist[], int pos[], int &n, int ele)
{
    int lastElement = heap[n - 1]; 
    int i = pos[ele];
 
    heap[pos[ele]] = lastElement; 
    pos[lastElement] = pos[ele];
    pos[ele] = n-1;
 
    n = n - 1;

    while(i>1) {
        int parent = (i-1)/2;
        if(dist[heap[parent]] < dist[heap[i]]) {
            pos[heap[parent]] = i;
            pos[heap[i]] = parent;
            swap(heap[i], heap[parent]);
        }
        i = parent;
    }
 
    heapify_delete(heap, dist, pos, n, 0);
}

int maximum(int heap[], int n) {
    if(n>0)
        return heap[0];
    else
        return -1;
}

void print(int heap[], int dist[], int pos[], int n)
{
	cout<<"\nThe Array Representation of Heap is\n";
	for(int i=0;i<n;i++)
	{
        cout<<"Vertex: "<<heap[i]<<" Weight: "<<dist[heap[i]]<<" pos: "<<pos[heap[i]]<<endl;
	}
}

// void printPath(int dad[], int src, int dest) {
//     int w = dest;
//     while(dad[w]!=-1) {
//         cout<<w<<" <-- ";
//     }
//     cout<<endl;
// }

void Dijkstra_Maxheap(struct AdjList *adjList, int src, int dest) {

    // auto start = high_resolution_clock::now();
    int i, w, fringeCount=0;
    int status[5000], bw[5000], dad[5000]; 
    int heap[5000], pos[5000], dist[5000], n=0;

    for(i=0; i<5000; i++) {
        status[i] = unseen;
        bw[i] = 999999;
        dist[i] = 999999;
        // dad[w] = -1;
    }
    status[src] = in_tree;

    struct Node *cur = adjList[src].head;
    while(cur != NULL) {
        w = cur->dest;
        status[w] = fringe;
        bw[w] = cur->weight;
        dad[w] = src;
        dist[w] = cur->weight;
        insert(heap, dist, pos, n, cur->dest);
        cur = cur->next;
        fringeCount++;
    }

    int count=0;

    while(fringeCount-->0) {

        int v = maximum(heap, n);
        status[v] = in_tree;
        cur = adjList[v].head;
        deleteElement(heap, dist, pos, n, v);

        while(cur!=NULL) {
            w = cur->dest;
            if(status[w]==unseen) {
                status[w] = fringe;
                bw[w] = min(bw[v], cur->weight);
                dad[w] = v;
                dist[w] = bw[w];
                fringeCount++;
                insert(heap, dist, pos, n, cur->dest);
            }
            else if((status[w]==fringe) && (bw[w]<min(bw[v], cur->weight))) {
                deleteElement(heap, dist, pos, n, w);
                bw[w] = min(bw[v], cur->weight);
                dist[w] = bw[w];
                insert(heap, dist, pos, n, w);
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
    // std::cout << "Time taken by Dijkstra with heap: "<< duration.count() << " milliseconds\n" << endl;
} 

#endif