#include "arithmetic_expression.h"

#include <gtest.h>

TEST(TArithmeticExpression, Correct_Calculate)
{
    string str = "(9 + 8*2) * (90/15 - 2)";
    vector <TArithmeticExpression> pol = Obrat_Polska(str);
    EXPECT_EQ(Calculate(pol), (9 + 8 * 2) * (90 / 15 - 2));
}

