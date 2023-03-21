/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iomanip>//setprecision
#include <iostream>
#include <ios> //streamsize
#include <string>

using std::cout;
using std::string;
using std::cin;

int main()
{
    cout << "Your name:\n";
    string name;
    cin >> name;
	cout << "Hello, " + name + "!";
    
	cout << "Your midterm and final exam grades:\n";
	double midterm, final;
	cin >> midterm >> final;
	cout << "Please enter all your homework grades, "
		"followed by end-of-file: \n";
    
	int count = 0;
	double sum = 0;
	
	double grade;
	
	while (cin >> grade) {
		++count;
		sum += grade;
	}
	
	std::streamsize prec = cout.precision();
	cout << "Your final grade is " << std::setprecision(3)
		<< 0.2 * midterm + 0.4 * final + 0.4 * sum / count
		<< std::setprecision(prec) << std::endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
