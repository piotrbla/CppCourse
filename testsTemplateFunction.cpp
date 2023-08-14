#include "testsTemplateFunction.h"
#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

double demo_abs_f(double value)
{
	return value < 0 ? -value : value;
}

int demo_abs_i(int value)
{
	return value < 0 ? -value : value;
}

void test_template_function_old_c()
{
	cout << demo_abs_f(6.1) << endl;
	cout << demo_abs_f(-3.1) << endl;
	cout << demo_abs_i(5) << endl;
	cout << demo_abs_i(-3) << endl;
	cout << endl;
}

double demo_abs(double value)
{
	return value < 0 ? -value : value;
}

int demo_abs(int value)
{
	return value < 0 ? -value : value;
}

void test_template_function_old_cpp()
{
	cout << demo_abs(6.1) << endl;
	cout << demo_abs(-3.1) << endl;
	cout << demo_abs(5) << endl;
	cout << demo_abs(-3) << endl;
	cout << endl;
}

template <class T>
T demo_abs_template(T value)
{
	return value < 0 ? -value : value;
}

void test_template_function_new_cpp()
{
	cout << demo_abs_template<double>(6.1) << endl;
	cout << demo_abs_template<double>(-3.1) << endl;
	cout << demo_abs_template<int>(5) << endl;
	cout << demo_abs_template<int>(-3) << endl;
	cout << endl;
}

template <class T>
T median(vector<T> vec)
{
	typedef typename vector<T>::size_type vec_size;
	vec_size size = vec.size();
	if (size == 0)
		throw std::domain_error("median of an empty vector");
	std::sort(vec.begin(), vec.end());
	vec_size mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

void test_template_median()
{
	vector<int> v1 = { 1, 2, 3, 4, 5 };
	vector<double> v2 = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	cout << median(v1) << endl;
	cout << median(v2) << endl;
}

void tests_template_function()
{
	//test_template_function_old_c();
	//test_template_function_old_cpp();
	//test_template_function_new_cpp();
	//test_template_median();
}
