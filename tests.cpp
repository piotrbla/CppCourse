#include <iomanip>		//setprecision
#include <iostream>		//cout, cin
#include <ios>			//streamsize
#include <string>		//string
#include <vector>		//vector
#include <list>			//list
#include <algorithm>	//sort
#include <chrono>		//chrono	
#include <numeric>		//accumulate

#include <fstream>
#include "median.h"
#include "grade.h"
#include "student_info.h"
#include <stdexcept>

using std::string;
using std::endl;
using std::streamsize;
using std::cout;
using std::setprecision;
using std::vector;
//using std::list;
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

uint64_t get_time_count()
{
	using namespace std::chrono;
	return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
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
	vector<Student_info>::const_iterator it = students.begin();
	while (it != students.end())
	{
		if (grade_fail(*it))
		{
			fail.push_back(*it);
			it = students.erase(it);
		}
		else
			++it;
	}
	return fail;
}

std::list <Student_info> extract_fails_iter(std::list<Student_info>& students)
{
	std::list<Student_info> fail;
	std::list<Student_info>::const_iterator it = students.begin();
	while (it != students.end())
	{
		if (grade_fail(*it))
		{
			fail.push_back(*it);
			it = students.erase(it);
		}
		else
			++it;
	}
	return fail;
}

void print_all_students_with_clasification(const vector<Student_info>& passed,
	const vector<Student_info>& failed)
{
	cout << "Passed students:" << endl;
	for (const auto& student : passed)
		cout << student.name << endl;
	cout << "Failed students:" << endl;
	for (const auto& student : failed)
		cout << student.name << endl;
	for (vector<Student_info>::const_iterator it = failed.begin(); it != failed.end(); ++it)
		cout << it->name << " " << it->final << endl;
}

void print_all_students_with_clasification(const std::list<Student_info>& passed,
	const std::list<Student_info>& failed)
{
	cout << "Passed students:" << endl;
	for (const auto& student : passed)
		cout << student.name << endl;
	cout << "Failed students:" << endl;
	for (const auto& student : failed)
		cout << student.name << endl;
	for (std::list<Student_info>::const_iterator it = failed.begin(); it != failed.end(); ++it)
		cout << it->name << " " << it->final << endl;
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
	uint64_t start = get_time_count();	
	vector<Student_info> fail = extract_fails_iter(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " vector basic" << endl;
	//print_all_students_with_clasification(students, fail);
}

void find_fail_test_list()
{
	vector<Student_info> students_vector = read_students();
	std::list<Student_info> students;
	std::copy(students_vector.begin(), students_vector.end(), std::back_inserter(students));
	std::list<Student_info> fail = extract_fails_iter(students);
	print_all_students_with_clasification(students, fail);
}

void find_fail_test_list_1()
{
	vector<Student_info> students_vector = read_students();
	std::list<Student_info> students;
	std::copy(
		students_vector.begin(), 
		students_vector.end(), 
		std::back_inserter(students)
	);
	std::list<Student_info> fail = extract_fails_iter(students);
	print_all_students_with_clasification(students, fail);
}

void find_fail_test_list_2()
{
	vector<Student_info> students_vector = read_students();
	std::list<Student_info> students;
	students.insert(
		students.begin(),
		students_vector.begin(),
		students_vector.end()
	);
	std::list<Student_info> fail = extract_fails_iter(students);
	print_all_students_with_clasification(students, fail);
}

void find_fail_test_list_3()
{
	vector<Student_info> students_vector = read_students();
	std::list<Student_info> students(
		students_vector.begin(),
		students_vector.end()
	);
	std::list<Student_info> fail = extract_fails_iter(students);
	print_all_students_with_clasification(students, fail);
}

void find_fail_test_list_4()
{
	vector<Student_info> students_vector = read_students();
	std::list<Student_info> students;
	students.assign(
		students_vector.begin(),
		students_vector.end()
	);
	uint64_t start = get_time_count();
	std::list<Student_info> fail = extract_fails_iter(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " list 1" << endl;
	//print_all_students_with_clasification(students, fail);
}

void find_fail_test_list_5()
{
	vector<Student_info> students_vector = read_students();
	std::list<Student_info> students;
	for (const auto& student : students_vector)
		students.push_back(student);
	uint64_t start = get_time_count();
	std::list<Student_info> fail = extract_fails_iter(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " list 2" << endl;
	//print_all_students_with_clasification(students, fail);
}

void find_did_all_hw_test()
{
	vector<Student_info> students_vector = read_students();
	vector<Student_info> did, didnt;
	std::list<Student_info> students;
	for (const auto& student : students_vector)
	{
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}
	if (did.empty())
	{
		cout << "No student did all homework!" << endl;
		return;
	}
	if (didnt.empty())
	{
		cout << "Every student did all homework!" << endl;
		return;
	}
}

double grade_aux(const Student_info& s)
{
	try
	{
		return grade(s);
	}
	catch (std::domain_error)
	{
		return grade(s.midterm, s.final, 0.0);
	}
}
double median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
	return median(grades);
}

void write_analysis(std::ostream& out, const string& name, 
	double analysis(const vector<Student_info>&),
	const vector<Student_info>& did,
	const vector<Student_info>& didnt)
{
	out << name << ": median (did) = " << analysis(did)
		<< "  median (didnt) = " << analysis(didnt)
		<< endl;
}

double average(const vector<double>& v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info& s)
{
	return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), average_grade);
	return median(grades);
}

double optimistic_median(const Student_info& s)
{
	vector<double> nonzero;
	remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);
	if (nonzero.empty())
		return grade(s.midterm, s.final, 0.0);
	else
		return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);
	return median(grades);
}

void analysis_test()
{
	vector<Student_info> students_vector = read_students();
	vector<Student_info> did, didnt;
	std::list<Student_info> students;
	for (const auto& student : students_vector)
	{
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}
	if (did.empty())
	{
		cout << "No student did all homework!" << endl;
		return;
	}
	if (didnt.empty())
	{
		cout << "Every student did all homework!" << endl;
		return;
	}
	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

}

bool pgrade(const Student_info& s)
{
	return !grade_fail(s);
}

std::vector <Student_info> extract_fails_eraser(std::vector<Student_info>& students)
{
	vector<Student_info> fail;
	std::remove_copy_if(students.begin(), students.end(),
		back_inserter(fail), pgrade);
	students.erase(
		remove_if(students.begin(), students.end(), grade_fail), 
		students.end());
	return fail;
}


void find_fail_test_new_1()
{
	vector<Student_info> students = read_students();
	uint64_t start = get_time_count();
	vector<Student_info> fail = extract_fails_eraser(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " eraser" << endl;
	//print_all_students_with_clasification(students, fail);
}

std::vector <Student_info> extract_fails_partition(std::vector<Student_info>& students)
{
	vector<Student_info>::iterator iter =
		std::stable_partition(students.begin(), students.end(), pgrade);
	vector<Student_info> fail(iter, students.end());
	students.erase(
		iter,
		students.end());
	return fail;
}

void find_fail_test_new_2()
{
	vector<Student_info> students = read_students();
	uint64_t start = get_time_count();
	std::vector<Student_info> fail = extract_fails_partition(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " partition" << endl;
	//print_all_students_with_clasification(students, fail);
}

bool one_function_grade(const Student_info& s)
{
	return grade(s) >= 3.0;
}

std::vector <Student_info> extract_fails_partition_predicate(std::vector<Student_info>& students)
{
	vector<Student_info>::iterator iter =
		std::stable_partition(students.begin(), students.end(), one_function_grade);
	vector<Student_info> fail(iter, students.end());
	students.erase(
		iter,
		students.end());
	return fail;
}
void find_fail_test_new_3()
{
	vector<Student_info> students = read_students();
	uint64_t start = get_time_count();
	std::vector<Student_info> fail = extract_fails_partition_predicate(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " predicate" << endl;;
	//print_all_students_with_clasification(students, fail);
}

std::vector <Student_info> extract_fails_partition_no_fun_predicate(std::vector<Student_info>& students)
{
	vector<Student_info>::iterator iter =
		std::stable_partition(students.begin(), students.end(), [](Student_info& n) {return grade(n) >= 3.0; });
	vector<Student_info> fail(iter, students.end());
	students.erase(
		iter,
		students.end());
	return fail;
}
void find_fail_test_new_4()
{
	vector<Student_info> students = read_students();
	uint64_t start = get_time_count();
	std::vector<Student_info> fail = extract_fails_partition_no_fun_predicate(students);
	uint64_t end = get_time_count();
	cout << "Time: " << end - start << " no_fun_predicate" << endl;
	//print_all_students_with_clasification(students, fail);
}

void tests()
{
	//find_fail_test_1();
	//find_fail_test_2();
	find_fail_test_3();//
	//find_fail_test_list();
	//find_fail_test_list_1();
	//find_fail_test_list_2();
	//find_fail_test_list_3();
	find_fail_test_list_4();//
	find_fail_test_list_5();//
	//find_did_all_hw_test();
	//analysis_test();
	find_fail_test_new_1();
	find_fail_test_new_2();
	find_fail_test_new_3();
	find_fail_test_new_4();


	//one_person_grade_tests();
	//read_hw_test();
}
