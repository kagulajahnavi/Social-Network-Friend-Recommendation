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
    unordered_map<int, vector<int>> adjList;

public:
    // User Operations
    void addUser(int id, string name);
    void displayUsers();

    // Friendship Operations
    void addFriendship(int u, int v);
    void displayNetwork();

    // Helper Functions
    bool userExists(int id);
    vector<int> getFriends(int id);
    void searchUser(int id);


    // BFS Features
    void recommendFriends(int id);
    void shortestPath(int start, int end);

    // Statistics
    int totalUsers();
    int totalConnections();
    void mostPopularUser();
};

#endif