#include <algorithm>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <iostream>
#include <execution>

using namespace std;

// From Listing 12-25:
struct Stopwatch {
    Stopwatch(std::chrono::nanoseconds& result)
    : result{ result },
    start{ std::chrono::high_resolution_clock::now() } { }
    ~Stopwatch() {
        result = std::chrono::high_resolution_clock::now() - start;
    }
private:
    std::chrono::nanoseconds& result;
    const std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

vector<long> make_random_vector() {
    vector<long> numbers(1'000'000'000);
    iota(numbers.begin(), numbers.end(), 0);
    mt19937_64 urng{ 121216 };
    shuffle(numbers.begin(), numbers.end(), urng);
    return numbers;
}

int main() {
    cout << "Constructing random vectors...";
    auto numbers_a = make_random_vector();
    auto numbers_b{ numbers_a };
    chrono::nanoseconds time_to_sort;
    cout << " " << numbers_a.size() << " elements.\n";
    cout << "Sorting with execution::seq...";
    {
        Stopwatch stopwatch{ time_to_sort };
        sort(execution::seq, numbers_a.begin(), numbers_a.end());
    }
    cout << " took " << time_to_sort.count() / 1.0E9 << " sec.\n";

    cout << "Sorting with execution::par...";
    {
        Stopwatch stopwatch{ time_to_sort };
        sort(execution::par, numbers_b.begin(), numbers_b.end());
    }
    cout << " took " << time_to_sort.count() / 1.0E9 << " sec.\n";
}