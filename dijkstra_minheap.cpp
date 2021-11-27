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

// struct HeapNode {
//     int v;
//     int dist;
// };

// struct HeapNode* newHeapNode(int v, int dist) {
//     struct HeapNode* heapNode = (struct HeapNode*) malloc(sizeof(struct HeapNode));
//     heapNode->v = v;
//     heapNode->dist = dist;
//     return heapNode;
// }

// struct MaxHeap {
//     int size;
//     int capacity;
//     int *pos;
//     struct HeapNode **array;
// };

// struct MaxHeap* createMaxHeap(int capacity)
// {
//     struct MaxHeap* maxHeap = (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
//     maxHeap->pos = (int *) malloc(capacity * sizeof(int));
//     maxHeap->size = 0;
//     maxHeap->capacity = capacity;
//     maxHeap->array = (struct HeapNode**) malloc(capacity * sizeof(struct HeapNode*));
//     return maxHeap;
// };

// void swapHeapNode(struct HeapNode** a, struct HeapNode** b) {
//     struct HeapNode* t = *a;
//     *a = *b;
//     *b = t;
// }

// void maxHeapify(struct MaxHeap *maxHeap, int idx) {
//     int largest, left, right;
//     largest = idx;
//     left = idx*2 + 1;
//     right = idx*2 + 2;

//     if(left<maxHeap->size && maxHeap->array[left]->dist > maxHeap->array[idx]->dist) {
//         largest = left;
//     }

//     if(right<maxHeap->size && maxHeap->array[right]->dist > maxHeap->array[idx]->dist) {
//         largest = right;
//     }

//     if(largest != idx) {
//         HeapNode *largest_node = maxHeap->array[largest];
//         HeapNode *idx_node = maxHeap->array[idx];

//         maxHeap->pos[largest_node->v] = idx;
//         maxHeap->pos[idx_node->v] = largest;
  
//         swapHeapNode(&maxHeap->array[largest], &maxHeap->array[idx]);
  
//         maxHeapify(maxHeap, largest);
//     }
// }

// int isEmpty(struct MaxHeap* maxHeap) {
//     return maxHeap->size == 0;
// }

// struct HeapNode* fetchMaxHeapNode(struct MaxHeap *maxHeap) {
//     if(isEmpty(maxHeap))
//         return NULL;
    
//     struct HeapNode *root = maxHeap->array[0];

//     struct HeapNode *maxHeapNode = maxHeap->array[maxHeap->size-1];
//     maxHeap->array[0] = maxHeapNode;

//     maxHeap->pos[root->v] = maxHeap->size-1;
//     maxHeap->pos[maxHeapNode->v] = 0;

//     --maxHeap->size;
//     maxHeapify(maxHeap, maxHeap->size);

//     return root;
// }

// void decreaseKey(struct MaxHeap* maxHeap, int v, int dist) {
//     int i = maxHeap->pos[v];
  
//     maxHeap->array[i]->dist = dist;
  
//     while (i && maxHeap->array[i]->dist > maxHeap->array[(i - 1) / 2]->dist)
//     {
//         maxHeap->pos[maxHeap->array[i]->v] = (i-1)/2;
//         maxHeap->pos[maxHeap->array[(i-1)/2]->v] = i;

//         swapHeapNode(&maxHeap->array[i], &maxHeap->array[(i - 1) / 2]);
  
//         i = (i - 1) / 2;
//     }
// }

void heapify_insert(int heap[], int dist[], int pos[], int n, int i)
{
	int parent;
	parent = (i-1)/2; //for finding the parent of child
	if(parent>=0)     //Check until index < 0
	{
		if(dist[heap[parent]]<dist[heap[i]])
		{
			swap(heap[parent], heap[i]);
            pos[heap[parent]] = parent;
            pos[heap[i]] = i;
			heapify_insert(heap, dist, pos, n, parent); //recursive heapify function
		}
	}
}

void heapify_delete(int heap[], int dist[], int pos[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && dist[heap[l]] > dist[heap[largest]])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && dist[heap[r]] > dist[heap[largest]])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(heap[i], heap[largest]);
        pos[heap[i]] = i;
        pos[heap[largest]] = largest;
 
        // Recursively heapify the affected sub-tree
        heapify_delete(heap, dist, pos, n, largest);
    }
}

void insert(int heap[], int dist[], int pos[], int &n, int vertex, int weight)
{
	/*Increase the Size of the Array by 1*/
	n=n+1;
	/*Insert the new element at the end of the Array*/
	heap[n-1]=vertex;
    dist[heap[n-1]]=weight;
    pos[heap[n-1]] = n-1;
	/*Heapify function*/
	heapify_insert(heap, dist, pos, n, n-1);
}

void deleteElement(int heap[], int dist[], int pos[], int& n, int ele)
{
    // Get the last element
    int lastElement = heap[n - 1]; //returns vertex
 
    // Replace root with last element
    heap[pos[ele]] = lastElement; //replace vertex at 
    pos[lastElement] = pos[ele];
    pos[ele] = -1;
 
    // Decrease size of heap by 1
    n = n - 1;
 
    // heapify the root node
    heapify_delete(heap, dist,  pos, n, 0);
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

void Dijkstra(struct AdjList *adjList, int src, int dest) {
	cout<<"Source: "<<src<<endl;
    cout<<"Dest: "<<dest<<endl;

    int i, w, fringeCount=0, max=-1, index=-1;
    int status[9], bw[9], dad[9]; 
    int heap[9], pos[9], dist[9], n=0;

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
        insert(heap, dist, pos, n, cur->dest, cur->weight);
        cur = cur->next;
        fringeCount++;
    }

    cout<<"Fringe count: "<<fringeCount<<endl;

    while(fringeCount>0) {
        max = -1; index=-1;
        for(i=0; i<9; i++) {
            if((status[i]==fringe) && (bw[i]>max)) {
                index = i;
                max = bw[i];
            }
        }

        int v = index;
        int v1 = maximum(heap, n);
        status[v] = in_tree;
        deleteElement(heap, dist, pos, n, v);
        cur = adjList[v].head;

        while(cur!=NULL) {
            w = cur->dest;
            if(status[w]==unseen) {
                status[w] = fringe;
                bw[w] = min(bw[v], cur->weight);
                dad[w] = v;
                dist[w] = bw[w];
                insert(heap, dist, pos, n, cur->dest, cur->weight);
            }
            else if((status[w]==fringe) && (bw[w]<min(bw[v], cur->weight))) {
                deleteElement(heap, dist, pos, n, w);
                bw[w] = min(bw[v], cur->weight);
                dist[w] = bw[w];
                insert(heap, dist, pos, n, w, cur->weight);
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
    Dijkstra(adjList, 1, 4);
}  