#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BIT_COUNT 12
#define MAX_ROWS 3000

void part1()
{
    char bitText[BIT_COUNT + 1];
    int rc, totalRows, positiveBits[BIT_COUNT], i, gammaRate, epsilonRate;
    FILE *fp;

    fp = fopen("input3.txt", "r");
    totalRows = 0;

    // Init array to 0
    i = 0;
initArrayLoop1:
    if (i == BIT_COUNT)
        goto initArrayLoopEnd1;
    positiveBits[i] = 0;
    ++i;
    goto initArrayLoop1;
initArrayLoopEnd1:

loop1:
    rc = fscanf(fp, "%s", bitText);
    if (rc == EOF)
        goto end1;

    ++totalRows;

    // Process read string
    i = 0;
dataLoop1:
    if (i == BIT_COUNT)
        goto dataLoopEnd1;
    if (bitText[i] == '1')
        ++positiveBits[i];
    ++i;
    goto dataLoop1;
dataLoopEnd1:

    goto loop1;

end1:

    // Calc correct digits
    gammaRate = 0;
    epsilonRate = 0;
    i = 0;
calcResultLoop1:
    if (i == BIT_COUNT)
        goto calcResultLoopEnd1;

    gammaRate = gammaRate << 1;
    epsilonRate = epsilonRate << 1;
    if (positiveBits[i] >= totalRows / 2) // Bit is 1
        ++gammaRate;
    if (positiveBits[i] < totalRows / 2)
        ++epsilonRate;

    ++i;
    goto calcResultLoop1;
calcResultLoopEnd1:

    printf("%d %d %d", gammaRate, epsilonRate, gammaRate * epsilonRate);
    fclose(fp);
}

void part2()
{
    // Instead of recursion use 2 int arrays holding values of rows valid for calculation.
    // Each cycle set value to 0 for non-valid rows. Iterate until only one row with value 1 remains.

    char bitText[MAX_ROWS][BIT_COUNT + 1];
    char *lastOxygen, *lastCo2;
    int rc, totalRows, i, digitToCheck, bitOxygenCount, bitCo2Count, numOxygenLeft, numCo2Left, oxygenRate, co2Rate;
    int validOxygen[MAX_ROWS], validCo2[MAX_ROWS];
    FILE *fp;

    fp = fopen("input3.txt", "r");
    totalRows = 0;

inputLoop2:
    rc = fscanf(fp, "%s", bitText[totalRows]);
    if (rc == EOF)
        goto inputLoopEnd2;

    validOxygen[totalRows] = 1;
    validCo2[totalRows] = 1;

    ++totalRows;
    goto inputLoop2;
inputLoopEnd2:

    // Iterate through all digits and perform elimination
    digitToCheck = 0;
eliminationLoop2:
    if (digitToCheck == BIT_COUNT)
        goto eliminationLoopEnd2;

    // Get most common digit
    i = 0;
    bitOxygenCount = 0;
    bitCo2Count = 0;
    // Keep track of how many rows are still valid. Once only one is left the processing for that can be skipped.
    numOxygenLeft = 0;
    numCo2Left = 0;
mostCommonDigitLoop2:
    if (i == totalRows)
        goto mostCommonDigitLoopEnd2;

    // If oxygen row is valid then check for bit. Add 1 for set bit and subtract for clear bit.
    // If final number is greater than 0 then most bits were set.
    if (validOxygen[i] == 1)
        goto processOxygenRow2;
    goto processOxygenRowEnd2;
processOxygenRow2:
    ++numOxygenLeft;
    if (bitText[i][digitToCheck] == '1')
        ++bitOxygenCount;
    if (bitText[i][digitToCheck] == '0')
        --bitOxygenCount;
    goto processOxygenRowEnd2;
processOxygenRowEnd2:

    if (validCo2[i] == 1)
        goto processCo2Row2;
    goto processCo2RowEnd2;
processCo2Row2:
    ++numCo2Left;
    if (bitText[i][digitToCheck] == '1')
        ++bitCo2Count;
    if (bitText[i][digitToCheck] == '0')
        --bitCo2Count;
    goto processCo2RowEnd2;
processCo2RowEnd2:

    ++i;
    goto mostCommonDigitLoop2;
mostCommonDigitLoopEnd2:

    // Go through both arrays and eliminate non valid values by iterating one more time and set all eliminated rows to 0
    i = 0;
removeInvalidRowsLoop2:
    if (i == totalRows)
        goto removeInvalidRowsEndLoop2;

    if (numOxygenLeft == 1)
        goto skipValidOxygenCheck2;
    if (validOxygen[i] == 1 && bitOxygenCount >= 0 && bitText[i][digitToCheck] == '0')
        validOxygen[i] = 0; // Invalid row, only set bits are valid
    if (validOxygen[i] == 1 && bitOxygenCount < 0 && bitText[i][digitToCheck] == '1')
        validOxygen[i] = 0; // Invalid row, only clear bits are valid
skipValidOxygenCheck2:

    if (numCo2Left == 1)
        goto skipValidCo2Check2;
    if (validCo2[i] == 1 && bitCo2Count >= 0 && bitText[i][digitToCheck] == '1')
        validCo2[i] = 0; // Invalid row, only set bits are valid
    if (validCo2[i] == 1 && bitCo2Count < 0 && bitText[i][digitToCheck] == '0')
        validCo2[i] = 0; // Invalid row, only clear bits are valid
skipValidCo2Check2:

    ++i;
    goto removeInvalidRowsLoop2;
removeInvalidRowsEndLoop2:

    ++digitToCheck;
    goto eliminationLoop2;
eliminationLoopEnd2:

    // Calc correct digits

    i = 0;
getResultLoop2:
    if (i == totalRows)
        goto getResultLoopEnd2;

    if (validOxygen[i] == 1)
        lastOxygen = bitText[i];
    if (validCo2[i] == 1)
        lastCo2 = bitText[i];

    ++i;
    goto getResultLoop2;
getResultLoopEnd2:

    i = 0;
    oxygenRate = 0;
    co2Rate = 0;
convertBinaryToInt2:
    if (i == BIT_COUNT)
        goto convertBinaryToIntEnd2;

    oxygenRate = oxygenRate << 1;
    co2Rate = co2Rate << 1;
    if (lastOxygen[i] == '1') // Bit is 1
        ++oxygenRate;
    if (lastCo2[i] == '1')
        ++co2Rate;

    ++i;
    goto convertBinaryToInt2;
convertBinaryToIntEnd2:

    printf("Ox bin: %s, Ox num: %d, co2 bin: %s, co2 num: %d, res: %d\n",
           lastOxygen, oxygenRate, lastCo2, co2Rate, oxygenRate * co2Rate);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    //part1();
    part2();

    return 0;
}
