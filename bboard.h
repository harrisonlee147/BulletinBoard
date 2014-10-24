// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee

// ================================================================
#include <string>
#include <vector>
#include "user.h"
#include "message.h"

using namespace std;

class Bboard
{
private:
	string title;
	vector<User> user_list;
	const User* current_user;
	vector<Message*> message_list;

public:
	// Constructors
	Bboard();
	Bboard(const string& ttl);
	//Destructor
	~Bboard();
	
	// Member functions
	//void setup();
	void login();
	void run();
	bool load_users(const string& userfile);
	bool load_messages(const string& datafile);
	bool save_messages(const string& datafile);

// Private Member Functions	
private:
    //add_user(const string& name, const string& pass);
	const User* get_user(const string& name, const string& pw) const;
	void display() const; 
	void add_topic(); 
	void add_reply();  
};


