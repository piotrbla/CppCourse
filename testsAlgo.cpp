#include "testsAlgo.h"
#include "testsString.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <ranges>

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
	vector <double> v = { 
		1, 2, 3, 4, 5, 6
	};
	double sum = std::accumulate(
		v.begin(), 
		v.end(), 
		0.1);
	cout << sum << endl;
}

void test_algo_find()
{
	vector <int> v = 
	{ 1, 15, 2, 3, 4, 5, 6};
	auto it_found = std::find(
		v.begin(), 
		v.end(), 
		5);
	if (it_found != v.end())
		cout << *it_found << endl;
	else
		cout << "not found" << endl;
	auto it_not_found = std::find(
		it_found,
		v.end(), 
		15);
	if (it_not_found != v.end())
		cout << *it_not_found << endl;
	else
		cout << "not found" << endl;
}

bool predicate_pair(int i) {
	return i % 2 == 0;
}

void test_algo_find_if_old()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6 };
	auto it_found = std::find_if(
		v.begin(),
		v.end(),
		predicate_pair
	);

	while (it_found != v.end())
	{
		cout << *it_found << endl;
		it_found += 1;
		it_found = std::find_if(
			it_found,
			v.end(),
			predicate_pair
		);
	}
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
	vector <int> v2 = { 4, 4, 5 };
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
	vector <int> v_copy(v.size());
	std::copy(
		v.begin(),
		v.end(),
		v_copy.begin());
	v_copy[2] = 5;
	for (auto i : v)
		cout << i << endl;
	cout << endl;
	for (auto i : v_copy)
		cout << i << endl;
}

void test_algo_remove_copy()
{
	vector <int> v = { 1, 2, 3, 4, 3, 6 };
	vector <int> v_copy(v.size());
	v_copy[4] = 10;
	std::remove_copy(
		v.begin(),
		v.end(),
		v_copy.begin(),
		3);
	for (auto i : v_copy)
		cout << i << endl;
}

bool accepted_char(char c)
{
	return (isdigit(c) ||
		c == ',' ||
		c == '{' ||
		c == '}');
}

bool not_accepted_char(char c)
{
	return !accepted_char(c);
}

void test_algo_remove_copy_if_function()
{
	string s = "{ 1, A 2, 3, A 4, 5, A 6 }";
	std::copy_if(
		s.begin(),
		s.end(),
		std::ostream_iterator<char>(cout),
		accepted_char);
}

void test_algo_remove_copy_if()
{
	test_algo_remove_copy_if_function();
	return;
	string s = "{ 1, A 2, 3, A 4, 5, A 6 }";
	std::remove_copy_if(
		s.begin(),
		s.end(),
		
		std::ostream_iterator<char>
		(cout),
		
		[](char c)
		{ return c == ' ' || c == 'A'; });
}

void test_algo_remove()
{
	vector <int> v = 
	{ 1, 2, 3, 4, 5, 6 };
	auto last = std::remove(
		v.begin(),
		v.end(),
		3);
	for (auto i : v)
		cout << i << endl;
	cout << endl;
	for (auto it = v.begin(); it != v.end(); ++it)
		cout << *it << endl;
	cout << endl;
	for (auto it = v.begin(); it != last; ++it)
		cout << *it << endl;
	cout << endl;
	v.erase(last, v.end());
	for (auto i : v)
		cout << i << endl;
	cout << endl;
}

void test_algo_remove_if()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6 };
	auto last = std::remove_if(
		v.begin(),
		v.end(),
		[](int i) { return i % 2 == 0; });
	for (auto i : v)
		cout << i << endl;
	cout << endl;
	v.erase(last, v.end());
	for (auto i : v)
		cout << i << endl;
}

void test_algo_transform()
{
	vector <int> v = { 1, 2, 3, 4, 5, 6 };
	vector <int> v2(v.size());
	std::transform(
		v.begin(),
		v.end(),
		v2.begin(),
		[](int i) { return i * 2; });
	for (auto i : v2)
		cout << i << endl;
}

void test_algo_partition()
{
	vector <int> v = 
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
	auto part = std::partition(
		v.begin(),
		v.end(),
		[](int i) { return i % 2 == 0; });
	
	for (auto i : v)
		cout << i << endl;
	cout << "part: " << *part << endl;
	
	for (auto it = v.begin(); it != part; ++it)
		cout << *it << endl;
	cout << endl;
	for (auto it = part; it != v.end(); ++it)
		cout << *it << endl;

}

void test_algo_stable_partition()
{
	vector <int> v =
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
	auto part = std::stable_partition(
		v.begin(),
		v.end(),
		[](int i) { return i % 2 == 0; });
	
	for (auto i : v)
		cout << i << endl;
	cout << "part: " << *part << endl;
	
	for (auto it = v.begin(); 
		it != part; ++it)
		cout << *it << endl;
	cout << endl;
	for (auto it = part; it != v.end(); ++it)
		cout << *it << endl;
	
}



void test_algo_iota()
{
	vector <int> v(10);
	std::iota(
		v.begin(),
		v.end(),
		15);
	for (auto i : v)
		cout << i << endl;
}

void test_algo_fill()
{
	vector <int> v(10);
	std::fill(
		v.begin(),
		v.end(),
		15);
	std::ranges::fill(v, 20);
	for (auto i : v)
		cout << i << endl;
}

void test_algo_ranges()
{
	vector <int> v =
	{ 1, 5, 2, 3, 4, 5, 6 };
	auto it_found = 
		std::ranges::find(v, 5);
	if (it_found != v.end())
		cout << *it_found << endl;
	else
		cout << "not found" << endl;
	auto it_not_found = 
		std::ranges::find(
		it_found,
		v.end(),
		5);
	if (it_not_found != v.end())
		cout << *it_not_found << endl;
	else
		cout << "not found" << endl;
}


void test_algo_min_max_element()
{
	vector <int> v =
	{ 1, 5, 2, 3, 4, 5, 6 };
	auto min = std::min_element(
		v.begin(),
		v.end());
	auto max = std::max_element(
		v.begin(),
		v.end());
	cout << *min << endl;
	cout << *max << endl;
}











void test_algo_minmax_element()
{
	vector <int> v =
	{ 1, 5, 2, 3, 4, 5, 6 };
	std::pair<
		vector<int>::iterator, 
		vector<int>::iterator> p =
		std::minmax_element(v.begin(), v.end());
	cout << *p.first << endl;
	cout << *p.second << endl;
	
	std::ranges::minmax_result<
		vector<int>::iterator> result =
		std::ranges::minmax_element(v);
	cout << *result.min << endl;
	cout << *result.max << endl;
	
	auto [mi, ma] = 
		std::minmax_element(v.begin(), v.end());
	cout << *mi << endl;
	cout << *ma << endl;

	auto [min, max] =
		std::ranges::minmax_element(v);

	cout << *min << endl;
	cout << *max << endl;
}

void test_algo_all_of()
{
	vector <int> v1 =
	{ 1, 5, 2, 3, 4, 5, 6 };
	vector <int> v2 =
	{ 2, 4, 6, 8, 10, 12 };
	if (std::all_of(
		v1.begin(),
		v1.end(),
		[](int i) { return i % 2 == 0; }))
		cout << "all even" << endl;
	else
		cout << "not all even" << endl;
	if (std::ranges::all_of(
		v2,
		[](int i) { return i % 2 == 0; }))
		cout << "all even" << endl;
	else
		cout << "not all even" << endl;
}

void test_algo_any_of()
{
	vector <int> v1 =
	{ 1, 5, 3, 3, 5, 5, 7 };
	if (std::any_of(
		v1.begin(),
		v1.end(),
		[](int i) { return i % 2 == 0; }))
		cout << "any even" << endl;
	else
		cout << "not any even" << endl;
	if (std::ranges::none_of(
		v1,
		[](int i) { return i % 2 == 0; }))
		cout << "none even" << endl;
	else
		cout << "some even" << endl;
}

void tests_algo()
{
	//test_algo_1();
	//test_algo_2();
	//test_algo_3();
	//test_algo_4();
	//test_algo_accumulate(); // E01
	//test_algo_find(); // E02
	//test_algo_find_if(); // E03
	//test_algo_search(); // E04
	//test_algo_copy(); // E05
	//test_algo_remove_copy(); // E06
	//test_algo_remove_copy_if(); //E07
	//test_algo_remove(); //E08 
	//test_algo_remove_if(); // E09
	//test_algo_transform(); // E10
	//test_algo_partition(); 	// E11
	//test_algo_stable_partition(); //E12
	//test_algo_iota(); //E13
	//test_algo_fill(); //E14
	//test_algo_ranges(); //E15
	//test_algo_min_max_element(); //E16
	//test_algo_minmax_element(); //E17
	//test_algo_all_of(); //E18
	test_algo_any_of(); //E19

}
