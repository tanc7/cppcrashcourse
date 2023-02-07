#include <cstdio>
#include <cstdint>
#include <cstdarg>
// Not a good example, something is wrong with the formula or the while loop
int sum (size_t n, ...) {
    va_list args;
    va_start(args,n);
    int result{};
    while (n--) {
        auto next_element = va_arg(args, int);
        result += next_element;
    }
    va_end(args);
    return result;
}

int main() {
    printf("The answer is %d", sum(1, 2, 3, 6, 8, 10, 12));
}