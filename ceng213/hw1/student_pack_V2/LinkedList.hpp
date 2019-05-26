#ifndef LINKEDLIST_HPP
#define	LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

#include <vector> //DELETE LATER

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head; 
    int length;  
public:

    LinkedList();
    LinkedList(const LinkedList<T>& ll);

    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data); 
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};

template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */
template <class T>
LinkedList<T> :: LinkedList ()
{
	Node<T> *tmp = new Node<T>;
	head = tmp;
	length = 0;
}
template<class T>
LinkedList<T> :: LinkedList (const LinkedList<T>& ll)
{
	*this = ll;
}
template<class T>
LinkedList<T>& LinkedList<T> :: operator= (const LinkedList<T>& ll)
{
	if (this == &ll) return *this;
	Node<T> *tmp = new Node<T>;
	head = tmp;
	length = 0;

	tmp = ll.getHead ()->getNext ();
	Node<T> *p = head;
	while (tmp)
	{
		Node<T> *t = new Node<T> (tmp->getData ());
		p->setNext (t);
		p = p->getNext ();
		tmp = tmp->getNext ();
		++ length;
	}
	return *this;
}

template<class T>
Node<T>* LinkedList<T> :: getHead() const
{
	return this->head;
}
template<class T>
Node<T>* LinkedList<T> :: first () const
{
	return head->getNext ();
}
template<class T>
Node<T>* LinkedList<T> :: findPrev (const T& d) const
{
	Node<T>* tmp = head;
	
	while (tmp->getNext ())
	{
		if (tmp->getNext ()->getData () == d)
			return tmp;
		tmp = tmp->getNext ();
	}

	return NULL;
}
template<class T>
Node<T>* LinkedList<T> :: findNode (const T& d) const
{
	Node<T>* tmp = head->getNext ();

	while (tmp)
	{
		if (tmp->getData () == d)
			return tmp;
		tmp = tmp->getNext ();
	}

	return NULL;
}

template<class T>
void LinkedList<T> :: insertNode (Node<T> *prev, const T& d)
{
	if (prev != NULL)
	{
		Node<T> *tmp = new Node<T> (d);
		tmp->setNext (prev->getNext ());
		prev->setNext (tmp);
		++ length;
	}
}

template<class T>
void LinkedList<T> :: deleteNode (Node<T> *prev)
{
	if (prev != NULL)
	{
		Node<T> *tmp = prev->getNext ();
		prev->setNext (tmp->getNext ());
		delete tmp;
		-- length;
	}
}
template<class T>
size_t LinkedList<T> :: getLength () const
{
	return this->length;
}
template<class T>
void LinkedList<T> :: clear ()
{
	while (getLength ())
	{
		deleteNode (head);
	}
}
template<class T>
void LinkedList<T> :: swap (int index1, int index2)
{
	if (!(index1 >= 0 && index1 < length) || !(index2 >= 0 && index2 < length) )
		return;
	if (index1 > index2) swap (index1, index2);
	Node<T> *n1 = first (), *n2 = first ();
	if (!n1 || !n2) return;

	while (index1 --) n1 = n1->getNext ();
	while (index2 --) n2 = n2->getNext ();

	T d1, d2;
	d1 = n1->getData ();
	d2 = n2->getData ();
	// T t = *d1;
	// *d1 = *d2;
	// *d1 = t;

	Node <T> *prev1 = findPrev (n1->getData ());
	Node <T> *prev2 = findPrev (n2->getData ());
	prev1->setNext (n2);
	prev2->setNext (n1);
	Node <T> *t = n1->getNext ();
	n1->setNext (n2->getNext ());
	n2->setNext (t);
}
template<class T>
LinkedList<T> :: ~LinkedList ()
{
	clear ();
	delete head;
}
/* end of your implementations*/
#endif	

