#include <cstring>
#include <ctime>
#include <malloc.h>
#include <random>

#include "Stack_list.hpp"

//------------------------------------------------------------

static void list_dtor   (list *lst);
static void first_test  (int number_of_tests, FILE *result);
static void second_test (int number_of_tests, FILE *result);
static void third_test  (int number_of_tests, FILE *result);

//------------------------------------------------------------

Stack_l *lstack_ctr(size_t element_size)
{
    Stack_l *st      = (Stack_l *)calloc(1, sizeof(Stack_l));
    st->content      = nullptr;
    st->element_size = element_size;  

    return st;  
}

int push_l(Stack_l *st, void *buff)
{
    list *content = (list *)calloc(1, sizeof(list));
    content->next = st->content;
    content->data = calloc(1, st->element_size);

    memcpy(content->data, buff, st->element_size); 

    st->content = content;  

    return 1; 
}

int top_l(Stack_l *st, void  *buff)
{
    if (st->content == nullptr)
        return 0;

    memcpy(buff, st->content->data, st->element_size);

    return 1;
}

int pop_l(Stack_l *st)
{
    if (st->content == nullptr)
        return 0;

    list *content = st->content;

    st->content = st->content->next;

    free(content->data);
    free(content);

    return 1;
}

Stack_l *lstack_dtr (Stack_l *st)
{
    list_dtor(st->content);
    free(st);

    return nullptr;
}

static void list_dtor(list *lst)
{
    if (lst == nullptr)
        return;

    list *list = lst,
         *next = lst->next;

    while (next != nullptr)
    {
        free(list);
        list = next;
        next = next->next;
    }

    free(list);
    
}

//------------------------------------------------------------

void stack_tests_l(FILE *result, int number_of_tests)
{

    fprintf(result, "Stack on the list\n");
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

        t1 = clock();
        
        Stack_l* st = lstack_ctr(4);

        int a = 1;

        for (int i = 0; i < 10e6; ++i)
            push_l(st, &a);
        
        int count = 10e6;
        for (int j = 0; j < 9; ++j)
        {
            count = count*3/4;
            for (int i = 0; i < count; ++i)
                pop_l(st);
            for (int i = 0; i < count/2; ++i)
                push_l(st, &a);
        }

        lstack_dtr(st);

        t2 = clock();

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
        
        Stack_l* st = lstack_ctr(4);

        int a = 1;

        for (int j = 0; j < 100; ++j)
        {
            for (int i = 0; i < 10000; ++i)
                push_l(st, &a);
            for (int i = 0; i < 10000; ++i)
                pop_l(st);
        }

        for (int i = 0; i < 10e6; ++i)
            push_l(st, &a);
        
        int count = 10e6;
        for (int j = 0; j < 9; ++j)
        {
            count = count*3/4;
            for (int i = 0; i < count; ++i)
                pop_l(st);
            for (int i = 0; i < count/2; ++i)
                push_l(st, &a);
        }

        for (int j = 0; j < 100; ++j)
        {
            for (int i = 0; i < 10000; ++i)
                push_l(st, &a);
            for (int i = 0; i < 10000; ++i)
                pop_l(st);
        }

        lstack_dtr(st);

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
        
        Stack_l* st = lstack_ctr(4);

        int a = 1;

        for (int i = 0; i < 10e6; ++i)
            push_l(st, &a);
    
        t1 = clock();

        fflush(stdout);

        for (int i = 0; i < 10e6; ++i)
        {
            int rnd = rand()%2 + 1;

            if (rnd == 1)
            {
                push_l(st, &a);
            }
            else
            {
                pop_l(st);
            }
        }

        lstack_dtr(st);

        t2 = clock();

        double time = (double)(1000*(t2-t1))/CLOCKS_PER_SEC;
        fprintf(result, "%3d: %.2f ms\n", testnum+1, time);

        sum_time += time;
    }

    fprintf(result, "\nAverage time: %.2f ms\n\n", sum_time/number_of_tests);
}
