/*
 * author: Alexander Edwards
 */

#include "ParseTable.hpp"
#include "Queue.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

Queue<std::string>* ParseTable::convertToPostfix(std::string str){
	std::string currentToken;
	std::string topOfS2;
	tokenStream.str(str);
	while(tokenStream.hasNext()){
		currentToken = tokenStream.getNextToken();
		std::cout << "TokenStream: "<< currentToken << std::endl;
		if(!stack2.isEmpty()){
			topOfS2 = stack2.showTop();
		}
		else{
			topOfS2 = "";
		}
		std::cout << "Perform Parse Action With: " << currentToken << " and " << topOfS2 << std::endl;
		performParseAction(currentToken, topOfS2);
	}
	u2();
	return &queue1;
}

void ParseTable::performParseAction(std::string inputSym, std::string topOfS2){
	if(topOfS2 == ""){
		if(!isOperator(inputSym))
			s1(inputSym);
		else
			s2(inputSym);
	}
	else if(topOfS2 == "="){
		if(!isOperator(inputSym))
				s1(inputSym);
		else if(inputSym == "="){
			err();
		}
		else if(inputSym == ")"){
			err();
		}
		else{
			s2(inputSym);
		}
	}
	else if(topOfS2 =="+" || topOfS2 == "-"){
		if(!isOperator(inputSym))
				s1(inputSym);
		else if(isFunction(inputSym)){
			s1(inputSym);
		}
		else if(inputSym=="="){
			err();
		}
		else if(inputSym=="+" || inputSym=="-" ){
			u1(inputSym);
		}
		else if(inputSym=="*" || inputSym=="/" || inputSym=="("){
			s2(inputSym);
		}
		else if(inputSym==")"){
			uc();
		}
	}
	else if(topOfS2=="*" || topOfS2 == "/"){
		if(!isOperator(inputSym))
				s1(inputSym);
		else if(isFunction(inputSym)){
			s1(inputSym);
		}
		else if(inputSym == "="){
			err();
		}
		else if(inputSym=="*" || inputSym=="/" || inputSym=="+" || inputSym=="-"){
			u1(inputSym);
		}
		else if(inputSym == "("){
			s2(inputSym);
		}
		else if(inputSym == ")"){
			uc();
		}
	}
	else if(topOfS2=="("){
		if(!isOperator(inputSym))
				s1(inputSym);
		else if(inputSym=="="){
			err();
		}
		else if(inputSym=="*" || inputSym=="/" || inputSym=="+" || inputSym=="-" || inputSym =="("){
			s2(inputSym);
		}
		else if(inputSym==")"){
			uc();
		}
	}
	else if(isFunction(topOfS2)){
		if(!isOperator(inputSym)){
			s1(inputSym);
		}
		else
			u1(inputSym);
	}
}
bool ParseTable::isOperator(std::string token){
	for(int i=0; i<sizeOfOpsArray;i++){
		if(operators[i] == token)
			return true;
	}
	return false;
}
bool ParseTable::isFunction(std::string token){
	for(int i=0; i<sizeOfFunctionsArray;i++){
		if(functions[i] == token)
			return true;
	}
	return false;
}
void ParseTable::s1(std::string input){
	queue1.enQueue(input);
}
void ParseTable::s2(std::string input){
	stack2.push(input);
}
void ParseTable::u1(std::string input){
	queue1.enQueue(stack2.pop());
	stack2.push(input);
}
void ParseTable::u2(){
	while(!stack2.isEmpty())
		queue1.enQueue(stack2.pop());
}
void ParseTable::uc(){
	std::string temp = stack2.pop();
	while(temp!="("){
		queue1.enQueue(temp);
		temp = stack2.pop();
	}
}
void ParseTable::err(){
	std::cout << "An Error occurred, input not valid" << std::endl;
	exit(EXIT_FAILURE);
}
ParseTable::~ParseTable() {
	// TODO Auto-generated destructor stub
}


ParseTable::ParseTable() {
	// TODO Auto-generated constructor stub

}
