#include "Graph.h"

void Graph::addUser(int id, string name)
{
    if(userExists(id))
    {
        cout << "User ID already exists!\n";
        return;
    }

    users[id] = User(id, name);
    cout << "User added successfully.\n";
}

bool Graph::userExists(int id)
{
    return users.find(id) != users.end();
}

void Graph::displayUsers()
{
    if(users.empty())
    {
        cout << "No users found.\n";
        return;
    }

    cout << "\n========== USERS ==========\n";

    for(auto &u : users)
    {
        cout << "ID: " << u.first
             << "   Name: " << u.second.getName()
             << endl;
    }
}
void Graph::searchUser(int id)
{
    if(!userExists(id))
    {
        cout << "\nUser not found.\n";
        return;
    }

    cout << "\n========== USER DETAILS ==========\n";
    cout << "User ID   : " << id << endl;
    cout << "User Name : " << users[id].getName() << endl;

    cout << "Friends   : ";

    vector<int> friends = getFriends(id);

    if(friends.empty())
    {
        cout << "No Friends";
    }
    else
    {
        for(int friendId : friends)
        {
            cout << users[friendId].getName() << " ";
        }
    }

    cout << endl;
}

void Graph::addFriendship(int u, int v)
{
    if(!userExists(u) || !userExists(v))
    {
        cout << "Invalid User ID.\n";
        return;
    }

    adjList[u].push_back(v);
    adjList[v].push_back(u);

    cout << "Friendship Added Successfully.\n";
}

vector<int> Graph::getFriends(int id)
{
    if(adjList.find(id) == adjList.end())
        return {};

    return adjList[id];
}

void Graph::displayNetwork()
{
    cout << "\n========== SOCIAL NETWORK ==========\n";

    for(auto &node : adjList)
    {
        cout << users[node.first].getName() << " -> ";

        for(int friendId : node.second)
        {
            cout << users[friendId].getName() << " ";
        }

        cout << endl;
    }
}
void Graph::recommendFriends(int id)
{
    if(!userExists(id))
    {
        cout << "User not found.\n";
        return;
    }

    unordered_map<int, int> mutualCount;
    set<int> directFriends;

    for(int f : adjList[id])
        directFriends.insert(f);

    for(int friendId : adjList[id])
    {
        for(int fof : adjList[friendId])
        {
            if(fof != id && directFriends.find(fof) == directFriends.end())
            {
                mutualCount[fof]++;
            }
        }
    }

    if(mutualCount.empty())
    {
        cout << "\nNo friend recommendations available.\n";
        return;
    }

    cout << "\n========== FRIEND RECOMMENDATIONS ==========\n";

    for(auto &rec : mutualCount)
    {
        cout << "ID : " << rec.first
             << "  Name : " << users[rec.first].getName()
             << "  Mutual Friends : " << rec.second
             << endl;
    }
}

void Graph::shortestPath(int start, int end)
{
    if(!userExists(start) || !userExists(end))
    {
        cout << "Invalid User ID.\n";
        return;
    }

    unordered_map<int,bool> visited;
    unordered_map<int,int> parent;
    queue<int> q;

    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while(!q.empty())
    {
        int current = q.front();
        q.pop();

        if(current == end)
            break;

        for(int neighbour : adjList[current])
        {
            if(!visited[neighbour])
            {
                visited[neighbour] = true;
                parent[neighbour] = current;
                q.push(neighbour);
            }
        }
    }

    if(!visited[end])
    {
        cout << "No connection found.\n";
        return;
    }

    vector<int> path;

    for(int v = end; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "\nShortest Connection:\n";

    for(int node : path)
    {
        cout << users[node].getName();

        if(node != end)
            cout << " -> ";
    }

    cout << endl;
}

int Graph::totalUsers()
{
    return users.size();
}

int Graph::totalConnections()
{
    int count = 0;

    for(auto &node : adjList)
        count += node.second.size();

    return count / 2;
}

void Graph::mostPopularUser()
{
    if(users.empty())
    {
        cout << "\nNo users available.\n";
        return;
    }

    int maxFriends = -1;
    int popularId = -1;

    for(auto &user : users)
    {
        int total = adjList[user.first].size();

        if(total > maxFriends)
        {
            maxFriends = total;
            popularId = user.first;
        }
    }

    cout << "\n========== MOST POPULAR USER ==========\n";
    cout << "User ID : " << popularId << endl;
    cout << "Name    : " << users[popularId].getName() << endl;
    cout << "Friends : " << maxFriends << endl;
}