// Course: CS 12 <Winter 2013>
//
// First Name: Harrison
// Last Name: Lee

// ================================================================
#include "user.h"
#include "message.h"
#include "bboard.h"
#include "topic.h"
#include "reply.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

//default constructor that creates a board with a default title, 
//empty user & message lists, and the "default" User
Bboard::Bboard()
: title("Jack's Amazing Bulletin Board"), current_user(0)
{
}


//same as default c'tor, except that it sets the title of the board.
Bboard::Bboard(const string& ttl)
: title(ttl), current_user(0)
{
}

//Deconstructor
Bboard::~Bboard()
{
	for (unsigned i = 0; i < message_list.size(); i++)
	{
		delete message_list.at(i);
	}
}

//In this assignment, we'll read the users info (username and password) 
//from a file rather than from standard input ("cin") and 
//redirection from terminal.
//This function gets a name/path (userfile) of a file that stores the 
//user info in the given format (See Input File Format Specs). It opens 
//and reads the file and fills the user_list vector.
//If there is an error while opening the file, the function should 
//return false, otherwise return true.
//Hint: The file format is same as before, you can simply use the 
//ifstream object instead of "cin".
bool Bboard::load_users(const string& userfile)
{
	ifstream fin;
	fin.open(userfile.c_str());
	//checks if file is open
	if (!fin.is_open())
	{
		return false;
	}
	
	string uname;
	string pass;
	
	// reading in list of users/passwords
	fin >> uname;
	while(fin.good() && uname != "end")
	{
		fin >> pass;
		User username(uname, pass);
		user_list.push_back(username);
		fin >> uname;
	}
	fin.close();
	return true;
}

//This function gets a name/path (datafile) of a file that stores the 
//messages (from previous sessions) in the given format (See File Format 
//Specs). It opens and reads a file and fills the message_list vector. 
//If an error occurs when opening the file, it returns false. 
//Returns true otherwise.
bool Bboard::load_messages(const string& datafile)
{
	  vector<vector<int> > children;
	  unsigned size, id, child_id;
      string temp, subj, author, body, tag, child_string;
      ifstream fin (datafile.c_str());
      
      fin >> size;
      
    while (fin.good())
    {
        fin >> temp;
        body = "";
        
        if (temp == "<begin_topic>")
        {
            children.push_back(vector <int> ());
            fin >> tag;     
            while (tag != ":body:")
            {
                if(tag == ":id:")
                {
                    fin >> id;
                }
                else if (tag == ":subject:")
                {
                    fin.ignore();
                    getline (fin,subj);
                }  
                else if (tag == ":from:")    
                {
                    fin >> author; 
                  
                } 
                else if (tag == ":children:")
                {
                    fin.ignore();
                    getline (fin, child_string);
                    stringstream convert (child_string);
                    while (convert >> child_id)
                    {
						children.at(children.size()-1).
						push_back(child_id-1);
                    }
                }
                fin >> tag;
            }
            
            if (tag == ":body:") // body found
            {
                fin.ignore();// remove \n
                getline (fin, temp); // get body
                while (temp != "<end>")
                {
                    body += temp + "\n";
                    getline (fin, temp); // get next line
                }
            }
            //adding topic into message_list vector
            Message* new_top = new Topic (author, subj, body, id);
            message_list.push_back(new_top);
        }
    
        else if (temp == "<begin_reply>")
        {
            children.push_back(vector <int> ()); 

            fin >> tag;    
            while (tag != ":body:")
            {
                if(tag == ":id:")
                {
                    fin >> id; 
                }
                else if (tag == ":subject:")
                {
                    fin.ignore();
                    getline (fin,subj);
                }  
                else if (tag == ":from:")    
                {
                    fin >> author;
                } 
                else if (tag == ":children:")
                {
                    fin.ignore();
                    getline (fin, child_string);
                    stringstream convert (child_string);
                    //changing string to ints
                    while (convert >> child_id)
                    {
                       children.at(children.size()-1).
                       push_back(child_id-1);
                    }
                }
                
                fin >> tag;
            }
            
            if (tag == ":body:") // body found
            {
                fin.ignore();// remove \n
                getline (fin, temp); // get body
                while (temp != "<end>")
                {
                    body+= temp + "\n";
                    getline (fin, temp); // get next line
                }
            }
            //Adding reply into message_list vector
            Message* new_rep = new Reply (author, subj.substr(4), 
										  body, id);
            message_list.push_back(new_rep);
        }
    }
    
    //adding child to message_list elements
	unsigned x = 0;
	
    for (unsigned a = 0; a < message_list.size(); a++)
    {
        for (unsigned b = 0; b < children.at(a).size(); b++)
        {
			//children is vec keeping track of replies
            x = children.at(a).at(b);
            message_list.at(a)->add_child(message_list.at(x));
        }
        
    }
    
    fin.close();
    
    return true;
}

//This function gets a name/path (datafile) of a file that will store 
//all of the the messages, and after opening the file writes the messages 
//into it with the same format (See File Format Specs). If an error 
//occurs when opening the file, it returns false. Returns true otherwise
bool Bboard::save_messages(const string& datafile)
{
	ofstream fout (datafile.c_str());
	
	//checks if file is open
	if (!fout.is_open())
	{
		return false;
	}
	else
	{
		fout << message_list.size() << endl;
		//going through message_list vector
		for (unsigned i = 0; i < message_list.size(); i++)
		{
			//converting into txt format and outputting on txt file
			fout << message_list.at(i)->to_formatted_string();
		}
		
		fout.close();
		return true;
	}
}


//asks for and validates current user/password
//This function asks for a username and password, and checks the 
//user_list vector for a matching User.
//If a match found, it sets current_user to the identified User from 
//the list (remember, current_user is now a pointer, not an actual 
//object). If not found, it will keep asking until a match is found or 
//the user types: 'q' or 'Q' as the username.
//You may assume we do not have a member with name 'q' or 'Q'. When the 
//user chooses to quit, say "Bye!" and just exit the login function.
//See the output specifications for details.
void Bboard::login()
{
	string name;
	string pass;

	//title of bulletin board
	cout << "Welcome to " << title << endl;
	// user inputs username
	cout << "Enter your username ('Q' or 'q' to quit): ";
	cin >> name;
	
	// If user wants to quit
	if (name == "q" || name == "Q")
	{
		cout << "Bye!" << endl;
		exit(0);
	}
	
	// user inputs password
	cout << "Enter your password: ";
	cin >> pass;
	
	if (NULL != get_user(name, pass))
	{
		// changes current_user to user if info correct
		current_user = get_user(name, pass);
	}
	
	// if invalid, asks again
	else
	{
		cout << "Invalid Username or Password!" << endl << endl;
		
		// user inputs username
		cout << "Enter your username ('Q' or 'q' to quit): ";
		cin >> name;
		
		// If user wants to quit
		if (name == "q" || name == "Q")
		{
			cout << "Bye!" << endl;
			exit(0);
		}
		
		// user inputs password
		cout << "Enter your password: ";
		cin >> pass;
		
		if (NULL != get_user(name, pass))
		{
			// changes current_user to user if info correct
			current_user = get_user(name, pass);
		}
	
		while (NULL == get_user(name, pass))
		{
			cout << "Invalid Username or Password!" << endl << endl;
		
			// user inputs username
			cout << "Enter your username ('Q' or 'q' to quit): ";
			cin >> name;
			
			// If user wants to quit
			if (name == "q" || name == "Q")
			{
				cout << "Bye!" << endl;
				exit(0);
			}
			
			// user inputs password
			cout << "Enter your password: ";
			cin >> pass;
			
			if (NULL != get_user(name, pass))
			{
				// changes current_user to user if info correct
				current_user = get_user(name, pass);
			}
		}
	}
	
	cout << "Welcome back " << name << "!" << endl << endl;
}

//In the main loop, you should display the following menu items:
//"Display Messages ('D' or 'd'), "Add New Message('N' or 'n')", and 
//"Quit ('Q' or 'q')".
//If the user selects one of these menu items, the corresponding method 
//of Bboard should be invoked; with any other input, 
//the user should be asked to try again.
//'Q'/'q' should terminate the program by invoking exit(0)
void Bboard::run()
{
	string action;
	
	///If current_user == NULL, call exit(0);
	if (current_user == NULL)
	{
		cout << "Not logged in, aborting...\n";
		exit(0);
	}
	///User's logged in, can access menu
	// Menu interface
	cout << "Menu" << endl;
	cout << "\t- Display Messages ('D' or 'd')" << endl;
	cout << "\t- Add New Topic ('N' or 'n')" << endl;
	cout << "\t- Add Reply to a Topic ('R' or 'r')" << endl;
    cout << "\t- Quit ('Q' or 'q')" << endl;
    cout << "\tChoose an action: ";
    cin >> action;
    cout << endl;
    
    while (action != "Q" || action != "q")
    {
		// Display messages
		if (action == "D" || action == "d")
		{
			display();
		}
		// new message
		else if (action == "N" || action == "n")
		{
			add_topic();
		}
		else if (action == "R" || action == "r")
		{
			add_reply();
		}
		// ends program
		else if (action == "Q" || action == "q")
		{
			cout << "Bye!\n";
			return;
		}
		
		// Menu interface
		cout << "Menu" << endl;
		cout << "\t- Display Messages ('D' or 'd')" << endl;
		cout << "\t- Add New Message ('N' or 'n')" << endl;
		cout << "\t- Add Reply to a Topic ('R' or 'r')" << endl;
		cout << "\t- Quit ('Q' or 'q')" << endl;
		cout << "\tChoose an action: ";
		cin >> action;
		cout << endl;
	}	
	
	// ends program
	if (action == "Q" || action == "q")
	{
		cout << "Bye!\n";
		return;
	}
}

/// Private member functions
//Checks if the username/password combination matches any of the Users 
//in the user_list.
//Returns true if a match is found, false otherwise. For login function
/*bool Bboard::user_exists(const string& name, const string& pass)
{
	bool exist = false;
	
	// checking if the user exists throug user_list
	for (unsigned i = 0; i < user_list.size(); i++)
	{
		exist = (user_list.at(i)).check(name, pass);
		if (exist)
		{
			return exist;
		}
	}
	return exist;
}*/

//This function now includes the functionality of the old "user_exists" 
//helper: It traverses the user_list, testing for the existence of a 
//user with the given name and password; if this user is NOT found, the 
//function returns NULL; otherwise it returns a pointer to the identified 
//User (the statement return &user_list.at(i) will work - 
//make sure you understand why!!) This function may be used by login() 
//to set the current_user (which is now, obviously, a pointer, not an 
//object). There must be no other way to set current_user to anything 
//other than NULL.
const User* Bboard::get_user(const string& name, const string& pw) const
{
	for (unsigned i = 0; i < user_list.size(); i++)
	{
		if (user_list.at(i).check(name, pw))
		{
			return &user_list.at(i);
		}
	}
	
	//if no user exists in user_list
	return NULL;
}

//This function would be used by the interface function run. 
//It asks the user to input a message. Every message includes a subject 
//line and a message line 
//    Subject: "Thanks"
//    Body: "I would like to thank you for this awesome board."
void Bboard::add_topic()
{
	string author;
	string subject;
	string body, temp;
	
	author = current_user->get_username();
	
	cout << "Enter Subject: ";
	cin.ignore();
	getline(cin, subject);
	//reading in body from user
	cout << "Enter Body: ";
	getline(cin, temp);
	while (temp.length() > 0)
	{
		body += temp + "\n";
		getline(cin, temp);
	}
	
	Message* topic = new Topic(author, subject, body, 
							   message_list.size()+1);
	
	cout << "Message recorded!" << endl << endl;
	
	message_list.push_back(topic);
}

//This function will traverse the Bboard's message list, and invoke the 
//print function on Topic objects ONLY. //It will then be the 
//responsibility of the Topic object to invoke the print function 
//recursively on its own replies. The Bboard dislay function will 
//ignore all Reply objects in its message list. 
void Bboard::display() const
{
	if (message_list.size() < 1)
	{
		cout << "Nothing to Display.";
		cout << endl << endl;
	}
	else
	{
		cout << "-----------------------------------------------";
		cout << endl;
		
		
		//going through message_list vector and printing out messages
		for (unsigned int i = 0; i < message_list.size(); i++)
		{
			//printing out topics only (topic's print prints replies)
			if (!message_list.at(i)->is_reply())
			{
				message_list.at(i)->print();
				cout << "----------------------------------";
				cout << "-------------";
				cout << endl;
			}
		}
	}
}

//The add_reply function first asks the user for the id of the Message 
//(which may be either a Topic or a Reply) to which they are replying; 
//if the number given greater than the size of message_list it should 
//output an error message and loop back, continuing to ask for a valid 
//Message id number until the user enters either -1 (or any negative 
//number, to return to the menu) or a valid id. If the id is valid, then 
//the function asks for the body of the new message, and constructs the 
//Reply, pushing back a pointer to it on the message_list.The subject of
//the Reply is a copy of the parent Topic's subject with the "Re: " prefix. 
void Bboard::add_reply() 
{
	int mess_id;
	
	cout << "\tEnter Message ID (-1 for Menu): ";
	cin >> mess_id;
		
	//if mess_id == -1, do menu
	if (mess_id == -1)
	{
		return;
	}
	// adding reply
	else if (static_cast<unsigned>(mess_id) <= message_list.size())
	{
		string author, subject, body, temp;
		//getting author
		author = current_user->get_username();
		//making subject Re: Subject name of topic being replied to
		subject = message_list.at(mess_id-1)->get_subject();
		//asking for body, user inputs body
		cout << "\tEnter Body: ";
		cin.ignore();
		getline(cin, temp);
		while (temp.length() > 0)
		{
			body += temp + "\n";
			getline(cin, temp);
		}
		
		//adding child to message being replied to	
		Message* topic = new Reply(author, subject, body, 
								   message_list.size()+1);
		message_list.push_back(topic);
		//updating child_list		   
		message_list.at(mess_id-1)->
			add_child(message_list.at(message_list.size()-1));
		
		cout << "Message recorded!" << endl << endl;
		
		
	}
	//id is invalid, asks user to re-enter id 
	else if (static_cast<unsigned>(mess_id) > message_list.size())
	{
		cout << "\tInvalid Message ID!!\n";
		add_reply();
	}
}

