#include <stdio.h>

void part1()
{
    int count, currNum, prevNum, rc;
    FILE *fp;

    fp = fopen("input1.txt", "r");

    count = 0;
    rc = fscanf(fp, "%d", &prevNum);
    if (rc == EOF)
        goto end;

loop:
    rc = fscanf(fp, "%d", &currNum);
    if (currNum > prevNum)
        ++count;

    prevNum = currNum;

    if (rc == EOF)
        goto end;
    goto loop;

end:
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
        goto end;
    rc = fscanf(fp, "%d", &val2);
    if (rc == EOF)
        goto end;
    rc = fscanf(fp, "%d", &val3);
    if (rc == EOF)
        goto end;

loop:
    rc = fscanf(fp, "%d", &nextVal);
    if (rc == EOF)
        goto end;

    if (val1 + val2 + val3 < val2 + val3 + nextVal)
        ++count;

    val1 = val2;
    val2 = val3;
    val3 = nextVal;
    goto loop;

end:
    printf("%d\n", count);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    part1();
    part2();

    return 0;
}
