#pragma once
#include <vector>

namespace Algorithms
{
	/// <summary>
	/// Complexity - O(n^2)
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="step"> - step must be incremented before using again</param>
	void insertionSort(std::vector<int>& arr, int step, std::pair<int, int>& idsCompared);

	/// <summary>
	/// Complexity - O(n^2)
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="step"></param>
	void bubbleSort(std::vector<int>& arr, int step, std::pair<int, int>& idsCompared);

	/// <summary>
	/// Complexity - O(n^2)
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="step"> - step must be incremented before using again</param> 
	void selectionSort(std::vector<int>& arr, int step, std::pair<int, int>& idsCompared);

	enum class Type
	{
		bubbleSort,
		insertionSort,
		selectionSort
	};
}

