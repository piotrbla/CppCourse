/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iomanip>		//setprecision
#include <iostream>		//cout, cin
#include <ios>			//streamsize
#include <string>		//string
#include <vector>		//vector
#include <algorithm>	//sort

using std::string;
using std::endl;
using std::streamsize;
using std::cout;
using std::setprecision;
using std::vector;
using std::sort;

double grade(double midterm, double final, double homework)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

int grade(int midterm, int final, int homework)
{
	return midterm + final + homework;
}

double grade(double midterm, double final, vector <double> homework)
{
	typedef vector<double>::size_type vec_size;
	vec_size size = homework.size();
	sort(homework.begin(), homework.end());
	vec_size mid = size / 2;
	double median = size % 2 == 0
		? (homework[mid] + homework[mid - 1]) / 2
		: homework[mid];
	return 0.2 * midterm + 0.4 * final + 0.4 * median;
}

void grade_test()
{
	cout << "Test1 : " 
		<< grade(0, 0, 0) << endl;
	cout << "Test2 : " 
		<< grade(4.5, 6.0, 7.0) << endl;
	cout << "Test3 : " 
		<< grade(4.9, 5.4, 4.53) << endl;
}

void tests()
{
	grade_test();
}

int main()
{
	tests(); return 0;
	double final = 4.0;
	double midterm = 3.0;
	vector<double> grades = { 5.1, 3.2, 3.1, 4.1, 4.3, 5, 5, 4, 3, 4 };
	typedef vector<double>::size_type vec_size;
	vec_size size = grades.size();
	if (size == 0) {
		cout << endl << "You must enter your grades. "
			"Please try again." << endl;
		return 1;
	}
	streamsize prec = cout.precision();
	cout << "Your course grade is " << setprecision(3)
		<< grade(midterm, final, grades)
		<< setprecision(prec) << endl;

	final = 5.0;
	cout << "Your course grade is " << setprecision(3)
		<< grade(midterm, final, grades)
		<< setprecision(prec) << endl;

	return 0;
}

