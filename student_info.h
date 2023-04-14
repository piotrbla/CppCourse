#ifndef COURSE_STUDENT_INFO_H
#define COURSE_STUDENT_INFO_H

#include <iostream>
#include <string>
#include <vector>

struct Student_info
{
	std::string name;
	double midterm, final;
	std::vector<double> homework;
};

std::istream& read_hw(std::istream& in, std::vector<double>& hw);
std::istream& read_student(std::istream& input_stream, Student_info& s);
double grade(const Student_info& s);
bool compare_students(const Student_info& x, const Student_info& y);

#endif //COURSE_STUDENT_INFO_H
