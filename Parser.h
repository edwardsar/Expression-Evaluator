/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <iostream>

class Parser {
public:
	std::string getNextToken();
	//void setDelimiters();
	bool isNext();
	char getCharacter();
	bool isOperator(char c);
	Parser(std::string is);
	virtual ~Parser();
private:
	int sizeOfDelimitersArray = 7;
	const char Delimiters[7] = { '-', '+', '*', '/', '(', ')', '='};
	std::string in; // input string is saved here and used for parsing
	int sPtr = 0; // used as a pointer to input string character elements

};

#endif /* PARSER_H_ */
