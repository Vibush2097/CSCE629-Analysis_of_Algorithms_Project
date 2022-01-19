#ifndef KRUSKAL_
#define KRUSKAL_

#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include "./graph.h"

using namespace std;
#define gray 0
#define white 1
#define black 2

struct Edge {
    int src;
    int dest;
    int weight;
};

void AddEdge(vector<struct Edge*> &edgeList, int src, int dest, int weight) {
    struct Edge *edge = (struct Edge*) malloc(sizeof(struct Edge));

    edge->src = src;
    edge->dest = dest;
    edge->weight = weight;

    edgeList.push_back(edge);
}

void heapify(vector<struct Edge*> &edgeList, int n, int idx) {
    int smallest = idx;
    int left  = 2*idx + 1;
    int right = 2*idx + 2;

    if((left < n) && (edgeList[smallest]->weight > edgeList[left]->weight)) {
        smallest = left;
    }

    if((right < n) && (edgeList[smallest]->weight > edgeList[right]->weight)) {
        smallest = right;
    }

    if(smallest != idx) {
        struct Edge *temp = edgeList[idx];
        edgeList[idx] = edgeList[smallest];
        edgeList[smallest] = temp;

        heapify(edgeList, n, smallest);
    }

}

void printHeap(vector<struct Edge*> &edgeList) {
    // cout<<"Sorted Edge List"<<endl;
    for(int i=0; i<edgeList.size(); i++) {
        std::cout<<"src: "<<edgeList[i]->src<<" dest: "<<edgeList[i]->dest<<" weight: "<<edgeList[i]->weight<<endl;
    }
}

void heapSort(vector<struct Edge*> &edgeList) {
    int n = edgeList.size();
    // cout<<"n: "<<n<<endl;

    for(int i=n/2-1; i>=0; i--) {
        heapify(edgeList, n, i);
    }

    for(int i=n-1; i>=0; i--) {
        struct Edge *temp = edgeList[0];
        edgeList[0] = edgeList[i];
        edgeList[i] = temp;

        heapify(edgeList, i, 0);
    }

    // printHeap(edgeList);
}

void makeset(int parent[], int rank[], int v) {
    parent[v] = -1;
    rank[v] = 0;
}

int find(int parent[], int v) {
    if (parent[v] == -1)
        return v;
    return parent[v] = find(parent, parent[v]);
}

int find_path_compression(int parent[], int v) {
    int w = v;
    vector<int> stack;
    while(parent[w]!=-1) {
        stack.push_back(w);
        w = parent[w];
    }              
    int n = stack.size();
    int u;
    while(n>0) {
        u = stack[n-1];
        parent[u] = w;
        --n;
    }                                                                       
    return w;
}

// union function
void unite(int parent[], int rank[], int r1, int r2)
{
    if (rank[r1] > rank[r2]) {
        parent[r2] = r1;
    }

    else if(rank[r2] > rank[r1]) {
        parent[r1] = r2;
    }

    else {
        parent[r2] = r1;
        rank[r1] += 1;
    }
}

void DFS(struct AdjList *adjList, int src, int parent[], int color[], int bw[]) {
    color[src] = gray;
    struct Node *cur = adjList[src].head;
    int w;

    while(cur!=NULL) {
        w = cur->dest;
        if(color[w] == white) {
            parent[w] = src;
            bw[w] = cur->weight;
            DFS(adjList, w, parent, color, bw);
        }
        cur = cur->next;
    }
    color[src] = black;
} 

void printPath(int parent[], int dest) {
    int cur = dest;
    while(cur!=-1) {
        cout<<cur<<" <-- ";
        cur = parent[cur];
    }
    cout<<endl;
}

void Kruskal(vector<struct Edge*> edgeList, struct AdjList *finalAdjList, int s, int t) {
    int parent[5000], rank[5000], n=5000;
    int color[n], dfs_parent[n], bw[n];
    // auto start = high_resolution_clock::now();

    for(int i=0; i<n; i++) {
        makeset(parent, rank, i);
    }

    int m = edgeList.size();
    heapSort(edgeList);

    for(int k=0; k<m; k++) {
        struct Edge *edge = edgeList[k];
        int r1 = find(parent, edge->src);
        int r2 = find(parent, edge->dest);

        if(r1 != r2) {
            // cout<<edge->src<<" - "<<edge->dest<<endl;
            addEdge(finalAdjList, edge->src, edge->dest, edge->weight);
            unite(parent, rank, r1, r2);
        }
    }

    for(int v=0; v<n; v++) {
        color[v] = white;
        dfs_parent[v] = -1;
        bw[v] = 1000000;
    }
    
    DFS(finalAdjList, s, dfs_parent, color, bw);

    int max_bw = 100000, cur=t;
    while(cur!=-1) {
        // cout<<cur<<" <-- ";
        max_bw = min(max_bw, bw[cur]);
        cur = dfs_parent[cur];
    }
    // cout<<endl;
    std::cout<<"Maximum bandwidth: "<<max_bw<<endl;

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(stop - start);
    // std::cout << "Time taken by Kruskal: "<< duration.count() << " milliseconds\n" << endl;
}

void Kruskal_Path_Compression(vector<struct Edge*> edgeList, struct AdjList *finalAdjList, int s, int t) {
    int parent[5000], rank[5000], n=5000;
    int color[n], dfs_parent[n], bw[n];
    // auto start = high_resolution_clock::now();

    for(int i=0; i<n; i++) {
        makeset(parent, rank, i);
    }

    int m = edgeList.size();
    heapSort(edgeList);

    for(int k=0; k<m; k++) {
        struct Edge *edge = edgeList[k];
        int r1 = find_path_compression(parent, edge->src);
        int r2 = find_path_compression(parent, edge->dest);

        if(r1 != r2) {
            // cout<<edge->src<<" - "<<edge->dest<<endl;
            addEdge(finalAdjList, edge->src, edge->dest, edge->weight);
            unite(parent, rank, r1, r2);
        }
    }

    for(int v=0; v<n; v++) {
        color[v] = white;
        dfs_parent[v] = -1;
        bw[v] = 1000000;
    }
    
    DFS(finalAdjList, s, dfs_parent, color, bw);

    int max_bw = 100000, cur=t;
    while(cur!=-1) {
        // cout<<cur<<" <-- ";        
        max_bw = min(max_bw, bw[cur]);
        cur = dfs_parent[cur];
    }
    // cout<<endl;
    std::cout<<"Maximum bandwidth: "<<max_bw<<endl;

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(stop - start);
    // std::cout << "Time taken by Kruskal: "<< duration.count() << " milliseconds\n" << endl;
}


#endif