#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */
VideoShare::VideoShare () {}
VideoShare::~VideoShare () {}

void VideoShare::createUser (const string &userName, const string &name, const string &surname )
{
	if (users.findNode (User (userName, name, surname)) == NULL)
	{
		User u (userName, name, surname);
		users.insertNode (users.getHead (), u);
	}
}

void VideoShare::loadUsers (const string &fileName)
{
	ifstream file (fileName.c_str ());
	string s;
	for (getline (file, s); !file.eof (); getline (file, s))
	{
		int f1 = s.find_first_of (';');
		int f2 = s.find_last_of  (';');
		if (f1 == 0) continue;
		createUser (s.substr (0, f1), s.substr (f1+1, f2-f1-1), s.substr (f2+1));
	}
	file.close ();
}

void VideoShare::createVideo (const string &title, const string &genre)
{
	if (videos.findNode (Video (title, genre)) == NULL)
	{
		Video v (title, genre);
		videos.insertNode (videos.getHead (), v);
	}
}

void VideoShare::loadVideos (const string &fileName)
{
	ifstream file (fileName.c_str ());
	string s;
	for (getline (file, s); !file.eof (); getline (file, s))
	{
		int f1 = s.find_first_of (';');
		if (f1 == 0) continue;
		createVideo (s.substr (0, f1), s.substr (f1+1));
	}
	file.close ();
}


void VideoShare::addFriendship (const string &userName1, const string &userName2)
{
	Node <User> *u1 = users.findNode (userName1);
	Node <User> *u2 = users.findNode (userName2);
	if (u1 && u2 && userName1 != userName2)
	{
		u1->getDataPtr ()->addFriend (u2->getDataPtr ());
		u2->getDataPtr ()->addFriend (u1->getDataPtr ());
	}
}

void VideoShare::removeFriendship (const string &userName1, const string &userName2)
{
	Node <User> *u1 = users.findNode (userName1);
	Node <User> *u2 = users.findNode (userName2);
	if (u1 && u2)
	{
		u1->getDataPtr ()->removeFriend (u2->getDataPtr ());
		u2->getDataPtr ()->removeFriend (u1->getDataPtr ());
	}
}

void VideoShare::updateUserStatus (const string &userName, Status newStatus)
{
	Node <User> *u = users.findNode (userName);
	if (u)
	{
		u->getDataPtr ()->updateStatus (newStatus);
	}
}

void VideoShare::subscribe (const string &userName, const string &VideoTitle)
{
	Node <User>  *u = users.findNode  (userName);
	Node <Video> *v = videos.findNode (VideoTitle);
	
	if (u && v && u->getDataPtr ()->getStatus () == ACTIVE)
	{
		u->getDataPtr ()->subscribe (v->getDataPtr ());
	}
}

void VideoShare::unSubscribe (const string &userName, const string &VideoTitle)
{
	Node <User>  *u = users.findNode  (userName);
	Node <Video> *v = videos.findNode (VideoTitle);

	if (u && v && u->getDataPtr ()->getStatus () == ACTIVE)
	{
		u->getDataPtr ()->unSubscribe (v->getDataPtr ());
	}
}

void VideoShare::deleteUser (const string &userName)
{
	Node <User> *nu = users.findNode (userName);
	if (nu)
	{
		User *u = nu->getDataPtr ();
		LinkedList <User*> *friends = new LinkedList <User*> (*(u->getFriends ()));
		for (Node <User*> *fr = friends->first (); fr; fr = fr->getNext ())
		{
			removeFriendship (userName, fr->getData ()->getUsername ());
		}
		users.deleteNode (users.findPrev (userName));
	}
}

void VideoShare::sortUserSubscriptions (const string &userName)
{
	Node <User> *u = users.findNode (userName);

	if (u)
	{
		bubbleSort (u->getDataPtr ()->getSubscriptions ());
	}
}

void VideoShare::printUserSubscriptions (const string &userName)
{
	Node <User> *u = users.findNode (userName);
	if (u)
	{
		u->getDataPtr ()->printSubscriptions ();
	}
}

void VideoShare::printFriendsOfUser (const string &userName)
{
	Node <User> *u = users.findNode (userName);

	if (u)
	{
		u->getDataPtr ()->printFriends ();
	}
}

void VideoShare::printCommonSubscriptions (const string &userName1, const string &userName2)
{
	Node <User> *n1 = users.findNode (userName1);
	Node <User> *n2 = users.findNode (userName2);

	if (n1 && n2)
	{
		User *u1 = n1->getDataPtr ();
		User *u2 = n2->getDataPtr ();
		LinkedList <Video*> *v1 = u1->getSubscriptions ();
		LinkedList <Video*> *v2 = u2->getSubscriptions ();

		Node <Video*> *i = v1->first ();
		Node <Video*> *j = v2->first ();

		while (i && j)
		{
			if (i->getData ()->getTitle () < j->getData ()->getTitle ())
			{
				i = i->getNext ();
			}
			else if (i->getData ()->getTitle () > j->getData ()->getTitle ())
			{
				j = j->getNext ();
			}
			else
			{
				cout << *(i->getData ());
				i = i->getNext ();
				j = j->getNext ();
			}
		}
	}
	cout << endl;
}


void VideoShare::printFriendSubscriptions (const string &username)
{
	LinkedList <Video*> *output = new LinkedList <Video*> ();
	Node <User> *nu = users.findNode (username);
	if (nu)
	{
		User *u = nu->getDataPtr ();
		for (Node <User*> *t = u->getFriends ()->getHead ()->getNext (); t; t = t->getNext ())
		{
			User *friend_user = t->getData ();
			for (Node <Video*> *k = friend_user->getSubscriptions ()->getHead ()->getNext (); k; k = k->getNext ())
			{
				if (output->findNode (k->getData ()) == NULL)
				{
					output->insertNode (output->getHead (), k->getData ());
				}
			}
		}
	}

	bubbleSort (output);
	for (Node <Video*> *t = output->getHead ()->getNext (); t; t = t->getNext ())
	{
		cout << *(t->getData ());
	}
	cout << endl;
	delete output;
}
void VideoShare::bubbleSort (LinkedList <Video*> *L)
{
	if (L)
	{
		int n = L->getLength ();
		bool sorted = false;
		for (int i = 0; i < n-1 && !sorted; ++ i)
		{
			sorted = true;
			Node <Video*> *t = L->first ();

			for (int j = 0; j < n-1-i; ++ j, t = t->getNext ())
			{
				if (t->getData ()->getTitle () > t->getNext ()->getData ()->getTitle ())
				{
					Node <Video*> *nx = t->getNext ();
					t->setNext (nx->getNext ());
					L->findPrev (t->getData ())->setNext (nx);
					nx->setNext (t);
					t = nx;
					sorted = false;
				}
			}
		}
	}
}

bool VideoShare::isConnected(const string & userName1, const string & userName2)
{
	Node <User> *nu1 = users.findNode (userName1);
	Node <User> *nu2 = users.findNode (userName2);

	if (nu1 && nu2)
	{
		User *u1 = nu1->getDataPtr ();
		User *u2 = nu2->getDataPtr ();

		LinkedList <User*> *st = new LinkedList <User*> ();
		LinkedList <string> *used = new LinkedList <string> ();
		
		st->insertNode (st->getHead (), u1);
		used->insertNode (used->getHead (), u1->getUsername ());
		while (st->getLength ())
		{
			User *u = st->first ()->getData ();
			st->deleteNode (st->getHead ());

			for (Node <User*> *v = u->getFriends ()->first (); v; v = v->getNext ())
			{
				User *to = v->getData ();

				if (to->getUsername () == userName2)
				{
					delete st; delete used;
					return true;
				}

				if (!used->findNode (to->getUsername ()))
				{
					st->insertNode (st->getHead (), to);
					used->insertNode (used->getHead (), to->getUsername ());
				}
			}
		}
		delete st; delete used;
	}
	return false;
}