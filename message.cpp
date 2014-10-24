// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee

// ================================================================
#include "message.h"
#include <iostream>
using namespace std;

//default constructor
Message::Message()
: author(""), subject(""), body(""), id(0)
{
}

//Constructor with parameters
Message::Message(const string& athr, const string& sbjct, 
				 const string& body, unsigned id)
: author(athr), subject(sbjct), body(body), id(id)
{
}

//Destructor
Message::~Message()
{
	//left blank because Bboard deletes necessary objects
}

//returns the subject string.
string Message::get_subject() const
{
	return subject;
}

// returns the id.
unsigned Message::get_id() const
{
	return id;
}

// Adds a pointer to the child to child_list. 
void Message::add_child(Message* child)
{
	child_list.push_back(child);
}
