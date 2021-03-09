# SocialNetwork-and-Polyglots

1. Social Network
The following idea: If A “follows” B, B “follows” C and C “follows” A, then perhaps A, B, C have similar interests and the engine should recommend that they follow each other (e.g. A to “follow” C, B to “follow” A, C to “follow” B, etc.).
X would like to discover all such groups of like-minded users that follow each other directly or indirectly (like in the above example). More specifically, he would like to quickly answer questions such as: Is user A in the same group as user B?

2. Polyglots
You are given the translation of a word that the user knows, the translation that must be learned in the end and its many other translations in different languages that are of interest to the user. Find out what’s the least amount of translations that the user has to learn before he can learn the final one, considering that the user will only be taught a new translation if it differs by only one letter from the previous one.

Solutions
1. Social Network
The input data which represents the social network users
that we read from the file is stored in a directed unweighted 
graph using adjacency lists, the nodes being the users and the edges (with their 
directions) representing the "follow" relationship. Because the 
indices of the graph and of the list start from 0, and in the 
description of the problem they start from 1, it is necesarry
that upon adding the edges between two nodes we also descrease 
the number of the node by one: it is simply an efficient 
"shifting" move. After building our graph, we make use of a 
mildly modified DFS, Tarjan's algorithm, for strongly connected 
components (scc), which allows us to store in an array (low[]) 
the ids of the sccs that each node is part of. Therefore, when 
reading the queries representing the possible like-minded users 
from the input file, we simply check if the ids in the array that
resulted from Tarjan's algorithm are the same for both users.

Time Complexity - O ( N + M + T )
Space Complexity - O ( N + M )

2. Polyglots
The input data is read from the input file and then stored in an 
array of type string, so that each word has an id that represents 
both the index of its position in the array and the nth word read
from the file. The ids of the words are added to a list of integers
in the order they were read. When adding nodes to the graph we 
compare words two by two, using two nested loops: one for the list
and the other one for the array. If the difference between the letters
of the two compared strings is one, then we add the node to the graph.
After constructing the unweighted graph, we want to look for the path
that has the least amount of edges, by using BFS for the shortest path
(adding another array called dist that stores for each index(=no of the
node) the distance from the starting point (in our case it is 0, because
we are only interested in the translation from the first word in the file).
We can then simply print -1 if the two nodes are not connected (if there
exist no translation using the words given) or the value in our dist array
from the index our end word had (we store the index when reading it with
the other words).
Because the input data is rather small, even though the time complexity 
is N^2, it does not affect the result. I think there exists an optimized 
solution to this problem and I will be looking about it.

Time Complexity -  O ( N^2 )
Space Complexity - O ( N + M )


