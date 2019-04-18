#include "ArrayList.hpp"
#include <iostream>
#include <string>
int main(){
	ArrayList<int> studentid_array;
	ArrayList<std::string> studentname_array;
	int studentid;
	std::string studentname;
	for(int i = 0; i < 10; i++){
		std::cout << "Please enter your Student ID and name, (i.e., 123 Ian Xu ): " << std::endl;
		std::cin >> studentid >> studentname;
		studentid_array.add(studentid);
		studentname_array.add(studentname);
	}

	for(int i = 0; i < 10; i++){
		std::cout << studentname_array.at(i) << " ";
		std::cout << "(ID#" << studentid_array.at(i) << ")" << std::endl;
	}

	/*try{
		ArrayList<int> intclass;
		intclass.add(1);
		std::cout<<"1"<< std::endl;
		intclass.add(2);
				std::cout<<"1"<< std::endl;

		intclass.add(3);
				std::cout<<"1"<< std::endl;

		int x = intclass.at(8);
		std::cout<< x << std::endl;

	}
	catch(...){
		std::cout<<"xxx"<<std::endl;
	}*/

    return 0;
}
