#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_NUMS 1000
#define MAX_BINGOS 500
#define BINGO_SIZE 5

void part1()
{
    int i, j, k, iteratorInput, iteratorTable, tmp, rc, sum, numOfEliminatedRow, numOfEliminatedColumn, numOfInputs, numOfBingoTables;
    int bingoInput[MAX_NUMS], bingoTables[MAX_BINGOS][BINGO_SIZE][BINGO_SIZE];
    FILE *fp;
    char c;

    fp = fopen("input4.txt", "r");

    // Read bingo input
    numOfInputs = 0;
readBingoNums1:
    char qwe[100];
    rc = fscanf(fp, "%d%c", &bingoInput[numOfInputs], &c);
    ++numOfInputs; // Increment count before checking for new line break condition
    if (rc == 0 || c == '\n')
        goto readBingoNumsEnd1;
    goto readBingoNums1;
readBingoNumsEnd1:

    //////// Parsing input
    // Read bingo tables
    numOfBingoTables = 0;
readBingoTables1:
    i = 0;
    j = 0;
parseSingleBingoTable1:
    // Check end condition
    // If row is fully read then parse next row
    if (j == BINGO_SIZE)
        goto parseSingleBingoTableIncrementK1;
    goto parseSingleBingoTableIncrementKEnd1;
parseSingleBingoTableIncrementK1:
    ++i;
    j = 0;
    goto parseSingleBingoTableIncrementKEnd1;
parseSingleBingoTableIncrementKEnd1:
    if (i == BINGO_SIZE)
        goto parseSingleBingoTableEnd1;

    // Read input one by one
    rc = fscanf(fp, "%d", &tmp);
    if (rc == EOF)
        goto readBingoTablesEnd1;

    bingoTables[numOfBingoTables][i][j] = tmp; // Only assign element if EOF was not reached

    ++j;
    goto parseSingleBingoTable1;
parseSingleBingoTableEnd1:

    ++numOfBingoTables;
    goto readBingoTables1;
readBingoTablesEnd1:
    //////// Parse of input end

    iteratorInput = 0;
iterateThroughInputs1:
    if (iteratorInput == numOfInputs)
        goto iterateThroughInputsEnd1;

    // Iterate through all bingo tables
    iteratorTable = 0;
iterateThroughAllBingoTables1:
    if (iteratorTable == numOfBingoTables)
        goto iterateThroughAllBingoTablesEnd1;

    // Mark out number
    i = 0;
iterateThroughRows1:
    if (i == BINGO_SIZE)
        goto iterateThroughRowsEnd1;
    j = 0;
    numOfEliminatedRow = 0;
    numOfEliminatedColumn = 0;
iterateThroughColumns1:
    if (j == BINGO_SIZE)
        goto iterateThroughColumnsEnd1;

    // Check rows
    if (bingoTables[iteratorTable][i][j] == bingoInput[iteratorInput])
        bingoTables[iteratorTable][i][j] = -1;
    // Check if all have been eliminated on row
    if (bingoTables[iteratorTable][i][j] == -1)
        ++numOfEliminatedRow;

    // Check columns
    if (bingoTables[iteratorTable][j][i] == bingoInput[iteratorInput])
        bingoTables[iteratorTable][j][i] = -1;
    // Check if all have been eliminated on column
    if (bingoTables[iteratorTable][j][i] == -1)
        ++numOfEliminatedColumn;

    // Break if bingo happened
    if (numOfEliminatedRow == BINGO_SIZE || numOfEliminatedColumn == BINGO_SIZE)
        goto iterateThroughInputsEnd1; // Break completely out of everything

    ++j;
    goto iterateThroughColumns1;
iterateThroughColumnsEnd1:
    ++i;
    goto iterateThroughRows1;
iterateThroughRowsEnd1:

    ++iteratorTable;
    goto iterateThroughAllBingoTables1;
iterateThroughAllBingoTablesEnd1:

    ++iteratorInput;
    goto iterateThroughInputs1;
iterateThroughInputsEnd1:

    // iteratorTable contains index of the winning table.
    // Iterate through tablo to calc final result
    sum = 0;
    i = 0;
iterateThroughFinalRows1:
    if (i == BINGO_SIZE)
        goto iterateThroughFinalRowsEnd1;
    j = 0;
iterateThroughFinalColumns1:
    if (j == BINGO_SIZE)
        goto iterateThroughFinalColumnsEnd1;

    // Check rows
    if (bingoTables[iteratorTable][i][j] != -1)
        sum += bingoTables[iteratorTable][i][j];

    ++j;
    goto iterateThroughFinalColumns1;
iterateThroughFinalColumnsEnd1:
    ++i;
    goto iterateThroughFinalRows1;
iterateThroughFinalRowsEnd1:

    printf("%d %d\n", numOfInputs, numOfBingoTables);
    printf("Sum: %d, num: %d, res: %d\n", sum, bingoInput[iteratorInput], sum * bingoInput[iteratorInput]);

    fclose(fp);
}

void part2()
{
}

int main(int argc, char *argv[])
{
    part1();
    part2();

    return 0;
}
