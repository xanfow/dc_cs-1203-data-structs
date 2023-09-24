// implementing Johnson and Trotter algorithm that switches adjacent integers in a given sequence of directed integers based on magnitude and direction of each integer at every step until there are no possible switches left in order to produce all unique permutations

// terminology : a directed integer is one that has a magnitude as well as a direction and an integer is mobile if it is greater than its adjacent integer in the direction it is facing

#include <stdio.h>
#include <stdbool.h>

// utility function for swapping values
void swap(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

// these are the two directions that integers can face in a single dimension plane
#define LEFT_TO_RIGHT 1
#define RIGHT_TO_LEFT 0

// utility function for finding the position of an element within an array and returning 1 plus the position
int searchArr(int a[], int n, int target)
{
  for (int i = 0; i < n; i++)
  {
    if (a[i] == target)
    {
      return i + 1;
    }
  }
}

// utility function to find the position of largest mobile integer in a[]
int getMobile(int a[], int dir[], int n)
{
  int mobile_prev = 0, mobile = 0;
  for (int i = 0; i < n; i++)
  {
    // checking if an adjacent element is smaller in direction 0 or RIGHT_TO_LEFT
    if (dir[a[i] - 1] == RIGHT_TO_LEFT && i != 0)
    {
      if (a[i] > a[i - 1] && a[i] > mobile_prev)
      {
        mobile = a[i];
        mobile_prev = mobile;
      }
    }

    // checking if an adjacent element is smaller in direction 1 or LEFT_TO_RIGHT
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
    return 0; // no mobile integer left in the array
  }
  else
  {
    return mobile;
  }
}

// prints the next permutation by detecting a mobile integer based on data in dir[]
void printNextPerm(int a[], int dir[], int n)
{
  int mobile = getMobile(a, dir, n);
  int pos = searchArr(a, n, mobile);

  // swapping the mobile integer with its adjacent integer in the direction it is facing to get the next permutation
  if (dir[a[pos - 1] - 1] == RIGHT_TO_LEFT)
  {
    swap(&a[pos - 1], &a[pos - 2]);
  }

  else if (dir[a[pos - 1] - 1] == LEFT_TO_RIGHT)
  {

    swap(&a[pos], &a[pos - 1]);
  }

  // flipping the directions for integers greater than largest mobile integer
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
    if (i == n - 1)
    {
      printf("%d ", a[i]);
    }
    else
    {
      printf("%d, ", a[i]);
    }
  }
  printf("\n");
}

// for efficiency the algorithm needs to end at the factorial of n (as no. of permutations possible is just n!)
int fact(int n)
{
  int f = 1;
  for (int i = 1; i <= n; i++)
  {
    f = f * i;
  }
  return f;
}

// calls printNextPerm() one by one to print all permutations
void printPermutation(int n)
{

  // an array to store the current permutation of integers from 1 to n
  int a[n];
  for (int i = 1; i <= n; i++)
  {
    a[i - 1] = i;
  }

  // printing the very first permutation
  printf("\nPermutations : \n");
  for (int i = 0; i < n; i++)
  {
    if (i == n - 1)
    {
      printf("%d ", a[i]);
    }
    else
    {
      printf("%d, ", a[i]);
    }
  }
  printf("\n");

  // an array to store the current directions for the integers in a[] (initially all directions are set to RIGHT_TO_LEFT or 0)
  int dir[n];
  for (int i = 0; i < n; i++)
  {
    dir[i] = RIGHT_TO_LEFT;
  }

  // for generating all permutations upper bounded by n! as there will only be n! permutations
  int topVal = fact(n);
  for (int i = 1; i < topVal; i++)
  {
    printNextPerm(a, dir, n);
  }
}

int main()
{
  int n;
  printf("Input a number for which to print the permutations: \n");
  scanf("%d", &n);

  printPermutation(n);
}
