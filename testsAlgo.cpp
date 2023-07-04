#include "testsAlgo.h"
#include "testsString.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::max;
using std::isspace;
using std::find_if;

vector <string> vertical_cat(const vector <string>& top, const vector <string>& bottom)
{
	vector <string> ret = top;
	//for (auto it = bottom.begin(); it != bottom.end(); ++it)
	//	ret.push_back(*it);
	//ret.insert(ret.end(), bottom.begin(), bottom.end());
	copy(bottom.begin(), bottom.end(), back_inserter(ret));
	return ret;
}

void test_algo_1()
{
	string sn = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
	vector <string> vn = split(sn);
	print_vector_with_index(vn);

	string si = "Ut tincidunt malesuada elit, quis pharetra sem. ";
	vector <string> vi = split(si);
	print_vector_with_index(vi);

	vector <string> fn = frame(vn);
	vector <string> result = vertical_cat(fn, vi);
	for (unsigned int i = 0; i < result.size(); ++i)
		cout << result[i] << endl;
}

vector<string> split_new(const string& s)
{
	typedef string::const_iterator iter;
	vector <string> ret;
	iter it = s.begin();
	while (it != s.end()) {
		it = find_if(it, s.end(), not_space);
		iter j = find_if(it, s.end(), space);
		if (it != s.end())
			ret.push_back(string(it, j));
		it = j;
	}
	return ret;
}

void test_algo_2()
{
	string sn = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
	vector <string> vn = split_new(sn);
	print_vector_with_index(vn);
}

bool is_palindrome(const string& s)
{
	return equal(
	 s.begin(), 
	 s.end(), 
	 s.rbegin()
	);
}

void test_algo_3()
{
	cout << is_palindrome("palindrome") << endl;
	cout << is_palindrome("radar") << endl;
	cout << is_palindrome("racecar") << endl;
	cout << is_palindrome("a") << endl;
	
}

bool not_url_char(char c)
{
	static const string url_ch = "~;/?:@=&$-_.+!*'(),";
	return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
	static const string sep = "://";
	typedef string::const_iterator iter;
	iter i = b;
	while ((i = search(i, e, sep.begin(), sep.end())) != e) {
		if (i != b && i + sep.size() != e) {
			iter beg = i;
			while (beg != b && isalpha(beg[-1]))
				--beg;
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}
		i += sep.size();
	}
	return e;
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
	return find_if(b, e, not_url_char);
}

vector<string> find_urls(const string& s)
{
	vector <string> ret;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();
	while (b != e) {
		b = url_beg(b, e);
		if (b != e) {
			iter after = url_end(b, e);
			ret.push_back(string(b, after));
			b = after;
		}
	}
	return ret;
}

void test_algo_4()
{	
	vector<string> urls = find_urls("http://adres1.com http://adres2.com http://adres3.com");
	for (unsigned int i = 0; i < urls.size(); ++i)
		cout << urls[i] << endl;
	cout << endl;
	urls = find_urls("ftp://adres1.com ftp:/adres2.com http://adres3.com");
	for (unsigned int i = 0; i < urls.size(); ++i)
		cout << urls[i] << endl;

}

void test_algo_accumulate()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6};
	int sum = std::accumulate(v.begin(), v.end(), 0);
	cout << sum << endl;
}

void test_algo_find()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6};
	auto it_found = std::find(
		v.begin(), 
		v.end(), 
		5);
	if (it_found != v.end())
		cout << *it_found << endl;
	else
		cout << "not found" << endl;
	auto it_not_found = std::find(
		v.begin(), 
		v.end(), 
		15);
	if (it_not_found != v.end())
		cout << *it_not_found << endl;
	else
		cout << "not found" << endl;
}

void test_algo_find_if()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6 };
	auto it_found = std::find_if(
		v.begin(),
		v.end(),
		[](int i) { 
			return i % 2 == 0; 
		});
	
	while(it_found != v.end())
	{
		cout << *it_found << endl;
		it_found += 1;
		it_found = std::find_if(
			it_found,
			v.end(),
			[](int i) {
				return i % 2 == 0;
			});
	}
}
void test_algo_search()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6 };
	vector <int> v2 = { 3, 4, 5 };
	auto it_found = std::search(
		v.begin(),
		v.end(),
		v2.begin(),
		v2.end());
	if (it_found != v.end())
		cout << *it_found << endl;
	else
		cout << "not found" << endl;
}

void test_algo_copy()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6 };
	vector <int> v2(v.size());
	std::copy(
		v.begin(),
		v.end(),
		v2.begin());
	for (auto i : v2)
		cout << i << endl;
}

void tests_algo()
{
	//test_algo_1();
	//test_algo_2();
	//test_algo_3();
	//test_algo_4();
	//test_algo_accumulate();
	//test_algo_find();
	//test_algo_find_if();
	test_algo_search();
}
