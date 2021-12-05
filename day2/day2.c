#include <stdio.h>
#include <string.h>

void part1()
{
    char command[100];
    int amount, depth, position, rc;
    FILE *fp;

    fp = fopen("input2.txt", "r");

    depth = 0;
    position = 0;

loop1:
    rc = fscanf(fp, "%s %d", command, &amount);
    if (rc == EOF)
        goto end1;

    if (strcmp(command, "forward") == 0)
        position += amount;
    if (strcmp(command, "down") == 0)
        depth += amount;
    if (strcmp(command, "up") == 0)
        depth -= amount;

    goto loop1;

end1:
    printf("%d %d %d\n", position, depth, position * depth);
    fclose(fp);
}

void part2()
{
    char command[100];
    int amount, depth, position, aim, rc;
    FILE *fp;

    fp = fopen("input2.txt", "r");

    depth = 0;
    position = 0;
    aim = 0;

loop2:
    rc = fscanf(fp, "%s %d", command, &amount);
    if (rc == EOF)
        goto end2;

    if (strcmp(command, "down") == 0)
        goto aimIncrease;
    if (strcmp(command, "up") == 0)
        goto aimDecrease;
    if (strcmp(command, "forward") == 0)
        goto aimCalc;
    goto aimEnd;
aimIncrease:
    aim += amount;
    goto aimEnd;
aimDecrease:
    aim -= amount;
    goto aimEnd;
aimCalc:
    position += amount;
    depth += aim * amount;
    goto aimEnd;
aimEnd:

    goto loop2;

end2:
    printf("%d %d %d %d\n", position, depth, aim, position * depth);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    part1();
    part2();

    return 0;
}
