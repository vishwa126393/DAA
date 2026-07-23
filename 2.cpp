#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
    This program compares 2 common searching algorithms:
    1. Linear Search
    2. Binary Search

    It creates a large sorted list of numbers, asks the user
    for a number to find, then times how long each algorithm
    takes to find it. Since binary search needs a sorted list
    to work, the list is sorted before either search runs.
*/

// ---------------------------------------------------------
// 1. LINEAR SEARCH
// Idea: Check every number one by one, from the start, until
// we find the one we're looking for. Simple, but slow for
// large lists since it may have to check every single number.
// ---------------------------------------------------------
int linearSearch(const vector<int>& numbers, int target)
{
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == target)
        {
            return i; // Found it — return its position
        }
    }
    return -1; // Not found
}

// ---------------------------------------------------------
// 2. BINARY SEARCH
// Idea: Only works on a SORTED list. Check the middle number.
// If it's too big, search the left half. If it's too small,
// search the right half. Repeat until found. Much faster than
// linear search because it skips half the list each step.
// ---------------------------------------------------------
int binarySearch(const vector<int>& numbers, int target)
{
    int low = 0;
    int high = numbers.size() - 1;

    while (low <= high)
    {
        int middle = low + (high - low) / 2;

        if (numbers[middle] == target)
        {
            return middle; // Found it
        }
        else if (numbers[middle] < target)
        {
            low = middle + 1; // Target must be in the right half
        }
        else
        {
            high = middle - 1; // Target must be in the left half
        }
    }

    return -1; // Not found
}

// ---------------------------------------------------------
// Helper function: times how long a search takes, in microseconds
// ---------------------------------------------------------
template <typename SearchFunction>
long long timeSearch(const vector<int>& numbers, int target, SearchFunction searchFunction, int& resultIndex)
{
    auto startTime = high_resolution_clock::now();
    resultIndex = searchFunction(numbers, target);
    auto endTime = high_resolution_clock::now();

    return duration_cast<microseconds>(endTime - startTime).count();
}

// ---------------------------------------------------------
// Helper function: prints the result of a search in a consistent format
// ---------------------------------------------------------
void printSearchResult(const string& searchName, int resultIndex, long long timeTaken)
{
    cout << "\n" << searchName << "\n";

    if (resultIndex != -1)
        cout << "Element found at index " << resultIndex << endl;
    else
        cout << "Element not found\n";

    cout << "Time Taken : " << timeTaken << " microseconds\n";
}

// ---------------------------------------------------------
// MAIN PROGRAM
// ---------------------------------------------------------
int main()
{
    const int totalNumbers = 100000;
    vector<int> sortedList(totalNumbers);

    // Creating a sorted list: 1, 2, 3, ..., totalNumbers
    for (int i = 0; i < totalNumbers; i++)
    {
        sortedList[i] = i + 1;
    }

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    int resultIndex;

    // Linear Search Timing
    long long linearTime = timeSearch(sortedList, target, linearSearch, resultIndex);
    printSearchResult("Linear Search", resultIndex, linearTime);

    // Binary Search Timing
    long long binaryTime = timeSearch(sortedList, target, binarySearch, resultIndex);
    printSearchResult("Binary Search", resultIndex, binaryTime);

    return 0;
}
