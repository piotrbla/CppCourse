/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iostream>
#include <string>

int main()
{
	std::string greeting = "Hello World!";
	std::cout << "Your name:" << std::endl;
    std::string name;
	std::cin >> name;
    
    std::cout << "Hello, " << name << "!\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
