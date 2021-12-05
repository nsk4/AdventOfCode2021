#include <stdio.h>

void part1()
{
    int count, currNum, prevNum, rc;
    FILE *fp;

    fp = fopen("input1.txt", "r");

    count = 0;
    rc = fscanf(fp, "%d", &prevNum);
    if (rc == EOF)
        goto end1;

loop1:
    rc = fscanf(fp, "%d", &currNum);
    if (rc == EOF)
        goto end1;
    if (currNum > prevNum)
        ++count;

    prevNum = currNum;

    goto loop1;

end1:
    printf("%d\n", count);
    fclose(fp);
}

void part2()
{
    int count, rc, val1, val2, val3, nextVal;
    FILE *fp;

    fp = fopen("input1.txt", "r");

    count = 0;

    rc = fscanf(fp, "%d", &val1);
    if (rc == EOF)
        goto end2;
    rc = fscanf(fp, "%d", &val2);
    if (rc == EOF)
        goto end2;
    rc = fscanf(fp, "%d", &val3);
    if (rc == EOF)
        goto end2;

loop2:
    rc = fscanf(fp, "%d", &nextVal);
    if (rc == EOF)
        goto end2;

    if (val1 + val2 + val3 < val2 + val3 + nextVal)
        ++count;

    val1 = val2;
    val2 = val3;
    val3 = nextVal;
    goto loop2;

end2:
    printf("%d\n", count);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    part1();
    part2();

    return 0;
}
