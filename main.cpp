#include <cstdio>
#include <ctime>

#include "Stack_dynamic.hpp"
#include "Stack_list.hpp"

int main()
{
    FILE *result = fopen("result.txt", "w");
    const int number_of_tests = 10;

    stack_tests_d(result, number_of_tests);
    stack_tests_l(result, number_of_tests);

    fclose(result);
}