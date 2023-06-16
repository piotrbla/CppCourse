#ifndef COURSE_TESTS_STRING_H
#define COURSE_TESTS_STRING_H
#include <string>
#include <vector>

void testsString();
std::vector <std::string> split(const std::string& s);
std::vector<std::string> frame(const std::vector <std::string>& v);
void print_vector_with_index(const std::vector<std::string>& v);
bool space(char c);
bool not_space(char c);
#endif //COURSE_TESTS_STRING_H
