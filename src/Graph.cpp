#include "Graph.h"

void Graph::addUser(int id, string name)
{
    users[id] = User(id, name);
}

bool Graph::userExists(int id)
{
    return users.find(id) != users.end();
}

void Graph::addFriendship(int u, int v)
{
    if(!userExists(u) || !userExists(v))
    {
        cout<<"User not found.\n";
        return;
    }

    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::displayUsers()
{
    cout<<"\n------ USERS ------\n";

    for(auto x : users)
    {
        cout<<x.first<<" -> "<<x.second.getName()<<endl;
    }
}

void Graph::displayGraph()
{
    cout<<"\n------ NETWORK ------\n";

    for(auto x : adj)
    {
        cout<<users[x.first].getName()<<" : ";

        for(int friendId : x.second)
        {
            cout<<users[friendId].getName()<<" ";
        }

        cout<<endl;
    }
}

vector<int> Graph::getFriends(int id)
{
    return adj[id];
}