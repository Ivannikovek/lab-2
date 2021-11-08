#include "pch.h"
#include "CppUnitTest.h"
#include "../../Lab 2/Lab 2/Lab 2.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestBinarySearch)
		{
			int arr[] = { 1, 2, 3, 4, 5, 7, 7 };
			Assert::AreEqual(BinarySearch(arr, 7, 0), -1);
			Assert::AreEqual(BinarySearch(arr, 7, 8), -1);
			Assert::AreEqual(BinarySearch(arr, 7, 9), -1);
			Assert::AreEqual(BinarySearch(arr, 7, 5), 4);
			Assert::AreEqual(BinarySearch(arr, 7, 7), 5);
		}

		TEST_METHOD(TestQuickSort)
		{
			const int N = 10;
			int arr1[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };
			int arr2[] = { 0, 1, 2, 3, 5, 6, 7, 7, 8, 9 };

			QuickSort(arr1, 0, N - 1);

			for (size_t i = 0; i < 10; i++)
				Assert::AreEqual(arr1[i], arr2[i]);
		}

		TEST_METHOD(TestInsertionSort)
		{
			const int N = 10;
			int arr1[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };
			int arr2[] = { 0, 1, 2, 3, 5, 6, 7, 7, 8, 9 };

			InsertionSort(arr1, N);

			for (size_t i = 0; i < 10; i++)
				Assert::AreEqual(arr1[i], arr2[i]);
		}

		TEST_METHOD(TestBogoSort)
		{
			const int N = 10;
			int arr1[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };
			int arr2[] = { 0, 1, 2, 3, 5, 6, 7, 7, 8, 9 };

			BogoSort(arr1, N);

			for (size_t i = 0; i < 10; i++)
				Assert::AreEqual(arr1[i], arr2[i]);
		}

		TEST_METHOD(TestCountingSort)
		{
			const int N = 10;
			unsigned char arr1[] = { 9, 8, 5, 3, 0, 2, 1, 6, 7, 7 };
			unsigned char arr2[] = { 0, 1, 2, 3, 5, 6, 7, 7, 8, 9 };

			CountingSort(arr1, N);

			for (size_t i = 0; i < 10; i++)
				Assert::AreEqual(arr1[i], arr2[i]);
		}
	};
}
