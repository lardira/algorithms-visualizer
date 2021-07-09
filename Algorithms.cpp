#include "Algorithms.h"


void Algorithms::bubbleSort(std::vector<int>& arr, int step)
{
	if (step < arr.size())
		for (int j = 0; j < arr.size() - 1 - step; j++)
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
}

void Algorithms::insertionSort(std::vector<int>& arr, int step)
{
	int k, j;
	if (step < arr.size())
	{
		k = arr[step];
		j = step - 1;
		while (j >= 0 && arr[j] > k)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = k;
	}
}

void Algorithms::selectionSort(std::vector<int>& arr, int step)
{
	int idBiggest = 0;

	if (step < arr.size())
	{
		for (int i = 0; i < arr.size() - step ;i++)
			if (arr[idBiggest] < arr[i])
				idBiggest = i;

		int t = arr[idBiggest];
		arr[idBiggest] = arr[arr.size() - 1 - step];
		arr[arr.size() - 1 - step] = t;
	}
}
