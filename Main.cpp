#include <iostream>
#include "Calculation.h"

using namespace std;

int main()
{
	Calculation finder;
	cout << finder.eval_expression("7-----8") << endl;	// Will give 1
	//cout << finder.eval_expression("7----8") << endl;	// Will give an error
	cout << finder.eval_expression("--7-----8") << endl;	// Will give 0 (--7 = 6) (- -- -- 8 -> (- -- 7) -> (- 6) = 0 
	cout << finder.eval_expression("7*-8") << endl;	// Will give -56
	/*
	cout << finder.eval_expression("1+2*3") << endl;
	cout << finder.eval_expression("2+2^2*3") << endl;
	cout << finder.eval_expression("1==2") << endl;
	cout << finder.eval_expression("1+3>2") << endl;
	cout << finder.eval_expression("(4>=4)&&0") << endl;
	cout << finder.eval_expression("(1+2) * 3 ") << endl;
	cout << finder.eval_expression("++++2-5*(3^2)") << endl;
	*/
	system("pause");
	return 0;
}
