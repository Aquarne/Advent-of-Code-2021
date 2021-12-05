#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point
{
    int x;
    int y;
};

struct point_array
{
    int count;
    int capacity;
    struct point *points;
};

void point_array_init(struct point_array *array);
void point_array_destroy(struct point_array *array);
void point_array_add(struct point_array *array, struct point point);

struct int_grid
{
    int width;
    int height;
    int *values;
};

void int_grid_init(struct int_grid *grid);
void int_grid_destroy(struct int_grid *grid);
void int_grid_set(struct int_grid *grid, int x, int y, int value);
int int_grid_get(struct int_grid *grid, int x, int y);

static void draw_line(struct int_grid *grid, struct point p1, struct point p2);

int main()
{
    int count = 0;
    struct point_array points;
    struct int_grid grid;

    point_array_init(&points);
    int_grid_init(&grid);

    {
        struct point p1, p2;

        while (!feof(stdin))
        {
            scanf(
                " %d %*c %d %*c%*c %d %*c %d ",
                &p1.x, &p1.y, &p2.x, &p2.y
            );
            
            point_array_add(&points, p1);
            point_array_add(&points, p2);
        }
    }

    for (int i = 0; i < points.count; i += 2)
    {
        struct point p1 = points.points[i];
        struct point p2 = points.points[i + 1];

        if ((p1.x >= p2.x && p1.y >= p2.y) || (p1.x > p2.x && p1.y < p2.y))
        {
            draw_line(&grid, p2, p1);
        }
        else
        {
            draw_line(&grid, p1, p2);
        }
    }

    int grid_count = grid.width * grid.height;
    for (int i = 0; i < grid_count; ++i)
    {
        count += grid.values[i] > 1;
    }

    printf("%d\n", count);

    point_array_destroy(&points);
    int_grid_destroy(&grid);

    return 0;
}

static void draw_line(struct int_grid *grid, struct point p1, struct point p2)
{
    int offset_x = p2.x - p1.x;
    int offset_y = p2.y - p1.y;

    if (offset_x == 0)
    {
        int x = p1.x;
        for (int y = p1.y; y <= p2.y; ++y)
        {
            int_grid_set(
                grid, x, y,
                int_grid_get(grid, x, y) + 1
            );
        }
    }
    else if (offset_y == 0)
    {
        int y = p1.y;
        for (int x = p1.x; x <= p2.x; ++x)
        {
            int_grid_set(
                grid, x, y,
                int_grid_get(grid, x, y) + 1
            );
        }
    }
    else if (offset_x == offset_y)
    {
        int x = p1.x;
        int y = p1.y;

        for (int i = 0; i <= offset_x; ++i)
        {
            int_grid_set(
                grid, x, y,
                int_grid_get(grid, x, y) + 1
            );

            ++x; ++y;
        }
    }
    else
    {
        int x = p1.x;
        int y = p1.y;

        for (int i = 0; i <= offset_x; ++i)
        {
            int_grid_set(
                grid, x, y,
                int_grid_get(grid, x, y) + 1
            );

            ++x; --y;
        }
    }
}

void point_array_init(struct point_array *array)
{
    array->count = 0;
    array->capacity = 0;
    array->points = NULL;
}

void point_array_destroy(struct point_array *array)
{
    free(array->points);
    point_array_init(array);
}

void point_array_add(struct point_array *array, struct point point)
{
    if (array->count + 1 > array->capacity)
    {
        array->capacity =
            array->capacity < 25 ?
                25 :
                array->capacity * 2;
        array->points = realloc(
            array->points,
            array->capacity * sizeof(struct point)
        );
    }

    array->points[array->count] = point;
    ++array->count;
}

void int_grid_init(struct int_grid *grid)
{
    grid->width = 0;
    grid->height = 0;
    grid->values = NULL;
}

void int_grid_destroy(struct int_grid *grid)
{
    free(grid->values);
    int_grid_init(grid);
}

void int_grid_set(struct int_grid *grid, int x, int y, int value)
{
    while (x + 1 > grid->width)
    {
        int old_width = grid->width;
        grid->width =
            grid->width < 500 ?
                500 :
                grid->width * 2;

        int *new_grid = malloc(grid->width * grid->height * sizeof(int));
        for (int i = 0; i < grid->height; ++i)
        {
            int old_offset = i * old_width;
            int offset = i * grid->width;

            for (int j = 0; j < old_width; ++j)
            {
                new_grid[offset + j] = grid->values[old_offset + j];
            }

            for (int j = old_width; j < grid->width; ++j)
            {
                new_grid[offset + j] = 0;
            }
        }

        free(grid->values);
        grid->values = new_grid;
    }

    while (y + 1 > grid->height)
    {
        int old_endpoint = grid->width * grid->height;
        grid->height =
            grid->height < 500 ?
                500 :
                grid->height * 2;
        grid->values = realloc(
            grid->values,
            grid->width * grid->height * sizeof(int)
        );
        
        memset(grid->values + old_endpoint, 0, (grid->width * grid->height - old_endpoint) * sizeof(int));
    }

    grid->values[y * grid->width + x] = value;
}

int int_grid_get(struct int_grid *grid, int x, int y)
{
    if (x >= grid->width || y >= grid->height)
    {
        return 0;
    }

    return grid->values[y * grid->width + x];
}
