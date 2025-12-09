#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int throw_at_rectangle(double x, double y, double x1, double y1, double x2, double y2)
{
    if (x1 == x2 || y1 == y2) // checks if valid rectangle
    {
        printf("Not a valid rectangle!\n");
        return 0;
    }

    if (x == x1 || x == x2 || y == y1 || y == y2)
    {
        return 3;
    }

    if (x > x1 && x < x2 && y > y1 && y < y2)
    {
        return 5;
    }

    if (x > x1 && x < x2 && y < y1 && y > y2)
    {
        return 5;
    }

    if (x < x1 && x > x2 && y > y1 && y < y2)
    {
        return 5;
    }

    if (x < x1 && x > x2 && y < y1 && y > y2)
    {
        return 5;
    }
    else
    {
        return 0;
    }
}

int test_deicmal_values()
{
    int result;
    const int expected = 0;
    result = throw_at_rectangle(3.5, 3.5, 2.12412, 3.1415, 2.7, 5.12512);
    if (result == expected)
    {
        // printf("test decimal values succeeded !\n");
        return 1;
    }
    else
    {
        printf("test decimal values failed !\n");
        return 0;
    }
}

int test_x1_equals_x2()
{
    int result;
    const int expected = 0;
    result = throw_at_rectangle(2, 3, 4, 6, 4, 3);
    if (result == expected)
    {
        // printf("test x1 = x2 succeeded !\n");
        return 1;
    }
    else
    {
        printf("test x1 = x2 failed !\n");
        return 0;
    }
}

int test_hitting_the_edge()
{
    int result;
    const int expected = 3;
    result = throw_at_rectangle(2, 3, 2, 4, 6, 7);
    if (result == expected)
    {
        // printf("test hitting the edge succeeded !\n");
        return 1;
    }
    else
    {
        printf("test hitting the edge failed !\n");
        return 0;
    }
}

int test_x1_bigger_than_x2()
{
    int result;
    const int expected = 5;
    result = throw_at_rectangle(3, 3, 5, 1, 1, 5);
    if (result == expected)
    {
        // printf("test x1 bigger than x2 succeeded !\n");
        return 1;
    }
    else
    {
        printf("test x1 bigger than x2 failed !\n");
        return 0;
    }
}

int hitting_corner()
{
    int result;
    const int expected = 3;
    result = throw_at_rectangle(3, 3, 1, 3, 1, 3);
    if (result == expected)
    {
        // printf("test y1 bigger than y2 succeeded !\n");
        return 1;
    }
    else
    {
        printf("test hitting corner failed !\n");
        return 0;
    }
}

int test_negative_values()
{
    int result;
    const int expected = 5;
    result = throw_at_rectangle(-3, -3, -5, -5, -1, -1);
    if (result == expected)
    {
        // printf("test negative values succeeded !\n");
        return 1;
    }
    else
    {
        printf("test negative values failed !\n");
        return 0;
    }
}

void main()
{
    int success_count = 0;
    if (test_deicmal_values() == 1)
    {
        success_count++;
    }
    if (test_hitting_the_edge() == 1)
    {
        success_count++;
    }
    if (test_negative_values() == 1)
    {
        success_count++;
    }
    if (test_x1_bigger_than_x2() == 1)
    {
        success_count++;
    }
    if (test_x1_equals_x2() == 1)
    {
        success_count++;
    }
    if (test_hitting_the_edge() == 1)
    {
        success_count++;
    }
    if (success_count == 6)
        printf("All tests were successful!\n");
}