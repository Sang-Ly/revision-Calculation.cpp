#include <iostream>
#include "Calculation.h"
#include "parser.h"
using namespace std;
int main() {
	Parser eval;
	cout << eval.eval_expression("(--7)-----8") << endl;
	cout << eval.eval_expression("1+2*3") << endl;
	cout << eval.eval_expression("1") << endl;
	cout << eval.eval_expression("2+2^2*3") << endl;
	cout << eval.eval_expression("1==2") << endl;
	cout << eval.eval_expression("1+3>2") << endl;
	cout << eval.eval_expression("(4>=4)&&0") << endl;
	cout << eval.eval_expression("(1+2) * 3 ") << endl;
	cout << eval.eval_expression("++++2-5*(3^2)") << endl;
	cout << eval.eval_expression("--7----8") << endl;
	cout << eval.eval_expression("(3*(6+(3+2+5+(6+2))))") << endl;
	cout << eval.eval_expression("10 +++  3") << endl;
	cout << eval.eval_expression("!!!3+1") << endl;
	cout << eval.eval_expression("(3^5)") << endl;
	//cout << eval.eval_expression("3 |||| 3") << endl;
	//cout << eval.eval_expression("10 / 0") << endl;
	//cout << eval.eval_expression("!/1") << endl;
	return 0;
}