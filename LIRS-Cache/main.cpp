#include <iostream>
#include "Cache.hpp"

const char* DUMP = "dump.txt";

void testFromPaper (Cache *cache)
{
    FILE *dump = fopen (DUMP, "w");
    if (dump == nullptr)
        return;

    #define TEST(num)                                                         \
    fprintf (dump, "----------------Access " #num "----------------\n");      \
    cache->hit (num);                                                         \
    cache->printState (dump);

    TEST(1);
    TEST(4);
    TEST(2);
    TEST(3);
    TEST(2);
    TEST(1);
    TEST(4);
    TEST(1);
    TEST(5);

    #undef TEST

    cache->printState (stdout);
    
}

int main ()
{
    int size;
    scanf ("%d", &size);

    if (size <= 0)
    {
        printf ("0 hits. Definitely. Why do you need a cache at all?\n");
        return 0;
    }

    Cache cache ((int)(0.9f * size), size - (int)(0.9f * size));

    int hits = 0, n, page;
    scanf ("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf ("%d", &page);
        hits += cache.hit (page);
    }

    printf ("%d hits\n", hits);
    return 0;
}
