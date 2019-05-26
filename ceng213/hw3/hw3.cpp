#include "hw3.h"

#define EMPTY_PAIR (std::make_pair(EMPTY, EMPTY))
#define DELETED_PAIR (std::make_pair (DELETED, DELETED))

AccessControl::AccessControl (int table1Size, int table2Size)
{
	n_regUsers = n_activeUsers = n_oldPasswords = 0;
	regUsers.resize (table1Size, EMPTY_PAIR);
	oldPasswords.resize (table1Size, make_pair (EMPTY, std::vector <std::string> ()));
	activeUsers.resize (table2Size, EMPTY);
}

AccessControl::~AccessControl () {}

float AccessControl::printPasswords ()
{
	for (size_t i = 0; i < regUsers.size (); ++ i)
	{
		std::cout << regUsers[i].first << " " << regUsers[i].second << std::endl;
	}

	return n_regUsers*1.0/regUsers.size ();
}

float AccessControl::printActiveUsers ()
{
	for (size_t i = 0; i < activeUsers.size (); ++ i)
	{
		std::cout << activeUsers[i] << std::endl;
	}
	return n_activeUsers*1.0/activeUsers.size ();
}

std::string AccessControl::getPassword (std::string username)
{
	for (int i = 0; i < (int)oldPasswords.size (); ++ i)
	{
		int index = hashFunction (username, oldPasswords.size (), i);
		if (oldPasswords[index].first == username)
			return *oldPasswords[index].second.rbegin ();
	}
	return "";
}

int AccessControl::addOldPassword (std::string username, std::string password)
{
	for (int i = 0; i < oldPasswords.size (); ++ i)
	{
		int index = hashFunction (username, oldPasswords.size (), i);
		if (oldPasswords[index].first == username)
		{
			oldPasswords[index].second.push_back (password);
			return 1;
		}
		if (oldPasswords[index].first == EMPTY)
		{
			oldPasswords[index].first = username;
			oldPasswords[index].second.push_back (password);
			++ n_oldPasswords;
			updateSize ();
			return 1;
		}
	}

	return 0;
}

int AccessControl::addUser (std::string username, std::string pass)
{
	int tableSize = (int)regUsers.size ();
	for (int i = 0; i < tableSize; ++ i)
	{
		int index = hashFunction (username, tableSize, i);
		if (regUsers[index].first == EMPTY || regUsers[index].first == DELETED)
		{
			regUsers[index] = make_pair (username, pass);
			++ n_regUsers;
			addOldPassword (username, pass);
			updateSize ();
			return 1;
		}
		if (regUsers[index].first == username)
		{
			return 0;
		}
	}
	return 0;
}

int AccessControl::updateSize ()
{
	int ret = 0;

	if ((float)n_regUsers/regUsers.size () > MAX_LOAD_FACTOR)
	{
		std::vector <std::pair <std::string, std::string> > temp = regUsers;
		int newSize = findNextPrimeSize (regUsers.size ());
		regUsers.assign (newSize, EMPTY_PAIR);

		for (int i = 0; i < temp.size (); ++ i)
		{
			if (temp[i].first == EMPTY || temp[i].first == DELETED) continue;
			std::string username = temp[i].first;
			std::string password;

			int passIndex = -1;
			for (int j = 0; j < oldPasswords.size (); ++ j)
			{
				int index = hashFunction (username, oldPasswords.size (), j);

				if (oldPasswords[index].first == username)
				{
					passIndex = index;
					break;
				}
			}
			for (int j = 0, pi = 0; j < regUsers.size () && pi < oldPasswords[passIndex].second.size (); ++ j)
			{
				int index = hashFunction (username, regUsers.size (), j);
				// std::cout << newSize << " " << index << "\n";
				if (regUsers[index].first == username)
				{
					break;
				}
				if (regUsers[index].first == EMPTY)
				{
					password = oldPasswords[passIndex].second[pi ++];
					regUsers[index] = make_pair (username, password);
				}
			}
		}
		++ ret;
	}

	if ((float)n_activeUsers/activeUsers.size () > MAX_LOAD_FACTOR)
	{
		std::vector <std::string> temp = activeUsers;
		int newSize = findNextPrimeSize (activeUsers.size ());
		activeUsers.assign (newSize, EMPTY);
		for (int i = 0; i < temp.size (); ++ i)
		{
			if (temp[i] == EMPTY || temp[i] == DELETED) continue;

			for (int j = 0; j < activeUsers.size (); ++ j)
			{
				int index = hashFunction (temp[i], activeUsers.size (), j);
				if (activeUsers[index] == EMPTY)
				{
					activeUsers[index] = temp[i];
					break;
				}
			}
		}
		++ ret;
	}


	if ((float)n_oldPasswords/oldPasswords.size () > MAX_LOAD_FACTOR)
	{
		std::vector <std::pair <std::string, std::vector <std::string> > > temp = oldPasswords;
		int newSize = findNextPrimeSize (oldPasswords.size ());
		oldPasswords.assign (newSize, make_pair (EMPTY, std::vector <std::string> ()));

		for (int i = 0; i < temp.size (); ++ i)
		{
			if (temp[i].first == EMPTY) continue;
			std::string username = temp[i].first;

			for (int j = 0; j < oldPasswords.size (); ++ j)
			{
				int index = hashFunction (username, oldPasswords.size (), j);
				if (oldPasswords[index].first == EMPTY)
				{
					oldPasswords[index] = temp[i];
					break;
				}
			}
		}
		++ ret;
	}

	return ret;
}

int AccessControl::addUsers (std::string filePath)
{
	std::ifstream fin (filePath.c_str ());
	std::string username, password;
	int ret = 0;
	while (fin >> username >> password)
	{
		ret += addUser (username, password);
	}
	return ret;
}

int AccessControl::delUser (std::string username, std::vector<std::string>& oldPass)
{
	int ret = 0;
	for (int i = 0; i < regUsers.size (); ++ i)
	{
		int index = hashFunction (username, regUsers.size (), i);

		if (regUsers[index].first == username)
		{
			oldPass.push_back (regUsers[index].second);
			regUsers[index] = DELETED_PAIR;
			-- n_regUsers;
			ret = 1;
		}
	}

	if (ret)
	{
		for (int i = 0; i < oldPasswords.size (); ++ i)
		{
			int index = hashFunction (username, oldPasswords.size (), i);
			if (oldPasswords[index].first == username)
			{
				oldPasswords[index].first = EMPTY;
				oldPasswords[index].second.clear ();
				-- n_oldPasswords;
				break;
			}
		}
	}
	
	return ret;
}

int AccessControl::changePass (std::string username, std::string oldpass, std::string newpass)
{
	std::string pass = "";
	for (int i = 0; i < (int)regUsers.size (); ++ i)
	{
		int index = hashFunction (username, regUsers.size (), i);

		if (regUsers[index].first == username ) pass = regUsers[index].second;

		if (regUsers[index] == EMPTY_PAIR && pass == oldpass)
		{
			regUsers[index] = make_pair (username, newpass);
			++ n_regUsers;
			addOldPassword (username, newpass);
			updateSize ();
			return 1;
		}
	}
	return 0;
}

int AccessControl::login (std::string username, std::string pass)
{
	std::string real_pass = getPassword (username);
	if (pass == real_pass)
	{
		for (int i = 0; i < (int)activeUsers.size (); ++ i)
		{
			int index = hashFunction (username, activeUsers.size (), i);
			if (activeUsers[index] == username) return 0;
			if (activeUsers[index] == EMPTY || activeUsers[index] == DELETED)
			{
				activeUsers[index] = username;
				++ n_activeUsers;
				updateSize ();
				return 1;
			}
		}
	}

	return 0;
}

int AccessControl::logout (std::string username)
{
	for (int i = 0; i < activeUsers.size (); ++ i)
	{
		int index = hashFunction (username, activeUsers.size (), i);
		if (activeUsers[index] == username)
		{
			activeUsers[index] = DELETED;
			-- n_activeUsers;
			return 1;
		}
	}
	return 0;
}