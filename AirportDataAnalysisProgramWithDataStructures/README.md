# Airport Data Analysis System (AVL Tree)

## Description
A high-performance flight indexing application built to analyze departure data from Istanbul Airport.
This project focuses on the implementation and maintenance of an AVL Tree ADT for $O(\log n)$ search efficiency.

## Features
* **AVL Tree Integration**: Destinations serve as keys for a self-balancing binary search tree.
* **Collision Handling**: Multiple flights sharing the same destination are stored within the same tree node.
* **Search & Retrieval**: Detailed flight info (Airline, Type, Date, Distance) can be queried by destination code.
* **Advanced Analytics**: Identifies the "Furthest Destination" by calculating the maximum kilometers recorded in the dataset.

## Technical Stack
* **ADT Implementation**: Modular design with `avltree.h` and `avltree.c`.
* **Algorithms**: Includes standard AVL rotations (LL, RR, LR, RL) to maintain balance during insertions.
* **Complexity**: Includes discussions on the time complexity of search and furthest-node discovery.