#include <vector>
#include <algorithm>
#include <stdexcept>
#include "median.h"
#include "grade.h"

using std::vector;
double grade(double midterm, double final, double homework)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

int grade(int midterm, int final, int homework)
{
	return midterm + final + homework;
}


double grade(double midterm, double final,
	const vector <double>& homework)
{
	typedef vector<double>::size_type vec_size;
	vec_size size = homework.size();
	if (size == 0)
		throw std::domain_error("Student has done no homework");
	return 0.2 * midterm + 0.4 * final + 0.4
		* median(homework);
}
