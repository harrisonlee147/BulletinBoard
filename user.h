#ifndef __USER_H__
#define __USER_H__

#include <string>
#include "user.h"

using namespace std;
 
class User
{
private:
	string username;
    string password;
 
public:
	// Constructors
	User();
    User(const string& uname, const string& pass);
    
    string get_username() const;
    bool check(const string& uname, const string& pass) const;
    void set_password(const string& newpass);
};
 
#endif
