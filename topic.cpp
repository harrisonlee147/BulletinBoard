// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee

// ================================================================
#include "topic.h"
#include "reply.h"
#include <iostream>
#include <fstream>
#include <sstream>

///Public member functions
//default constructor
Topic::Topic()
: Message() {}

//Parameterized constructor
Topic::Topic(const string& athr, const string& sbjct, const string& body, 
	  unsigned id)
: Message(athr, sbjct, body, id) {}

//prints topic objects
//also prints topic's children by invoking print_subtree(indentation)
void Topic::print() const
{
	cout << "Message " << "#" << id << ": ";
	cout << subject << endl;
	cout << "from " << author << ": ";
	cout << body << endl;
	for (unsigned i = 0; i < child_list.size(); i++)
	{
		dynamic_cast<Reply*>(child_list.at(i))->print_subtree(1);
	}
}

//returns true if object is reply
bool Topic::is_reply() const
{
	return false;
}

//changes topic into format provided by specs
string Topic::to_formatted_string() const
{
	string format;
	stringstream str_id, child_id;
	//converting id from into into string
	str_id << id;
	
	format = "<begin_topic>\n:id: " + str_id.str();
	format +="\n:subject: " + subject + "\n:from: "  + author;
	//topic has children
	if (child_list.size() > 0)
	{
		format +=  "\n:children: ";
		for (unsigned i = 0; i < child_list.size(); i++)
		{
			//converting child_id into a string
			child_id << child_list.at(i)->get_id() << " ";
		}
		format += child_id.str();
	}
	
	format += "\n:body: " + body + "<end>\n";
	return format;
}



