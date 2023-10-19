// implementing merge and quick sort, both with theoretical time complexity analyses and experimental data and comparasion with heap sort.

#include <stdio.h>
#include <stdlib.h>

int qsNoOfComparasions, msNoOfComparasions;

void swap(int *xp, int *yp) // utitlity function for swapping values of two variables
{
  int temp;
  temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int partition(int inArray[], int base, int ceiling) // utility function used by quickSortRec() to partition an array or a sub-range within an array, by picking a pivot element and shifting all elements smaller than the pivot element to the left, and all elements larger to the right of the pivot element
{
  int pivot = inArray[ceiling]; // initially setting the pivot as the last element in the array as it nets the fastest speed when it comes to sorting the array
  int i = (base - 1);           // represents the index of elements in the array that are smaller than the pivot element

  for (int j = base; j <= ceiling - 1; j++) // loops over every element in inArray[base..ceiling - 1]; ceiling element is excluded as that element as been chosen as the pivot for partitioning the array
  {
    qsNoOfComparasions++;
    if (inArray[j] < pivot) // current element is smaller that the pivot element
    {
      i++;                            // incrementing the index of smaller elements
      swap(&inArray[i], &inArray[j]); // replacing the current element by the ith element (the ith element would either just be the jth element itself or some other element that is larger than the pivot element)
    }
  }
  swap(&inArray[i + 1], &inArray[ceiling]); // at the end of the loop swapping the pivot element which is at the ceiling with an element that comes just after all elements that are smaller than the pivot element in the array, in order to attain partioned array which has all smaller elements with respect to the pivot element on the left side and larger elements on the right side (which may or may not be sorted by this point depending on the number of partitions that have been created so far)
  return (i + 1);                           // returning the index of the pivot
}

void quickSortRec(int inArray[], int base, int ceiling) // recursive quick sort algorithm (ascending order)
{
  if (base < ceiling)
  {
    // paritioning the array or a sub-range in the array once to get the initial pivot index
    int pivotIndex = partition(inArray, base, ceiling);
    // recursively partioning the left and the right sides of the pivot until sub-partitions have no elements to be partioned, i.e. base >= ceiling, in other words, until the gap between ceiling and the pivot index as well as the base and the pivot index is reduced to 0, at which point by the property of partioning the array will be sorted
    quickSortRec(inArray, base, pivotIndex - 1);
    quickSortRec(inArray, pivotIndex + 1, ceiling);
  }
}

void merger(int inArray[], int base, int middle, int ceiling) // utility function used by mergeSortRec() to merge two sub-ranges in an array (inArray[base..middle] and inArray[middle + 1..ceiling]), while ensuring that in the merged array, elements are appended in sorted order
{
  int i, j, k; // iterator variables
  // finds the sizes of both sub-ranges of the array
  int sizeOfLeftArr = middle - base + 1;
  int sizeOfRightArr = ceiling - middle;

  int left[sizeOfLeftArr], right[sizeOfRightArr]; // new temporary arrays for holding elements of both the sub-ranges of the input array

  for (i = 0; i < sizeOfLeftArr; i++) // populating the left array appropriately with the elements of the left sub-range of the input array
  {
    left[i] = inArray[base + i];
  }

  for (j = 0; j < sizeOfRightArr; j++) // populating the right array appropriately with the elements of the right sub-range of the input array
  {
    right[j] = inArray[middle + 1 + j];
  }

  // initializing the iterator variables again
  i = 0;
  j = 0;
  k = base;

  while (i < sizeOfLeftArr && j < sizeOfRightArr)
  {
    msNoOfComparasions++;
    // picks the smallest of the two elements from the top of both the sub-ranges to be added to the merged array, while incrementing the counter of only the sub-range from which an element was picked
    if (left[i] <= right[j])
    {
      inArray[k] = left[i];
      i++;
    }
    else
    {
      inArray[k] = right[j];
      j++;
    }
    k++; // irrespective of where the element was picked from, an element was added to the merged array hence the counter for the merged array is incremented
  }

  // if one of the sub-ranges is depelted early then the above loop teminates leaving the remaining elements in the other sub-range unattended, hence we need to collect these elements from the sub-range which was ignored; obviously since these sub-ranges are split into sizes of one (by mergeSortRec()) and then merged back, the elements in the ignored sub-range would already be in sorted order and can simply be copied to the merged array in the same order; only one of these while loops will trigger in any case
  while (i < sizeOfLeftArr) // some elements in the left sub-range was ignored
  {
    inArray[k] = left[i];
    i++;
    k++;
  }

  while (j < sizeOfRightArr) // some elements in the right sub-range was ignored
  {
    inArray[k] = right[j];
    j++;
    k++;
  }
}

void mergeSortRec(int inArray[], int base, int ceiling) // recursive merge sort algorithm (ascending order)
{
  if (base < ceiling)
  {
    int middle = base + (ceiling - base) / 2; // finds the index of the middle element while avoiding overflow for very large indexes

    // recursively splits the array into two equal sub-ranges until there is only one element left in each of the two sub-ranges
    mergeSortRec(inArray, base, middle);
    mergeSortRec(inArray, middle + 1, ceiling);

    // merges the two sub-ranges from the previous lines while appending elements in sorted order
    merger(inArray, base, middle, ceiling);
  }
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
  // datasets used for testing algorithmic time complexity of quick sort algorithm; the algorithmic space complexity of quick sort algorithm is O(1), since the sorting occurs in place on the same array and no extra space is required (if we don’t consider the recursive stack space required while execution to keep track of each recursive function call)
  int twelveElmArray[] = {8, 19, 9, 11, 12, 11, 13, 5, 6, 7, 3, 17};
  int bestCaseEightElmArray[] = {20, 10, 30, 40, 60, 50, 80, 70};
  int worstCaseEightElmArray[] = {10, 9, 8, 7, 6, 5, 4, 3};

  printf("Quick Sort : \n");
  printf("---------------------\n\n");

  printf("Average Case 12 Element Array\n");
  printf("Before -> ");
  displayArray(twelveElmArray, 12);
  qsNoOfComparasions = 0;
  quickSortRec(twelveElmArray, 0, 11);
  printf("Total Comparasions : %d\n", qsNoOfComparasions);
  printf("After -> ");
  displayArray(twelveElmArray, 12);
  printf("\n\n");

  printf("Best Case 8 Element Array\n");
  printf("Before -> ");
  displayArray(bestCaseEightElmArray, 8);
  qsNoOfComparasions = 0;
  quickSortRec(bestCaseEightElmArray, 0, 7);
  printf("Total Comparasions : %d\n", qsNoOfComparasions);
  printf("After -> ");
  displayArray(bestCaseEightElmArray, 8);
  printf("\n\n");

  printf("Worst Case 8 Element Array\n");
  printf("Before -> ");
  displayArray(worstCaseEightElmArray, 8);
  qsNoOfComparasions = 0;
  quickSortRec(worstCaseEightElmArray, 0, 7);
  printf("Total Comparasions : %d\n", qsNoOfComparasions);
  printf("After -> ");
  displayArray(worstCaseEightElmArray, 8);
  printf("\n\n");

  // datasets used for testing algorithmic time complexity of merge sort algorithm; the algorithmic space complexity of merge sort algorithm is O(n); this is because in the merge phase, two new temporary sub-arrays are created with elements copied from the main array, however the space of both of these sub-arrays combined or added cannot be more than the space of the input array since the number of elements in both sub-arrays summed is equal to the number of elements in the input array.
  int msTwelveElmArray[] = {8, 19, 9, 11, 12, 11, 13, 5, 6, 7, 3, 17};
  int msTenElmArray[] = {91, 2, -34, 3, 52, -1, 113, 53, 612, -7};
  int msSortedEightElmArray[] = {10, 20, 30, 40, 50, 60, 70, 80};
  int msReverseSortedEightElmArray[] = {9, 7, 3, 2, 1, -3, -4, -51};

  printf("Merge Sort : \n");
  printf("---------------------\n\n");

  printf("Average Case 10 Element Array\n");
  printf("Before -> ");
  displayArray(msTenElmArray, 10);
  msNoOfComparasions = 0;
  mergeSortRec(msTenElmArray, 0, 9);
  printf("Total Comparasions : %d\n", msNoOfComparasions);
  printf("After -> ");
  displayArray(msTenElmArray, 10);
  printf("\n\n");

  printf("Average Case 12 Element Array\n");
  printf("Before -> ");
  displayArray(msTwelveElmArray, 12);
  msNoOfComparasions = 0;
  mergeSortRec(msTwelveElmArray, 0, 11);
  printf("Total Comparasions : %d\n", msNoOfComparasions);
  printf("After -> ");
  displayArray(msTwelveElmArray, 12);
  printf("\n\n");

  printf("Best Case 8 Element Array\n");
  printf("Before -> ");
  displayArray(msSortedEightElmArray, 8);
  msNoOfComparasions = 0;
  mergeSortRec(msSortedEightElmArray, 0, 7);
  printf("Total Comparasions : %d\n", msNoOfComparasions);
  printf("After -> ");
  displayArray(msSortedEightElmArray, 8);
  printf("\n\n");

  printf("Worst Case 8 Element Array\n");
  printf("Before -> ");
  displayArray(msReverseSortedEightElmArray, 8);
  msNoOfComparasions = 0;
  mergeSortRec(msReverseSortedEightElmArray, 0, 7);
  printf("Total Comparasions : %d\n", msNoOfComparasions);
  printf("After -> ");
  displayArray(msReverseSortedEightElmArray, 8);
  printf("\n\n");
}

/*
Algorithmic Time Complexity Analysis - Quick Sort :
-------------------------------------------------------

! Considering 'n' as the number of elements in the array to be sorted.

-------------------------------------------------------

In general, the time consumed by Quick Sort can be written as follows :

    T(n) = | 0 if n <= 1
    T(n) = | T(k) + T(n-k-1) + O(n) ow

where, T(k) and T(n-k-1) refer to two recursive calls, while the last term O(n) refers to the partitioning process for every recursive call. The number of items less than pivot is denoted by k.

This general function can be tweaked to provide the algorithmic time complexity analysis for all three cases!

-------------------------------------------------------

Average Case TC is given by the following recurrence,

    T(n) = | 0 if n <= 1
    T(n) = | n - 1 + (1/n * Σ(i = 0..n - 1) (T(i) + T(n - i - 1))) ow

The recurrence n - 1 + (1/n * Σ(i = 0..n - 1) (T(i) + T(n - i - 1))) simplifies to 2n * ln(n) ≈ 1.39n log_2(n), thus we get a quasilinear polynomial which suggests that the resulting complexity in the average case is Θ(n log(n)). When the input is a random permutation of elements, the resulting parts of the partition have sizes i and n − i − 1, and i is uniform random from 0 to n − 1. Thus, the above recurrence helps in estimating the average number of comparisons over all permutations of the input sequence by averaging over all possible splits and noting that the number of comparisons for the single partition is n − 1.

Experimental Example :

Average Case 12 Element Array
Before -> [ 8, 19, 9, 11, 12, 11, 13, 5, 6, 7, 3, 17 ]
Total Comparasions : 38
After -> [ 3, 5, 6, 7, 8, 9, 11, 11, 12, 13, 17, 19 ]

-------------------------------------------------------

Best Case TC is given by the following recurrence,

    T(n) = | 0 if n <= 1
    T(n) = | 2T(n/2) + O(n) ow

Since, the recurrence 2T(n/2) + O(n) simplifies to 2 log_2 (n) * p (where p is the number of paritions required for sorting), we again get a quasilinear polynomial which suggests that the resulting complexity in the best case is Ω(n log(n)). The best case occurs when we always divide the arrays and subarrays into two partitions of equal size, because then, if the number of elements n is doubled, we only need one additional partitioning level.

Experimental Example :

Best Case 8 Element Array
Before -> [ 20, 10, 30, 40, 60, 50, 80, 70 ]
Total Comparasions : 18
After -> [ 10, 20, 30, 40, 50, 60, 70, 80 ]

Here, n = 8, and the number of partitions p = 3; so Total Comparasions = 2 * log_2 (8) * 3 = 2 * 3 * 3 = 18

-------------------------------------------------------

Worst Case TC is given by the following function,

    T(n) = | 0 if n <= 1
    T(n) = | T(0) + T(n-1) + O(n) ow

Since the recurrence, T(0) + T(n-1) + O(n) simplifies to n^2, we get a quadratic polynomial which suggests that the resulting complexity in the worst case is O(n^2). The worst case occurs when the partitioning algorithm picks the largest or smallest element as the pivot element every time, this happens when the data to be sorted is already sorted in some order resulting in a situation where every partition divides data into and empty partition and another partition with n - 1 elements (all greater/smaller than the pivot element, depending on the premature sorted order of data).

Experimental Example :

Worst Case 8 Element Array
Before -> [ 10, 9, 8, 7, 6, 5, 4, 3 ]
Total Comparasions : 28
After -> [ 3, 4, 5, 6, 7, 8, 9, 10 ]

Here, n = 8; so Total Comparasions = n * (n - 1)/2 = 8 * 7 / 2 = 56 / 2 = 28
*/

// -----------------------------------------------------------------------------------------------------------

/*
Algorithmic Time Complexity Analysis - Merge Sort :
-------------------------------------------------------

! Considering 'n' as the number of elements in the array to be sorted.

-------------------------------------------------------

In general, the time consumed by Merge Sort can be written as follows :

    T(n) = | 0 if n <= 1
    T(n) = | 2T(n/2) + O(n)  ow

where, 2T(n/2) refers to two recursive calls splitting the main array into two sub-ranges of near equal lengths, while the last term O(n) refers to the merging process (which is only linear as it has many loops but none of them are nested) at the end of every recursive call.

This reccurence suggests that the time complexity of Merge Sort is a quasilinear polynomial in Θ(n log(n)), Ω(n log(n)), and O(n log(n)) in average, best, and worst cases respectively. The time complexity remains to be the same in all three cases as the algorithm always divides the input array into two halves and then takes linear time to merge the two halves, irrespective of whether the input array was sorted, reverse sorted, or in jumbled order.

-------------------------------------------------------

Experimental Examples :

Average Case 10 Element Array
Before -> [ 91, 2, -34, 3, 52, -1, 113, 53, 612, -7 ]
Total Comparasions : 23
After -> [ -34, -7, -1, 2, 3, 52, 53, 91, 113, 612 ]

Here, n = 10, which will get divided to two subranges of 5 elements, then both the sub-ranges will be split into two sub-ranges of 3 and 2 elements, then the sub-range with 3 elements will be split into sub-ranges of 2 and 1 elements, while the remaining two sub-ranges of 2 elements will be split into 4 sub-ranges each of 1 element, and then finally the remaining sub-range of 1 elements (from the split of the sub-ranges of 3 elements) will be added back once again; Total Comparasions = (2 * 5) + (3 + 2) + (2 + 1) + (2 * 1) + (2 * 1) + 1 = 10 + 5 + 8 = 23

Average Case 12 Element Array
Before -> [ 8, 19, 9, 11, 12, 11, 13, 5, 6, 7, 3, 17 ]
Total Comparasions : 33
After -> [ 3, 5, 6, 7, 8, 9, 11, 11, 12, 13, 17, 19 ]

Here, n = 12; so (by similar kind of splitting logic as in the first example) Total Comparasions = (2 * 6) + (2 * 3) + (2 * 2) + (2 * 2) + (2 * 1) + (2 * 1) + (2 * 1) + 1 = 12 + 6 + 8 + 6 + 1 = 33

Best Case 8 Element Array
Before -> [ 10, 20, 30, 40, 50, 60, 70, 80 ]
Total Comparasions : 12
After -> [ 10, 20, 30, 40, 50, 60, 70, 80 ]

Here, n = 8; so (by similar kind of splitting logic as in the first example) Total Comparasions = (4 * 2) + (2 * 2) = 8 + 4 = 12

Worst Case 8 Element Array
Before -> [ 9, 7, 3, 2, 1, -3, -4, -51 ]
Total Comparasions : 12
After -> [ -51, -4, -3, 1, 2, 3, 7, 9 ]

Here, n = 8; so (by similar kind of splitting logic as in the first example) Total Comparasions = (4 * 2) + (2 * 2) = 8 + 4 = 12
*/

// -----------------------------------------------------------------------------------------------------------

/*
When comparing both quick sort and merge sort to heap sort we need to know the following details about heap sort :

The algorithmic space complexity of heap sort is O(1), since heap sort is an in-place sorting method, i.e., no additional memory space is required except for loop and auxiliary variables, and the number of these helper variables is always the same.

The algorithmic time complexity of heap sort is a quasilinear polynomial in Θ(n log(n)), Ω(n log(n)), and O(n log(n)) in average, best, and worst cases respectively, just like the merge sort. This is becuase, the heapInsert() method takes O(n log(n)) time to build a heap by inserting n items, and the heapDelete() takes O(n log(n)) time to remove n items from the heap, thus the combined complexity is just O(n log(n)) no matter whether the input array was jumbled, sorted or reverse sorted.

Heap sort is an unstable sorting algorithm because operations on the heap can change the relative order of equal/same elements in the output array, in other words, there is no guarantee that the order of equal/same elements in the sorted array are the same as in the input array.

(Note : since we have already done heap sort in class, I have not explicitly implemented it here again (but referred to functions from that program in lecture slides), neither did the question ask for such implementation)

Heap Sort & Quick Sort :
-------------------------------------------------------

Due to the O(n^2) worst case time complexity of (last element as pivot) quick sort, heap sort will in some cases be better than quick sort. Next, when it comes to space complexity, both algorithms offer the same space complexity which is O(1).

A potential attacker with sufficient knowledge of the quick sort algorithm's strategy (last element as pivot, median pivot, etc) can exploit this knowledge to crash or freeze the program with prepared input data. Thus, owing to this reason as well, heap sort is preferred over quick sort.

-------------------------------------------------------

Merge Sort & Quick Sort :
-------------------------------------------------------
Although the time complexity of both algorithms is the same, the constants involved are not. Merge sort will be faster than heap sort, since merge sort moves data and each of these move operations perform sequential reads from two recursive calls and a sequential write in a single merged function call that means a single merge sort move will do one read and one write. In contrast, heap sort swaps data, which means two reads and two writes per swap.

When it comes to space complexity of the two algorithms, heap sort is better compared to merge sort in that it does not require additional memory and is O(1). In contrast, merge sort requires additional memory in the order of O(n).

Merge sort is a stable sorting algorithm, unlike heap sort that is unstable. This may not be a huge differentiating factor between the two algorithms overall, however in select cases depending on the data that is to be sorted this can matter a lot.
*/
