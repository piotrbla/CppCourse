#include <iostream>		//cout, cin
#include <vector>		//vector
#include <numeric>		//accumulate, reduce

using std::vector;
using std::cout;
using std::endl;
using std::accumulate;

int vectorTester()
{
	vector <double> numbers = 
		{ 4.3, 3.2, 3.4, 4.1, 4.5 };
	vector <double>::size_type size = 
		numbers.size();
	double result= std::accumulate(
		numbers.begin(),
		numbers.end(),
		0.0
	);
	//auto result = std::reduce(
	//	numbers.begin(), 
	//	numbers.end()
	//);
	cout << "The sum of the numbers is "
		<< result << endl;
	cout << "The average of the numbers is "
		<< result / size << endl;
	double sum = std::accumulate(
		numbers.begin(), 
		numbers.end(),
		decltype(numbers)::value_type(0)
	);
	cout << "The sum of the numbers is "
		<< sum << endl;

	return 0;
}






//#include <numeric>		//accumulate
//using std::accumulate;
//double sum = accumulate(
//	numbers.begin(),
//	numbers.end(),
//	0.0
//);
//  sum = std::accumulate(numbers.begin(), numbers.end(),
//decltype(numbers)::value_type(0));
//auto result = std::reduce(numbers.begin(), numbers.end());
//cout << "The sum of the numbers is "
//<< sum << endl;
//cout << "The average of the numbers is "
//<< sum / size << endl;
//std::vector<int> sums(data.size());
//
////SUM ALL NUMBERS IN A GIVEN VECTOR.
//inclusive_scan(data.begin(), data.end(),
//	sums.begin());
//
////SUM OF FIRST 5 ELEMENTS.
//std::cout << "Sum of first 5 elements :: " << sums[4] << std::endl;
//
////SUM OF ALL ELEMENTS
//std::cout << "Sum of all elements :: " << sums[data.size() - 1] << std::endl;
//WITHOUT EXECUTION POLICY
//int sum = std::reduce(vec.begin(), vec.end());
//
////TAKING THE ADVANTAGE OF EXECUTION POLICIES
//int sum2 = std::reduce(std::execution::par, vec.begin(), vec.end());