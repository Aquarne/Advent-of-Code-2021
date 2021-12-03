#include <stdio.h>
#include <stdlib.h>

#define BINARY_LEN 12
#define _CSTR(x) #x
#define CSTR(x) _CSTR(x)

struct binary_string_array
{
    unsigned int count;
    unsigned int capacity;
    char *digits;
};

static void array_init(struct binary_string_array *array);
static void array_destroy(struct binary_string_array *array);
static void array_write(struct binary_string_array *array, const char *binary_string);
static void array_copy(struct binary_string_array *dst, const struct binary_string_array *src);

static int get_oxygen_rating(const struct binary_string_array *const array, unsigned int start);
static int get_co2_rating(const struct binary_string_array *const array, unsigned int start);

int main()
{
    int oxygen_rating = 0;
    int co2_rating = 0;
    struct binary_string_array b0, b1;
    char b[BINARY_LEN+1];

    array_init(&b0);
    array_init(&b1);

    while (!feof(stdin))
    {
        scanf(" %" CSTR(BINARY_LEN) "s ", b);

        if (b[0] == '0')
        {
            array_write(&b0, b);
        }
        else
        {
            array_write(&b1, b);
        }
    }

    if (b1.count >= b0.count)
    {
        oxygen_rating = get_oxygen_rating(&b1, 1);
        co2_rating = get_co2_rating(&b0, 1);
    }
    else
    {
        oxygen_rating = get_oxygen_rating(&b0, 1);
        co2_rating = get_co2_rating(&b1, 1);
    }

    printf("%d * %d = %d\n", oxygen_rating, co2_rating, oxygen_rating * co2_rating);

    array_destroy(&b0);
    array_destroy(&b1);

    return 0;
}

static int binary_string_to_int(const char *binary_string)
{
    int value = 0;
    for (int i = 0; i < BINARY_LEN; ++i)
    {
        value = (value << 1) | (binary_string[i] - '0');
    }
    return value;
}

static int get_oxygen_rating(const struct binary_string_array *const array, unsigned int start)
{
    struct binary_string_array current;
    struct binary_string_array b0, b1;

    array_init(&current);
    array_copy(&current, array);

    array_init(&b0);
    array_init(&b1);

    for (int i = start; i < BINARY_LEN; ++i)
    {
        if (current.count == 1)
            break;

        for (int j = i; j < current.count; j += BINARY_LEN)
        {
            char b = current.digits[j];
            if (b == '0')
            {
                array_write(&b0, current.digits + (j - i));
            }
            else
            {
                array_write(&b1, current.digits + (j - i));
            }
        }

        if (b1.count >= b0.count)
        {
            array_copy(&current, &b1);
        }
        else
        {
            array_copy(&current, &b0);
        }

        b0.count = 0;
        b1.count = 0;
    }

    int oxygen_rating = binary_string_to_int(current.digits);

    array_destroy(&current);
    array_destroy(&b0);
    array_destroy(&b1);

    return oxygen_rating;
}

static int get_co2_rating(const struct binary_string_array *const array, unsigned int start)
{
    struct binary_string_array current;
    struct binary_string_array b0, b1;

    array_init(&current);
    array_copy(&current, array);

    array_init(&b0);
    array_init(&b1);

    for (int i = start; i < BINARY_LEN; ++i)
    {
        if (current.count == 1)
            break;

        for (int j = i; j < current.count; j += BINARY_LEN)
        {
            char b = current.digits[j];
            if (b == '0')
            {
                array_write(&b0, current.digits + (j - i));
            }
            else
            {
                array_write(&b1, current.digits + (j - i));
            }
        }

        if (b0.count <= b1.count)
        {
            array_copy(&current, &b0);
        }
        else
        {
            array_copy(&current, &b1);
        }

        b0.count = 0;
        b1.count = 0;
    }

    int co2_rating = binary_string_to_int(current.digits);

    array_destroy(&current);
    array_destroy(&b0);
    array_destroy(&b1);

    return co2_rating;
}

static void array_init(struct binary_string_array *array)
{
    array->count = 0;
    array->capacity = 0;
    array->digits = NULL;
}

static void array_destroy(struct binary_string_array *array)
{
    free(array->digits);
    array_init(array);
}

static void array_write(struct binary_string_array *array, const char *binary_string)
{
    if (array->count + BINARY_LEN > array->capacity)
    {
        array->capacity =
            array->capacity < 120 ?
                120 :
                array->capacity * 10;
        array->digits = realloc(
            array->digits,
            array->capacity
        );
    }

    for (int i = 0; i < BINARY_LEN; ++i)
    {
        array->digits[array->count + i] = binary_string[i];
    }

    array->count += BINARY_LEN;
}

static void array_copy(struct binary_string_array *dst, const struct binary_string_array *src)
{
    if (dst->capacity < src->count)
    {
        dst->capacity = src->count;
        dst->digits = realloc(
            dst->digits,
            dst->capacity
        );
    }

    dst->count = src->count;
    for (int i = 0; i < dst->count; ++i)
    {
        dst->digits[i] = src->digits[i];
    }
}
