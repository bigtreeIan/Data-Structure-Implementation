#include <gtest/gtest.h>
#include "ArrayList.hpp"
#include <iostream>
#include <string>

TEST(ArrayListTests, TemplateClassCreateArrayBasedListWithSpecificElements1){

	ArrayList<int> intclass;
	std::cout << "ArrayList<int> constructed" << std::endl;
	ArrayList<double> doubleclass;
	std::cout << "ArrayList<double> constructed" << std::endl;
	ArrayList<std::string> stringclass;
	std::cout << "ArrayList<string> constructed" << std::endl;
}

TEST(ArrayListTests, TemplateClassCreateArrayBasedListWithSpecificElements2){
	ArrayList<int> arrayint;
	ArrayList<int> intclass2(arrayint);
	std::cout << "ArrayList<int> object constructed" << std::endl;
	ArrayList<double> arraydouble;
	ArrayList<double> doubleclass2(arraydouble);
	std::cout << "ArrayList<double> object constructed" << std::endl;
	ArrayList<std::string> arraystring;
	ArrayList<std::string> stringclass2(arraystring);
	std::cout << "ArrayList<string> object constructed" << std::endl;
}

TEST(ArrayListTests, ATMemberFunctionThrowExceptionWhenIndexOutOfBound){
	ArrayList<int> intclass;
	intclass.add(1);
	intclass.add(2);
	intclass.add(3);
	//ASSERT_NO_THROW(intclass.at(3));
	ASSERT_THROW({intclass.at(5);}, indexoutofboundsexception);
}