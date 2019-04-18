// ArrayList.hpp
//
// ICS 46 Spring 2016
// Project #0
// 
// This is a class declaration for our ArrayList class, which implements an
// array-based list of strings.  Our ArrayList has three member variables:
//
// * A pointer to a dynamically-allocated array of strings
// * An unsigned integer that keeps track of the list's size (i.e., how many
//   strings are currently stored in it)
// * Another unsigned integer that keeps track of the list's capacity (i.e.,
//   how big the current array is)
//
// It provides a modest amount of additional functionality; in a practical
// ArrayList class, we'd need more than this, but these demonstrate the most
// interesting parts of what you might realistically build.
//
// * Read values given an index
// * Assign to values given an index and a new value
// * Add a new string to the end of the list
// * Find out the list's size
// * Find out the list's capacity
//
// Our ArrayList is well-behaved, as well, which requires the Big Three,
// because we'll need to control what happens when an ArrayList is destroyed,
// copied, or assigned.

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <string>
#include <exception>
#include <iostream>

class indexoutofboundsexception: public std::exception{
public:
	indexoutofboundsexception(){
		std::cout<<"Index Out Of Bounds!!!"<<std::endl;
	}
};

template <typename ElementType>
class ArrayList
{
public:
    // Initializing an ArrayList makes it be empty and have a smallish
    // initial capacity.
    ArrayList();
//    std::cout << "ArrayList::ArrayList()" << std::endl;



    // This is the declaration for a "copy constructor".  C++ automaticaly
    // invokes this whenever an ArrayLIst object is constructed as a copy of
    // an existing one (e.g., when a ArrayList is passed by value, when a
    // ArrayList variable is defined as a copy of an existing one).
    //
    // If you don't write a copy constructor, one is generated automatically,
    // which simply does a member-by-member copy of the member variables, in
    // the order that they're declared.  In our case, that's problematic,
    // because we don't want to copy the pointer to the array of strings; we
    // want to copy the array itself, so that the new ArrayList has a separate
    // array from the original one.  So we need our own copy constructor.
    //template <typename OtherElementType>
    ArrayList(const ArrayList<ElementType>& a);


    // This is the declaration for a "destructor", recognizable because its
    // name is the name of the class preceded by a "~" character (and because
    // there is no return type).  C++ automatically invokes this just before
    // a ArrayList object dies.  After the destructor runs, the member variables
    // are themselves destroyed, in the reverse of the order they're declared
    // in the class.  But that's not enough in our case, because we don't just
    // want the pointer to the dynamically-allocated array to be destroyed;
    // we want the array itself to be destroyed.  The destructor will do that.
    ~ArrayList();


    // This is the declaration for an "assignment operator".  In general, we
    // can redefine almost any operator in the C++ language by writing
    // functions whose name are "operator@" for any operator "@" (e.g.,
    // "operator=" for assignment, "operator+" for addition, "operator[]"
    // for indexing, etc.).
    //
    // Overloading operators requires understanding their underlying behavior
    // in more detail than you might be accustomed to.  In the case of
    // assignment, it's important to understand two things:
    //
    // (1) It's possible to do an assignment without modifying the object
    //     on the right-hand side, so we declare the parameter here to be
    //     const.
    // (2) Assignment is an expression that returns a value; specifically,
    //     assignment generally returns a reference to the object on the
    //     left-hand side (which we know will be an lvalue and, thus, can
    //     have a reference pointed to it).  While we could define our
    //     particular operator overload to return something different, it's
    //     best if we overload operators so they behave like their built-in
    //     counterparts, which follows the design "principle of least
    //     surprise".
    ArrayList<ElementType>& operator=(const ArrayList<ElementType>& a);


    // Unlike the version we wrote in lecture, the at() function is declared
    // here to return a reference to an actual string stored in the vector,
    // as opposed to returning a copy.  This has two effects:
    //
    // (1) It is a performance optimization, because it avoids copying the
    //     string in order to return it.
    // (2) It means we need different versions of the function for const
    //     ArrayList than for non-const ArrayList.  If the ArrayList is const,
    //     we have to return a const reference to one of its strings, because
    //     returning a non-const reference to the string would allow us to
    //     change it; if the ArrayList is non-const, we can return a non-const
    //     reference to the string and allow it to be changed.  C++ will
    //     automatically call the appropriate overload of the at() function
    //     depending on whether we call it on a const or non-const ArrayList.
    //
    // Given that at() returns a reference, we can then use it as either an
    // lvalue or an rvalue:
    //
    //     cout << a.at(3) << endl;
    //     a.at(3) = "Boo";
    //
    // However, the latter of the two examples will only be permitted if the
    // ArrayList is non-const, because it requires the returned string reference
    // not to be const (or else we won't be allowed to assign to it).
    ElementType& at(unsigned int index);

    const ElementType& at(unsigned int index) const;


    // add() adds a new string to the end of the ArrayList.  If the underlying
    // array is full, it is replaced by a new, larger array and the capacity
    // will grow as a result.
    void add(const ElementType& s);



    // size() returns the size of the ArrayList.
    unsigned int size() const;


    // capacity() returns the capacity of the ArrayList.
    unsigned int capacity() const;


private:
    ElementType* items;
    unsigned int sz;
    unsigned int cap;
};

namespace{
	const unsigned int initialCapacity = 10;

	template <typename ElementType>
	void arrayCopy(ElementType* target, ElementType* source, unsigned int size){
		for(unsigned int i = 0; i < size; i++){
			target[i] = source[i];
		}
	}
}

template <typename ElementType>
ArrayList<ElementType>::ArrayList()
:items(new ElementType[initialCapacity]), sz(0), cap(initialCapacity){}

template <typename ElementType>
ArrayList<ElementType>::ArrayList(const ArrayList<ElementType>& a)
:items(new ElementType[a.cap]), sz(a.sz), cap(a.cap){}

template <typename ElementType>
ArrayList<ElementType>::~ArrayList(){
	delete[] items;
}

template <typename ElementType>
ArrayList<ElementType>& ArrayList<ElementType>::operator=(const ArrayList<ElementType>& a){
	if (this != &a){
		ElementType* newItems = new ElementType[a.cap];
        arrayCopy(newItems, a.items, a.sz);
        sz = a.sz;
        cap = a.cap;
        delete[] items;
        items = newItems;
    }
    return *this;
}

template <typename ElementType>
ElementType& ArrayList<ElementType>::at(unsigned int index){
	if(index < 0 or index >= sz){
		delete[] items;
		items = nullptr;
    	throw indexoutofboundsexception();
    }
    else{
    	return items[index];
    }
}

template <typename ElementType>
const ElementType& ArrayList<ElementType>::at(unsigned int index) const{
    if(index < 0 or index >= sz){
    	delete[] items;
    	items = nullptr;
    	throw indexoutofboundsexception();
    }
    else{
    	return items[index];
    }
}

template <typename ElementType>
void ArrayList<ElementType>::add(const ElementType& s){
    if (sz == cap){
    	int newCap = cap * 2 + 1;
        ElementType* newItems = new ElementType[newCap];
        arrayCopy(newItems, items, sz);

        cap = newCap;

        delete[] items;
        items = newItems;
    }
    items[sz] = s;
    sz++;
}

template <typename ElementType>
unsigned int ArrayList<ElementType>::size() const
{
    return sz;
}

template <typename ElementType>
unsigned int ArrayList<ElementType>::capacity() const
{
    return cap;
}


#endif // ARRAYLIST_HPP

