#include <iostream>
#include "Cache.cpp"

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

    Cache cache (size * 0.9f, size - size * 0.9f);

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
