#pragma once
#include "Calculation.h"
class Parser
{
public: int eval_expression(const string& expression);
private:
	Calculation calculator;				// Declare Calculation object
	bool is_operator(char ch) const;	// Check if character matches with operator
	static const string OPERATORS;		// Declare string operators
	void processOperator(char op, string & converted);
	string convertString(string expression);
	void errorCheck(string expression);		// Check if encounter an error
};