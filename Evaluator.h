/*
 * Evaluator.h
 *
 *  Created on: Mar 26, 2015
 *      Author: alex
 */

#ifndef EVALUATOR_H_
#define EVALUATOR_H_
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include <string>


class Evaluator {
private:
	HashTable<double>* symbolTable;
	double rhs;
	std::string lhs;
	bool symbolTableFlag;
	Stack<double> operandStack;
	int numOfOperators = 9;
	std::string Operators[9] = { "-", "+", "*", "/", "=", "SIN", "COS", "ABS", "SQRT"};
	bool isVar(std::string str);
	double valueOf(std::string in);
	bool isUndefined(std::string in);
public:
	double evaluatePostfix(Queue<std::string>* postfixQueue);
	bool isOperator(std::string);
	Evaluator();
	Evaluator(HashTable<double>* HT);
	virtual ~Evaluator();
};

#endif /* EVALUATOR_H_ */
