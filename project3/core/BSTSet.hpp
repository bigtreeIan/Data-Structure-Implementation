// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct BSTNode{
        T data;
        BSTNode* LeftChild;
        BSTNode* RightChild;
    };
    BSTNode* RootPtr;

    unsigned int FindSize(BSTNode* RootPtr) const;
    BSTNode* Add(BSTNode* RootPtr, const T& element);
    bool search(BSTNode* RootPtr, const T& element) const;
    void DeleteNode(BSTNode* RootPtr);
    BSTNode* CopyAll(const BSTNode* OtherRootPtr);

};

//constructor and public function
template <typename T>
BSTSet<T>::BSTSet()
    :RootPtr{nullptr}
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    DeleteNode(RootPtr);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    CopyAll(s.RootPtr);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if(this != &s){
        DeleteNode(RootPtr);
        RootPtr = nullptr;
        RootPtr = CopyAll(s.RootPtr);
    }
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    RootPtr = Add(RootPtr, element);
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    return search(RootPtr, element);
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return FindSize(RootPtr);
}

//private function
template<typename T>
unsigned int BSTSet<T>::FindSize(BSTNode* RootPtr) const{
    BSTNode* Current = RootPtr;
    if(Current == nullptr){
        return 0;
    }
    else{
        return FindSize(Current->LeftChild) + FindSize(Current->RightChild) + 1;
    }
}


template <typename T>
typename BSTSet<T>::BSTNode* BSTSet<T>::Add(BSTNode* RootPtr, const T& element){
    if(RootPtr == nullptr){
        BSTNode* NewChild = new BSTNode();
        NewChild->data = element;
        NewChild->LeftChild = nullptr;
        NewChild->RightChild = nullptr;
        return NewChild;
    }
    else if(element > RootPtr->data){
        RootPtr->RightChild = Add(RootPtr->RightChild, element);
    }
    else if(element < RootPtr -> data){
        RootPtr->LeftChild = Add(RootPtr->LeftChild, element);
    }
    return RootPtr;
}

template <typename T>
bool BSTSet<T>::search(BSTNode* RootPtr, const T& element) const{
    if(RootPtr == nullptr){
        return false;
    }
    if(RootPtr->data == element){
        return true;
    }
    if(element > RootPtr->data){
        return search(RootPtr->RightChild, element);
    }
    else{
        return search(RootPtr->LeftChild, element);
    }
}

template <typename T>
void BSTSet<T>::DeleteNode(BSTNode* RootPtr){
    if(RootPtr == nullptr){
        return;
    }
    if(RootPtr != nullptr){
        DeleteNode(RootPtr->LeftChild);
        DeleteNode(RootPtr->RightChild);
        delete RootPtr;
    }
}

template <typename T>
typename BSTSet<T>::BSTNode* BSTSet<T>::CopyAll(const BSTNode* OtherRootPtr){
    BSTNode* Current = OtherRootPtr;
    if(Current == nullptr){
        return nullptr;
    }
    BSTNode* CopyNode = new BSTNode;
    CopyNode->data = Current->data;
    CopyNode->RightChild = CopyAll(Current->RightChild);
    CopyNode->LeftChild = CopyAll(Current->LeftChild);
    return CopyNode;
}

#endif // BSTSET_HPP

