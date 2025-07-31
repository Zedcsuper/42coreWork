#include <iostream>
#define N 4

void    printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j])
                std::cout << "Q ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

bool    isSafe(int board[N][N], int row, int col)
{
    int i, j;
    for (i = 0; i < col; i++) // left
    {
        if (board[row][i])
            return false;
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) //up left
    {
        if (board[i][j])
            return false;
    }

    for (i = row, j = col; j >= 0 && i < N; i++, j--) // down left
    {
        if (board[i][j])
            return false;
    }
    return true;
}

bool    solveNQUntil(int board[N][N], int col)
{
    if (col >= N)
        return true;
    for (int i = 0; i < N; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;
            if (solveNQUntil(board, col + 1))
                return true;
            board[i][col] = 0;
        }
    }
    return false;

}

bool    queenSolve()
{
     int board[N][N] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
     if (solveNQUntil(board, 0) == false)
     {
        std::cout << "Solution does not exist" << std::endl;
        return false; 
     }
     printSolution(board);
     return true;

}

int main()
{
    queenSolve();
    return 0;
}

