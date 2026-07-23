#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
    This program compares 5 common sorting algorithms:
    1. Bubble Sort
    2. Selection Sort
    3. Insertion Sort
    4. Merge Sort
    5. Quick Sort

    It fills a list with random numbers, then times how long
    each algorithm takes to sort a COPY of that same list.
    This way, every algorithm is tested on identical data,
    so the comparison is fair.
*/

// ---------------------------------------------------------
// 1. BUBBLE SORT
// Idea: Repeatedly compare neighbors and swap them if they
// are in the wrong order. After each full pass, the largest
// unsorted number "bubbles up" to its correct position.
// ---------------------------------------------------------
void bubbleSort(vector<int>& numbers)
{
    int size = numbers.size();

    for (int pass = 0; pass < size - 1; pass++)
    {
        for (int i = 0; i < size - pass - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                swap(numbers[i], numbers[i + 1]);
            }
        }
    }
}

// ---------------------------------------------------------
// 2. SELECTION SORT
// Idea: For each position, find the smallest number in the
// remaining unsorted part of the list, then place it there.
// ---------------------------------------------------------
void selectionSort(vector<int>& numbers)
{
    int size = numbers.size();

    for (int current = 0; current < size - 1; current++)
    {
        int smallestIndex = current;

        for (int i = current + 1; i < size; i++)
        {
            if (numbers[i] < numbers[smallestIndex])
            {
                smallestIndex = i;
            }
        }

        swap(numbers[current], numbers[smallestIndex]);
    }
}

// ---------------------------------------------------------
// 3. INSERTION SORT
// Idea: Build the sorted list one number at a time. Take the
// next number and insert it into its correct position among
// the numbers already sorted.
// ---------------------------------------------------------
void insertionSort(vector<int>& numbers)
{
    int size = numbers.size();

    for (int i = 1; i < size; i++)
    {
        int currentValue = numbers[i];
        int j = i - 1;

        // Shift larger numbers one step to the right
        while (j >= 0 && numbers[j] > currentValue)
        {
            numbers[j + 1] = numbers[j];
            j--;
        }

        numbers[j + 1] = currentValue;
    }
}

// ---------------------------------------------------------
// 4. MERGE SORT
// Idea: Split the list into halves until each piece has just
// one number (already "sorted"). Then merge pairs of sorted
// pieces back together in the correct order.
// ---------------------------------------------------------

// Merges two sorted sections of the list: [start..mid] and [mid+1..end]
void mergeTwoHalves(vector<int>& numbers, int start, int mid, int end)
{
    vector<int> leftHalf(numbers.begin() + start, numbers.begin() + mid + 1);
    vector<int> rightHalf(numbers.begin() + mid + 1, numbers.begin() + end + 1);

    int i = 0, j = 0, k = start;

    // Compare numbers from both halves and place the smaller one first
    while (i < leftHalf.size() && j < rightHalf.size())
    {
        if (leftHalf[i] <= rightHalf[j])
            numbers[k++] = leftHalf[i++];
        else
            numbers[k++] = rightHalf[j++];
    }

    // Add any leftover numbers
    while (i < leftHalf.size())
        numbers[k++] = leftHalf[i++];

    while (j < rightHalf.size())
        numbers[k++] = rightHalf[j++];
}

void mergeSort(vector<int>& numbers, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;

        mergeSort(numbers, start, mid);       // Sort left half
        mergeSort(numbers, mid + 1, end);      // Sort right half
        mergeTwoHalves(numbers, start, mid, end); // Combine both halves
    }
}

// ---------------------------------------------------------
// 5. QUICK SORT
// Idea: Pick a "pivot" number. Move all smaller numbers to
// its left and all bigger numbers to its right. Repeat this
// for the left and right sections separately.
// ---------------------------------------------------------

// Places the pivot in its correct position and returns that position
int partition(vector<int>& numbers, int low, int high)
{
    int pivot = numbers[high]; // Choosing the last number as pivot
    int boundary = low - 1;    // Marks the edge of "smaller than pivot" numbers

    for (int i = low; i < high; i++)
    {
        if (numbers[i] < pivot)
        {
            boundary++;
            swap(numbers[boundary], numbers[i]);
        }
    }

    swap(numbers[boundary + 1], numbers[high]);
    return boundary + 1;
}

void quickSort(vector<int>& numbers, int low, int high)
{
    if (low < high)
    {
        int pivotPosition = partition(numbers, low, high);

        quickSort(numbers, low, pivotPosition - 1);  // Sort left of pivot
        quickSort(numbers, pivotPosition + 1, high); // Sort right of pivot
    }
}

// ---------------------------------------------------------
// Helper function: times how long a sort takes, in microseconds
// ---------------------------------------------------------
template <typename SortFunction>
long long timeSort(vector<int> numbers, SortFunction sortFunction)
{
    auto startTime = high_resolution_clock::now();
    sortFunction(numbers);
    auto endTime = high_resolution_clock::now();

    return duration_cast<microseconds>(endTime - startTime).count();
}

// ---------------------------------------------------------
// MAIN PROGRAM
// ---------------------------------------------------------
int main()
{
    const int totalNumbers = 100;
    vector<int> originalList(totalNumbers);

    // Fill the list with random numbers between 0 and 999
    srand(time(0));
    for (int i = 0; i < totalNumbers; i++)
    {
        originalList[i] = rand() % 1000;
    }

    cout << "Number of Elements = " << totalNumbers << "\n\n";

    // Each sort runs on its own fresh copy of the same original list,
    // so the comparison between algorithms stays fair.

    long long bubbleTime = timeSort(originalList, bubbleSort);
    cout << "Bubble Sort Time    : " << bubbleTime << " microseconds\n";

    long long selectionTime = timeSort(originalList, selectionSort);
    cout << "Selection Sort Time : " << selectionTime << " microseconds\n";

    long long insertionTime = timeSort(originalList, insertionSort);
    cout << "Insertion Sort Time : " << insertionTime << " microseconds\n";

    long long mergeTime = timeSort(originalList, [](vector<int>& numbers) {
        mergeSort(numbers, 0, numbers.size() - 1);
    });
    cout << "Merge Sort Time     : " << mergeTime << " microseconds\n";

    long long quickTime = timeSort(originalList, [](vector<int>& numbers) {
        quickSort(numbers, 0, numbers.size() - 1);
    });
    cout << "Quick Sort Time     : " << quickTime << " microseconds\n";

    return 0;
}
