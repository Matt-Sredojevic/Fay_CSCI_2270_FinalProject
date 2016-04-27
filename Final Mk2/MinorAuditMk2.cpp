#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "AuditGraph.h"

using namespace std;

AuditGraph * AUDIT = new AuditGraph;

int main()
{
	cout << "==================================================="	<< endl;
	cout << "      COMPUTER SCIENCE MINOR PROGRESS CHECKER"			<< endl;
	cout << "                      made for"						<< endl;
	cout << "           University of Colorado, Boulder"			<< endl;
	cout << "___________________________________________________"	<< endl;
	cout << ""														<< endl;
	cout << "            A final project for CSCI 2270"				<< endl;
	cout << "                    By Justin Fay"						<< endl;
	cout << "==================================================="	<< endl;
	cout << ""														<< endl;
	AUDIT->readMinor();
	AUDIT->readElective();
	int menu;
	while(menu!=7)
	{
		cout << "============MENU============"	<< endl;
		cout << "1: List all classes"			<< endl;
		cout << "2: List completed classes"		<< endl;
		cout << "3: List electives"				<< endl;
		cout << "4: Show requisites"			<< endl;
		cout << "5: Add a completed class"		<< endl;
		cout << "6: Remaining requirements"		<< endl;
		cout << "7: End audit"					<< endl;
		cout << "============================"  << endl;
		cout <<	endl;
		cin >> menu;
		if(menu==1)
		{
			AUDIT->listAll();
		}
		else if(menu==2)
		{
			AUDIT->listComplete();
		}
		else if(menu==3)
		{

		}
		else if(menu==4)
		{
			string find, prefix;
			int number;
			cout << "Enter class prefix and number (Ex: \"CSCI 2270\"):" << endl;
			cin.ignore();
			getline(cin, find);
			stringstream ss(find);
			ss >> prefix;
			ss >> number;
			AUDIT->showReq(prefix, number);
		}
		else if(menu==5)
		{
			string add, prefix;
			int number;
			cout << "Enter class prefix and number (Ex: \"CSCI 2270\"):" << endl;
			cin.ignore();
			getline(cin, add);
			stringstream ss(add);
			ss >> prefix;
			ss >> number;
			if(number!=0)
			{
				AUDIT->addComplete(prefix, number);
			}
			else
			{
				cout << "please enter a valid class" << endl;
			}
		}
		else if(menu==6)
		{
			AUDIT->remaining();
		}
		else if(menu==7)
		{
			delete AUDIT;
			return 0;
		}
	}
}
