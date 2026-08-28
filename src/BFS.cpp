#include "BFS.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

void BFS::recommendFriends(Graph &g, int userId)
{
    if(!g.userExists(userId))
    {
        cout << "User not found!\n";
        return;
    }

    vector<int> friends = g.getFriends(userId);

    set<int> directFriends;
    for(int f : friends)
        directFriends.insert(f);

    unordered_map<int,int> score;

    for(int f : friends)
    {
        vector<int> second = g.getFriends(f);

        for(int s : second)
        {
            if(s != userId && directFriends.find(s) == directFriends.end())
            {
                score[s]++;
            }
        }
    }

    if(score.empty())
    {
        cout << "\nNo friend recommendations available.\n";
        return;
    }

    cout << "\n========== Friend Recommendations ==========\n";

    for(auto x : score)
    {
        cout << "User ID : " << x.first
             << "   Mutual Friends : "
             << x.second << endl;
    }

    cout << "============================================\n";
}

void BFS::shortestPath(Graph &g, int start, int end)
{
    if(!g.userExists(start) || !g.userExists(end))
    {
        cout << "Invalid User!\n";
        return;
    }

    queue<int> q;
    unordered_map<int,bool> visited;
    unordered_map<int,int> parent;

    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while(!q.empty())
    {
        int current = q.front();
        q.pop();

        if(current == end)
            break;

        vector<int> neighbours = g.getFriends(current);

        for(int x : neighbours)
        {
            if(!visited[x])
            {
                visited[x] = true;
                parent[x] = current;
                q.push(x);
            }
        }
    }

    if(!visited[end])
    {
        cout << "No connection found.\n";
        return;
    }

    vector<int> path;

    for(int v=end; v!=-1; v=parent[v])
        path.push_back(v);

    reverse(path.begin(),path.end());

    cout << "\nShortest Connection:\n";

    for(int x : path)
        cout << x << " ";

    cout << endl;
}