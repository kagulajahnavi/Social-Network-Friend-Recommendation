#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph social;

    // Sample Users
    social.addUser(1, "Alice");
    social.addUser(2, "Bob");
    social.addUser(3, "Charlie");
    social.addUser(4, "David");
    social.addUser(5, "Emma");

    // Friendships
    social.addFriendship(1, 2);
    social.addFriendship(1, 3);
    social.addFriendship(2, 4);
    social.addFriendship(3, 4);
    social.addFriendship(4, 5);

    int choice;

    do
    {
       cout << "\n=========================================\n";
       cout << " SOCIAL NETWORK FRIEND RECOMMENDATION\n";
       cout << "=========================================\n";
       cout << "1. Add User\n";
       cout << "2. Add Friendship\n";
       cout << "3. Display Users\n";
       cout << "4. Display Network\n";
       cout << "5. Recommend Friends\n";
       cout << "6. Find Shortest Connection\n";
       cout << "7. Show Statistics\n";
       cout << "8. Search User\n";
       cout << "9. Most Popular User\n";
       cout << "0. Exit\n";
       cout << "=========================================\n";
       cout << "Enter Choice: ";
    cin >> choice;

        switch(choice)
{
    case 1:
    {
        int id;
        string name;

        cout << "Enter User ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter User Name: ";
        getline(cin, name);

        social.addUser(id, name);

        cout << "\nUser Added Successfully!\n";
        break;
    }

    case 2:
    {
        int u1, u2;

        cout << "Enter First User ID: ";
        cin >> u1;

        cout << "Enter Second User ID: ";
        cin >> u2;

        social.addFriendship(u1, u2);

        cout << "\nFriendship Added!\n";
        break;
    }

    case 3:
        social.displayUsers();
        break;

    case 4:
        social.displayNetwork();
        break;

    case 5:
    {
        int id;

        cout << "Enter User ID: ";
        cin >> id;

        social.recommendFriends(id);
        break;
    }

    case 6:
    {
        int start, end;

        cout << "Enter Start User ID: ";
        cin >> start;

        cout << "Enter End User ID: ";
        cin >> end;

        social.shortestPath(start, end);
        break;
    }

    case 7:
        cout << "\nTotal Users : "
             << social.totalUsers() << endl;

        cout << "Total Friendships : "
             << social.totalConnections() << endl;
        break;

    case 8:
{
    int id;

    cout << "Enter User ID: ";
    cin >> id;

    social.searchUser(id);
    break;
}
    case 9:
{
    social.mostPopularUser();
    break;
}

    case 0:
        cout << "\nThank You!\n";
        break;

    default:
        cout << "\nInvalid Choice!\n";
        break;
}
        

    } while(choice != 0);

    return 0;
}