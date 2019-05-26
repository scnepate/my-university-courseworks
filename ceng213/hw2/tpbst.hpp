#ifndef TWOPHASEBST_H
#define TWOPHASEBST_H

#include <iostream>
#include <string>
#include <stack>
#include <list>
// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class TwoPhaseBST {
private: //do not change
    struct SecondaryNode {
        std::string key;
        T data;
        SecondaryNode *left;
        SecondaryNode *right;
        SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r);
    };

    struct PrimaryNode {
        std::string key;
        PrimaryNode *left;
        PrimaryNode *right;
        SecondaryNode *rootSecondaryNode;
        PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn);
    };

public: // do not change.
    TwoPhaseBST();
    ~TwoPhaseBST();

    TwoPhaseBST &insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data);
    TwoPhaseBST &remove(const std::string &primaryKey, const std::string &secondaryKey);
    TwoPhaseBST &print(const std::string &primaryKey = "", const std::string &secondaryKey = "");
    T *find(const std::string &primaryKey, const std::string &secondaryKey);

private: // you may add your own utility member functions here.
    void destructNode(PrimaryNode * &root);
    void destructNode(SecondaryNode * &root);

    void print (PrimaryNode *node);
    void print (SecondaryNode *node);

    PrimaryNode *findMax (PrimaryNode *node);
    SecondaryNode *findMax (SecondaryNode *node);

    SecondaryNode *findMin (SecondaryNode *node);
    SecondaryNode *findParent (std::string &key, SecondaryNode *node);

    void in_order_output (PrimaryNode *node, PrimaryNode *mmx);
    void in_order_output (SecondaryNode *node, SecondaryNode *mmx);

    void remove (const std::string &key, SecondaryNode *&node);


private: // do not change.
    PrimaryNode *root; //designated root.

    // do not provide an implementation. TwoPhaseBST's are not copiable.
    TwoPhaseBST(const TwoPhaseBST &);
    const TwoPhaseBST &operator=(const TwoPhaseBST &);
};



template <class T>
typename TwoPhaseBST<T>::PrimaryNode* TwoPhaseBST<T>::findMax (TwoPhaseBST<T>::PrimaryNode *node)
{
    if (node)
    for (; node->right; node = node->right);
    return node;
}
template <class T>
typename TwoPhaseBST<T>::SecondaryNode* TwoPhaseBST<T>::findMax (TwoPhaseBST<T>::SecondaryNode *node)
{
    if (node)
    for (; node->right; node = node->right);
    return node;
}

template <class T>
typename TwoPhaseBST<T>::SecondaryNode* TwoPhaseBST<T>::findMin (TwoPhaseBST<T>::SecondaryNode *node)
{
    if (node)
    for (; node->left; node = node->left);
    return node;
}

template <class T>
typename TwoPhaseBST<T>::SecondaryNode* TwoPhaseBST<T>::findParent (std::string &key, TwoPhaseBST<T>::SecondaryNode *node)
{
    if (!node) return NULL;
    if (key < node->key)
    {
        if (node->left)
        {
            if (node->left->key == key) return node;
            return findParent (key, node->left);
        }
    }
    else if (key > node->key)
    {
        if (node->right)
        {
            if (node->right->key == key) return node;
            return findParent (key, node->right);
        }
    }
    return NULL;
}

template <class T>
void TwoPhaseBST<T>::print (TwoPhaseBST<T>::PrimaryNode *node)
{
    std::cout << '"' << node->key << "\" : {";
    in_order_output (node->rootSecondaryNode, findMax (node->rootSecondaryNode));
    std::cout << "}";
}

template <class T>
void TwoPhaseBST<T>::print (TwoPhaseBST<T>::SecondaryNode *node)
{
    std::cout << '"' << node->key << "\" : \"" << node->data << '"';
}



template <class T>
TwoPhaseBST<T>::SecondaryNode::SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r)
        : key(k), data(d), left(l), right(r) {}

template <class T>
TwoPhaseBST<T>::PrimaryNode::PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn)
        : key(k), left(l), right(r), rootSecondaryNode(rsn) {}

template <class T>
TwoPhaseBST<T>::TwoPhaseBST() : root(NULL) {}

template <class T>
TwoPhaseBST<T>::~TwoPhaseBST() {
    destructNode(root);
}



template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data) {
    /* IMPLEMENT THIS */
    PrimaryNode *pn = root;
    if (!pn)
    {
        root = new PrimaryNode (primaryKey, NULL, NULL, new SecondaryNode (secondaryKey, data, NULL, NULL));
        pn = root;
    }
    else for (; pn; )
    {
        if (primaryKey == pn->key)
        {
            SecondaryNode *sn = pn->rootSecondaryNode;
            if (!pn->rootSecondaryNode)
            {
                pn->rootSecondaryNode = new SecondaryNode (secondaryKey, data, NULL, NULL);
                return *this;
            }
            for (; sn; )
            {
                if (secondaryKey < sn->key)
                {
                    if (sn->left) sn = sn->left;
                    else
                    {
                        sn->left = new SecondaryNode (secondaryKey, data, NULL, NULL);
                        return *this;
                    }
                }
                else
                {
                    if (sn->right) sn = sn->right;
                    else
                    {
                        sn->right = new SecondaryNode (secondaryKey, data, NULL, NULL);
                        return *this;
                    }
                }
            }
        }
        else if (primaryKey < pn->key)
        {
            if (pn->left) pn = pn->left;
            else
            {
                pn->left = new PrimaryNode (primaryKey, NULL, NULL, new SecondaryNode (secondaryKey, data, NULL, NULL));
                return *this;
            }
        }
        else
        {
            if (pn->right) pn = pn->right;
            else
            {
                pn->right = new PrimaryNode (primaryKey, NULL, NULL, new SecondaryNode (secondaryKey, data, NULL, NULL));
                return *this;
            }
        }
    }

    return *this;
}



template <class T>
void TwoPhaseBST<T>::remove (const std::string &key, SecondaryNode *&node)
{
    if (!node) return;
    if (key < node->key)
    {
        if (node->left)
        {
            if (node->left->key == key)
            {
                SecondaryNode *d = node->left;

                if (d->left && d->right)
                {
                    SecondaryNode *rightMin = findMin (d->right);
                    SecondaryNode *rightMinParent = findParent (rightMin->key, d);

                    node->left = rightMin;
                    if (rightMinParent == d) rightMinParent->right = rightMin->right;
                    else rightMinParent->left = rightMin->right;

                    rightMin->left = d->left;
                    rightMin->right = d->right;
                }
                else node->left = (d->left)?d->left:d->right;
                delete d;
            }
            else remove (key, node->left);
        }
    }
    else if (key > node->key)
    {
        if (node->right)
        {
            if (node->right->key == key)
            {
                SecondaryNode *d = node->right;

                if (d->left && d->right)
                {
                    SecondaryNode *rightMin = findMin (d->right);
                    SecondaryNode *rightMinParent = findParent (rightMin->key, d);

                    node->right = rightMin;
                    if (rightMinParent == d) rightMinParent->right = rightMin->right;
                    else rightMinParent->left = rightMin->right;

                    rightMin->left = d->left;
                    rightMin->right = d->right;
                }
                else node->right = (d->left)?d->left:d->right;
                delete d;
            }
            else remove (key, node->right);
        }
    }
}
template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::remove(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */
    PrimaryNode *pn = root;

    for (; pn; (primaryKey<pn->key?pn=pn->left:pn=pn->right))
    {
        if (primaryKey == pn->key)
        {
            if (pn->rootSecondaryNode)
            {
                if (pn->rootSecondaryNode->key == secondaryKey)
                {
                    SecondaryNode *d = pn->rootSecondaryNode;
                    if (d->left && d->right)
                    {
                        SecondaryNode *rightMin = findMin (d->right);
                        SecondaryNode *rightMinParent = findParent (rightMin->key, d);

                        pn->rootSecondaryNode = rightMin;
                        if (rightMinParent->key == d->key) rightMinParent->right = rightMin->right;
                        else rightMinParent->left = rightMin->right;

                        rightMin->left = d->left;
                        rightMin->right = d->right;
                    }
                    else
                    {
                        pn->rootSecondaryNode = (d->left)?d->left:d->right;
                    }
                    
                    delete d;
                }
                else
                {
                    remove (secondaryKey, pn->rootSecondaryNode);
                }
            }
            break;
        }
    }

    return *this;
}



template <class T>
void TwoPhaseBST<T>::in_order_output (TwoPhaseBST<T>::PrimaryNode *node, TwoPhaseBST<T>::PrimaryNode *mmx)
{
    if (!node) return;
    if (node->left) in_order_output (node->left, mmx);
    print (node);
    if (node != mmx) std::cout << ", ";
    if (node->right) in_order_output (node->right, mmx);
}
template <class T>
void TwoPhaseBST<T>::in_order_output (TwoPhaseBST<T>::SecondaryNode *node, TwoPhaseBST<T>::SecondaryNode *mmx)
{
    if (!node) return;
    if (node->left) in_order_output (node->left, mmx);
    print (node);
    if (node != mmx) std::cout << ", ";
    if (node->right) in_order_output (node->right, mmx);
}



template <class T>
TwoPhaseBST<T> &TwoPhaseBST<T>::print(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */
    if (primaryKey == "" && secondaryKey != "") return *this;
    
    std::cout << "{";

    if (primaryKey != "")
    {
        for (PrimaryNode *pn = root; pn; (primaryKey<pn->key?pn=pn->left:pn=pn->right))
            if (pn->key == primaryKey)
            {
                if (secondaryKey == "")
                    print (pn);
                else for (SecondaryNode *sn = pn->rootSecondaryNode; sn; (secondaryKey<sn->key?sn=sn->left:sn=sn->right))
                    if (sn->key == secondaryKey)
                    {
                        std::cout << "\"" << primaryKey << "\" : {";
                            print (sn);
                        std::cout << "}";
                    }
            }
    }
    else in_order_output (root, findMax (root));

    std::cout << "}\n";

    return *this;
}

template <class T>
T *TwoPhaseBST<T>::find(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */
    for (PrimaryNode *pn = root; pn; (primaryKey<pn->key?pn=pn->left:pn=pn->right))
        if (primaryKey == pn->key)
            for (SecondaryNode *sn = pn->rootSecondaryNode; sn; (secondaryKey<sn->key?sn=sn->left:sn=sn->right))
                if (secondaryKey == sn->key) return &sn->data;
    return NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::PrimaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    destructNode(root->rootSecondaryNode);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::SecondaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    delete root;

    root = NULL;
}

#endif //TWOPHASEBST_H
