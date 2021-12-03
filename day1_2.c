#include <stdio.h>

int main()
{
    int count = 0;
    int n[4];
    int sum1, sum2;

    for (int i = 0; i < 3; ++i)
    {
        scanf("%d ", n+i);
    }

    while (!feof(stdin))
    {
        scanf("%d ", n+3);

        sum1 = n[1] + n[2] + n[3];
        sum2 = n[0] + n[1] + n[2];

        if (sum1 > sum2)
        {
            ++count;
        }

        for (int i = 1; i < 4; ++i)
        {
            n[i-1] = n[i];
        }
    }

    printf("%d\n", count);

    return 0;
}
