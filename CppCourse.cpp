/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iostream>
#include <string>

int main()
{
    std::cout << "Your name:" << std::endl;
    std::string name;
    std::cin >> name;
    
	const std::string greeting = "Hello, " + name + "!";
	const std::string spaces(greeting.size(), ' ');
	const std::string second = "* " + spaces + " *";
	const std::string first(second.size(), '*');
	
	std::cout << std::endl;
	std::cout << first << std::endl;
	std::cout << second << std::endl;
	std::cout << "* " << greeting << " *" << std::endl;
	std::cout << second << std::endl;
	std::cout << first << std::endl;
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
