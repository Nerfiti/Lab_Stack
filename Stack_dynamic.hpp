#include <cstdio>

struct Stack_d
{
    int size            = 0;
    int capacity        = 0;
    size_t element_size = 0;

    void **content      = nullptr;
};

Stack_d *stack_ctr (size_t size, size_t element_size);
int      push_d    (Stack_d *st, void  *buff);
int      top_d     (Stack_d *st, void  *buff);
int      pop_d     (Stack_d *st);
Stack_d *stack_dtr (Stack_d *st);

void stack_tests_d (FILE *result, int number_of_tests);