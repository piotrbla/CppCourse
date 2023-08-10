/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iomanip>		//setprecision
#include <iostream>		//cout, cin
#include <ios>			//streamsize
#include <string>		//string
#include <vector>		//vector
#include "median.h"
#include "grade.h"
#include "student_info.h"
#include "tests.h"
#include "testsString.h"
#include "testsAlgo.h"
#include "testsAssociative.h"

using std::string;
using std::endl;
using std::streamsize;
using std::cout;
using std::setprecision;
using std::vector;

void grades_test()
{
	double final = 4.0;
	double midterm = 3.0;
	vector<double> grades = { 5.1, 3.2, 3.1, 4.1, 4.3, 5, 5, 4, 3, 4 };
	typedef vector<double>::size_type vec_size;
	vec_size size = grades.size();
	if (size == 0) {
		cout << endl << "You must enter your grades. "
			"Please try again." << endl;
		return;
	}
	streamsize prec = cout.precision();
	cout << "Your course grade is " << setprecision(3)
		<< grade(midterm, final, grades)
		<< setprecision(prec) << endl;

	final = 5.0;
	cout << "Your course grade is " << setprecision(3)
		<< grade(midterm, final, grades)
		<< setprecision(prec) << endl;
}

int main()
{
	//tests_associative(); return 0;
	//grades_test(); return 0;
	tests_algo(); return 0;
	//tests_string(); return 0;
	//tests(); return 0;
	return 0;
}

