#include "Calculation.h"
#include <string>
#include <iostream>
#include <sstream> 
using namespace std;
int Calculation::precedence(char op) const { // Check the precedence of the operator
	switch (op) {
	case '!': case 'U': case 'D': case '-': return 8; break;		// return precedence value of 8
	case '^': return 7;	break;										// return precedence value of 7
	case '*': case '/': case '%': return 6; break;					// return precedence value of 6
	case '+': case 'S': return 5; break;							// return precedence value of 5
	case '>': case '<': case 'G': case 'L': return 4; break;		// return precedence value of 4
	case '=': return 3; break;										// return precedence value of 3
	case '&': return 2; break;										// return precedence value of 2
	case '|': return 1; break;										// return precedence value of 1
	case '(': case ')': return 0; break;							// return precedence value of 0
	}
}
void Calculation::eval(int token) { operandStack.push(token); }
void Calculation::eval(char token) {
	if (token == '(' || operatorStack.empty()) operatorStack.push(token);
	else if (precedence(token) < precedence(operatorStack.top()) || (token == ')')) {
		while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(token) <= precedence(operatorStack.top())))
			operatorEval(precedence(operatorStack.top()));
		if (token != ')') operatorStack.push(token);
		if (!operatorStack.empty() && operatorStack.top() == '(') operatorStack.pop();
	}
	else operatorStack.push(token);
}
void Calculation::clearStacks() {
	while (!operatorStack.empty()) operatorStack.pop();
	while (!operatorStack.empty()) operandStack.pop();
}
int Calculation::returnAnswer() {
	while (!operatorStack.empty()) operatorEval(precedence(operatorStack.top()));
	return operandStack.top();
}
void Calculation::operatorEval(int prec) {
	int calculation, lhs, rhs; // Declare variable
	if (prec == 8) {			// when prec value is equal to 8
		calculation = operandStack.top();		// store top of operand stack to calculation variable
		operandStack.pop();						// pop top of operand stack
		switch (prec) {
		case 8:
			if (operatorStack.top() == 'U') calculation++;		
			else if (operatorStack.top() == '!') {	
				if (calculation != 0) calculation = 0;
				else  calculation = 1;
			}
			else if (operatorStack.top() == 'D') calculation--;
			else if (operatorStack.top() == '-') calculation = calculation * -1;
			break;
		}
		operandStack.push(calculation);
		operatorStack.pop();
	}
	else {  // When precedence value is not 8
		rhs = operandStack.top();					// Store top of operand stack into rhs variable
		operandStack.pop();							// Pop top of operand stack
		lhs = operandStack.top();					// Store the next top of operand stack into lhs variable
		operandStack.pop();							// Pop top of operand stack
		switch (prec) {	// check precedence 
		case 7:	calculation = pow(lhs, rhs); break;
		case 6:
			if (operatorStack.top() == '*') calculation = lhs * rhs;
			else if (operatorStack.top() == '/') calculation = lhs / rhs;
			else if (operatorStack.top() == '%') calculation = lhs % rhs;
			break;
		case 5:
			if (operatorStack.top() == 'S') calculation = lhs - rhs;		// Check if top of operator stack equal to -
			else if (operatorStack.top() == '+') calculation = lhs + rhs;
			break;
		case 4: // When precedence value equal to 4
			if (operatorStack.top() == 'G') {					// Check if top of operator stack equal to >=
				if (lhs >= rhs) calculation = 1;						// Evaluate lhs if greater than or equal to rhs
				else calculation = 0;							// Push 0 onto operand stack if false
			}
			else if (operatorStack.top() == 'L') {					// Check if top of operator stack equal to <=
				if (lhs <= rhs)	calculation = 1;					// Evaluate lhs if less than or equal to rhs
				else calculation = 0;							// Push 0 onto operand stack if false
			}
			else if (operatorStack.top() == '>') {				// Check if top of operator stack equal to >
				if (lhs > rhs) calculation = 1;								// Evaluate lhs if greater than rhs 
				else calculation = 0;						// Push 0 onto operand stack if false
			}
			else if (operatorStack.top() == '<') {			// Check if top of operator stack equal to <
				if (lhs < rhs) calculation = 1;									// Evaluate lhs if less than rhs 
				else calculation = 0;						// Push 0 onto operand stack if false
			}
			break;
		case 3: // When precedence value equal to 3
			if (operatorStack.top() == 'N') {		// Check if top of operator stack equal to !=
				if (lhs != rhs)	calculation = 1;					// Evaluate lhs if not equal to rhs 
				else calculation = 0;
			}
			else if (operatorStack.top() == '=') {	// Check if top of operator stack equal to =
				if (lhs == rhs) calculation = 1;
				else calculation = 0;
			}
			break;
		case 2: // When precedence value equal to 2
			if (lhs && rhs)	calculation = 1;						// Check if top of operator stack equal to &
			else calculation = 0;
			break;
		case 1: // When precedence value equal to 1
			if (lhs || rhs)	calculation = 1;		
			else calculation = 0;
			break;
		case 0: break;
		}
		operandStack.push(calculation);
		operatorStack.pop();
	}
}