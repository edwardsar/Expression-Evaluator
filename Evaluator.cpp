/*
 * author: Alexander Edwards
 */

#include "Evaluator.hpp"
#include "List.hpp"
#include "Queue.hpp"
#include <string>
#include "HashTable.hpp"
#include <cctype>
#include <sstream>
#include <iostream>
#include <math.h>

double Evaluator::evaluatePostfix(Queue<std::string>* postfixQueue){
	std::string tempToken;
	double a, b;


	while(!postfixQueue->isEmpty()){
		tempToken = postfixQueue->deQueue();


		if(isVar(tempToken) && !isOperator(tempToken)  && isUndefined(tempToken)){
			lhs = tempToken;
			if(!postfixQueue->isEmpty())
				tempToken = postfixQueue->deQueue();
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
			}
			else if(tempToken == "SIN"){
							a = operandStack.pop();
							operandStack.push(sin(a));
			}
			else if(tempToken == "COS"){
							a = operandStack.pop();
							operandStack.push(cos(a));
			}
			else if(tempToken == "SQRT"){
							a = operandStack.pop();
							operandStack.push(sqrt(a));
			}
			else if(tempToken == "ABS"){
							a = operandStack.pop();
							operandStack.push(abs(a));
			}
			else if(tempToken == "="){
							a = operandStack.showTop();
							std::cout << "setting " << lhs << " to " << a << std::endl;
							symbolTable->insert(lhs.c_str(),a);
			}
		}

	}
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
