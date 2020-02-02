# Cheapest Route Using Dijkstra's Shortest Path Algorithm

[Dijkstra's]([https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)) shortest path algorithm is a greedy algorithm to find the shortest distances of each node from a particular source node in graphs. This algorithm is not capable of discovering the shortest path is the cases with negative weights.

Dijkstra's algorithm benefits this program in finding the cheapest route for traveling from a source to the destination. As there are no negative prices, the algorithm is capable of operating in this context. The weighted graph of flights and prices are being stored in the form of a matrix called an adjacency matrix. As a fact, as the size of the matrix grows, the possibility of finding the cheapest routs grows. Furthermore, the layover time has no adverse effect on the last result, which is not realistic.

This program keeps logs of attempts in well-formatted text files in the directory of the binary application. There is also a point that this program is designed to operate on Microsoft Windows operating system. For Linux and macOS machines, minor changes are mandatory.

# Screen Shots
| ![Running](https://github.com/mirerfangheibi/Cheapest-Route-Dijkstra/blob/master/Screen%20Shots/Running.png?raw=true)Fig.1: Running | ![Log](https://github.com/mirerfangheibi/Cheapest-Route-Dijkstra/blob/master/Screen%20Shots/Log.png?raw=true)Fig.2: Log File |
|--|--|
