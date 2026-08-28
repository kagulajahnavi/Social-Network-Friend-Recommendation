#include "User.h"

User::User()
{
    id = 0;
    name = "";
}

User::User(int id, string name)
{
    this->id = id;
    this->name = name;
}

int User::getId() const
{
    return id;
}

string User::getName() const
{
    return name;
}

void User::setId(int id)
{
    this->id = id;
}

void User::setName(string name)
{
    this->name = name;
}