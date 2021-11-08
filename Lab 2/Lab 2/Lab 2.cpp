#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int BinarySearch(const int* array, const size_t size, const int elem_to_find) {
	size_t left = 0, right = size;
	while (left < right) {
		int middle = (right - left) / 2 + left;
		if (elem_to_find < array[middle])
			right = middle;
		else
			if (elem_to_find > array[middle])
				left = middle + 1;
			else
				return middle;
	}

	return -1;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void print_array(const int* array, const size_t N) {
	for (size_t i = 0; i < N; i++)
		std::cout << array[i] << ' ';
	std::cout << std::endl;
}

void print_array(const unsigned char* array, const size_t N) {
	for (size_t i = 0; i < N; i++)
		std::cout << (unsigned int)array[i] << ' ';
	std::cout << std::endl;
}

void QuickSort(int* array, const size_t left, const size_t right) {
	size_t middle_ind = (right - left) / 2 + left;
	int middle = array[middle_ind];

	size_t i = left, j = right;
	while (i < j) {
		for (; i < right && array[i] < middle; i++);
		for (; j > left && array[j] > middle; j--);

		if (i <= j) {
			if (i < j)
				swap(array[i], array[j]);
			i++;
			if (j != 0)		//to avoid underflowing for size_t
				j--;
		}
	}

	if (j > left)
		QuickSort(array, left, j);
	if (i < right)
		QuickSort(array, i, right);
}

void InsertionSort(int* array, const size_t size) {
	for (size_t i = 1; i < size; i++) {

		int inserting_value = array[i];

		int j = i - 1; //int j to avoid underflowing for size_t
		for (; j >= 0; j--) {
			if (inserting_value < array[j])     //if inserting less then temp
				array[j + 1] = array[j];		//move temp right
			else
				break;
		}

		array[j + 1] = inserting_value;
	}
}

/*void BubbleSort(int* array, const size_t size) {
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size - 1 - i; j++)
			if (array[j] > array[j + 1])
				swap(array[j], array[j + 1]);
}*/

bool isSorted(int* array, const size_t size) {
	for (size_t i = 0; i < size - 1; i++)
		if (array[i] > array[i + 1])
			return false;
	return true;
}

void randomShaking(int* array, const size_t size) {
	for (size_t i = 0; i < size; i++)
		swap(array[i], array[(i + rand()) % size]);
}

void BogoSort(int* array, const size_t size) {
	while (!isSorted(array, size))
		randomShaking(array, size);
}

void CountingSort(unsigned char* array, const size_t size) {
	unsigned char max = array[0];

	for (size_t i = 0; i < size; i++)
		if (array[i] > max)
			max = array[i];

	size_t* counts = new size_t[max + 1]();

	for (size_t i = 0; i < size; i++)
		++counts[array[i]];

	for (size_t i = 0, j = 0; i <= max; i++)
		if (counts[i] != 0) {
			array[j] = i;
			j++;
			--counts[i];
			if (counts[i] != 0)
				i--;
		}

	delete[] counts;
}

void randomFilling(int* array, int* array2, const size_t size) {
	srand(time(0));
	for (size_t i = 0; i < size; i++)
		array[i] = array2[i] = rand() - RAND_MAX / 2;
}

void Experiment() {
	int** array_quick = new int* [5];
	size_t size = 10;
	for (size_t i = 0; i < 5; i++) {
		array_quick[i] = new int[size];
		size *= 10;
	}

	int** array_insertion = new int* [5];
	size = 10;
	for (size_t i = 0; i < 5; i++) {
		array_insertion[i] = new int[size];
		size *= 10;
	}

	clock_t time_quick[5] = { 0,0,0,0,0 };
	clock_t time_insertion[5] = { 0,0,0,0,0 };

	for (size_t i = 0; i < 10; i++) {
		std::cout << i << " step proccessing..." << std::endl;

		size = 10;
		for (size_t i = 0; i < 5; i++) {
			randomFilling(array_quick[i], array_insertion[i], size);
			size *= 10;
		}

		clock_t start;

		std::cout << "QuickSorting..." << std::endl;
		size = 10;
		for (size_t i = 0; i < 5; i++) {
			std::cout << i << ' ';
			start = std::clock();
			QuickSort(array_quick[i], 0, size - 1);
			time_quick[i] += std::clock() - start;
			size *= 10;
		}
		std::cout << '\n';

		std::cout << "InsertionSorting..." << std::endl;
		size = 10;
		for (size_t i = 0; i < 5; i++) {
			std::cout << i << " ";
			start = std::clock();
			InsertionSort(array_insertion[i], size);
			time_insertion[i] += std::clock() - start;
			size *= 10;
		}
		std::cout << '\n';
	}

	double average_quick[5];
	for (size_t i = 0; i < 5; i++)
		average_quick[i] = 1.0 * time_quick[i] / CLOCKS_PER_SEC / 10;

	double average_insertion[5];
	for (size_t i = 0; i < 5; i++)
		average_insertion[i] = 1.0 * time_insertion[i] / CLOCKS_PER_SEC / 10;

	for (size_t i = 0; i < 5; i++)
		delete[] array_quick[i];
	delete[] array_quick;

	for (size_t i = 0; i < 5; i++)
		delete[] array_insertion[i];
	delete[] array_insertion;

	std::ofstream file("experiment.txt");

	file << "QuickSort (10, 100, 1000, 10000, 100000):" << std::endl;

	for (size_t i = 0; i < 5; i++)
		file << average_quick[i] << ' ';

	file << "\nInsertionSort (10, 100, 1000, 10000, 100000):" << std::endl;

	for (size_t i = 0; i < 5; i++)
		file << average_insertion[i] << ' ';
}

//#define USUAL_MAIN

#ifdef USUAL_MAIN

int main()
{
	
	int arr[] = { 1, 2, 3, 4, 5, 7, 7 };
	std::cout << "Array 1:" << std::endl;
	print_array(arr, 7);
	std::cout << "BinarySearch:" << std::endl;
	std::cout << "'0': ";
	std::cout << BinarySearch(arr, 7, 0) << std::endl;
	std::cout << "'8': ";
	std::cout << BinarySearch(arr, 7, 8) << std::endl;
	std::cout << "'9': ";
	std::cout << BinarySearch(arr, 7, 9) << std::endl;
	std::cout << "'5': ";
	std::cout << BinarySearch(arr, 7, 5) << std::endl;


	int arr2[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };


	int arr3[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };


	int arr4[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };
	unsigned char arr5[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };


	const size_t N = 10;

	std::cout << std::endl;

	std::cout << "Array 2:" << std::endl;
	print_array(arr2, N);

	std::cout << "QuickSort:" << std::endl;
	QuickSort(arr2, 0, N - 1);
	print_array(arr2, N);
	

	std::cout << "InsertionSort:" << std::endl;
	InsertionSort(arr3, N);
	print_array(arr3, N);
	
	std::cout << "BogoSort:" << std::endl;
	BogoSort(arr4, N);
	print_array(arr4, N);

	std::cout << "CountingSort:" << std::endl;
	CountingSort(arr5, N);
	print_array(arr5, N);
	

	return 0;
}

#endif // USUAL_MAIN

#ifndef USUAL_MAIN
int main()
{
	Experiment();

	return 0;
}

#endif // USUAL_MAIN