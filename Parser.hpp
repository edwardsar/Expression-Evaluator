/*
 * author: Alexander Edwards
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_
#include <string>

class Parser {
public:
	std::string getNextToken();
	//void setDelimiters();
	bool hasNext();
	void reset();
	Parser(std::string is);
	Parser();
	virtual ~Parser();
	void str(std::string str);
private:
	bool isOperator(char c);
	char getCharacter();
	int sizeOfDelimitersArray = 7;
	const char Delimiters[7] = { '-', '+', '*', '/', '(', ')', '='};
	std::string in; // input string is saved here and used for parsing
	int sPtr = 0; // used as a pointer to input string character elements

};

#endif /* PARSER_HPP_ */
