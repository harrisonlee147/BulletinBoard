#ifndef __MESSAGE_H__
#define __MESSAGE_H__ 

#include <string>
#include <vector>

using namespace std;

class Message  // abstract base class
{
protected:  
	string author;
    string subject;
    string body;
    unsigned id; //size of the message_list vector
    vector<Message*> child_list;
    // This is how a Message is able to keep track of its Replies
 
public:
	//default constructor
	Message();
	//Parameterized constructor; id will be the size of message_list
    Message(const string& athr, const string& sbjct, const string& body, 
		    unsigned id);
	///Destructor, defined in derived classes
    //be careful here, you must invoke delete on pointers to objects
    //How many Message/Reply/Topic objects do you have in your program?
    virtual ~Message();

    virtual void print() const = 0;

    // returns true if the object is reply.
    virtual bool is_reply() const = 0;

    //returns the subject string.
    string get_subject() const;

    // returns the id.
    unsigned get_id() const;

    virtual string to_formatted_string() const = 0; //do later

    // Adds a pointer to the child to child_list. 
	void add_child(Message* child);
};

#endif
