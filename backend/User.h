#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
private:
    int id;
    string name;

public:
    User();
    User(int id, string name);

    int getId() const;
    string getName() const;

    void setId(int id);
    void setName(string name);
};

#endif