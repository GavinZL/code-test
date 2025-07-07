

#include <iostream>
#include <string>



int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "You entered an empty string." << std::endl;
    } else {
        std::cout << "You entered: " << input << std::endl;
    }

    return 0;
}