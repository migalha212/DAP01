#include "CLInterface.h"

void presentUI() {
    system("cls"); // clears the terminal
    std::string introduction = "Welcome to the Command Line Interface\nThis is just a demo\n\nEnter anything to close the program!";
    std::cout << introduction;
    int a;
    std::cin >> a;
}
