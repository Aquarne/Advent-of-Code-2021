#include <stdio.h>

int main()
{
    int pos = 0;
    int depth = 0;
    char cmd[8];
    int x;

    while (!feof(stdin))
    {
        scanf(" %7s  %d ", cmd, &x);
        
        switch(cmd[0])
        {
            case 'f':
                pos += x;
                break;
            
            case 'u':
                x = -x;
            case 'd':
                depth += x;
                break;
        }
    }

    printf("%d * %d = %d\n", pos, depth, pos * depth);

    return 0;
}
