// main file

#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#define MAX 1000000000

float time_diff(struct timeval* start, struct timeval* end);
bool brute_force_way(const long* arr, const unsigned long& arr_size, const long& key_sum);
bool better_way(const long* arr, const unsigned long& arr_size, const long& key_sum);
void sort(long* arr, const unsigned long& arr_size);  // sort in non-decreasing order
void insertion_sort(long* arr, const unsigned long& arr_size);
long median(const long* arr, const unsigned long& begin, const unsigned long& end);
void quicksort(long* arr, unsigned long begin, unsigned long end);
unsigned long partition(long* arr, unsigned long begin, unsigned long end);


int main(int argc, char **argv) {
	srand(time(0));

	struct timeval main_start, main_end;
	gettimeofday(&main_start, NULL);

	/** to take input from file
	std::ifstream input_data;
	input_data.open("./input_data.txt");
	*/

	long key_sum{};
	std::cout << "Enter key sum: ";
	std::cin >> key_sum;

	unsigned long arr_size{};
	//input_data >> arr_size;
	std::cout << "Reading array size, ";
	std::cin >> arr_size;
	std::cout << "got: " << arr_size << "\n";
	assert((arr_size <= 10e5 + 1));

	long* arr = new long[arr_size];
	std::cout << "Reading array elements\n";

	struct timeval arr_input_start, arr_input_end;
	gettimeofday(&arr_input_start, NULL);

	// take input in array
	{
		/** (from file)
		long input_element{};
		unsigned long count{};
		while (input_data >> input_element) {
			// check constraint for array elements
			assert((-10e9-1 < input_element) && (input_element < 10e9 + 1));
			*(arr + count++) = input_element;
			// check constraint for array size
			assert((count <= arr_size));
			if (!(count % 10000)) {  // just to be sure that data is getting entered
				std::cout << count << " elements entered\n";
			}
		}
		*/

		// random input to array
		for (unsigned long idx = 0; idx < arr_size; ++idx) {
			*(arr + idx) = rand() % MAX;
		}
	}

	gettimeofday(&arr_input_end, NULL);
	std::cout << "\n==> Time taken in array element input: "
		<< time_diff(&arr_input_start, &arr_input_end) << "\n";

	std::cout << "Array input complete, array size: " << arr_size << "\n";

	// sorting is not necessary for brute force way
	{
		struct timeval sort_time_start, sort_time_end;
		gettimeofday(&sort_time_start, NULL);
		sort(arr, arr_size);
		gettimeofday(&sort_time_end, NULL);
		std::cout << "\n==> Time taken in sorting array: "
			<< time_diff(&sort_time_start, &sort_time_end) << "\n";

		//std::cout << "\nAfter sorting: \n[ ";
		//for (unsigned long idx = 0; idx < arr_size; ++idx) {
			//std::cout << *(arr + idx);
			//if (idx < arr_size - 1) {
				//std::cout << ", ";
			//}
		//}
		//std::cout << " ]\n";
	}

	// you can try brute_force_way() here too
	struct timeval algo_time_start, algo_time_end;
	gettimeofday(&algo_time_start, NULL);

	if (better_way(arr, arr_size, key_sum)) {
		std::cout << "Pair found\n";
	}
	else {
		std::cout << "Pair not found\n";
	}
	gettimeofday(&algo_time_end, NULL);
	std::cout << "\n==> Time taken in actual algo: "
		<< time_diff(&algo_time_start, &algo_time_end) << "\n";

	delete[] arr;

	gettimeofday(&main_end, NULL);
	std::cout << "\n==> Total time taken: "
		<< time_diff(&main_start, &main_end) << std::endl;
	return 0;
}

float time_diff(struct timeval* start, struct timeval* end) {
	return ((end->tv_sec - start->tv_sec) +
			1e-6*(end->tv_usec - start->tv_usec));
}

long median(const long* arr, const unsigned long& begin, const unsigned long& end) {
	unsigned long mid = (begin + end) / 2;
	if (*(arr + begin) < *(arr + mid)) {
		if (*(arr + begin) >= *(arr + end)) {
			return *(arr + begin);
		}
		else if (*(arr + mid) < *(arr + end)) {
			return *(arr + mid);
		}
	}
	else {
		if (*(arr + begin) < *(arr + end)) {
			return *(arr + begin);
		}
		else if (*(arr + mid) >= *(arr + end)) {
			return *(arr + mid);
		}
	}
	return *(arr + end);
}

void sort(long* arr, const unsigned long& arr_size) {
	if (arr_size < 10) {  // this is the count which js uses to switch probably
		// insertion sort is better for array with small size
		insertion_sort(arr, arr_size);
	}
	else {
		// quicksort good with large set of elements
		quicksort(arr, 0, arr_size - 1);
	}
}

void insertion_sort(long* arr, const unsigned long& arr_size) {
	for (unsigned long idx = 1; idx < arr_size; ++idx) {
		unsigned long sidx = idx;
		while (sidx > 0 && *(arr + sidx) < *(arr + sidx - 1)) {
			long temp = *(arr + sidx);
			*(arr + sidx) = *(arr + sidx - 1);
			*(arr + sidx - 1) = temp;
			sidx--;
		}
	}
}

void quicksort(long* arr, unsigned long begin, unsigned long end) {
	unsigned long pivot_index{};

	if (begin != end) {
		pivot_index = partition(arr, begin, end);
	}

	// if begin reference is not incremented upto pivot element yet, keep comparing
	if (begin < pivot_index - 1) {
		quicksort(arr, begin, pivot_index - 1);
	}

	// if end reference is not upto pivot_index yet, keep comparing
	if (pivot_index < end) {
		quicksort(arr, pivot_index, end);
	}
}

unsigned long partition(long* arr, unsigned long begin, unsigned long end) {
	long pivot_element{};
	unsigned long left = begin;
	unsigned long right = end;

	if ((end - begin) > 2) {  // contains atleast 3 elements
		pivot_element = median(arr, begin, end);
	}
	else {
		pivot_element = *(arr + (long)floor((begin + end) / 2));
	}

	while (left <= right) {
		while (*(arr + left) < pivot_element) { left++; }
		while (*(arr + right) > pivot_element) { right--; }

		// swap left and right index elements if left & right haven't crossed each-other
		if (left <= right) {
			long temp = *(arr + left);
			*(arr + left) = *(arr + right);
			*(arr + right) = temp;

			left++;
			right--;
		}
	}
	return left;
}

// time complexity: O(n^2) worst case
bool brute_force_way(const long* arr, const unsigned long& arr_size, const long& key_sum) {
	for (unsigned long idx = 0; idx < arr_size - 1; ++idx) {
		for (unsigned long sidx = idx + 1; sidx < arr_size; ++sidx) {
			if (*(arr + idx) + *(arr + sidx) == key_sum) {
				return true;
			}
		}
	}
	return false;
}

// time complexity: O(n)
bool better_way(const long* arr, const unsigned long& arr_size, const long& key_sum) {
	// need sorted array(sort it first before calling this function)
	long head = 0;  // first element
	long tail = arr_size - 1;  // last element
	while (head < tail) {
		if (*(arr + head) + *(arr + tail) == key_sum) {
			return true;
		}
		if (*(arr + head) + *(arr + tail) > key_sum) {
			tail--;
		}
		else {
			head++;
		}
	}
	return false;
}