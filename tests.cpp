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
vector<Student_info> read_students()
{
	vector<Student_info> students;
	Student_info record;
	std::ifstream in("hw.txt");
	while (read_student(in, record))
	{
		students.push_back(record);
	}
	in.close();
	sort(students.begin(), students.end(), compare_students);
	return students;
}

string::size_type get_longest_name_length(const vector<Student_info>& students)
{
	string::size_type longest_name_length = 0;
	for (auto& student : students)
		longest_name_length = std::max(longest_name_length, student.name.size());
	return longest_name_length;
}


void read_hw_test()
{
	using std::domain_error;
	string::size_type maxlen = 0;

	vector<Student_info> students = read_students();
	maxlen = get_longest_name_length(students);
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
}

bool grade_fail(const Student_info& student)
{
	return grade(student) < 3.0;
}

vector<Student_info> extract_fails_push(vector<Student_info>& students)
{
	vector<Student_info> fail, pass;
	vector<Student_info>::size_type i = 0;
	while (i != students.size())
	{
		if (grade_fail(students[i]))
			fail.push_back(students[i]);
		else
			pass.push_back(students[i]);
		++i;
	}
	students = pass;
	return fail;
}

vector<Student_info> extract_fails_erase(vector<Student_info>& students)
{
	vector<Student_info> fail;
	vector<Student_info>::size_type i = 0;
	//vector<Student_info>::size_type size_bad = students.size();
	while (i != students.size())
	{
		if (grade_fail(students[i]))
		{
			fail.push_back(students[i]);
			students.erase(students.begin() + i);
		}
		else
			++i;
	}
	return fail;
}

vector<Student_info> extract_fails_iter(vector<Student_info>& students)
{
	vector<Student_info> fail;
	vector<Student_info>::size_type i = 0;
	vector<Student_info>::iterator iter = students.begin();
	while (iter != students.end())
	{
		if (grade_fail(*iter))
		{
			fail.push_back(*iter);
			iter = students.erase(iter);
		}
		else
			++iter;
	}
	return fail;
}

void print_all_students_with_clasification(vector<Student_info>& passed, vector<Student_info>& failed)
{
	cout << "Passed students:" << endl;
	for (const auto& student : passed)
		cout << student.name << endl;
	cout << "Failed students:" << endl;
	for (const auto& student : failed)
		cout << student.name << endl;
}

void find_fail_test_1()
{
	vector<Student_info> students = read_students();
	vector<Student_info> fail = extract_fails_push(students);
	print_all_students_with_clasification(students, fail);
}

void find_fail_test_2()
{
	vector<Student_info> students = read_students();
	vector<Student_info> fail = extract_fails_erase(students);
	print_all_students_with_clasification(students, fail);
}

void find_fail_test_3()
{
	vector<Student_info> students = read_students();
	vector<Student_info> fail = extract_fails_iter(students);
	print_all_students_with_clasification(students, fail);
}

void tests()
{
	find_fail_test_1();
	//find_fail_test_2();
	//find_fail_test_3();
	//find_fail_test_4();

	//one_person_grade_tests();
	//read_hw_test();
}
