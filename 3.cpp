#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// Iterative Factorial
unsigned long long factorial(int n, bool recursive)
{
    if (recursive)
    {
        if (n <= 1)
            return 1;

        return n * factorial(n - 1, true);
    }

    unsigned long long ans = 1;

    while (n > 1)
    {
        ans = ans * n;
        n--;
    }

    return ans;
}

int main()
{
    int n;

    cout << "Enter a non-negative integer (e.g., 20): ";
    cin >> n;

    if (n < 0)
    {
        cout << "Invalid input!";
        return 0;
    }

    auto s1 = high_resolution_clock::now();
    unsigned long long iterative = factorial(n, false);
    auto e1 = high_resolution_clock::now();

    auto s2 = high_resolution_clock::now();
    unsigned long long recursive = factorial(n, true);
    auto e2 = high_resolution_clock::now();

    duration<double, nano> t1 = e1 - s1;
    duration<double, nano> t2 = e2 - s2;

    cout << "\n--- Results for " << n << "! ---" << endl;
    cout << "Iterative Result : " << iterative << endl;
    cout << "Iterative Time   : " << t1.count() << " ns" << endl;
    cout << "-------------------------------" << endl;
    cout << "Recursive Result : " << recursive << endl;
    cout << "Recursive Time   : " << t2.count() << " ns" << endl;

    return 0;
}
