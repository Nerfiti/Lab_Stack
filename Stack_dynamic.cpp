#include <cassert>
#include <cstring>
#include <ctime>
#include <malloc.h>
#include <random>

#include "Stack_dynamic.hpp"

//-----------------------------------------------------------------------

static void first_test  (int number_of_tests, FILE *result);
static void second_test (int number_of_tests, FILE *result);
static void third_test  (int number_of_tests, FILE *result);

//-----------------------------------------------------------------------

Stack_d *stack_ctr(size_t size, size_t element_size)
{
    Stack_d *st = (Stack_d *)calloc(element_size, sizeof(Stack_d));

    st->size         = 0;
    st->capacity     = size;
    st->element_size = element_size;

    st->content      = (void **)calloc(element_size, st->capacity);

    return st;
}

int push_d(Stack_d *st, void *buff)
{
    if (st->size >= st->capacity)
    {
        st->content = (void **)realloc(st->content, 2*(st->capacity+1) * st->element_size);
        st->capacity = 2*st->capacity;
    }
    if (st == nullptr)
        return 0;
    assert(st->size < st->capacity);

    memcpy((char *)(st->content) + st->size*st->element_size, buff, st->element_size);
    st->size++;

    return 1;
}

int top_d(Stack_d *st, void *buff)
{
    if (st->size == 0)
        return 0;

    memcpy(buff, (char *)(st->content) + (st->size-1)*st->element_size, st->element_size);
    return 1;
}

int pop_d(Stack_d *st)
{
    if (st->size == 0)
        return 0;

    st->size--;
    return 1;
}

Stack_d *stack_dtr(Stack_d *st)
{
    free(st->content);
    free(st);
    return nullptr;
}

//-----------------------------------------------------------------------

void stack_tests_d(FILE *result, int number_of_tests)
{

    fprintf(result, "Stack on the dynamic array\n");
    fprintf(result, "---------------------------------------------------\n\n");
    
    first_test  (number_of_tests, result);
    
    fprintf(result, "---------------------------------------------------\n\n");
    
    second_test (number_of_tests, result);
    
    fprintf(result, "---------------------------------------------------\n\n");
    
    third_test  (number_of_tests, result);
    
    fprintf(result, "---------------------------------------------------\n\n");
}

static void first_test(int number_of_tests, FILE *result)
{
    double sum_time = 0;

    fprintf(result, "Test 1\n\n");

    for (int testnum = 0; testnum < number_of_tests; ++testnum)
    {
        clock_t t1 = 0,
                t2 = 0;
        
        Stack_d* st = stack_ctr(10, 4);

        int a = 1;

        t1 = clock();

        for (int i = 0; i < 10e6; ++i)
            push_d(st, &a);
        
        while (st->size > 10e5)
        {
            int count = st->size/2;
            for (int i = 0; i < count; ++i)
                pop_d(st);
            for (int i = 0; i < count/2; ++i)
                push_d(st, &a);
        }

        t2 = clock();

        stack_dtr(st);

        double time = (double)(1000*(t2-t1))/CLOCKS_PER_SEC;
        fprintf(result, "%3d: %.2f ms\n", testnum+1, time);

        sum_time += time;
    }

    fprintf(result, "\nAverage time: %.2f ms\n\n", sum_time/number_of_tests);
}

static void second_test(int number_of_tests, FILE *result)
{
    double sum_time = 0;

    fprintf(result, "Test 2\n\n");

    for (int testnum = 0; testnum < number_of_tests; ++testnum)
    {
        clock_t t1 = 0,
                t2 = 0;

        t1 = clock();
        
        Stack_d* st = stack_ctr(10, 4);

        int a = 1;

        for (int j = 0; j < 100; ++j)
        {
            for (int i = 0; i < 10000; ++i)
                push_d(st, &a);
            for (int i = 0; i < 10000; ++i)
                pop_d(st);
        }

        for (int i = 0; i < 10e6; ++i)
            push_d(st, &a);
        
        while (st->size > 10e5)
        {
            int count = st->size/2;
            for (int i = 0; i < count; ++i)
                pop_d(st);
            for (int i = 0; i < count/2; ++i)
                push_d(st, &a);
        }

        for (int j = 0; j < 100; ++j)
        {
            for (int i = 0; i < 10000; ++i)
                push_d(st, &a);
            for (int i = 0; i < 10000; ++i)
                pop_d(st);
        }

        stack_dtr(st);

        t2 = clock();

        double time = (double)(1000*(t2-t1))/CLOCKS_PER_SEC;
        fprintf(result, "%3d: %.2f ms\n", testnum+1, time);

        sum_time += time;
    }

    fprintf(result, "\nAverage time: %.2f ms\n\n", sum_time/number_of_tests);
}

static void third_test(int number_of_tests, FILE *result)
{
    double sum_time = 0;

    fprintf(result, "Test 3\n\n");

    for (int testnum = 0; testnum < number_of_tests; ++testnum)
    {
        clock_t t1 = 0,
                t2 = 0;
        
        Stack_d* st = stack_ctr(10, 4);

        int a = 1;

        for (int i = 0; i < 10e6; ++i)
            push_d(st, &a);
    
        t1 = clock();
        
        for (int i = 0; i < 10e6; ++i)
        {
            int rnd = rand()%2 + 1;

            if (rnd == 1)
            {
                push_d(st, &a);
            }
            else
            {
                pop_d(st);
            }
        }

        stack_dtr(st);

        t2 = clock();

        double time = (double)(1000*(t2-t1))/CLOCKS_PER_SEC;
        fprintf(result, "%3d: %.2f ms\n", testnum+1, time);

        sum_time += time;
    }

    fprintf(result, "\nAverage time: %.2f ms\n\n", sum_time/number_of_tests);
}

