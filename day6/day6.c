#include <stdio.h>
#include <stdlib.h>

#define MAX_FISH 100000000
#define MAX_DAYS_PART1 80
#define MAX_DAYS_PART2 256
#define FISH_BIRTH_TIMER 8
#define FISH_REPOP_TIMER 6

void part1()
{
    int rc, numFish, tmp, day, fish;
    short *fishArray;
    FILE *fp;

    fishArray = (short *)malloc(MAX_FISH * sizeof(short));
    if (fishArray == NULL)
        goto mallocError1;

    fp = fopen("input6.txt", "r");

    numFish = 0;
readInput1:
    rc = fscanf(fp, "%d,", &tmp);
    if (rc == EOF)
        goto readInputEnd1;
    fishArray[numFish] = tmp;
    ++numFish;
    goto readInput1;
readInputEnd1:
    fclose(fp);

    day = 0;
loopDay1:
    if (day == MAX_DAYS_PART1)
        goto loopDayEnd1;

    // Iterate through all the fish, start at the end so that the new fish can be added
    fish = numFish - 1;
loopFish1:
    if (fish < 0)
        goto loopFishEnd1;

    // Decrease fish timer
    fishArray[fish]--;
    if (fishArray[fish] < 0)
        goto spawnFish1;
    goto spawnFishEnd1;
spawnFish1:
    fishArray[fish] = FISH_REPOP_TIMER;
    fishArray[numFish] = FISH_BIRTH_TIMER;
    ++numFish;

    if (numFish >= MAX_FISH)
        goto fishOverflow1;
spawnFishEnd1:

    --fish;
    goto loopFish1;
loopFishEnd1:
    ++day;
    goto loopDay1;
loopDayEnd1:

    printf("Total: %d\n", numFish);
    goto mallocErrorEnd1;
mallocError1:
    printf("Malloc error");
mallocErrorEnd1:
    goto fishOverflowEnd1;
fishOverflow1:
    printf("!!!! FISH OVERFLOW !!!!\n");
    printf("Day: %d, fish: %d, count: %d\n", day, fish, numFish);
fishOverflowEnd1:

    free(fishArray);
}

void part2()
{
    int rc, i, tmp, day, fishCounter;
    long birthFishCount, numFish, fishArray[FISH_BIRTH_TIMER + 1]; // Include number 8
    FILE *fp;

    i = 0;
initArray2:
    if (i == FISH_BIRTH_TIMER + 1)
        goto initArrayEnd2;
    fishArray[i] = 0;
    ++i;
    goto initArray2;
initArrayEnd2:

    fp = fopen("input6.txt", "r");
readInput2:
    rc = fscanf(fp, "%d,", &tmp);
    if (rc == EOF)
        goto readInputEnd2;
    fishArray[tmp]++;
    goto readInput2;
readInputEnd2:
    fclose(fp);

    day = 0;
loopDay2:
    if (day == MAX_DAYS_PART2)
        goto loopDayEnd2;

    // Iterate through all the fish counters and shift values.
    // Memorize number of fish that spawned new fish and readd that value
    // to repop timer and birth timer.
    birthFishCount = fishArray[0];
    fishCounter = 0;
loopFishCounter2:
    if (fishCounter == FISH_BIRTH_TIMER)
        goto loopFishCounterEnd2;

    fishArray[fishCounter] = fishArray[fishCounter + 1];

    ++fishCounter;
    goto loopFishCounter2;
loopFishCounterEnd2:
    fishArray[FISH_REPOP_TIMER] += birthFishCount;
    fishArray[FISH_BIRTH_TIMER] = birthFishCount;

    ++day;
    goto loopDay2;
loopDayEnd2:

    // Sum number of fish in array
    numFish = 0;
    i = 0;
countFinalNumOfFish:
    if (i == FISH_BIRTH_TIMER + 1)
        goto countFinalNumOfFishEnd2;

    numFish += fishArray[i];
    ++i;
    goto countFinalNumOfFish;
countFinalNumOfFishEnd2:

    printf("Total: %ld\n", numFish);
}

int main(int argc, char *argv[])
{
    part1();
    part2();
    return 0;
}
