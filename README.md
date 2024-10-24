# Algorithms and Data Structures - University of Wrocław

This repository contains a collection of algorithms and data structures implemented as part of the *Algorithms and Data Structures* 
course at the University of Wrocław. Each file corresponds to a well-known problem or concept, with efficient solutions written in C++ (and C).

## Table of Contents
- [Overview](#overview)
- [Files](#files)
- [Description of Algorithms](#description-of-algorithms)

## Overview
This project includes several key algorithms and data structures commonly covered in computer science courses, focusing on topics such as sorting, tree structures, dynamic programming, and graph theory.
The implementations are designed to be efficient, showcasing optimized approaches to solving classical problems.

## Files
Below is a brief overview of the files and the problems they solve:

- **2SUM.cpp** & **3SUM.cpp**: Solutions for the classic 2SUM and 3SUM problems.
- **ClosestThreePoints.cpp** & **ClosestTwoPoints.cpp**: Algorithms to find the closest points on a plane.
- **Genealogy.cpp**: A solution for a genealogy problem involving family trees.
- **IDUL.cpp**: Implementation of the AVL Tree data structure.
- **Knapsack.cpp**: Solves the Unbounded Knapsack problem using dynamic programming.
- **LCA.cpp**: Lowest Common Ancestor algorithm for trees.
- **LCIS.cpp** & **LCS.cpp**: Optimized algorithms for finding the Longest Common Increasing Subsequence and Longest Common Subsequence (with Hirschberg trick for O(n) space!!!).
- **Most_Disjoint_Segments.cpp**: Finds the maximum number of disjoint line segments.
- **Topology-Sort.cpp**: Implements topological sorting for acyclic directed graphs.
- **Trie-Tree.c**: A Trie data structure implementation.
- **bst.cpp**: Binary Search Tree (BST) implementation.
- **heap.cpp**: Min/Max Heap implementation.

## Description of Algorithms
### 2SUM & 3SUM Problem
These algorithms aim to find pairs or triples in an array that sum up to a specific target, optimized using hashing and two-pointer techniques.

### Closest Points Algorithms
Efficient solutions using divide and conquer techniques to determine the closest pair/triplet of points in a 2D space.

### Genealogy (Lab1)
A family tree problem solved using tree traversal techniques, demonstrating the application of depth-first search (DFS) and dynamic parent-child relationships.

### AVL Tree (IDUL)
An AVL tree is a self-balancing binary search tree. This implementation ensures O(log n) time complexity for insertions, deletions, and lookups.

### Unbounded Knapsack Problem
A dynamic programming solution to maximize the total value when placing items in a knapsack, allowing for an unlimited quantity of each item.

### Lowest Common Ancestor (LCA)
Efficiently finds the lowest common ancestor of two nodes in a tree using binary lifting.

### LCIS & LCS
Two classical dynamic programming problems, optimized for time and space complexity, that solve sequence alignment problems.

### Most Disjoint Segments
This problem is solved using a greedy algorithm to find the maximum number of non-overlapping segments from a given set of line segments.

### Topological Sort
An algorithm to order the vertices of a directed acyclic graph (DAG) in a linear sequence such that for every directed edge UV, vertex U comes before vertex V.

### Trie Tree
This data structure is used for efficient prefix searching, commonly used in applications like autocomplete.
