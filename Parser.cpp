/*
 * author: Alexander Edwards
 */

#include "Parser.hpp"
#include <string>
#include <iostream>

std::string Parser::getNextToken(){
	char c;
	std::string temp = "";
	c = getCharacter();
	if(isOperator(c)){
		return temp + c;
	}
	do{
		if(isOperator(c)){
			sPtr--;
			break;
		}
		temp = temp + c;
		c = getCharacter();
	}while(sPtr <= in.size());
	return temp;
}
void Parser::reset(){
	sPtr = 0;
}
void Parser::str(std::string str){
	in = str;
	reset();
}
bool Parser::isOperator(char c){
	for(int i=0; i<sizeOfDelimitersArray; i++){
		if(c==Delimiters[i])
			return true;
	}
	return false;
}

bool Parser::hasNext(){
	return sPtr < in.size();
}
char Parser::getCharacter(){
	while(in[sPtr] == ' '){
		sPtr++;
	}
	char temp = in[sPtr];
	sPtr++;
	return temp;

}
Parser::Parser(std::string is) {
	in = is;
}
Parser::Parser(){

}
Parser::~Parser() {
	// TODO Auto-generated destructor stub
}
