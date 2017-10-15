#pragma once
#include <stack>
using namespace std;
class Calculation
{
public:
	void eval(int tokenReceived);
	void eval(char tokenReceived);
	void Calculation::clearStacks();
	int returnAnswer();
private:
	int precedence(char op) const;
	void operatorEval(int prec);
	stack<int> operandStack;
	stack<char> operatorStack;
};