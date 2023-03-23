/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iomanip>//setprecision
#include <iostream>
#include <ios> //streamsize
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::cin;
using std::endl;
using std::streamsize;
using std::cout;
using std::setprecision;

int main2()
{
	cout << "Please enter all your homework grades, "
		"followed by end-of-file: \n";
    
	double sum = 0;
	
	std::vector<double> grades;
	double grade;
	
	while (cin >> grade) {
		grades.push_back(grade);
	}
	typedef std::vector<double>::size_type vec_size;
	vec_size size = grades.size();
	if (size == 0) {
		cout << endl << "You must enter your grades. "
			"Please try again." << endl;
		return 1;
	}
	
	std::sort(grades.begin(), grades.end());
	vec_size mid = size / 2;
	double median;
	median = size % 2 == 0 
		? (grades[mid] + grades[mid - 1]) / 2
		: grades[mid];
	streamsize prec = cout.precision();
	cout << "Your median grade is " << setprecision(3) 
		<< median << setprecision(prec) << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
