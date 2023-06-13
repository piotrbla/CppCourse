#include <iostream>
#include <string>
#include <vector>
#include "testsString.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::max;

void print_vector_with_index(const vector<string>& v)
{
	typedef vector<string>::size_type vec_size;
	vec_size size = v.size();
	for (vec_size i = 0; i < size; ++i)
	{
		cout <<"[" << (i < 10 ? " " : "") << i << "] = " << v[i] << endl;
	}
}

void testString1()
{
	string s = "Hello, world!Hello, world!Hello, world!";
	cout << s << endl;
	cout << s << " size = " << s.size() << endl;
	cout << s << " length = " << s.length() << endl;
	cout << s << " max_size = " << s.max_size() << endl;
	cout << s << " capacity = " << s.capacity() << endl;
	cout << s << " empty = " << s.empty() << endl;
	for (unsigned int i = 0; i < s.size(); ++i)
		cout << "s[" << i << "] element = " << s[i] << endl;
}

vector <string> split(const string& s)
{
	vector <string> ret;
	typedef string::size_type string_size;
	string_size i = 0;
	while (i != s.size()) {
		while (i != s.size() && isspace(s[i]))
			++i;
		string_size j = i;
		while (j != s.size() && !isspace(s[j]))
			++j;
		if (i != j) {
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}

bool space(char c)
{
	return isspace(c);
}

bool not_space(char c)
{
	return !isspace(c);
}

vector <string> split_improved(const string& s)
{
	vector <string> ret;
	auto it = s.begin();
	while (it != s.end()) {
		it = find_if(it, s.end(), not_space);
		auto j = find_if(it, s.end(), space);
		if (it != s.end())
			ret.push_back(string(it, j));
		it = j;
	}
	return ret;
}

void testString2()
{
	string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut tincidunt malesuada elit, quis pharetra sem. In vitae neque fringilla, viverra quam sit amet, fringilla augue. Sed augue nulla, bibendum eget iaculis eu, hendrerit ac augue. Etiam sagittis consectetur pretium";
	vector <string> v = split(s);
	print_vector_with_index(v);
}

void testString3()
{
	string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut tincidunt malesuada elit, quis pharetra sem. In vitae neque fringilla, viverra quam sit amet, fringilla augue. Sed augue nulla, bibendum eget iaculis eu, hendrerit ac augue. Etiam sagittis consectetur pretium";
	vector <string> v = split_improved(s);
	print_vector_with_index(v);
}

string::size_type width(const vector <string>& v)
{
	string::size_type maxlen = 0;
	for (auto it = v.begin(); it != v.end(); ++it)
		maxlen = max(maxlen, it->size());
	return maxlen;
}

vector<string> frame(const vector <string>& v)
{
	vector <string> ret;
	string::size_type maxlen = width(v);
	string border(maxlen + 4, '*');
	ret.push_back(border);
	for (auto it = v.begin(); it != v.end(); ++it) {
		ret.push_back("* " + *it + string(maxlen - it->size(), ' ') + " *");
	}
	ret.push_back(border);
	return ret;
}

void testString4()
{
	string sn = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
	vector <string> vn = split(sn);
	print_vector_with_index(vn);
	cout << "width(vn) = " << width(vn) << endl;
	vector <string> fn = frame(vn);
	print_vector_with_index(fn);
}

vector <string> vcat(const vector <string>& top, const vector <string>& bottom)
{
	vector <string> ret = top;
	//for (auto it = bottom.begin(); it != bottom.end(); ++it)
	//	ret.push_back(*it);
	ret.insert(ret.end(), bottom.begin(), bottom.end());
	return ret;
}

void testString5()
{
	string sn = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
	vector <string> vn = split(sn);
	print_vector_with_index(vn);
	cout << "width(vn) = " << width(vn) << endl;

	string si = "Ut tincidunt malesuada elit, quis pharetra sem. ";
	vector <string> vi = split_improved(si);
	print_vector_with_index(vi);
	cout << "width(vi) = " << width(vi) << endl;

	vector <string> fn = frame(vn);
	vector <string> vertical_cat = vcat(fn, vi);
	for (unsigned int i = 0; i < vertical_cat.size(); ++i)
		cout << "vertical_cat[" << i << "] = " << vertical_cat[i] << endl;
}

vector <string> hcat(const vector <string>& left, const vector <string>& right)
{
	vector <string> ret;
	string::size_type width1 = width(left) + 1;
	auto it_left = left.begin();
	auto it_right = right.begin();
	while (it_left != left.end() || it_right != right.end()) {
		string s;
		if (it_left != left.end())
			s = *it_left++;
		s += string(width1 - s.size(), ' ');
		if (it_right != right.end())
			s += *it_right++;
		ret.push_back(s);
	}
	return ret;
}

void testString6()
{
	string sn = "Lorem ipsum dolor sit. ";
	vector <string> vn = split(sn);
	print_vector_with_index(vn);
	cout << "width(vn) = " << width(vn) << endl;
	string si = "Ut tincidunt malesuada elit, quis pharetra sem. ";
	vector <string> vi = split_improved(si);
	print_vector_with_index(vi);
	cout << "width(vi) = " << width(vi) << endl;
	vector <string> fn = frame(vn);
	vector <string> horizontal_cat = hcat(fn, vi);
	print_vector_with_index(horizontal_cat);
}

void testString7()
{
	string s;
	getline(std::cin, s);
	vector <string> vn = split(s);
	print_vector_with_index(vn);
}


















void testsString()
{
	//testString1();
	//testString2();
	//testString3();
	//testString4();
	//testString5();
	//testString6();
	testString7();
}