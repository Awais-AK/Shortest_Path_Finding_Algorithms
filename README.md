# Shortest Path Finding Algorithms

1. We are taking input of the graph from the input files as command line arguements

2. We can run the command line arguement using the following commands

```
g++ bellman_ford.cpp
a.exe sample1.txt  
```

3. The input file contains the information in the following format
	
        V
        E
        start1 	end1   cost1
        start2 	end2   cost2
          .	  .	 .
          .	  .	 .
          .	  .	 .
        startE 	endE   costE

    where V denotes the number of nodes/vertices
    E denotes the number of edges

    next "E" lines contain edge information: 

    start_i denotes start node of the edge i

    end_i denotes end node of the edge i

    cost_i denotes the cost of the edge i
    
4. The code asks the source and destination of the path required from the user and provides the max limit for entry
   write two whole numbers with some space between them 
   1st number denotes the source node
   2nd number denotes the destination node
   
5. The code outputs the Shortest Path and its path length (if exists)

