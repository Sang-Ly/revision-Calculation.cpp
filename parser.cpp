#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
const string Parser::OPERATORS = "UD-!^/*%S+GL<>N=&|()";
bool Parser::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}
int Parser::eval_expression(const string& expression) {
	calculator.clearStacks();
	errorCheck(expression);
	char token;
	string converted = convertString(expression);
	istringstream stream(converted);
	while (stream >> token) {
		if (isdigit(token)) {
			stream.putback(token);
			int value;
			stream >> value;
			calculator.eval(value);
		}
		else calculator.eval(token);
	}
	return calculator.returnAnswer();
}
void Parser::processOperator(char op, string& converted) {
	if ((converted.back() == ')' || !is_operator(converted.back())) && op == '-') converted += 'S';
	else if (converted.back() == '-' && op == '-') converted.back() = 'D';
	else if (converted.back() == '+' && op == '+' && (converted.size() <= 2 || (converted[converted.size() - 2] == '+' || converted[converted.size() - 2] == 'U')))
		converted.back() = 'U';
	else if (converted.back() == '<' && op == '=') converted.back() = 'L';
	else if (converted.back() == '>' && op == '=') converted.back() = 'G';
	else if (converted.back() == '!' && op == '=') converted.back() = 'N';
	else if (converted.back() == '=' && op == '=') converted.back() = '=';
	else if (converted.back() == '&' && op == '&') converted.back() = '&';
	else if (converted.back() == '|' && op == '|') converted.back() = '|';
	else converted += op;
}
void Parser::errorCheck(string expression) {
	bool operandBefore = false;
	int charCount = 0;
	string temp, unaryOP = "UD-!", binaryOP = "/*%S+GL<>N=&|", singleCharBinaryOP = "/*%S+<>";
	try {
		for (int k = 0; k < expression.size(); k++) {
			charCount++;
			if (isdigit(expression[k])) operandBefore = true;
			if (is_operator(expression[k])) operandBefore = false;
			if (operandBefore == true && expression[k] == ' ' && isdigit(expression[k + 1]))
				throw std::exception("Two operands in a row @ char: ");
			if (!isblank(expression[k])) temp += expression[k];
		}
		expression.swap(temp);
		charCount = 0;
		for (int j = 0; j < expression.size(); j++) {
			charCount++;
			if (!isdigit(expression[j]) && !is_operator(expression[j]))
				throw std::exception("Invalid Entry @ char: ");
			if (j >= 1) {			
				if (expression[j] == '/' && expression[j + 1] == '0')
					throw std::exception("Division by zero @ char: ");
				if (expression[j] == '&' && (expression[j + 1] != '&' && expression[j - 1] != '&'))
					throw std::exception("Only one & operator @ char: ");
				if (expression[j] == '|' && (expression[j + 1] != '|' && expression[j - 1] != '|'))
					throw std::exception("Only one | operator @ char: ");
				if (expression[j] == '&' && (expression[j + 1] == '&' && expression[j - 1] == '&')){
					charCount++;
					throw std::exception("Two binary operands at @ char: ");
				}
				if (expression[j] == '|' && (expression[j + 1] == '|' && expression[j - 1] == '|')) {
					charCount++;
					throw std::exception("Two binary operands at @ char: ");
				}
			}
		}
		expression = convertString(expression);
		charCount = 1;
		if (binaryOP.find(expression[0]) != string::npos)
			throw std::exception("Expression can't start with a binary operator @ char : ");
		if (expression[0] == ')')
			throw std::exception("Expression can't start with a closed parenthesis @ char: ");
		for (int x = 0; x < expression.size(); x++){
			if (isdigit(expression[x]) || singleCharBinaryOP.find(expression[x] != string::npos)) charCount++;
			else charCount += 2;
			if (binaryOP.find(expression[x]) != string::npos && binaryOP.find(expression[x + 1]) != string::npos)
				throw std::exception("Two binary operators in a row @ char : ");
			if (unaryOP.find(expression[x]) != string::npos && binaryOP.find(expression[x + 1]) != string::npos) {
				throw std::exception("A unary operand can't be followed by a binary operator @ char ");
			}
		}
	}catch (exception e) {
		cout << e.what() << charCount << endl;
		exit(0);
	}
}
string Parser::convertString(string expression) {
	string converted = "";
	for (int k = 0; k < expression.size(); k++) {
		if (converted.empty())
			converted = expression[k];
		else if (!is_operator(expression[k]) && expression[k] != ' ')
			converted += expression[k];
		else if (is_operator(expression[k]))
			processOperator(expression[k], converted);
	}
	return converted;
}