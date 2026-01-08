#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
protected:
    string password;
    string email;

public:
    void set_email(const string &e);
    void set_password(const string &p);

    virtual bool login(const string &email, const string &pass) = 0;
};

#endif