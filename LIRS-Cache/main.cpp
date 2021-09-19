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
    Cache cache (3, 2);
    testFromPaper (&cache);
}
