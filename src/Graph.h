#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include "User.h"

using namespace std;

class Graph
{
private:

    unordered_map<int, User> users;
    unordered_map<int, vector<int>> adj;

public:

    void addUser(int id,string name);

    void addFriendship(int u,int v);

    void displayUsers();

    void displayGraph();

    bool userExists(int id);

    vector<int> getFriends(int id);

    void recommendFriends(int id);

    void shortestPath(int start,int end);
};

#endif