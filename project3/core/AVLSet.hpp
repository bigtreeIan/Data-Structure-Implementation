// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct AVLNode{
        T data;
        int height;
        AVLNode* LeftChild;
        AVLNode* RightChild;
    };
    AVLNode* RootPtr;

    unsigned int FindSize(AVLNode* RootPtr) const;
    AVLNode* Add(AVLNode* RootPtr, const T& element);
    bool search(AVLNode* RootPtr, const T& element) const;
    void DeleteNode(AVLNode* RootPtr);
    AVLNode* CopyAll(const AVLNode* OtherRootPtr);
    int FindHeight(AVLNode* CurrentNode);
    int NeedRotation(AVLNode* CurrentNode);
    AVLNode* LL(AVLNode* RotatedNode);
    AVLNode* RR(AVLNode* RotatedNode);
   // AVLNode* LR(AVLNode* RotatedNode);
   // AVLNode* RL(AVLNode* RotatedNode);
};


template <typename T>
AVLSet<T>::AVLSet()
    :RootPtr{nullptr}
{
}

template <typename T>
AVLSet<T>::~AVLSet()
{
    DeleteNode(RootPtr);
}

template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    CopyAll(s.RootPtr);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    if(this != &s){
        DeleteNode(RootPtr);
        RootPtr = nullptr;
        RootPtr = CopyAll(s.RootPtr);
    }
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    RootPtr = Add(RootPtr, element);
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    return search(RootPtr, element);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return FindSize(RootPtr);
}


//private function:
template <typename T>

//get the size of AVLTree
unsigned int AVLSet<T>::FindSize(AVLNode* RootPtr) const{
    AVLNode* Current = RootPtr;
    if(Current == nullptr){
        return 0;
    }
    else{
        return FindSize(Current->LeftChild) + FindSize(Current->RightChild) + 1;
    }
}

//add element to AVLTree
template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::Add(AVLNode* RootPtr, const T& element){
    if(RootPtr == nullptr){
        AVLNode* NewChild = new AVLNode();
        NewChild->data = element;
        NewChild->LeftChild = nullptr;
        NewChild->RightChild = nullptr;
        return NewChild;
    }
    if(element > RootPtr->data){
        RootPtr->RightChild = Add(RootPtr->RightChild, element);
    }
    else if(element < RootPtr -> data){
        RootPtr->LeftChild = Add(RootPtr->LeftChild, element);
    }

    RootPtr->height = FindHeight(RootPtr);
    int difference = NeedRotation(RootPtr);
    if(difference < -1){
        if(NeedRotation(RootPtr->RightChild) > 0){
            RootPtr->RightChild = LL(RootPtr->RightChild);
            return RR(RootPtr);
        }
        else{
            return RR(RootPtr);
        }
    }
    else if(difference > 1){
        if(NeedRotation(RootPtr->LeftChild) > 0){
            return LL(RootPtr);
        }
        else{
            RootPtr->LeftChild = RR(RootPtr->LeftChild);
            return LL(RootPtr);
        }
    }
    RootPtr->height = FindHeight(RootPtr);
    return RootPtr;

}

//Check if the Tree is balance, if not, give corresponse rotation 
//   according to the difference between left tree and right tree
template <typename T>
int AVLSet<T>::NeedRotation(AVLNode* CurrentNode){
    int Diff = FindHeight(CurrentNode->LeftChild) - FindHeight(CurrentNode->RightChild);
    return Diff;
}

//Left left rotation
template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::LL(AVLNode* RotatedNode){
    AVLNode* CurrentNode = RotatedNode->LeftChild;
    RotatedNode->LeftChild = CurrentNode->RightChild;
    CurrentNode->RightChild = RotatedNode;
    RotatedNode->height = FindHeight(RotatedNode);
    CurrentNode->height = FindHeight(CurrentNode);
    return CurrentNode;
}

// Left Right rotation

/*
template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::LR(AVLNode* RotatedNode){
    RootPtr->LeftChild = RR(RootPtr->LeftChild);
    AVLNode* CurrentNode = RotatedNode->LeftChild;
    RotatedNode->LeftChild = CurrentNode->RightChild;
    CurrentNode->RightChild = RotatedNode;
    RotatedNode->height = FindHeight(RotatedNode);
    CurrentNode->height = FindHeight(CurrentNode);
    return CurrentNode;
}
*/

//Right Right rotation
template <typename T>    
typename AVLSet<T>::AVLNode* AVLSet<T>::RR(AVLNode* RotatedNode){
    AVLNode* CurrentNode = RotatedNode->RightChild;
    RotatedNode->RightChild = CurrentNode->LeftChild;
    CurrentNode->LeftChild = RotatedNode;
    RotatedNode->height = FindHeight(RotatedNode);
    CurrentNode->height = FindHeight(CurrentNode);
    return CurrentNode;
}

/*
//Right Left rotation
template <typename T>    
typename AVLSet<T>::AVLNode* AVLSet<T>::RL(AVLNode* RotatedNode){
    RootPtr->RightChild = LL(RootPtr->RightChild);
    AVLNode* CurrentNode = RotatedNode->RightChild;
    RotatedNode->RightChild = CurrentNode->LeftChild;
    CurrentNode->LeftChild = RotatedNode;
    RotatedNode->height = FindHeight(RotatedNode);
    CurrentNode->height = FindHeight(CurrentNode);
    return CurrentNode;
}*/

//keep tracking the height of a node
template <typename T>
int AVLSet<T>::FindHeight(AVLNode* CurrentNode){
    if(CurrentNode == nullptr){
        return -1;
    }

    int LeftHeight = 1 + FindHeight(CurrentNode->LeftChild);
    int RightHeight = 1 + FindHeight(CurrentNode->RightChild);
    if(LeftHeight > RightHeight){
        return LeftHeight;
    }
    else{
        return RightHeight;
    }
}

//search if an element is in the AVLTree
template <typename T>
bool AVLSet<T>::search(AVLNode* RootPtr, const T& element) const{
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

//Delete the node. (for destructor)
template <typename T>
void AVLSet<T>::DeleteNode(AVLNode* RootPtr){
    AVLNode* Current = RootPtr;
    if(RootPtr != nullptr){
        DeleteNode(Current->LeftChild);
        DeleteNode(Current->RightChild);
        delete RootPtr;
    }
}

//Copy a AVLTree. (for copy constructor)
template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::CopyAll(const AVLNode* OtherRootPtr){
    if(OtherRootPtr == nullptr){
        return nullptr;
    }
    AVLNode* CopyNode = new AVLNode;
    CopyNode->data = OtherRootPtr->data;
    CopyNode->RightChild = CopyAll(OtherRootPtr->RightChild);
    CopyNode->LeftChild = CopyAll(OtherRootPtr->LeftChild);
    return CopyNode;
}




#endif // AVLSET_HPP

