
#include "library.h"

#include <stdio.h>
#include <string>

#define FUNC "=========="

std::string str = R"(
A,
B,
C,
$FUNC,
D
)";

// int main()
// {

//     // cam::A a;
//     // a.show();

//     printf("%s\n", str.c_str());

//     return 0;

// }


#include <iostream>

#define MACRO R"(
    world
    )"

int main() {
    std::string str = R"(Hello,!)" MACRO R"( wonder)";
    std::cout << str << std::endl;
    return 0;
}