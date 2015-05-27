/*
 * author: Alexander Edwards
 */

#include "HashTable.hpp"
#include<iostream>
#include<string.h>
#include "ParseTable.hpp"
#include "Evaluator.hpp"

bool quit(std::string str){
	return str == "quit";
}
int main(void){
	HashTable<double> symbolTable;
	std::string input;
	ParseTable parsTable;
	Evaluator evaluator(&symbolTable);

	std::cout << "\nEnter Expression\n> ";
	std::getline(std::cin, input);
	while(input!="quit"){
		std::cout << "Ans: " << evaluator.evaluatePostfix(parsTable.convertToPostfix(input)) << std::endl;
		std::cout << "Enter Expression\n> ";
		std::getline(std::cin, input);
	}



	return 0;
}
