// implementing the Tower of Hanoi and the Eight Queens problems using recursion

#include <stdio.h>
#include <stdlib.h>

int solutionsCounter = 0; // counter for the number of solutions for the problem
int stepsCounter = 0;

void displayBoard(int chessBoard[8][8]) // utitlity function that prints the state of the board with Qs representing the boxes where queens are palced and blank spaces representing other empty boxes
{
  for (int i = 0; i < 8; i++) // iterating over every row of the board
  {
    printf("---------------------------------\n");
    for (int j = 0; j < 8; j++) // iterating over every column of the board
    {
      if (chessBoard[i][j]) // i.e. board[i][j] = 1, meaning this particular box on the board has a queen placed on it
        printf("| Q ");
      else
        printf("|   ");
    }
    printf("|\n");
  }
  printf("---------------------------------\n\n");
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

// struct node, typedef *NODEPTR, createNode(), isEmpty(), pop(), push(), and printRod() are utility functions that help in implementing stacks that represent the rods in the tower of Hanoi problem; lifted from lecture codes for ease
struct node
{
  int info;
  struct node *next;
};

typedef struct node *NODEPTR;

NODEPTR createNode(int val)
{
  NODEPTR p;
  p = (NODEPTR)malloc(sizeof(struct node));
  p->info = val;
  p->next = NULL;
  return p;
}

int isEmpty(NODEPTR p)
{
  if (p == NULL)
    return 1;
  else
    return 0;
}

int pop(NODEPTR *ap)
{
  NODEPTR temp;
  int val;

  if (isEmpty(*ap))
    return -9999;
  else
  {
    temp = *ap;
    (*ap) = (*ap)->next;
    val = temp->info;
    free(temp);
    return val;
  }
}

void push(NODEPTR *ap, int elm)
{
  NODEPTR temp;
  temp = createNode(elm);
  if (*ap == NULL)
    *ap = temp;
  else
  {
    temp->next = *ap;
    *ap = temp;
  }
}

void printRod(NODEPTR p, int noOfDisks) // basically the printStack() but modified to display the rods in a better way
{

  NODEPTR temp;

  if (isEmpty(p))
  {
    for (int i = 0; i < noOfDisks + 1; i++) // prints spaces
    {
      printf(" ");
    }

    printf("|\n"); // prints empty rod

    // prints base of the rod
    for (int i = 0; i < noOfDisks + 1; i++)
    {
      printf("--");
    }
    printf("-\n");

    return;
  }

  for (temp = p; temp != NULL; temp = temp->next)
  {
    for (int i = 0; i < (noOfDisks - temp->info) + 1; i++) // prints spaces
    {
      printf(" ");
    }

    for (int i = 0; i < temp->info; i++) // prints left half of a disk
    {
      printf("-");
    }

    printf("|"); // prints rod

    for (int i = 0; i < temp->info; i++) // prints right half of a disk
    {
      printf("-");
    }
    printf("\n");
  }

  // prints base of the rod
  for (int i = 0; i < noOfDisks + 1; i++)
  {
    printf("--");
  }
  printf("-\n");
}

void solveForTowerOfHanoi(int noOfDisks, int initialNoOfDisks, NODEPTR initialRods[], NODEPTR *originalRod, NODEPTR *helperRod, NODEPTR *finalRod, char original, char helper, char final) // a recursion algorithm to solve the Tower of Hanoi problem
{
  if (noOfDisks == 1) // simple case where there is only one disk to be moved
  {
    stepsCounter++;
    printf("STEP %d : Move disk 1 from rod %c to rod %c\n", stepsCounter, original, final);
    push(finalRod, pop(originalRod));

    printf("\nOriginal Rod (A):\n\n");
    printRod(initialRods[0], initialNoOfDisks);
    printf("\nFinal Rod (C):\n\n");
    printRod(initialRods[1], initialNoOfDisks);
    printf("\nHelper Rod (B):\n\n");
    printRod(initialRods[2], initialNoOfDisks);
    printf("\n");

    return;
  }

  // recursively solve the problem for noOfDisks - 1 number of disks
  solveForTowerOfHanoi(noOfDisks - 1, initialNoOfDisks, initialRods, originalRod, finalRod, helperRod, original, final, helper);
  stepsCounter++;
  printf("STEP %d : Move disk %d from rod %c to rod %c\n", stepsCounter, noOfDisks, original, final);
  push(finalRod, pop(originalRod));

  printf("\nOriginal Rod (A):\n\n");
  printRod(initialRods[0], initialNoOfDisks);
  printf("\nFinal Rod (C):\n\n");
  printRod(initialRods[1], initialNoOfDisks);
  printf("\nHelper Rod (B):\n\n");
  printRod(initialRods[2], initialNoOfDisks);
  printf("\n");

  // recursing again while unwrapping to place the disks in correct order on the final rod
  solveForTowerOfHanoi(noOfDisks - 1, initialNoOfDisks, initialRods, helperRod, originalRod, finalRod, helper, original, final);
}

void main()
{
  int chessBoard[8][8] = {{0}}; // using a 2D array to represent the 8x8 chess board, where a zero in any cell represents that no queen has been placed in the corresponding box on the chess board, and a 1 represents otherwise; this array is initialized with 0s in all cells meaning that no queens have been placed on the chess board as of now

  printf("Solutions to the Eight Queens problem are :\n\n");
  solveForEightQueens(chessBoard, 0);

  int noOfDisks;
  printf("\nInput the number of disks on the first rod for the Tower of Hanoi problem (must be >= 1) : ");
  scanf("%d", &noOfDisks);

  NODEPTR rods[3]; // using stacks to represent all the three rods in the problem, all stored in an array
  rods[0] = NULL;  // original rod
  rods[1] = NULL;  // final rod
  rods[2] = NULL;  // helper rod

  // populating the first rod with all the disks
  for (int i = 0; i < noOfDisks; i++)
  {
    push(&rods[0], (noOfDisks - i));
  }

  printf("\nInitial state of the rods : \n");
  printf("\nOriginal Rod (A):\n\n");
  printRod(rods[0], noOfDisks);
  printf("\nFinal Rod (C):\n\n");
  printRod(rods[1], noOfDisks);
  printf("\nHelper Rod (B):\n\n");
  printRod(rods[2], noOfDisks);

  printf("\nSolution to the Tower of Hanoi problem for %d disk(s) with steps is :\n\n", noOfDisks);
  solveForTowerOfHanoi(noOfDisks, noOfDisks, rods, &rods[0], &rods[2], &rods[1], 'A', 'B', 'C');

  printf("All disk have been moved from the original rods to the final rod in correct order!\n\n");
}
