#include <stdlib.h>
#include <stdio.h>

int main()
{
    // Generate data
    const unsigned arraySize = 32768;
    int data[arraySize];

    srand(1);
    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = rand() % 256;

    // Test
    long long sum = 0;

    for (unsigned i = 0; i < 100000; ++i)
    {
        // Primary loop
        for (unsigned c = 0; c < arraySize; ++c)
        {
            if (data[c] >= 128)
                sum += data[c];
        }
    }
    printf("sum=%lld\n", sum);
    return 0;
}

