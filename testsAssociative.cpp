#include "testsAssociative.h"
#include "testsAlgo.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <ios>
#include <numeric>
#include <iterator>
#include <list>
#include <cctype>
#include <fstream>
#include <chrono>
#include "testsString.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::unordered_map;

unordered_map<string, vector<int>> find_ref_unordered(std::ifstream& in, vector<string> find_words(const string&) = split)
{
	string line;
	int line_number = 0;
	unordered_map<string, vector<int>> ret;
	while (getline(in, line))
	{
		++line_number;
		vector<string> words = find_words(line);
		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
		{
			ret[*it].push_back(line_number);
		}
	}
	return ret;
}

std::string get_lorem_n_words(int n)
{
	std::ifstream file("lorem.txt");
	std::string result;
	std::string str;
	int i = 0;
	while (std::getline(file, str))
	{
		std::istringstream iss(str);
		std::string word;
		while (std::getline(iss, word, ' '))
		{
			result += word + " ";
			i++;
			if (i == n)
				return result;
		}
	}
	return result;
}

void test_map_basic()
{
	map<string, int> m;
	m["anykey"] = 25;
	m["otherkey"] = 42;
	m["anykey"] = 24;
	cout << m["anykey"] << endl;
	cout << m["otherkey"] << endl;

	map<string, int>::iterator it1 = m.find("anykey");
	if (it1 != m.end())
	{
		cout << "Found " << it1->first << " " << it1->second << endl;
	}
	map<string, int>::iterator it2 = m.find("otherkey");
	if (it2 != m.end())
	{
		cout << "Found " << it2->first << " " << it2->second << endl;
	}
	else
	{
		cout << "Not found" << endl;
	}
	cout << "Size: " << m.size() << endl;
	cout << "Max size: " << m.max_size() << endl;
	cout << "Empty: " << m.empty() << endl;
	map<string, int>::iterator it3 = m.find("justkey");
	if (it3 != m.end())
	{
		cout << "Found " << it3->first << " " << it3->second << endl;
	}
	else
	{
		cout << "Not found" << endl;
	}

	cout << "Count: " << m.count("anykey") << endl;
	cout << "Count: " << m.count("otherkey") << endl;
	cout << "Count: " << m.count("justkey") << endl;
	if (std::any_of(m.begin(), m.end(), [](const std::pair<string, int>& p) { return p.second == 24; }))
	{
		cout << "Found 24" << endl;
	}
	else
	{
		cout << "Not found 24" << endl;
	}
	
}

void test_map_word_count()
{
	map<std::string, int> counter;
	string word;
	std::istringstream iss(get_lorem_n_words(50));
	while (getline(iss, word, ' '))
	{
		++counter[word];
	}
	cout << endl;
	for (const auto& p : counter)
	{
		cout << p.first << " " << p.second << endl;
	}
	//for (map<string, int>::const_iterator it = counter.begin(); it != counter.end(); ++it)
	//{
	//	cout << it->first << " " << it->second << endl;
	//}
	cout << endl << "size: " << counter.size() << endl;
}


map<string, vector<int>> find_ref(std::ifstream& in, vector<string> find_words(const string&) = split)
{
	string line;
	int line_number = 0;
	map<string, vector<int>> ret;
	while (getline(in, line))
	{
		++line_number;
		vector<string> words = find_words(line);
		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
		{
			ret[*it].push_back(line_number);
		}
	}
	return ret;
}


void test_map_word_find_ref()
{
	std::ifstream file("lorem.txt");
	map<string, vector<int>> xref = find_ref(file);
	cout << endl;
	for (const auto& p : xref)
	{
		cout << std::setw(20) << p.first << " ";
		for (const auto& i : p.second)
		{
			cout << i << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void test_map_word_find_ref_time()
{
	std::ifstream file("lorem.txt");
	//std::ifstream file("loremBig.txt");
	auto start = std::chrono::high_resolution_clock::now();
	//map<string, vector<int>> xref = find_ref(file);
	unordered_map<string, vector<int>> xref = find_ref_unordered(file);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	cout << endl;
	/**/
	for (const auto& p : xref)
	{
		cout << std::setw(20) << p.first << " ";
		for (const auto& i : p.second)
		{
			cout << i << " ";
		}
		cout << endl;
	}
	cout << endl;
	/**/
	cout << "Elapsed time: " << elapsed.count() << endl;
}

void tests_associative()
{
	//test_map_basic();
	//test_map_word_count();
	//test_map_word_find_ref();
	test_map_word_find_ref_time();
	//test_multimap();
	//test_set();
	//test_multiset();
	//test_unordered_map();
	//test_unordered_multimap();
	//test_unordered_set();
	//test_unordered_multiset();
}
