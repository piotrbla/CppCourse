#include <iomanip>		//setprecision
#include <iostream>		//cout, cin
#include <ios>			//streamsize
#include <string>		//string
#include <vector>		//vector
#include <algorithm>	//sort
#include <fstream>
#include "median.h"
#include "grade.h"
#include "student_info.h"

using std::string;
using std::endl;
using std::streamsize;
using std::cout;
using std::setprecision;
using std::vector;
using std::sort;

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
			<< grade(4.9, 5.4, empty_grades) << setprecision(prec) << endl;
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
	sort(students.begin(), students.end(), compare_students);

	for (auto& student : students)
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
