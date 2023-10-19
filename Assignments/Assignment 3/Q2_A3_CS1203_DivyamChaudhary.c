// implementing insertion and bubble sorts, comparing theoretical time complexity analysis with experimental data (present at the end of program code as comments)

#include <stdio.h>

void swap(int *xp, int *yp) // utitlity function for swapping values of two variables
{
  int temp;
  temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void insertionSortIter(int inArray[], int arraySize) // iterative insertion sort algorithm (ascending order)
{
  int i, j, searchKey, noOfComparasions = 1, whileFirstCompare = 1; // extra varibales for help with measuring algorithmic time complexity

  for (i = 1; i < arraySize; i++) // outer loop iterating over inArray[1..arraySize - 1]
  {
    searchKey = inArray[i];
    j = i - 1;

    noOfComparasions++;
    whileFirstCompare = 1;

    while (j >= 0 && inArray[j] >= searchKey) // inner loop iterating in reverse order over inArray[0..i - 1]
    {
      if (whileFirstCompare)
      {
        whileFirstCompare = 0;
      }
      else
      {
        noOfComparasions++;
      }

      if (j == 0 && i == arraySize - 1)
      {
        noOfComparasions--;
      }

      // pushing elements in inArray[0..i - 1] that are greater than search value to one index on the right to make space for the search value to be added at its correct index in the sorted order
      inArray[j + 1] = inArray[j];
      j = j - 1;
    }

    inArray[j + 1] = searchKey; // placing the search value in its appropriate sorted position for the current iteration
  }

  printf("Total Comparasions : %d\n", noOfComparasions);
}

void bubbleSortIter(int inArray[], int arraySize) // iterative bubble sort algorithm (ascending order)
{
  int i, j, noOfComparasions = 0, swapOccured; // extra varibales for help with measuring algorithmic time complexity and shortcircuiting the bubble sort algorithm when no swaps occur in the inner loop, which means the array is already sorted

  for (i = 0; i < arraySize - 1; i++) // outer loop iterating over inArray[0..arraySize - 1]
  {
    swapOccured = 0;

    for (j = 0; j < arraySize - i - 1; j++) // inner loop iterating over inArray[0..arraySize - (i + 1)]
    {
      noOfComparasions++;
      if (inArray[j] > inArray[j + 1])
      {
        // swapping adjacent elements in inArray[0..arraySize - (i + 1)] if one is greater than the next
        swap(&inArray[j], &inArray[j + 1]);
        swapOccured = 1;
      }
    }

    // shortcircuiting the bubble sort algorithm when the inner loop doesn't change anything, which means the array has been sorted
    if (!swapOccured)
    {
      break;
    }
  }

  printf("Total Comparasions : %d\n", noOfComparasions);
}

void displayArray(int inArray[], int arraySize) // function to print the entire entire array
{
  int i;

  printf("[ ");
  for (i = 0; i < arraySize; i++)
  {
    if (i == arraySize - 1)
    {
      printf("%d ]", inArray[i]);
    }
    else
    {
      printf("%d, ", inArray[i]);
    }
  }
  printf("\n");
}

void main()
{
  // datasets used for testing algorithmic time complexity; since arrays are being used for storing data in conjuction with the iterative nature of both algorithms results in the algorithmic space complexity to be constant, i.e. O(1) where both algorithms function with constant space in memory
  int fourElmArray[] = {12, 117, 0, 61};
  int thrityTwoElmArray[] = {24, 45, 3, 95, -31, 631, 60, 71, 247, 15, -24, -656, -34, 94, 98, 135, 2, 32, 763, 457, -13, 134, 66, 7, 456, 5, -11, -43, -91, 268, 236, 74};

  int sortedFiveElmArray[] = {10, 20, 30, 40, 50};
  int sortedTenElmArray[] = {11, 22, 33, 44, 55, 55, 66, 77, 88, 99};

  int reverseSortedFiveElmArray[] = {9, 7, 3, 2, 1};
  int reverseSortedTenElmArray[] = {105, 95, 85, 75, 65, 55, 45, 35, 25, 15};

  // one of the two sets of testing function calls have been commented to test one algorithm at a time, otherwise the later algorithm will be working on datasets that have already been sorted by the previous algorithm
  printf("Insertion Sort : \n");
  printf("---------------------\n\n");
  printf("Average Case 4 Element Array\n");
  printf("Before -> ");
  displayArray(fourElmArray, 4);
  insertionSortIter(fourElmArray, 4);
  printf("After -> ");
  displayArray(fourElmArray, 4);
  printf("\n\n");

  printf("Average Case 32 Element Array\n");
  printf("Before -> ");
  displayArray(thrityTwoElmArray, 32);
  insertionSortIter(thrityTwoElmArray, 32);
  printf("After -> ");
  displayArray(thrityTwoElmArray, 32);
  printf("\n\n");

  printf("Best Case 5 Element Array\n");
  printf("Before -> ");
  displayArray(sortedFiveElmArray, 5);
  insertionSortIter(sortedFiveElmArray, 5);
  printf("After ->");
  displayArray(sortedFiveElmArray, 5);
  printf("\n\n");

  printf("Best Case 10 Element Array\n");
  printf("Before -> ");
  displayArray(sortedTenElmArray, 10);
  insertionSortIter(sortedTenElmArray, 10);
  printf("After -> ");
  displayArray(sortedTenElmArray, 10);
  printf("\n\n");

  printf("Worst Case 5 Element Array\n");
  printf("Before -> ");
  displayArray(reverseSortedFiveElmArray, 5);
  insertionSortIter(reverseSortedFiveElmArray, 5);
  printf("After -> ");
  displayArray(reverseSortedFiveElmArray, 5);
  printf("\n\n");

  printf("Worst Case 10 Element Array\n");
  printf("Before -> ");
  displayArray(reverseSortedTenElmArray, 10);
  insertionSortIter(reverseSortedTenElmArray, 10);
  printf("After -> ");
  displayArray(reverseSortedTenElmArray, 10);
  printf("\n\n");

  // printf("Bubble Sort : \n");
  // printf("---------------------\n\n");
  // printf("Average Case 4 Element Array\n");
  // printf("Before -> ");
  // displayArray(fourElmArray, 4);
  // bubbleSortIter(fourElmArray, 4);
  // printf("After -> ");
  // displayArray(fourElmArray, 4);
  // printf("\n\n");

  // printf("Average Case 32 Element Array\n");
  // printf("Before -> ");
  // displayArray(thrityTwoElmArray, 32);
  // bubbleSortIter(thrityTwoElmArray, 32);
  // printf("After -> ");
  // displayArray(thrityTwoElmArray, 32);
  // printf("\n\n");

  // printf("Best Case 5 Element Array\n");
  // printf("Before -> ");
  // displayArray(sortedFiveElmArray, 5);
  // bubbleSortIter(sortedFiveElmArray, 5);
  // printf("After -> ");
  // displayArray(sortedFiveElmArray, 5);
  // printf("\n\n");

  // printf("Best Case 10 Element Array\n");
  // printf("Before -> ");
  // displayArray(sortedTenElmArray, 10);
  // bubbleSortIter(sortedTenElmArray, 10);
  // printf("After -> ");
  // displayArray(sortedTenElmArray, 10);
  // printf("\n\n");

  // printf("Worst Case 5 Element Array\n");
  // printf("Before -> ");
  // displayArray(reverseSortedFiveElmArray, 5);
  // bubbleSortIter(reverseSortedFiveElmArray, 5);
  // printf("After -> ");
  // displayArray(reverseSortedFiveElmArray, 5);
  // printf("\n\n");

  // printf("Worst Case 10 Element Array\n");
  // printf("Before -> ");
  // displayArray(reverseSortedTenElmArray, 10);
  // bubbleSortIter(reverseSortedTenElmArray, 10);
  // printf("After -> ");
  // displayArray(reverseSortedTenElmArray, 10);
  // printf("\n\n");
}

/*
Algorithmic Time Complexity Analysis - Insertion Sort :
-------------------------------------------------------

! Considering 'n' as the number of elements in the array to be sorted.

-------------------------------------------------------

Average Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | n * (n - 1) * 1/4 ow

Since, n * (n - 1) * 1/4 simplifies to (n^2 - n) * 1/4, we get a quadratic polynomial which suggests that the resulting complexity in the average case is Θ(n^2). The average case occurs when the elements in the array before sorting are in jumbled order.

Experimental Examples :

Average Case 4 Element Array
Before -> [ 12, 117, 0, 61 ]
Total Comparasions : 5
After -> [ 0, 12, 61, 117 ]

Here, n = 4; so Total Comparasions = (4^2 - 4)/4 = 12/4 = 3 ~ 5, here as the value of 'n' is rather small we see a slight mismatch in the value provided by the recurrence and the one measured by the counters in code, however as n -> infinity, this inaccuracy disappears; see next example.

Average Case 32 Element Array
Before -> [ 24, 45, 3, 95, -31, 631, 60, 71, 247, 15, -24, -656, -34, 94, 98, 135, 2, 32, 763, 457, -13, 134, 66, 7, 456, 5, -11, -43, -91, 268, 236, 74 ]
Total Comparasions : 248
After -> [ -656, -91, -43, -34, -31, -24, -13, -11, 2, 3, 5, 7, 15, 24, 32, 45, 60, 66, 71, 74, 94, 95, 98, 134, 135, 236, 247, 268, 456, 457, 631, 763 ]

Here, n = 32; so Total Comparasions = (32^2 - 32)/4 = 992/4 = 248.

-------------------------------------------------------

Best Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | n ow

Since, there are n comparison operations, we have a linear polynomial, which suggests that the resulting time complexity in the best case is Ω(n). The best case occurs when the elements in the array before sorting already appear in sorted order. In this situation, there is precisely one comparison in the inner loop and no swap operations at all.

Experimental Examples :

Best Case 5 Element Array
Before -> [ 10, 20, 30, 40, 50 ]
Total Comparasions : 5
After ->[ 10, 20, 30, 40, 50 ]

Here, n = 5; so Total Comparasions = 5.

Best Case 10 Element Array
Before -> [ 11, 22, 33, 44, 55, 55, 66, 77, 88, 99 ]
Total Comparasions : 10
After -> [ 11, 22, 33, 44, 55, 55, 66, 77, 88, 99 ]

Here, n = 10; so Total Comparasions = 10.

-------------------------------------------------------

Worst Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | n * (n - 1) * 1/2 ow

Since, n * (n - 1) * 1/2 simplifies to (n^2 - n) * 1/2, we get a quadratic polynomial which suggests that the resulting complexity in the worst case is O(n^2). The worst case occurs when the elements in the array before sorting are in reverse order of the sorting that is going to occur.

Experimental Examples :

Worst Case 5 Element Array
Before -> [ 9, 7, 3, 2, 1 ]
Total Comparasions : 10
After -> [ 1, 2, 3, 7, 9 ]

Here, n = 5; so Total Comparasions = (5^2 - 5)/2 = 20/2 = 10.

Worst Case 10 Element Array
Before -> [ 105, 95, 85, 75, 65, 55, 45, 35, 25, 15 ]
Total Comparasions : 45
After -> [ 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 ]

Here, n = 10; so Total Comparasions = (10^2 - 10)/2 = 90/2 = 45.
*/

// -----------------------------------------------------------------------------------------------------------

/*
Algorithmic Time Complexity Analysis - Bubble Sort :
-------------------------------------------------------

! Considering 'n' as the number of elements in the array to be sorted.

-------------------------------------------------------

Average Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | 1/2 * (n^2 - (n * ln(n)) - (e + ln(2) - 1) * n) + O(sqrt(n)) ow ; where e = Euler's constant

Since, the largest degree of n in the above expression is 2, we can infer that it is a quadratic polynomial which suggests that the resulting complexity in the average case is Θ(n^2). The average case occurs when the elements in the array before sorting are in jumbled order. Here the expression is a little complex because it is the expected number of comparisons for a randomly chosen permutation of the list (1, 2, ..., n), where we also need to consider the fact that the algorithm shorts without computing all permutations when the sorted order is achieved prematurely.

Experimental Examples :

Average Case 4 Element Array
Before -> [ 12, 117, 0, 61 ]
Total Comparasions : 6
After -> [ 0, 12, 61, 117 ]

Average Case 32 Element Array
Before -> [ 24, 45, 3, 95, -31, 631, 60, 71, 247, 15, -24, -656, -34, 94, 98, 135, 2, 32, 763, 457, -13, 134, 66, 7, 456, 5, -11, -43, -91, 268, 236, 74 ]
Total Comparasions : 490
After -> [ -656, -91, -43, -34, -31, -24, -13, -11, 2, 3, 5, 7, 15, 24, 32, 45, 60, 66, 71, 74, 94, 95, 98, 134, 135, 236, 247, 268, 456, 457, 631, 763 ]

-------------------------------------------------------

Best Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | n - 1 ow

Since, there are n - 1 comparison operations, we have a linear polynomial, which suggests that the resulting time complexity in the best case is Ω(n). The best case occurs when the elements in the array before sorting already appear in sorted order. In this situation, the algorithm will determine in the first iteration that no number pairs need to be swapped and will then terminate immediately.

Experimental Examples :

Best Case 5 Element Array
Before -> [ 10, 20, 30, 40, 50 ]
Total Comparasions : 4
After -> [ 10, 20, 30, 40, 50 ]

Here, n = 5; so Total Comparasions = 5 - 1 = 4.

Best Case 10 Element Array
Before -> [ 11, 22, 33, 44, 55, 55, 66, 77, 88, 99 ]
Total Comparasions : 9
After -> [ 11, 22, 33, 44, 55, 55, 66, 77, 88, 99 ]

Here, n = 10; so Total Comparasions = 10 - 1 = 9.

-------------------------------------------------------

Worst Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | n * (n - 1) * 1/2 ow

Since, n * (n - 1) * 1/2 simplifies to (n^2 - n) * 1/2, we get a quadratic polynomial which suggests that the resulting complexity in the worst case is O(n^2). The worst case occurs when the elements in the array before sorting are in reverse order of the sorting that is going to occur.

Experimental Examples :

Worst Case 5 Element Array
Before -> [ 9, 7, 3, 2, 1 ]
Total Comparasions : 10
After -> [ 1, 2, 3, 7, 9 ]

Here, n = 5; so Total Comparasions = (5^2 - 5)/2 = 20/2 = 10.

Worst Case 10 Element Array
Before -> [ 105, 95, 85, 75, 65, 55, 45, 35, 25, 15 ]
Total Comparasions : 45
After -> [ 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 ]

Here, n = 10; so Total Comparasions = (10^2 - 10)/2 = 90/2 = 45.
 */

// -----------------------------------------------------------------------------------------------------------

/* In conclusion, even if the exact constant and polynomials may differ, yet through the asymptotic notations we find that the best, worst, as well as the average case time complexities for both insertion and bubble sort are the same for a sufficiently large n. */
