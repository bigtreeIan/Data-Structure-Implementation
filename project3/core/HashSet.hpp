// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <iostream>
#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    HashFunction hashFunction;
    struct HashNode{
        T data;
        HashNode* next;
    };
    int sz;
    int cap;

    //create head as a pointer to an array of pointer(head[i], which store the location of linkedlist)
    HashNode** head;

    void Add(HashNode** head, const T& element);
    bool search(HashNode** head, const T& element) const;
    void DeleteNode(HashNode** head, int cap);
    HashNode** CopyAll(HashSet& s, int cap);
    int newhash(const T& element, int cap) const; 
};


template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    sz = 0;
    cap = DEFAULT_CAPACITY;
    head = new HashNode*[cap];
    //initialize the head pointer point to null
    for(int i = 0; i < cap; i++){
        head[i] = nullptr;
    }
}

template <typename T>
HashSet<T>::~HashSet()
{
    DeleteNode(head, cap);
}

template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
    head = CopyAll(s, s.cap);
}

template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        hashFunction = s.hashFunction;
        head = CopyAll(s, s.cap);
        DeleteNode(head, cap);
    }
    return *this;
}

template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}

template <typename T>
void HashSet<T>::add(const T& element)
{
    //before adding, check if the CURRENT!! cap is over 80%.
    int capusage = (sz + 1) / cap;
    if(capusage >= 0.8){
        //double the cap by create a new hashnode which has 2 times cap than the old one
        //add the element in the old hashnode into new hashnode
        //delete the old one;
        //copy the head and delete it
        HashNode** oldhead = CopyAll(*this, cap);
        DeleteNode(head, cap);
        //create the empty new head with 2 times cap;
        head = new HashNode* [cap * 2];
        //initialize all the pointer in head points to null
        for(int i = 0; i < cap * 2; i++){
            head[i] = nullptr;
        }
        //for the pointer who contain linkedlist, go through the list and add it to head.
        for(int i = 0; i < cap; i++){
            HashNode* templist = oldhead[i];
            while(templist != nullptr){
                Add(head, templist->data);
                templist = templist->next;
            }
        }
        DeleteNode(oldhead, cap);
        cap = cap * 2;
    }
    Add(head, element);
    sz = sz + 1;
}
    //too much memory use, test later:
    // //create a new head with two times capacity;
    // HashNode** temphead = new HashNode* [cap * 2];
    // for(int i = 0; i < cap * 2; i++){
    //     temphead[i] = nullptr;
    // }
    // for(int i = 0; i < cap; i++){
    //     HashNode* copyhead = head[i];
    //     while(copyhead != nullptr){
    //         Add(temphead, copyhead->data);
    //         copyhead = copyhead -> next;
    //     }
    // }
    // DeleteNode(head, cap);
    // head = temphead;
    // DeleteNode(temphead, cap*2);

template <typename T>
bool HashSet<T>::contains(const T& element) const
{
    return search(head, element);
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return sz;
}

//private function

//delete all the node:
template <typename T>
void HashSet<T>::DeleteNode(HashNode** head, int cap){
    for(int i = 0; i < cap; i++){
        HashNode* temphead = head[i];
        while(temphead != nullptr){
            HashNode* templist = temphead;
            temphead = temphead->next;
            delete templist;
        }
    }
    delete head;
    sz = 0;
}

//copy the Hashtable
template <typename T>
typename HashSet<T>::HashNode** HashSet<T>::CopyAll(HashSet& s, int cap){
    //create a new pointer to poniter
    HashNode** copynode = new HashNode*[cap];
    for(int i = 0; i < cap; i++){
        if(s.head[i] == nullptr){
            copynode[i] = nullptr;
    }
        if(s.head[i] != nullptr){
            copynode[i] = new HashNode;
            copynode[i]->data = s.head[i]->data;
            copynode[i]->next = nullptr;
            HashNode* temphead = s.head[i];
            HashNode* tempcopy = copynode[i];
            while(temphead->next != nullptr){
                tempcopy->next = new HashNode;
                tempcopy->next->data = temphead->next->data;
                tempcopy->next->next = nullptr;
                tempcopy = tempcopy->next;
                temphead = temphead->next;
            }
        }
    }
    sz = s.sz;
    return copynode;
}
    
//in case the index is over the cap use hash function % cap as the hashFunction.
template <typename T>
int HashSet<T>::newhash(const T& element, int cap) const{
    return hashFunction(element) % cap;
}

//add element to the hashtable based on the index compute from hash function,
//also determine if the cap is over 80%, if so double the cap automaticly;
template <typename T>
void HashSet<T>::Add(HashNode** head, const T& element){
    int index = newhash(element, cap);
    if(search(head, element) == false){
        //when the index contain no element
        if(head[index] == nullptr){
            head[index] = new HashNode;
            head[index]->data = element;
            head[index]->next = nullptr;
        }
        //when there is already a linked list pointed by the head[index]
        else{
            HashNode* newlist = head[index];
            while(newlist->next != nullptr){
                newlist = newlist->next;
            }
            newlist->next = new HashNode;
            newlist->next->data = element;
            newlist->next->next = nullptr;
        }
    }
}

template <typename T>
bool HashSet<T>::search(HashNode** head, const T& element) const{
    int index = newhash(element, cap);
    HashNode* temphead = head[index];
    while(temphead != nullptr){
        if(element == temphead->data){
            return true;
        }        
        temphead = temphead->next;
}
    return false;
}


#endif // HASHSET_HPP