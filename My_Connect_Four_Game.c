#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void wait_ms(int milliseconds) {
    clock_t start = clock();
    while ((clock() - start) < milliseconds * (CLOCKS_PER_SEC / 1000)) {}
}

void printGrid(int rows, int colms, char grid[rows][colms]) {
    int i, j;
    printf("\n");
    for (i = 0; i < rows; i++) {
        printf(" %d ", i + 1);
        for (j = 0; j < colms; j++) {
            printf(" %c |", grid[i][j]);
        }
        printf("\n");

        if (i == rows - 1) {
            for (j = 0; j < colms; j++) {
                if (j == 0) printf("   ");
                printf(" %d  ", j + 1);
            }
        }
    }
}

int checkWin(int rows, int colms, char grid[rows][colms], int r, int c, char ch) {
    int i, j, m, count;

    // Row Check
    for (m = 0; m < colms - 3; m++) {
        count = 0;
        for (j = m; j < colms; j++) {
            if (grid[r][j] == ch) count++;
            else break;
        }
        if (count >= 4) return 1;
    }

    // Column Check
    for (m = 0; m < rows - 3; m++) {
        count = 0;
        for (j = m; j < rows; j++) {
            if (grid[j][c] == ch) count++;
            else break;
        }
        if (count >= 4) return 1;
    }

    // Diagonal / Check
    {
        count = 1;
        int rr = r + 1, cc = c - 1;
        while (rr < rows && cc >= 0 && grid[rr][cc] == ch) { count++; rr++; cc--; }

        rr = r - 1; cc = c + 1;
        while (rr >= 0 && cc < colms && grid[rr][cc] == ch) { count++; rr--; cc++; }

        if (count >= 4) return 1;
    }

    return 0;
}

int placePiece(int rows, int colms, char grid[rows][colms], int col, char ch) {
    int i;
    if (grid[0][col] != '*') return -1;

    for (i = rows - 1; i >= 0; i--) {
        if (grid[i][col] == '*') {
            grid[i][col] = ch;
            return i;
        }
    }

    return -1;
}

int isDraw(int rows, int colms, char grid[rows][colms]) {
    int i, j, count = 0;
    for (i = 0; i < rows; i++)
        for (j = 0; j < colms; j++)
            if (grid[i][j] == 'R' || grid[i][j] == 'Y') count++;

    return (count == rows * colms);
}

int main() {
    srand(time(0));
    int rows, colms;

    while (1) {
        printf("Enter number of rows (>=4): ");
        scanf("%d", &rows);
        printf("Enter number of columns (>=4): ");
        scanf("%d", &colms);

        if (rows >= 4 && colms >= 4) break;
        printf("\nRows & Columns must be >= 4\n");
    }

    char grid[rows][colms];
    int i, j;

    for (i = 0; i < rows; i++)
        for (j = 0; j < colms; j++)
            grid[i][j] = '*';

    while (1) {

        printGrid(rows, colms, grid);

        // ---------------- PLAYER TURN ----------------
        int playerCol, placedRow;
        while (1) {
            printf("\n\n\tYour Turn\nEnter column: ");
            scanf("%d", &playerCol);

            if (playerCol < 1 || playerCol > colms) {
                printf("Invalid column\n");
                continue;
            }

            placedRow = placePiece(rows, colms, grid, playerCol - 1, 'R');

            if (placedRow == -1) {
                printf("Column full, choose again\n");
            } else break;
        }

        if (checkWin(rows, colms, grid, placedRow, playerCol - 1, 'R')) {
            printGrid(rows, colms, grid);
            printf("\n----------- You Win -----------\n");
            return 0;
        }

        if (isDraw(rows, colms, grid)) {
            printGrid(rows, colms, grid);
            printf("\n----------- Draw -----------\n");
            return 0;
        }

        // ---------------- COMPUTER TURN ----------------
        int compCol, r2;
        printf("\n\n\tComputer Turn\n");
        while (1) {
            compCol = rand() % colms;
            wait_ms(300);
            r2 = placePiece(rows, colms, grid, compCol, 'Y');
            if (r2 != -1) break;
        }

        if (checkWin(rows, colms, grid, r2, compCol, 'Y')) {
            printGrid(rows, colms, grid);
            printf("\n----------- Computer Wins -----------\n");
            return 0;
        }

        if (isDraw(rows, colms, grid)) {
            printGrid(rows, colms, grid);
            printf("\n----------- Draw -----------\n");
            return 0;
        }
    }

    return 0;
}

