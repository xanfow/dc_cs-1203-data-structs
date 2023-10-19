// implementing the Tower of Hanoi and the Eight Queen problems using recursion

#include <stdio.h>

int solutionsCounter = 0; // counter for the number of solutions for the problem

void displayBoard(int chessBoard[8][8]) // utitlity function that prints the state of the board with Qs representing the boxes where queens are palced and _s representing other empty boxes
{
  for (int i = 0; i < 8; i++) // iterating over every row of the board
  {
    for (int j = 0; j < 8; j++) // iterating over every column of the board
    {
      if (chessBoard[i][j]) // i.e. board[i][j] = 1, meaning this particular box on the board has a queen placed on it
        printf("Q ");
      else
        printf("_ ");
    }
    if (i != 7) // printing a newline space after printing every row of the board
    {
      printf("\n");
    }
  }
}

int isSafeSpot(int chessBoard[8][8], int row, int column) // utility function used by solveForEightQueens() that checks whether the box represented by board[row][column] is a safe position for a queen to be paced and accordingly returns true or false
{
  // since this function is only called when "column" number of queens have been safely already placed in the boxes from 0 to column - 1 on the chess board, we only need to check the left side of the present box for attacking attacking queens (the right of the box will be empty)
  int i, j;

  for (i = 0; i < column; i++) // checks the left side of the current row for any other queens
  {
    if (chessBoard[row][i]) // a queen is present at chessBoard[row][i]
    {
      return 0;
    }
  }

  for (i = row, j = column; i >= 0 && j >= 0; i--, j--) // checks top-left daigonal for any other queens
  {
    if (chessBoard[i][j]) // a queen is present at chessBoard[i][j]
    {
      return 0;
    }
  }

  for (i = row, j = column; j >= 0 && i < 8; i++, j--) // checks the lower-left daigonal for any other queens
  {
    if (chessBoard[i][j]) // a queen is present at chessBoard[i][j]
    {
      return 0;
    }
  }

  return 1;
}

void solveForEightQueens(int chessBoard[8][8], int column) // a backtracking recursion algorithm to solve the Eight Queens problem
{
  if (column == 8) // if all queens have been placed on the board, the board can be printed
  {
    solutionsCounter++;
    printf("Solution Number %d : \n", solutionsCounter);
    displayBoard(chessBoard);
    printf("\n-----------------------\n");
  }

  // placing queens
  for (int i = 0; i < 8; i++) // iterating over every row of the chess board to place a queen in it
  {
    if (isSafeSpot(chessBoard, i, column))
    {
      chessBoard[i][column] = 1;                   // if the current box on the board is safe, then palce a queen on it
      solveForEightQueens(chessBoard, column + 1); // recursively solve to place queens in further rows on the chess board with a queen already placed in the current box

      chessBoard[i][column] = 0; // if placing the queen in current box doesn't lead to a full solution where 8 queens have been palced safely on the chess board (in which case that solution will get printed and this line will never be executed), simply backtrack
    }
  }
}

void solveForTowerOfHanoi(int noOfDisks, char firstRod, char helperRod, char secondRod) // a recursion algorithm to solve the Tower of Hanoi problem
{
  if (noOfDisks == 1) // simple case where there is only one disk to be moved
  {
    printf("Move disk 1 from rod %c to rod %c\n", firstRod, secondRod);
    return;
  }

  // recursively solve the problem for noOfDisks - 1 number of disks
  solveForTowerOfHanoi(noOfDisks - 1, firstRod, secondRod, helperRod);
  printf("Move disk %d from rod %c to rod %c\n", noOfDisks, firstRod, secondRod);

  // recursing again while unwrapping to place the disks in correct order on the final rod
  solveForTowerOfHanoi(noOfDisks - 1, helperRod, firstRod, secondRod);
}

void main()
{
  int chessBoard[8][8] = {{0}}; // using a 2D array to represent the 8x8 chess board, where a zero in any cell represents that no queen has been placed in the corresponding box on the chess board, and a 1 represents otherwise; this array is initialized with 0s in all cells meaning that no queens have been placed on the chess board as of now

  printf("Solutions to the Eight Queens problem are :\n\n");
  solveForEightQueens(chessBoard, 0);

  int noOfDisks;
  printf("\nInput the number of disks on the first rod for the Tower of Hanoi problem : ");
  scanf("%d", &noOfDisks);

  printf("\nSolution to the Tower of Hanoi problem for %d disks with steps is (note that rod A is the original rod with all disks on it, rod C is the final rod where all disks have to be moved, and rod B is a helper rod) :\n\n", noOfDisks);
  solveForTowerOfHanoi(noOfDisks, 'A', 'B', 'C');
  printf("\n");
}
