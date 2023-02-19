#include <cstdio>

struct list
{
    void *data = nullptr;
    list *next = nullptr;
};


struct Stack_l
{
    size_t element_size = 0;
    list *content       = nullptr;
};

Stack_l *lstack_ctr (size_t   element_size);
int      push_l     (Stack_l *st, void  *buff);
int      top_l      (Stack_l *st, void  *buff);
int      pop_l      (Stack_l *st);
Stack_l *lstack_dtr (Stack_l *st);

void stack_tests_l  (FILE *result, int number_of_tests);