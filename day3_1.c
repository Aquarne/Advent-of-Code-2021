#include <stdio.h>
#include <string.h>

#define BINARY_LEN 12
#define _CSTR(x) #x
#define CSTR(x) _CSTR(x)

int main()
{
    int gamma = 0;
    int epsilon = 0;
    int count[BINARY_LEN][2];
    char b[BINARY_LEN+1];

    memset(count, 0, sizeof(count));

    while (!feof(stdin))
    {
        scanf(" %" CSTR(BINARY_LEN) "s ", b);

        for (int i = 0; i < BINARY_LEN; ++i)
        {
            ++count[i][b[i]-'0'];
        }
    }

    for (int i = 0; i < BINARY_LEN; ++i)
    {
        int least = count[i][0] > count[i][1];
        epsilon = (epsilon << 1) | least;
        gamma = (gamma << 1) | !least;
    }

    printf("%d * %d = %d\n", gamma, epsilon, gamma * epsilon);

    return 0;
}
