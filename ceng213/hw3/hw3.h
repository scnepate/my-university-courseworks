#ifndef _HW3_H
#define _HW3_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>  // use just for std::pair< >
#include <fstream>

#define MAX_LOAD_FACTOR 0.65
#define EMPTY (std::string("EMPTY"))
#define DELETED (std::string("DELETED"))

#define which_table (a) (a)

class AccessControl
{
public:
	AccessControl(int table1Size, int table2Size);
	~AccessControl();

	int addUser(std::string username, std::string pass);
	int addUsers(std::string filePath);
	int delUser(std::string username, std::vector<std::string>& oldPasswords);
	int changePass(std::string username, std::string oldpass, std::string newpass);

	int login(std::string username, std::string pass);
	int logout(std::string username);

	float printActiveUsers();
	float printPasswords();
	// void printOldPasswords ();
private:
	std::vector <std::pair <std::string, std::string> > regUsers;
	int n_regUsers;

	std::vector <std::string> activeUsers;
	int n_activeUsers;

	std::vector <std::pair <std::string, std::vector <std::string> > > oldPasswords;
	int n_oldPasswords;

	int updateSize ();
	int addOldPassword (std::string username, std::string password);
	
	std::string getPassword (std::string username);

	int hashFunction (std::string key, int tableSize, int index)
	{
	   int length = key.length();
	   int newK = 0;
	   for (int i = 0; i < length; i++)
	     newK += (int) key[i];

		 // hash function 1 -> (newK % tableSize)
		 // hash function 2 -> (newK * tableSize - 1) % tableSize)

	   return ((newK % tableSize) + index * ((newK * tableSize - 1) % tableSize)) % tableSize;
	}

	int prime (int n)
	{
		if (!(n&1)) return 0;
		for (int i = 3; i*i <= n; i += 2)
			if (!(n%i)) return 0;
		return 1;
	}
	int findNextPrimeSize (int n)
	{
		for (n = 2*n+1; !prime (n); n += 2);
		return n;
	}
};

#endif
