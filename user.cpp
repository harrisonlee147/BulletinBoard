// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee

// ================================================================
#include "user.h"
#include <string>

using namespace std;

//creates a user with empty name and password.
User::User()
: username(), password()
{
}

//creates a user with given username and password.
User::User(const string& uname, const string& pass)
: username(uname), password(pass)
{
}

//returns the username
string User::get_username() const
{
	return username;
}

//returns true if the stored username/pw matches with the parameters.
// Otherwise returns false.
//Even though User with empty user/pw is actually a valid User object
//(it is the default User), must still return false if given an 
//empty username string.
bool User::check(const string& uname, const string& pass) const
{
	if (username == uname && password == pass)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//sets a new pw. This function will not be used in the current assn
void User::set_password(const string& newpass)
{
	password = newpass;
}
