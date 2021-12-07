#include <stdio.h>

#define FLOOR_SIZE 1000

void part1()
{
    int rc, i, j, x1, x2, y1, y2, numOverlapped;
    short floor[FLOOR_SIZE][FLOOR_SIZE];
    FILE *fp;

    fp = fopen("input5.txt", "r");

    i = 0;
initFloorX1:
    if (i == FLOOR_SIZE)
        goto initFloorXEnd1;
    j = 0;
initFloorY1:
    if (j == FLOOR_SIZE)
        goto initFloorYEnd1;
    floor[i][j] = 0;
    ++j;
    goto initFloorY1;
initFloorYEnd1:
    ++i;
    j = 0;
    goto initFloorX1;
initFloorXEnd1:

readInput1:
    rc = fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
    if (rc == EOF)
        goto readInputEnd1;

    // Skip if line is diagonal
    if (x1 != x2 && y1 != y2)
        goto readInput1;
    i = x1;
    j = y1;
iterateLine1:
    floor[i][j]++;

    if (i == x2 && j == y2)
        goto iterateLineEnd1;
    if (y1 < y2)
        ++j;
    if (y1 > y2)
        --j;
    if (x1 < x2)
        ++i;
    if (x1 > x2)
        --i;
    goto iterateLine1;
iterateLineEnd1:

    goto readInput1;
readInputEnd1:

    numOverlapped = 0;
    i = 0;
iterateResultFloorX1:
    if (i == FLOOR_SIZE)
        goto iterateResultFloorXEnd1;
    j = 0;
iterateResultFloorY1:
    if (j == FLOOR_SIZE)
        goto iterateResultFloorYEnd1;

    if (floor[i][j] > 1)
        ++numOverlapped;

    ++j;
    goto iterateResultFloorY1;
iterateResultFloorYEnd1:
    ++i;
    j = 0;
    goto iterateResultFloorX1;
iterateResultFloorXEnd1:

    printf("Num: %d\n", numOverlapped);
    fclose(fp);
}

void part2()
{
    // Identical to part 1 except that we can safely remove diagonal condition
    int rc, i, j, x1, x2, y1, y2, numOverlapped;
    short floor[FLOOR_SIZE][FLOOR_SIZE];
    FILE *fp;

    fp = fopen("input5.txt", "r");

    i = 0;
initFloorX2:
    if (i == FLOOR_SIZE)
        goto initFloorXEnd2;
    j = 0;
initFloorY2:
    if (j == FLOOR_SIZE)
        goto initFloorYEnd2;
    floor[i][j] = 0;
    ++j;
    goto initFloorY2;
initFloorYEnd2:
    ++i;
    j = 0;
    goto initFloorX2;
initFloorXEnd2:

readInput2:
    rc = fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
    if (rc == EOF)
        goto readInputEnd2;

    i = x1;
    j = y1;
iterateLine2:
    floor[i][j]++;

    if (i == x2 && j == y2)
        goto iterateLineEnd2;
    if (y1 < y2)
        ++j;
    if (y1 > y2)
        --j;
    if (x1 < x2)
        ++i;
    if (x1 > x2)
        --i;
    goto iterateLine2;
iterateLineEnd2:

    goto readInput2;
readInputEnd2:

    numOverlapped = 0;
    i = 0;
iterateResultFloorX2:
    if (i == FLOOR_SIZE)
        goto iterateResultFloorXEnd2;
    j = 0;
iterateResultFloorY2:
    if (j == FLOOR_SIZE)
        goto iterateResultFloorYEnd2;

    if (floor[i][j] > 1)
        ++numOverlapped;

    ++j;
    goto iterateResultFloorY2;
iterateResultFloorYEnd2:
    ++i;
    j = 0;
    goto iterateResultFloorX2;
iterateResultFloorXEnd2:

    printf("Num: %d\n", numOverlapped);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    part1();
    part2();

    return 0;
}
