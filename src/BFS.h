#ifndef BFS_H
#define BFS_H

#include "Graph.h"

class BFS
{
public:
    static void recommendFriends(Graph &g, int userId);
    static void shortestPath(Graph &g, int start, int end);
};

#endif