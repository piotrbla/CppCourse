#include "student_info.h"
#include "grade.h"

double grade(const Student_info& s)
{
	return grade(s.midterm, s.final, s.homework);
}

std::istream& read_hw(std::istream& in, std::vector<double>& hw)
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

bool compare_students(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

bool did_all_hw(const Student_info& s)
{
	return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}