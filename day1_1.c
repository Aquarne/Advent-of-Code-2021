#include <stdio.h>

int main()
{
    int count = 0;
    int prev, current;

    scanf("%d ", &prev);

    while (!feof(stdin))
    {
        scanf("%d ", &current);

        if (current > prev)
        {
            ++count;
        }

        prev = current;
    }

    printf("%d\n", count);

    return 0;
}
