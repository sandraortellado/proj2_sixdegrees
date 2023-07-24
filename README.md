Project 2: Six Degrees, Pahse 1

Author: Sandra Ortellado

Assignment completion time: 20 hours

Program purpose: Play the game Six Degrees of Kevin Bacon using musical 
artists, and output a path to get from the
first artist to the second via musical collaborations

Help received: Graphs topic on canvas.

Files included:

* main.cpp: interactively accept queries in the form of an input
command and the names of artists.
* SixDegrees.cpp: Define functions in SixDegrees class.
* SixDegrees.h: Define SixDegrees class.
* CollabGraph.cpp: Define functions in CollabGraph class,
* CollabGraph.h: Define CollabGraph class.
* unit_testing.cpp: test functions in CollabGraph and SixDegrees class.
* README.md: Explanation of assignment, approach, and code provided.
* Makefile: File for compiling and linking.

Compilation and running: 
make ; ./SixDegrees datafile [commandFile] [outputFile]

Data structures and algorithms:
* Graph: A non-linear data structure consisting of vertices and edges.
By using graphs we can easily find the shortest path, 
neighbors of the nodes, and many more. However, graphs use 
lots of pointers which can be complex to handle, and can have large 
memory complexity.

* Stack: Stacks are a type of container adaptors with LIFO (Last In 
First Out) type of working, where a new element is added at one end (top) 
and an element is removed from that end only. Stacks help in managing data 
that follows the LIFO technique, but have memory of limited size and do not
allow random accessing.

* Queues: Queues are a type of container adaptor, specifically designed 
to operate in a FIFO context (first-in first-out), where elements are 
inserted into one end of the container and extracted from the other. 
Queues allow large amount of data to be managed efficiently with ease, 
but operations such as insertion and deletion
of elements from the middle are time consuming.

Testing strategy: testing three functions implemented, and all 3 commands 
in caseof both path existing and not existing.

Additional questions:

1. The difference between BFS and DFS: BFS uses Queue data structure
for finding the shortest path, while DFS uses a stack. BFS is a 
traversal approach in which we first walk through all nodes on 
the same level before moving on to the next level, while DFS is 
a traversal approach in which the traverse begins at the root node 
and proceeds through the nodes as far as possible until we reach the 
node with no unvisited nearby nodes. BFS builds the tree level by level,
while DFS builds the tree sub-tree by sub-tree. BFS is more suitable 
for searching vertices closer to the given source, while DFS 
is more suitable when there are solutions away from source.
Pros of BFS:
* If there is more than one solution then it will find 
the solution with minimal steps.
* It will find the closest goal in less time.
Cons of BFS:
* Memory constraints
* If solution is far away then it consumes time.
Pros of DFS:
* May find a path faster than bfs.
* May find the larger distant element (from source vertex) in less time.
Cons of DFS:
* May not find optimal solution to the problem.
* May get trapped in searching useless path.
2. Not was implemented using bfs, with the added restriction upon adding 
neighbors to the queue, that the neighbor name added could not be in 
the list of names gathered to be excluded.
3. Runtime:
* bfs: O(number of vertices + number of edges), in the worst case, 
it will explore every vertex and edge
* dfs: O(number of vertices + number of edges), 
the algorithm explores each vertex and edge exactly once.
* not: O(number of vertices + number of edges), this is the same
as bfs.
