#include <iostream>
#include <iomanip>

#include "./includes/plot/plot.h"
#include "./includes/token/function.h"
#include "./includes/token/operator.h"
#include "./includes/token/integer.h"
#include "./includes/token/leftparen.h"
#include "./includes/token/rightparen.h"

#include "./includes/animate/animate.h"

#include <SFML/Graphics.hpp>

using namespace std;

int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;

    animate calc;
    calc.run();
    cout << "\n\n\n=====================" << endl;
    return 0;
}
