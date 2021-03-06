// count elements in vector until it hits '-99'

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
	vector<int> numbers { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, -99, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101 };
	// vector<int> numbers;  // size is 0
	int count {};
	if (numbers.size() != 0) {
		while (count <= numbers.size() - 1) {
			if (numbers.at(count) == -99) {
				break;
			}
			count++;
		}
	}
	cout << "Count till hit -99: " << count << endl;
	std::vector<char> a(3);
	std::vector<std::vector<char>> b(3, std::vector<char>(3));
	return 0;
}
