#include <set>
#include <vector>
#include <array>
#include <iostream>
#include <limits>
#include <chrono>
#include <future>
#include <sstream>
#include <string>

using namespace std;

struct Stopwatch {
    Stopwatch(std::chrono::nanoseconds& result)
    : result{ result },
    start{ std::chrono::high_resolution_clock::now() } { }
    ~Stopwatch() {
        result = std::chrono::high_resolution_clock::now() - start;
    }
private:
    std::chrono::nanoseconds& result;
    const std::chrono::time_point<std::chrono::high_resolution_clock>start;
};

template <typename T>
std::multiset<T> factorize(T x) {
    std::multiset<T> result{1};
    for (T candidate{2};candidate <= x; candidate++) {
        if (x%candidate == 0) {
            result.insert(candidate);
            x /= candidate;
            candidate = 1;
        }
    }
    return result;
}

string factor_task (unsigned long x) {
    chrono::nanoseconds elapsed_ns;
    set<unsigned long long> factors;
    {
        Stopwatch stopwatch(elapsed_ns);
        factors = factorize(x);

    }
}

int main() {}