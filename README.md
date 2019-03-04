# Social NetWrok Analysis
Backend implementation of social relations and clusters with basic visualiser
to mine a given social network, detect influenciers followers and community topic

  - Implement graph based data analysis function to mine a given social network
  - Some analysis e.g. Centrality, LanceWilliams HAC, Hierarchical Clustering, Agglomerative Clustering, Closeness/Betweenness Centrality
#### Input Data 
from a text file and build a directed weighted graph using the graph ADT, samples are shown in `/graphs`
for example 
0, 4, 5 represents 0->4 with a weight 5

#### Stage 1 build graphs
    Implemented adjavency List representation 
#### Stage 2 Dijkstra's algorithm
    In discovering "influencers", ew need to repeatedly find shortest paths between all pairs of node.
    By Implementing Dijkstra's algorithm to discover shortest paths from a given source to all other nodes in the graph based on Priority Queue 
#### Stage 3 Centrality Measures for Social Network Analysis
    Centrality measures 
    higher betweenness measure often correspond to influencers
##### Degree Centrality
defined as the number of links incident upon a node
##### Closeness Centrality
##### Betweenness Centrality

#### Stage 4

## How to use the testing interface 
To use Dijkstra get the shortest path output for your search on the input graph, and compare output files with correct solution in /dijkstarPaths
```sh
$ ./testDijstark [input file]   # for any input file
$ ./testDijstra.sh 1    # test search on graph1
```
## To use Centrality
Run `${./testCentralityMeasures}` to get **HELP** to use the test interface

 Usage: ./testCentralityMeasures [file] [flag]
| Flag | def |
| ------ | ------ |
| d | degree centrality |
| do | degree out centrality |
| di | degree in centrality |
| c | closeness centrality |
| b | betweenness centrality |
| bn | betweenness centrality normalised|
| v[m] | trigger Graph Vis with mode [m] |
    0    : DEFAULT
    1    : DEGREE_IN
    2    : DEGREE_OUT
    3    : DEGREE
    4    : CLOSENESS
    5    : BETWEENNESS

## To use graphVis interface

call `graphVis(g, DEFAULT)`


# LanceWilliamsHAC analysis of clusters of users' social relationship

the sample visualization as shown below
![image](https://user-images.githubusercontent.com/37000892/53711320-bd63e300-3e95-11e9-8cc9-51874ff87325.png)


