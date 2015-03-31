/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */
#include "HashTable.h"
#include<iostream>
#include<string.h>
#include "ParseTable.h"
#include "Evaluator.h"

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
