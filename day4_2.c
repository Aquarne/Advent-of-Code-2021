#include <stdio.h>
#include <stdlib.h>

struct int_array
{
    int count;
    int capacity;
    int *values;
};

static void int_array_init(struct int_array *array);
static void int_array_destroy(struct int_array *array);
static void int_array_add(struct int_array *array, int value);

int main()
{
    unsigned int board_count = 0;
    unsigned int boards_won = 0;
    struct int_array board_sums;
    struct int_array board_marked_sums;
    struct int_array board_marked_pos;
    struct int_array board_wins;
    struct int_array boards;
    struct int_array numbers;

    int_array_init(&board_sums);
    int_array_init(&board_marked_sums);
    int_array_init(&board_marked_pos);
    int_array_init(&board_wins);
    int_array_init(&boards);
    int_array_init(&numbers);

    {
        int n;
        char last;

        do
        {
            scanf(" %d ", &n);
            int_array_add(&numbers, n);
        }
        while ((last = fgetc(stdin)) == ',');

        ungetc(last, stdin);
    }

    {
        int sum = 0;
        int n;

        while (!feof(stdin))
        {
            for (int i = 0; i < 25; ++i)
            {
                scanf(" %d ", &n);
                sum += n;
                int_array_add(&boards, n);
            }

            int_array_add(&board_sums, sum);
            sum = 0;
        }

        board_count = board_sums.count;
    }

    for (int i = 0; i < board_count; ++i)
    {
        int_array_add(&board_marked_sums, 0);
    }

    for (int i = 0; i < board_count; ++i)
    {
        int_array_add(&board_wins, 0);
    }

    {
        int count = board_count * 10;
        for (int i = 0; i < count; ++i)
        {
            int_array_add(&board_marked_pos, 0);
        }
    }

    int board_index = 0;
    int n = 0;
    for (int ni = 0; ni < numbers.count; ++ni)
    {
        n = numbers.values[ni];
        for (int bi = 0; bi < board_count; ++bi)
        {
            int boffset = 25 * bi;
            for (int i = 0; i < 5; ++i)
            {
                for (int j = 0; j < 5; ++j)
                {
                    int bn = boards.values[boffset + 5 * i + j];
                    if (bn == n)
                    {
                        board_marked_sums.values[bi] += bn;

                        int poffset = 10 * bi;
                        int row = ++board_marked_pos.values[poffset + i];
                        int col = ++board_marked_pos.values[poffset + 5 + j];

                        if (row == 5 || col == 5)
                        {
                            if (board_wins.values[bi] == 0)
                            {
                                board_index = bi;

                                ++boards_won;

                                if (boards_won == board_count)
                                {
                                    // end all loops.
                                    ni = numbers.count;
                                    bi = boards.count;
                                }
                            }

                            ++board_wins.values[bi];
                        }

                        // end board loop.
                        i = 5;
                        j = 5;
                    }
                }
            }
        }
    }

    int unmarked_sum = board_sums.values[board_index] - board_marked_sums.values[board_index];
    printf("(%d) %d * %d = %d\n", board_index, unmarked_sum, n, unmarked_sum * n);

    int_array_destroy(&board_sums);
    int_array_destroy(&board_marked_sums);
    int_array_destroy(&board_marked_pos);
    int_array_destroy(&board_wins);
    int_array_destroy(&boards);
    int_array_destroy(&numbers);

    return 0;
}

static void int_array_init(struct int_array *array)
{
    array->count = 0;
    array->capacity = 0;
    array->values = NULL;
}

static void int_array_destroy(struct int_array *array)
{
    free(array->values);
    int_array_init(array);
}

static void int_array_add(struct int_array *array, int value)
{
    if (array->count + 1 > array->capacity)
    {
        array->capacity =
            array->capacity < 25 ?
                25 :
                array->capacity * 2;
        array->values = realloc(
            array->values,
            array->capacity * sizeof(int)
        );
    }

    array->values[array->count] = value;
    ++array->count;
}
