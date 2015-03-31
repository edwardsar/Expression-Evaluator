/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */
#include "HashTable.h"
#include<iostream>
#include<string.h>
#include "Parser.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "Evaluator.h"

bool quit(std::string str){
	return str == "quit";
}
int main(void){
	HashTable<double> symbolTable;
	std::string input;
	Queue<std::string> evTest;
	Evaluator evaluator(&symbolTable);
	Parser pars;

	evTest.enQueue("A");
	evTest.enQueue("2");
	evTest.enQueue("=");

	std::cout << "ans: " << evaluator.evaluatePostfix(&evTest) << std::endl;

	evTest.enQueue("A");
	std::cout << "ans: " << evaluator.evaluatePostfix(&evTest) << std::endl;
	return 0;
}
