/* CppCourse.cpp : This file contains the 'main' function.Program execution begins and ends there. */

#include <iomanip>		//setprecision
#include <iostream>		//cout, cin
#include <ios>			//streamsize
#include <string>		//string
#include <vector>		//vector
#include <algorithm>	//sort
#include <fstream>

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

double median(vector<double> vec)
{
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();
	if (size == 0)
		throw std::domain_error("median of an empty vector");
	sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, 
	const vector <double> &homework)
{
	typedef vector<double>::size_type vec_size;
	vec_size size = homework.size();
	if (size == 0)
		throw std::domain_error("Student has done no homework");
	return 0.2 * midterm + 0.4 * final + 0.4 
		* median(homework);
}

void good_precision_test()
{
	cout << setprecision(3);
	vector<double> empty_grades = {};
	try
	{
		streamsize prec = cout.precision();
		double final_grade = grade(4.9, 5.4, empty_grades);
		cout << "Test6 : " << setprecision(5)
			<< final_grade << setprecision(prec) << endl;
	}
	catch (std::domain_error e)
	{
		cout << e.what() << endl;
	}
	cout << "Test7 : " << 4.951245 << endl;
}

void bad_precision_test()
{
	cout << setprecision(3);
	vector<double> empty_grades = {};
	try
	{
		streamsize prec = cout.precision();
		cout << "Test4 : " << setprecision(5) 
			<< grade(4.9, 5.4, empty_grades) <<  setprecision(prec) << endl;
	}
	catch (std::domain_error e)
	{
		cout << e.what() << endl;
	}
	cout << "Test5 : " << 4.951245 << endl;
}

void one_person_grade_tests()
{
	cout << "Test1 : "
		<< grade(0, 0, 0) << endl;
	cout << "Test2 : "
		<< grade(4.5, 6.0, 7.0) << endl;
	cout << "Test3 : "
		<< grade(4.9, 5.4, 4.53) << endl;
	bad_precision_test();
	good_precision_test();
}

struct Student_info
{
	string name;
	double midterm, final;
	vector<double> homework;
};

std::istream& read_hw(std::istream& in, vector<double>& hw)
{
	if (in)
	{
		hw.clear();
		double x;
		while (in >> x)
			hw.push_back(x);
		in.clear();
	}
	return in;
}

std::istream& read_student(std::istream& input_stream, Student_info& s)
{
	input_stream >> s.name >> s.midterm >> s.final;
	read_hw(input_stream, s.homework);
	return input_stream;
}

double grade(const Student_info& s)
{
	return grade(s.midterm, s.final, s.homework);
}

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

void read_hw_test()
{
	using std::domain_error;
	std::ifstream in("hw.txt");
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;
	while (read_student(in, record))
	{
		maxlen = std::max(maxlen, record.name.size());
		students.push_back(record);
	}
	sort(students.begin(), students.end(), compare);

	for(auto &student:students)
	{
		cout << student.name << string(maxlen + 1 - student.name.size(), ' ');
		try
		{
			double final_grade = grade(student);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec) << endl;
		}
		catch (domain_error e)
		{
			cout << e.what() << endl;
		}
	}

	
	for (vector<Student_info>::size_type i = 0;
		i != students.size(); 
		++i)
	{
		cout << students[i].name << string(maxlen + 1 - students[i].name.size(), ' ');
		try
		{
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec) << endl;
		}
		catch (domain_error e)
		{
			cout << e.what() << endl;
		}
	}
	in.close();
}

void tests()
{
	//one_person_grade_tests();
	read_hw_test();
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

