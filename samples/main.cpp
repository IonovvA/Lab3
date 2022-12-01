#include "arithmetic_expression.h"

#include <iostream>
using namespace std;

int main() 
{
    string str = "(26 * 6 + 10 * 5 - 6) / 20";
    cout << "Example: " << str << endl;
    vector <TArithmeticExpression> pol;
    try
    {
        pol = Obrat_Polska(str);
    }
    catch (exception ex)
    {
        cout << ex.what();
        return 0;
    }
    cout << "Reverse Polish notation: " << endl;
    for (int i = 0; i < pol.size(); i++) 
    {
        cout << pol[i];
    }
    cout << "Answer: " << Calculate(pol) << endl;
    return 0;
}
