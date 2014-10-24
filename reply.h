// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee

// ================================================================
#ifndef __REPLY_H__
#define __REPLY_H__

#include "message.h"
using namespace std;

class Reply: public Message
{
   // no new member variables

public:
   //default constructor
   Reply();

   /* Parameterized constructor - similar to Message's constructor except:
   *  The subject should be initialized to "Re: <sbjct>" not <sbjct>.
   */
   Reply(const string& athr, const string& sbjct, const string& body, unsigned id);

   /* print the reply to screen in the given format - see output specs for details
   * Then it invokes print_subtree(n) on each of the messages in child_list 
   * (we leave it to you to figure out what n is!)
   */
   virtual void print() const;
     
   /* This function is responsible for printing the selected Reply and all of its subtree recursively
   * After printing the Reply with the given indentation and format (see output details).
   * it calls the print_subtree function of all of the Replies in its child_list(see message)
   * with incremented indentation value. 
   *
   * Note: Each indentation value represent 2 spaces. e.g. if indentation=1 the reply should be indented
   * 2 spaces, if it's 2, indent by 4 spaces. 
   */       
   virtual void print_subtree(unsigned indentation) const;
     
   virtual bool is_reply() const; 
     
   /* to_formatted_string writes the contents of the Reply to a string in the following format:
       <begin_reply>
       :id: 4
       :subject: single line
       :from: author
       :children: 5 6 [this line should not be printed if there are no children.]
       :body: multiple lines
       2nd line
       <end>
    * the line starting with :children: has the list of id's of all children (See file specs. for details)
    */
	virtual string to_formatted_string() const;
};

#endif
