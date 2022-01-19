#include <stdio.h>
#include <iostream>
#include <random>
#include "./graph.h"
#include "./dijkstra_maxheap.h"
#include "./dijkstra.h"
#include "./kruskal.h"
#include <chrono>
#include <time.h>
#include <fstream>
using namespace std::chrono;
using namespace std;

void generateSparseGraph(struct AdjList* &adjList, vector<struct Edge*> &edgeList) {
    int i, weight, v, w;
    static int adjMatrix[5000][5000];

    for(i=0; i<5000; i++) {
        adjMatrix[i%5000][(i+1)%5000] = 1;
        adjMatrix[(i+1)%5000][i%5000] = 1;
    }

    for(i=0; i<11000; i++) {
        srand(i+time(NULL)*rand());
        v = rand() % 5000;
        w = (rand()+1) % 5000;
        adjMatrix[v][w] = 1;
        adjMatrix[w][v] = 1;
    }

    for(int i=0; i<5000; i++) {
        for(int j=0; j<5000; j++) {
            if(adjMatrix[i][j]==1) {
                srand(i+time(NULL)*rand());
                weight = rand()%10000 + 1;
                addEdge(adjList, i, j, weight);
                AddEdge(edgeList, i, j, weight);
                adjMatrix[i][j] = 0;
                adjMatrix[j][i] = 0;
            }
        }
    }
}

void generateDenseGraph(struct AdjList* &adjList, vector<struct Edge*> &edgeList) {
    int i, weight, v, w;
    static int adjMatrix[5000][5000];

    for(i=0; i<5000; i++) {
        adjMatrix[i%5000][(i+1)%5000] = 1;
        adjMatrix[(i+1)%5000][i%5000] = 1;
    }

    for(i=0; i<2800000; i++) {
        srand(i+time(NULL)*rand());
        v = (rand()+i) % 5000;
        w = (rand()+i+1) % 5000;
        adjMatrix[v][w] = 1;
        adjMatrix[w][v] = 1;
    }

    for(int i=0; i<5000; i++) {
        for(int j=0; j<5000; j++) {
            if(adjMatrix[i][j]==1) {
                srand(i+time(NULL)*rand());
                weight = rand()%10000 + 1;
                addEdge(adjList, i, j, weight);
                AddEdge(edgeList, i, j, weight);
                adjMatrix[i][j] = 0;
                adjMatrix[j][i] = 0;
            }
        }
    }
}

int main() {   
    int i;
    int s, t, v, w, weight;

    // For Dijkstra algorithm
    struct AdjList *sparseGraphs[5];
    struct AdjList *denseGraphs[5]; 

    // For Kruskal's algorithm
    vector<struct Edge*> edgeListSparse[5];
    vector<struct Edge*> edgeListDense[5];

    for(i=0;i<5;i++) {
        sparseGraphs[i] = (struct AdjList*) malloc(sizeof(struct Node)*5000);
        denseGraphs[i] = (struct AdjList*) malloc(sizeof(struct Node)*5000);
    }

    for(i=0; i<5; i++) {
        for(int j=0; j<5000; j++) {
            sparseGraphs[i][j].head = NULL;
            denseGraphs[i][j].head = NULL;
        }
    }

    for(i=0; i<5; i++) {
        generateSparseGraph(sparseGraphs[i], edgeListSparse[i]);
        cout<<"Edge count for sparse graph "<<(i+1)<< ": "<<edgeListSparse[i].size()<<endl;
        generateDenseGraph(denseGraphs[i], edgeListDense[i]);
        cout<<"Edge count for dense graph "<<(i+1)<< ": "<<edgeListDense[i].size()<<endl;
    }

    // ofstream file1("Times/sparse_disjkstra_no_heap.txt");
    // ofstream file2("Times/sparse_disjkstra_heap.txt");
    // ofstream file3("Times/sparse_kruskal.txt");
    ofstream file4("Times/dense_disjkstra_no_heap.txt");
    ofstream file5("Times/dense_disjkstra_heap.txt");
    // ofstream file6("Times/dense_kruskal.txt");
    // ofstream file7("Times/sparse_kruskal_path_compression.txt");
    // ofstream file8("Times/dense_kruskal_path_compression.txt");

    // std::cout<<"For Graphs with average degree of connectivity 6"<<endl;
    // // For loop to iterate over each graph
    // for(i=0; i<5; i++) {
    //     std::cout<<"Graph Number "<<(i+1)<<endl;

    //     // for loop to generate 5 random s-t points
    //     for(int k=0; k<5; k++) {
    //         struct AdjList *finalAdjList = (struct AdjList*) malloc(sizeof(struct Node)*5000);
    //         for(int j=0; j<5000; j++) {
    //             finalAdjList[j].head = NULL;
    //         }

    //         s = rand()%5000;
    //         t = rand()%5000;
    //         std::cout<<"--- Start of test for s-t path number "<<(k+1)<<" ---\n"<<endl;
    //         std::cout<<"Source: "<<s<<endl;
    //         std::cout<<"Destination: "<<t<<endl;
    //         std::cout<<"\n";

    //         // Dijkstra without heap
    //         auto start = high_resolution_clock::now();
    //         Dijkstra(sparseGraphs[i], s, t);
    //         auto stop = high_resolution_clock::now();
    //         auto duration = duration_cast<milliseconds>(stop - start);
    //         std::cout << "Time taken by Dijkstra without heap: "<< duration.count() << " milliseconds\n" << endl;
    //         // file1 << duration.count()<<endl;

    //         // Dijkstra with heap
    //         start = high_resolution_clock::now();
    //         Dijkstra_Maxheap(sparseGraphs[i], s, t);
    //         stop = high_resolution_clock::now();
    //         duration = duration_cast<milliseconds>(stop - start);
    //         std::cout << "Time taken by Dijkstra with heap: "<< duration.count() << " milliseconds\n" << endl;
    //         // file2 << duration.count()<<endl;

    //         // Kruskal
    //         start = high_resolution_clock::now();
    //         Kruskal(edgeListSparse[i], finalAdjList, s, t);
    //         stop = high_resolution_clock::now();
    //         duration = duration_cast<milliseconds>(stop - start);
    //         std::cout << "Time taken by Kruskal: "<< duration.count() << " milliseconds\n" << endl;
    //         // file3 << duration.count()<<endl;
    //         free(finalAdjList);

    //         finalAdjList = (struct AdjList*) malloc(sizeof(struct Node)*5000);
    //         for(int j=0; j<5000; j++) {
    //             finalAdjList[j].head = NULL;
    //         }

    //         start = high_resolution_clock::now();
    //         Kruskal_Path_Compression(edgeListSparse[i], finalAdjList, s, t);
    //         stop = high_resolution_clock::now();
    //         duration = duration_cast<milliseconds>(stop - start);
    //         std::cout << "Time taken by Kruskal with path compression: "<< duration.count() << " milliseconds\n" << endl;
    //         // file7 << duration.count()<<endl;
    //         free(finalAdjList);
            
    //         std::cout<<"--- End of test for s-t path number "<<(k+1)<<" ---\n"<<endl;
    //     } 
    //     std::cout<<"----------------------------------------------------------------------------------\n";
    // }

    std::cout<<"\n\n";
    std::cout<<"For graphs with an average connectivity of 20%"<<endl;
    for(i=0; i<5; i++) {
        std::cout<<"Graph Number "<<(i+1)<<endl;

        // for loop to generate 5 random s-t points
        for(int k=0; k<10; k++) {
            struct AdjList *finalAdjList = (struct AdjList*) malloc(sizeof(struct Node)*5000);
            for(int j=0; j<5000; j++) {
                finalAdjList[j].head = NULL;
            }

            s = rand()%5000;
            t = rand()%5000;
            if(s==t)
                t = (t+5)%5000;
            std::cout<<"--- Start of test for s-t path number "<<(k+1)<<" ---\n"<<endl;
            std::cout<<"Source: "<<s<<endl;
            std::cout<<"Destination: "<<t<<endl;
            std::cout<<"\n";

            // Dijkstra without heap
            auto start = high_resolution_clock::now();
            Dijkstra(denseGraphs[i], s, t);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            std::cout << "Time taken by Dijkstra without heap: "<< duration.count() << " milliseconds\n" << endl;
            file4 << duration.count()<<endl;

            // Dijkstra with heap
            start = high_resolution_clock::now();
            Dijkstra_Maxheap(denseGraphs[i], s, t);
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            std::cout << "Time taken by Dijkstra with heap: "<< duration.count() << " milliseconds\n" << endl;
            file5 << duration.count()<<endl;

            // // Kruskal
            // start = high_resolution_clock::now();
            // Kruskal(edgeListDense[i], finalAdjList, s, t);
            // stop = high_resolution_clock::now();
            // duration = duration_cast<milliseconds>(stop - start);
            // std::cout << "Time taken by Kruskal: "<< duration.count() << " milliseconds\n" << endl;
            // // file6 << duration.count()<<endl;
            // free(finalAdjList);

            // finalAdjList = (struct AdjList*) malloc(sizeof(struct Node)*5000);
            // for(int j=0; j<5000; j++) {
            //     finalAdjList[j].head = NULL;
            // }

            // start = high_resolution_clock::now();
            // Kruskal_Path_Compression(edgeListDense[i], finalAdjList, s, t);
            // stop = high_resolution_clock::now();
            // duration = duration_cast<milliseconds>(stop - start);
            // // file8 << duration.count()<<endl;
            // std::cout << "Time taken by Kruskal with path compression: "<< duration.count() << " milliseconds\n" << endl;
            // free(finalAdjList);

            std::cout<<"--- End of test for s-t path number "<<(k+1)<<" ---\n"<<endl;
        } 
        std::cout<<"----------------------------------------------------------------------------------\n";
    }

    for(i=0; i<5; i++) {
        free(sparseGraphs[i]);
        free(denseGraphs[i]);
    }

    // file1.close();
    // file2.close();
    // file3.close();
    file4.close();
    file5.close();
    // file6.close();
    // file7.close();
    // file8.close();

    return 0;
}