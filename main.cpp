// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee
// Login id: <hlee088>
// email address: <hlee088@ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <023>
// TA: Mike Izbicki
//
// Assignment: <assn6>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// ================================================================

#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "message.h"
#include "bboard.h"
#include "topic.h"
#include "reply.h"

using namespace std;

int main(int argc, char** argv)
{  
	if(argc != 3){
		cout << "ERROR: Invalid program call."<< endl
		<< "Usage: <program_name> userfile datafile"<< endl;
		return -1;
	}
	string userfile(argv[1]);
	string datafile(argv[2]);

	Bboard bb("CS12 Bulletin Board");

	// load users from file
	if( !bb.load_users(userfile) )
	{
	 cout << "ERROR: Cannot load users from "<< userfile << endl;
	 return -1;
	}

	// load messages   
	if( !bb.load_messages(datafile) )
	{
	 cout << "ERROR: Cannot load messages from "<< datafile << endl;
	 return -1;
	}
	
	//bb.run(); //user shouldn't be able to access menu
	bb.login();
	bb.run();

	// save messages
	if( !bb.save_messages(datafile) )
	{
	 cout << "ERROR: Cannot save messages to "<< datafile << endl;
	 return -1;
	}
	
	return 0;
} 
