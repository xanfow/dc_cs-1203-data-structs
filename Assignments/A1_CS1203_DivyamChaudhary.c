// implementing a Queue data structure using a Linked List by encapsulating the front and rear nodes within the Queue structure

#include <stdio.h>
#include <stdlib.h>

#define BADVAL -9999 // global constant for an error value

typedef struct node // node pointer structure and type alias definition
{
  int info;
  struct node *next; // recursively (kind of) appending node pointers to create a Linked List
} *NODEPTR;

typedef struct queue // Queue structure and type alias definition
{
  NODEPTR front, rear;
} QUEUE;

void initialize(QUEUE *inQ) // utility function to initialize the front and rear of the queue at the time of definition
{
  inQ->front = inQ->rear = NULL;
}

NODEPTR createNode(int elm) // utility function used by insert() to create a new node pointer for the element that is to be added to the queue
{
  NODEPTR new;
  new = (NODEPTR)malloc(sizeof(struct node)); // dynamic memory allocation for the new element's node pointer
  new->info = elm;
  new->next = NULL;

  return new;
}

int insert(QUEUE *inQ, int elm) // function for inserting an element to the queue
{
  NODEPTR newElmNode;
  newElmNode = createNode(elm);

  if (inQ->front == NULL) // checks if front of the queue is a null node pointer which means that the queue is empty
  {
    inQ->front = newElmNode;
    inQ->rear = newElmNode;
  } // if queue was empty then both front and rear shall point towards the new value's node pointer
  else
  {
    (inQ->rear)->next = newElmNode; // connecting the last element's node pointer to the new element's node pointer
    inQ->rear = newElmNode;         // updating the rear pointer to point towards the newly added element's node pointer
  }

  return (inQ->rear)->info;
};

int delete(QUEUE *inQ) // function to delete/pop an element from the front of the queue
{
  NODEPTR deletedNode;
  int deletedVal;

  if (inQ->front == NULL) // checks if front of the queue is a null node pointer which means that the queue is empty
    return BADVAL;        // when queue is empty there is nothing to be deleted hence the error value
  else
  {
    deletedNode = inQ->front;          // temporarly saving the node pointer of the element to be deleted
    (inQ->front) = (inQ->front)->next; // updating the front of the queue to point to the node pointer of the next element in the queue

    deletedVal = deletedNode->info; // extracting the value of the element that is to be deleted
    free(deletedNode);              // deleting/releasing the element from memory

    if (inQ->front == NULL) // checks if front of the queue is a null node pointer which means that the queue has been emptied after deletion of the value
    {
      inQ->rear = NULL; // if the queue has been emptied then the rear node pointer shall also be nullified
    }

    return deletedVal;
  }
};

void printQueue(QUEUE *inQ)
{
  NODEPTR qTraversalNode; // node pointer that help in iterating over all values in the queue

  if (inQ->front == NULL) // checks if front of the queue is a null node pointer which means that the queue is empty
  {
    printf("Nothing to print! Queue is empty.\n");
    return;
  }

  printf("<- F |");
  for (qTraversalNode = inQ->front; qTraversalNode != NULL; qTraversalNode = qTraversalNode->next) // traverses along the queue to print each element until the last element has been printed after which the qTraversalNode will be nullified
    if (qTraversalNode->next == NULL)
    {
      printf("%d", qTraversalNode->info);
    }
    else
    {
      printf("%d, ", qTraversalNode->info);
    }
  printf("| <- R\n");
};

int main()
{

  QUEUE myQueue;
  initialize(&myQueue); // option to initialize the queue not provided to the user because 1) they might use it when there are elements present in the queue, which will result in a memory leak as the queue will get initialized or completely emptied without freeing up the memory of the elements previouly stored in it; and 2) there is no need to ever initialize the queue after this once, as when a value is deleted from a singleton queue, both the front and rear node pointers get nullified in essence initializing the queue

  int elm, option;

  while (1)
  {
    printf("Please choose a task to perform on the queue from the following list.\n");
    printf("0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: ");
    scanf("%d", &option);

    switch (option)
    {
    case 0:
      exit(0);
    case 1:
      int resp = delete (&myQueue);

      if (resp == BADVAL) // printing the appropriate message based on the response of the delete() function call
      {
        printf("No value to delete! Queue is already empty.\n\n");
      }
      else
      {
        printf("Value %d deleted from the queue!\n\n", resp);
      }

      break;
    case 2:
      printf("Input the element to be inserted: ");
      scanf("%d", &elm);

      printf("\nValue %d inserted to the queue!\n\n", insert(&myQueue, elm));

      break;
    case 3:
      printQueue(&myQueue);
      printf("\n");

      break;
    default:
      printf("Invalid choice, please try again!\n\n");
    } // extra new line escape sequences have been added to the printf() commands to provide sufficient separation in the outputs for clarity of reading
  }
}

/*
Output for TEST RUN - 1:

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 1
No value to delete! Queue is already empty.

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
Nothing to print! Queue is empty.

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 2
Input the element to be inserted: 24

Value 24 inserted to the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 2
Input the element to be inserted: 34

Value 34 inserted to the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
<- F |24, 34| <- R

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 2
Input the element to be inserted: 45

Value 45 inserted to the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
<- F |24, 34, 45| <- R

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 1
Value 24 deleted from the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
<- F |34, 45| <- R

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 0
*/

/*
Output for TEST RUN - 2:

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 2
Input the element to be inserted: 4

Value 4 inserted to the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
<- F |4| <- R

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: -12
Invalid choice, please try again!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 5
Invalid choice, please try again!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 2
Input the element to be inserted: 34

Value 34 inserted to the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 2
Input the element to be inserted: 678

Value 678 inserted to the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
<- F |4, 34, 678| <- R

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 1
Value 4 deleted from the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 1
Value 34 deleted from the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
<- F |678| <- R

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 1
Value 678 deleted from the queue!

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 1
No value to delete! Queue is already empty.

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 3
Nothing to print! Queue is empty.

Please choose a task to perform on the queue from the following list.
0 to exit | 1 for deleting/popping | 2 to insert an element | 3 to print the queue | Input Choice: 0
*/
