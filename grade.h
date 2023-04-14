#ifndef COURSE_GRADE_H
#define COURSE_GRADE_H

#include <vector>

double grade(double, double, double);

int grade(int, int, int);

double grade(double midterm, double final,
	const std::vector <double>& homework);

#endif	/* COURSE_GRADE_H */