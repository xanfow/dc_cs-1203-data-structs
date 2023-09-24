// implementing Johnson and Trotter algorithm

#include <stdio.h>
#include <stdbool.h>

void swap(int *xp, int *yp)
{
  int temp;
  temp = *xp;
  *xp = *yp;
  *yp = temp;
}

#define LEFT_TO_RIGHT 1
#define RIGHT_TO_LEFT 0

// searchArr() and getMobile() are utility functions for finding the position of largest mobile integer in a[]
int searchArr(int a[], int n, int mobile)
{
  for (int i = 0; i < n; i++)
  {
    if (a[i] == mobile)
    {
      return i + 1;
    }
  }
}

// to find the largest mobile integer
int getMobile(int a[], int dir[], int n)
{
  int mobile_prev = 0, mobile = 0;
  for (int i = 0; i < n; i++)
  {
    // direction 0 is RIGHT_TO_LEFT
    if (dir[a[i] - 1] == RIGHT_TO_LEFT && i != 0)
    {
      if (a[i] > a[i - 1] && a[i] > mobile_prev)
      {
        mobile = a[i];
        mobile_prev = mobile;
      }
    }

    // direction 1 is LEFT_TO_RIGHT
    if (dir[a[i] - 1] == LEFT_TO_RIGHT && i != n - 1)
    {
      if (a[i] > a[i + 1] && a[i] > mobile_prev)
      {
        mobile = a[i];
        mobile_prev = mobile;
      }
    }
  }

  if (mobile == 0 && mobile_prev == 0)
  {
    return 0;
  }
  else
  {
    return mobile;
  }
}

// prints the next permutation based on dir[]
void printNextPerm(int a[], int dir[], int n)
{
  int mobile = getMobile(a, dir, n);
  int pos = searchArr(a, n, mobile);

  // swapping based on data in dir[]
  if (dir[a[pos - 1] - 1] == RIGHT_TO_LEFT)
  {
    swap(&a[pos - 1], &a[pos - 2]);
  }

  else if (dir[a[pos - 1] - 1] == LEFT_TO_RIGHT)
  {

    swap(&a[pos], &a[pos - 1]);
  }

  // changing the directions for elements greater than largest mobile integer
  for (int i = 0; i < n; i++)
  {
    if (a[i] > mobile)
    {
      if (dir[a[i] - 1] == LEFT_TO_RIGHT)
      {
        dir[a[i] - 1] = RIGHT_TO_LEFT;
      }
      else if (dir[a[i] - 1] == RIGHT_TO_LEFT)
      {
        dir[a[i] - 1] = LEFT_TO_RIGHT;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// to end the algorithm for efficiency it ends at the factorial of n (no. of permutations possible is just n!)
int fact(int n)
{
  int res = 1;
  for (int i = 1; i <= n; i++)
  {
    res = res * i;
  }
  return res;
}

// calls printNextPerm() one by one to print all permutations
void printPermutation(int n)
{

  // to store current permutation storing the elements from 1 to n
  int a[n];
  for (int i = 1; i <= n; i++)
  {
    a[i - 1] = i;
  }

  // printing the very first permutation
  for (int i = 0; i < n; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");

  // to store current directions (initially all directions are set to RIGHT TO LEFT or 0)
  int dir[n];
  for (int i = 0; i < n; i++)
  {
    dir[i] = RIGHT_TO_LEFT;
  }

  // for generating all permutations
  int topVal = fact(n);
  for (int i = 1; i < topVal; i++)
  {
    printNextPerm(a, dir, n);
  }
}

int main()
{
  int n;
  printf("Input a number: \n");
  scanf("%d", &n);

  printPermutation(n);
}
