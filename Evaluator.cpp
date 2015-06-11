// Author: Alexander Edwards


#include "Evaluator.hpp"
#include "List.hpp"
#include "Queue.hpp"
#include <string>
#include "HashTable.hpp"
#include <cctype>
#include <sstream>
#include <iostream>
#include <math.h>
#include <cstdlib>

double Evaluator::evaluatePostfix(Queue<std::string>* postfixQueue){
	std::string tempToken;
	double a, b;

	std::cout << "Postfix notation: ";
	while(!postfixQueue->isEmpty()){
		tempToken = postfixQueue->deQueue();
		std::cout << tempToken << " ";
		if(isVar(tempToken) && !isOperator(tempToken)  && isUndefined(tempToken)){
			lhs = tempToken;
			if(!postfixQueue->isEmpty()){
				tempToken = postfixQueue->deQueue();
				std::cout << tempToken << " ";
			}
		}

		if(!isOperator(tempToken)){

			operandStack.push(valueOf(tempToken));
		}
		else{
			if(tempToken == "+"){
				b = operandStack.pop();
				a = operandStack.pop();
				operandStack.push(a+b);
			}
			else if(tempToken == "-"){
							b = operandStack.pop();
							a = operandStack.pop();
							operandStack.push(a-b);
			}
			else if(tempToken == "*"){
							b = operandStack.pop();
							a = operandStack.pop();
							operandStack.push(a*b);
			}
			else if(tempToken == "/"){
							b = operandStack.pop();
							a = operandStack.pop();
							if(b != 0)
								operandStack.push(a/b);
							else {
								std::cout << "ERROR: Divide by zero" << std::endl;
								exit(EXIT_FAILURE);
							}
			}
			else if(tempToken == "SIN" || tempToken == "sin"){
							a = operandStack.pop();
							operandStack.push(sin(a));
			}
			else if(tempToken == "COS" || tempToken == "cos"){
							a = operandStack.pop();
							operandStack.push(cos(a));
			}
			else if(tempToken == "SQRT" || tempToken == "sqrt"){
							a = operandStack.pop();
							operandStack.push(sqrt(a));
			}
			else if(tempToken == "ABS" || tempToken == "abs"){
							a = operandStack.pop();
							operandStack.push(abs(a));
			}
			else if(tempToken == "="){
							a = operandStack.showTop();
							symbolTable->insert(lhs.c_str(),a);
			}
		}

	}
	std::cout << std::endl;
	rhs = operandStack.pop();
	return rhs;
}

double Evaluator::valueOf(std::string in){
	std::stringstream ss;
	double out;
	if(symbolTableFlag && isVar(in)){
		return *(symbolTable->getData(in.c_str()));
	}
	else{
		ss.str(in);
		ss >> out;
		ss.clear();
		return out;
	}
}

bool Evaluator::isVar(std::string str){
	return isalpha(str[0]);
}
bool Evaluator::isUndefined(std::string in){
	return !(symbolTable->search(in.c_str()));
}

bool Evaluator::isOperator(std::string str){
	for(int i=0; i < numOfOperators; i++){
		if(str == Operators[i])
			return true;
	}
	return false;
}
Evaluator::Evaluator() {
	symbolTable = nullptr;
	symbolTableFlag = false;
	rhs = 0;

}
Evaluator::Evaluator(HashTable<double>* ht){
	symbolTable = ht;
	symbolTableFlag = true;
	rhs = 0;
}

Evaluator::~Evaluator() {

}

