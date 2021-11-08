// Lab 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

//log2(N)
int BinarySearch(const int* array, size_t size, int elem_to_find) {
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

/*
int partition(int* a, int l, int r)
{
	int v = a[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j) {
		while (a[i] < v)
			i++;
		while (a[j] > v)
			j--;
		if (i >= j)
			break;
		swap(a[i++], a[j--]);
	}
	return j;
}

void quickSort(int* a, int l, int r) {
	if (l < r) {
		int q = partition(a, l, r);
		quickSort(a, l, q);
		quickSort(a, q + 1, r);
	}
}
*/

void print_array(const int* array, size_t N) {
	/*for (int i = 0; i < N; i++)
		std::cout << i << ' ';
	std::cout << std::endl;*/

	for (size_t i = 0; i < N; i++)
		std::cout << array[i] << ' ';
	std::cout << std::endl;
}

void QuickSort(int* array, size_t left, size_t right) {
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
			if (j != 0)		//avoiding overflow for size_t
				j--;
		}
	}

	if (j > left)
		QuickSort(array, left, j);
	if (i < right)
		QuickSort(array, i, right);
}


void BubbleSort(int* array, size_t size) {
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size - 1 - i; j++)
			if (array[j] > array[j + 1])
				swap(array[j], array[j + 1]);
}

bool isSorted(int* array, size_t size) {
	for (size_t i = 0; i < size - 1; i++)
		if (array[i] > array[i + 1])
			return false;
	return true;
}

void cicleLeftMove(int* array, size_t start, size_t end) {
	int first = array[start];
	for (size_t i = start; i < end; i++)
		array[i] = array[i + 1];
	array[end] = first;
}

bool bruteForcing(int* array, size_t start, size_t size) {
	if (start == size - 1)
		return isSorted(array, size);

	for (size_t i = 0; i < size - start; i++) {
		if (bruteForcing(array, start + 1, size))
			return true;
		cicleLeftMove(array, start, size - 1);
	}

	return false;
}

void randomShaking(int* array, size_t size) {
	for (size_t i = 0; i < size; i++)
		swap(array[i], array[(i + rand()) % size]);
}

void BogoSort(int* array, size_t size) {
	while (!isSorted(array, size))
		randomShaking(array, size);
}

void CountingSort(unsigned char* array, size_t size) {
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

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 7, 9 };
	std::cout << BinarySearch(arr, 7, 8);

	//int arr[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };
	//const int N = 10;

	//int arr[] = { 1, 3, 4, 2 };
	//int N = 4;

	//print_array(arr, N);
	//std::cout << std::endl;

	//QuickSort(arr, 0, N-1);

	//BubbleSort(arr, N);

	//BogoSort(arr, N);

	//CountingSort(arr, N);

	//print_array(arr, N);
	/*
	int arr2[] = { 1, 7, 8, 0, 4, 5, 1 };

	print_array(arr2, 7);
	std::cout << std::endl;

	quickSort(arr2, 0, 6);

	print_array(arr2, 7);
	*/
}