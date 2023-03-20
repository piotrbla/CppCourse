/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iostream>
#include <string>

int main()
{
    std::cout << "Your name:" << std::endl;
    std::string name;
    std::cin >> name;
    
	const std::string greeting = "Hello, " + name + "!";

    const int pad = 1;
	int vertical_padding = pad;
    if (greeting.size() > 15)
	{
		vertical_padding = pad * 2;
	}
	int rows = pad * 2 + vertical_padding * 2 + 1;
	const int cols = greeting.size() + pad * 2 + 2;

	std::cout << std::endl;
	int r = 0; 
	while(r != rows)
	{
		int c = 0;

		while (c != cols)
		{
			if (r == pad + vertical_padding && c == pad + vertical_padding)
			{
				std::cout << greeting;
				c += greeting.size();
			}
			else
			{
				if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
					std::cout << "*";
				else
					std::cout << " ";
				++c;
			}
		}
		r++;
		std::cout << std::endl;
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
