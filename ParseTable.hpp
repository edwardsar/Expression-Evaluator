/*
 * author: Alexander Edwards
 */

#ifndef PARSETABLE_H_
#define PARSETABLE_H_
#include "Stack.hpp"
#include "Queue.hpp"
#include <string>
#include "Parser.hpp"

class ParseTable {
private:
	Queue<std::string> queue1;
	Stack<std::string> stack2;
	std::string input;
	Parser tokenStream;
	void performParseAction(std::string inputSym, std::string topOfS2);
	int sizeOfOpsArray = 11;
	std::string operators[11]={ "-", "+", "*", "/", "(", ")", "="};
	int sizeOfFunctionsArray = 4;
	std::string functions[4] = {"SIN", "COS", "ABS", "SQRT"};
	bool isOperator(std::string token);
	bool isFunction(std::string token);
	void s1(std::string input);
	void s2(std::string input);
	void u1(std::string input);
	void u2();
	void uc();
	void err();
public:
	Queue<std::string>* convertToPostfix(std::string str);
	ParseTable();
	virtual ~ParseTable();
};

#endif /* PARSETABLE_H_ */
