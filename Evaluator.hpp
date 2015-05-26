/*
 * author: Alexander Edwards
 */

#ifndef EVALUATOR_HPP_
#define EVALUATOR_HPP_
#include "Queue.hpp"
#include "Stack.hpp"
#include "HashTable.hpp"
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
	void displayPostfix();
public:
	double evaluatePostfix(Queue<std::string>* postfixQueue);
	bool isOperator(std::string);
	Evaluator();
	Evaluator(HashTable<double>* HT);
	virtual ~Evaluator();
};

#endif /* EVALUATOR_HPP_ */
