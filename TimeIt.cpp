#include <iostream>
#include <vector>

#include <chrono>
#include <cstdint>
#include <intrin.h>

uint64_t time_with_chrono() {
	using namespace std::chrono;

	uint64_t start = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
	
	system("cls");

	uint64_t end = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();

	uint64_t delta = end - start;
	return delta;
}

uint64_t time_with_TSC() {
	uint64_t start = __rdtsc();
	system("cls");
	return __rdtsc() - start;
}

void time_tests()
{
	using std::cout;
	size_t length = 10;
	std::vector<uint64_t> chrono_times;
	std::vector<uint64_t> TSC_times;
	for (size_t i = 0; i < length; i++)
	{
		chrono_times.push_back(time_with_chrono());
		TSC_times.push_back(time_with_TSC());
	}
	for (size_t i = 0; i < length; i++)
	{
		cout << "time_with_chrono: " << chrono_times[i] << '\n';
		cout << "time_with_TSC:    " << TSC_times[i] << '\n';
	}
}

