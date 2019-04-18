// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <algorithm>
#include <string>
#include <iostream>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{

	return words.contains(word);
}

std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
	//create a vector of suggestion word and a vector of letters from A-Z
	std::vector<std::string> suggestion;
	std::vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	//std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//1. swap
	for(int i = 0; i < word.size(); i++){
		std::string temp = word;
		std::swap(temp[i], temp[i + 1]);
		//std::cout << "swap: " << temp << std::endl; 
		if(wordExists(temp) == true 
			and std::find(suggestion.begin(), suggestion.end(), temp) == suggestion.end()){
			suggestion.push_back(temp);
			//std::cout << "swap found: " << temp << std::endl;
		}
		temp = word;
	}

	//2. insert
	for(int i = 0; i < word.size(); i++){
		std::string temp = word;
		for(int j = 0; j < alphabet.size(); j++){
			temp.insert(i, 1, alphabet[j]);
			//std::cout << "insert: " << temp << std::endl; 
			if(wordExists(temp) == true
				and std::find(suggestion.begin(), suggestion.end(), temp) == suggestion.end()){
				suggestion.push_back(temp);
				//std::cout << "insert found: " << temp << std::endl; 
			}
			temp = word;
		}
	}

	//3. delete
	for(int i = 0; i < word.size(); i++){
		std::string temp = word;
		temp.erase(i, 1);
		if(wordExists(temp) == true
			and std::find(suggestion.begin(), suggestion.end(), temp) == suggestion.end()){
			suggestion.push_back(temp);
		}
		temp = word;
	}

	//4. replace
	for(int i = 0; i < word.size(); i++){
		std::string temp = word;
		for(int j = 0; j < alphabet.size(); j++){
			//temp.replace(i, i+1, alphabet[j]);
			temp[i] = alphabet[j];
			if(wordExists(temp) == true
				and std::find(suggestion.begin(), suggestion.end(), temp) == suggestion.end()){
				suggestion.push_back(temp);
			}
		}
		temp = word;
	}

	//5. split
	for(int i = 0; i < word.size(); i++){
		std::string temp = word;
		temp.insert(i, 1, ' ');
		//std::cout << "after split: " << temp << std::endl;
		std::string first_word;
		std::string second_word;
		int stop_pos = temp.find(' ');
		first_word = temp.substr(0, stop_pos);
		second_word = temp.substr(stop_pos + 1);
		if(wordExists(first_word) == true 
			and wordExists(second_word) == true
			and std::find(suggestion.begin(), suggestion.end(), first_word) == suggestion.end()
			and std::find(suggestion.begin(), suggestion.end(), second_word) == suggestion.end()){
			suggestion.push_back(temp);
		}
		temp = word;
	}
	return suggestion;
}
