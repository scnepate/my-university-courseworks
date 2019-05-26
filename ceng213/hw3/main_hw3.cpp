#include "hw3.h"

#include <iostream>
#include <iomanip>
using namespace std;

AccessControl t (4, 4);

int delUser (string username)
{
	vector <string> ok;
	int ret = t.delUser (username, ok);
	cout << ret << endl;
	if (ret)
	{
		cout << " oldPasswords: ";
		for (int i = 0; i < ok.size (); ++ i)
		{
			cout << ok[i] << (i==ok.size()-1?"\n":" ");
		}
	}
	return ret;
}

int main ()
{
	cout << "\nhw3 -- main_hw3.cpp file\n\n";

	cout << "addUser (\"Brian\", \"BriansPassword\"): " << t.addUser ("Brian", "BriansPassword") << endl;
	cout << "addUsers (\"list_of_users.txt\"): " << t.addUsers ("list_of_users.txt") << endl;

	cout << "changePass (\"Brian\", \"Briannagetsfucked\", \"BriansNewPassword\"): " << t.changePass ("Brian", "Briannagetsfucked", "BriansNewPassword") << endl;
	cout << "changePass (\"Brian\", \"BriansPassword\", \"BriansNewPassword\"): " << t.changePass ("Brian", "BriansPassword", "BriansNewPassword") << endl;
	cout << "changePass (\"Brian\", \"BriansNewPassword\", \"BriansNeeeeewPassword\"): " << t.changePass ("Brian", "BriansNewPassword", "BriansNeeeeewPassword") << endl;
	cout << "changePass (\"Brian\", \"BriansPassword\", \"BriansNewNEWNEWNEWPassword\"): " << t.changePass ("Brian", "BriansPassword", "BriansNewNEWNEWNEWPassword") << endl;
	cout << "changePass (\"Dijkstra\", \"dijkstraspassword\", \"dijkstrasNEWpassword\"): " << t.changePass ("Dijkstra", "dijkstraspassword", "dijkstrasNEWpassword") << endl;
	cout << "changePass (\"Knuth\", \"KnuthsPassword\", \"fuckingfuck\"): " << t.changePass ("Knuth", "KnuthsPassword", "fuckingfuck") << endl;

	cout << "delUser(\"Knuth): ";
	delUser ("Knuth");

	cout << "delUser(\"McFucker): ";
	delUser ("McFucker");

	cout << endl;
	t.printPasswords ();


	cout << "login (\"Brian\", \"BriansNewPassword\"): " << t.login ("Brian", "BriansNewPassword") << endl;
	cout << "login (\"Brian\", \"BriansNewNEWNEWNEWPassword\"): " << t.login ("Brian", "BriansNewNEWNEWNEWPassword") << endl;
	cout << "login (\"Brian\", \"BriansNeeeeewPassword\"): " << t.login ("Brian", "BriansNeeeeewPassword") << endl;
	cout << "login (\"Dijkstra\", \"dsadsadsadsa\"): " << t.login ("Dijkstra", "dsadsadsadsa") << endl;
	cout << "login (\"Dijkstra\", \"dijkstrasNEWpassword\"): " << t.login ("Dijkstra", "dijkstrasNEWpassword") << endl;

	cout << endl;
	t.printActiveUsers ();
	cout << endl;

	cout << "logout (\"HelloWorld\"): " << t.logout ("HelloWorld") << endl;
	cout << "logout (\"Brian\"): " << t.logout ("Brian") << endl;

	cout << endl;
	t.printActiveUsers ();
	cout << endl;

	return 0;
}