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

int test_all_zero()
{
    int result;
    const int expected = 0;
    result = throw_at_rectangle(0, 0, 0, 0, 0, 0);
    if (result == expected)
    {
        printf("testx succeeded !\n");
        return 1;
    }
    else
    {
        printf("testx failed !\n");
        return 0;
    }
}

int test_valid_rect() {}

void main()
{
    test_all_zero();
}