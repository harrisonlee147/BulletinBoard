#include "reply.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

///Contructors
//default constructer
Reply::Reply()
: Message() {}

//parameterized constructor
Reply::Reply(const string& athr, const string& sbjct, const string& body, 
			 unsigned id)
: Message(athr, "Re: " + sbjct, body, id) {}


///Print functions
void Reply::print() const
{
	print_subtree(1);
}
//used to print replies recursively, spaces = indentation*2
void Reply::print_subtree(unsigned indentation) const
{
	cout << endl;
	for (unsigned i = 0; i < indentation; i++)
		cout << "  ";
	cout << "Message " << "#" << id << ": ";
	cout << subject << endl;
	for (unsigned i = 0; i < indentation; i++)
		cout << "  ";
	cout << "from " << author << ": ";
	for (unsigned i = 0; i < body.size(); i++)
	{
		if (body.at(i) == '\n')
		{
			cout << body.at(i); 
			for (unsigned a = 0; a < indentation; a++)
			{
				cout << "  ";
			}
		}
		else 
		{
			cout << body.at(i);
		}
	}
	cout << endl;
	for (unsigned i = 0; i < child_list.size(); i++)
	{
		dynamic_cast<Reply*>(child_list.at(i))->
			print_subtree(indentation+1);
	}
}

bool Reply::is_reply() const
{
	return true;
}

//returns string formatted as specs
string Reply::to_formatted_string() const
{
	string format;
	stringstream str_id, child_id;
	//converting id from into into string
	str_id << id;
	
	format = "<begin_reply>\n:id: " + str_id.str();
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
