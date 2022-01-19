# CSCE629-Analysis_of_Algorithms_Project

This is a project done for the CSCE629 Analysis of Algorithms course project taught my Jianer Chen at Texas A&M university.

The aim of this project is to compare the running times for 2 different algorithms to solve the widest path (Maximum bandwidth problem), namely:
1. Dijkstra's algorithm
2. Dijkstra's algorithm with max heap
3. Kruskal's algorithm without path compression
4. Kruskal's algorithm using union-find path compression

In order to test these algorithms, 2 types of graphs were used
1. Sparse graphs: graphs with 5000 vertices and an average vertex degree of 6
2. Dense graphs: graphs with 5000 vertices with a 20% average connectivity

All graphs are randomly generated. For the purpose of comparison, 25 random dense and 25 random sparse graphs were tested and the amount of running time was measured for each.

The results for sparse graphs is as follows:  
|Algorithm	                      | Avg running time      |  
|---------------------------------|:---------------------:|
|Dijkstra without heap	          |  40.64 milliseconds   |
|Dijkstra with heap&nbsp	        |      1 millisecond    |
|Kruskal without path compression	|4.88 milliseconds      |
|Kruskal with path compression 	  |9.76 milliseconds      |

The results for dense graphs is as follows:  
Algorithm	                           Avg running time  
Dijkstra without heap	              329.76 milliseconds  
Dijkstra with heap	                335.04 milliseconds  
Kruskal without path compression	  2534.12 milliseconds  
Kruskal with path compression	      3526.4 milliseconds  

