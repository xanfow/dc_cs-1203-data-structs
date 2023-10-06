// implementing inorder traversal without recursion, using a stack of node pointers

#include <stdio.h>
#include <stdlib.h>

struct BinNode // binary node pointer structure definition
{
  int key;
  struct BinNode *left, *right; // recursively (kind of) appens binary node pointers on left and right to create a Binary Tree
};

struct BinNode *createNode(int val) // utility function used by insert() to create a new binary node pointer for the element that is to be added to the tree
{
  struct BinNode *newNode;

  newNode = (struct BinNode *)malloc(sizeof(struct BinNode)); // dynamic memory allocation for the new element's binary node pointer
  newNode->key = val;
  newNode->left = newNode->right = NULL;
  return newNode;
}

void displayNode(struct BinNode *inNode) // utility function used to print a binary node pointer's address and value
{

  if (inNode == NULL)
    printf("Node does not exist!\n");
  else
    printf("%x %d\n", (unsigned int *)inNode, inNode->key);
}

struct BinNode *insert(struct BinNode *rootNode, int val) // function for inserting an element to the tree
{
  struct BinNode *temp, *parent;
  int direction;

  if (rootNode == NULL) // meaning that the tree is empty
  {
    rootNode = createNode(val); // when the tree is empty, the new binary node becomes the root node pointer
    return rootNode;
  }

  temp = rootNode;
  while (temp != NULL) // searching if the element already exists in the tree, otherwise finding the right position for the new element in the tree
  {
    if (temp->key == val)
    {
      printf("Node with value %d exists!\n", val);
      return temp;
    }

    if (val < temp->key)
    {
      parent = temp;
      temp = temp->left;
      direction = 0; // if the left pointer stored in the binary node pointer stored in temp in this iteration is NULL then the new element will get added there
    }
    else
    {
      parent = temp;
      temp = temp->right;
      direction = 1; // if the right pointer stored in the binary node pointer stored in temp in this iteration is NULL then the new element will get added there
    }
  }
  temp = createNode(val); // inserting the new element at its appropriate position
  if (direction == 0)
    parent->left = temp;
  else
    parent->right = temp;

  return temp;
}

void displayTree(struct BinNode *currentNode, int space) // function to print the entire binary tree
{
  int i;

  if (currentNode == NULL) // meaning that the previous node that was printed was a leaf node in the tree
  {
    return;
  }

  space += 10;

  displayTree(currentNode->right, space); // recursively printing the right side of the tree/sub-tree first, as the tree is being printed left to right, instead of top to bottom

  printf("\n");
  for (i = 10; i < space; i++)
  {
    printf(" ");
  }

  printf("%d\n", currentNode->key); // after recursively printing nodes on the right of the current node printing the current node

  displayTree(currentNode->left, space); // lastly recursively printing the right side of the tree/sub-tree
}

typedef struct StackNode // stack node pointer structure and alias definition
{
  struct BinNode *info;
  struct StackNode *next;
} *STACKNODE;

STACKNODE stackCreate(struct BinNode *val) // utility function used by stackPush() to create a new stack node pointer for the element that is to be added to the stack
{
  STACKNODE newNode;
  newNode = (STACKNODE)malloc(sizeof(struct StackNode)); // dynamic memory allocation for the new element's stack node pointer
  newNode->info = val;
  newNode->next = NULL;
  return newNode;
}

struct BinNode *stackPop(STACKNODE *headPointer) // function to pop/delete the top element for the stack
{
  STACKNODE temp;
  struct BinNode *val;

  temp = *headPointer;
  (*headPointer) = (*headPointer)->next; // updating the head of the stack
  val = temp->info;
  free(temp); // releasing the dynamically assigned memory to erase/delete the element's stack node pointer
  return val;
}

void stackPush(STACKNODE *headPointer, struct BinNode *elm) // function to add an element at the of the stack
{
  STACKNODE temp;
  temp = stackCreate(elm);
  if (*headPointer == NULL) // meaning the stack is empty
    *headPointer = temp;    // when the stack is empty, the new element's stack node pointer becomes the new head of the stack
  else
  {
    temp->next = *headPointer; // connecting the new element's stack node pointer to the old top element in the stack
    *headPointer = temp;       // updating the top of the stack
  }
}

void inorderTraversalIter(struct BinNode *startNode) // inorder traversal through iteration, using a stack of node pointers
{
  if (startNode == NULL) // meaning that the binary tree is empty
  {
    printf("Nothing to traverse! The tree is empty.");
    return;
  }
  STACKNODE tempNode = NULL;               // initializing a new stack to store binary node pointer's
  struct BinNode *currentNode = startNode; // current will act as an iterator variable over the binary tree's nodes
  stackPush(&tempNode, currentNode);       // pushing the starting node of the binary tree (from where the inorder traversal is to be done) to the top of the stack

  while (tempNode != NULL) // iterating over the stack until it becomes empty, i.e. until all nodes in the binary tree have been exhausted
  {
    if (currentNode == NULL) // the base condition is hit, meaning that the top of the stack stores either a leaf node or a binary node with no left sub-node
    {
      struct BinNode *deletedNode = stackPop(&tempNode); // popping the binary node pointer stored at the top of the stack
      printf("%d   ", deletedNode->key);                 // printing the value of the popped binary node pointer
      currentNode = deletedNode->right;                  // after reaching the left most depth of the untraversed tree, traversing on to the nearest right binary node in the tree
      if (currentNode != NULL)                           // this check is important because in the case where the top element of the stack that was just popped stored a leaf node, there won't be a right sub-node to be traversed and so a null pointer shouldn't be pushed to the stack in order to avoid segmentation faults
      {
        stackPush(&tempNode, currentNode);
      }
    }
    else
    {
      currentNode = currentNode->left; // traversing to reach the left most depth of the untraversed tree pushing each traversed binary node pointer to the stack in the process
      if (currentNode != NULL)         // this check is important because after finding the left most depth of the untraveresed tree (which can either be a leaf node or a binary node with no left sub-node), there won't be a left sub-node to be traversed and so a null pointer shouldn't be pushed to the stack in order to avoid segmentation faults
      {
        stackPush(&tempNode, currentNode);
      }
    }
  }
}

void main()
{
  struct BinNode *root = NULL, *temp;
  int elm, menu;

  while (1)
  {
    printf("Please choose a task to perform on the binary tree from the following list.\n");
    printf("0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: ");
    scanf("%d", &menu);

    switch (menu)
    {
    case 0:
      exit(0);
    case 1:
      printf("\nInput the element to be inserted: ");
      scanf("%d", &elm);

      temp = insert(root, elm);
      if (root == NULL)
      {
        root = insert(root, elm);
      }

      displayNode(temp);
      printf("\n");

      break;
    case 2:
      if (root == NULL)
      {
        printf("Nothing to print! The tree is empty.\n");
      }

      displayTree(root, 0);
      printf("\n");

      break;
    case 3:
      inorderTraversalIter(root);
      printf("\n\n");

      break;
    default:
      printf("Invalid choice, please try again!\n\n");
    } // extra new line escape sequences have been added to the printf() commands to provide sufficient separation in the outputs for clarity of reading
  }
}

/*
Output for TEST RUN - 1:

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 2
Nothing to print! The tree is empty.

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 3
Nothing to traverse! The tree is empty.

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 23
Invalid choice, please try again!

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 7
6b8030 7

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 10
6b80d0 10

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 16
6bc470 16

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 84
6bc4c0 84

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 17
6bc510 17

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 2

                              84

                                        17

                    16

          10

7

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 3
7   10   16   17   84

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 0
*/

/*
Output for TEST RUN - 2:

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 64
e8030 64

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 128
e80d0 128

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 0
ec470 0

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 1
ec4c0 1

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 3
ec510 3

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 1

Input the element to be inserted: 72
ec560 72

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 2

          128

                    72

64

                              3

                    1

          0

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 3
0   1   3   64   72   128

Please choose a task to perform on the binary tree from the following list.
0 to exit | 1 for inserting an element | 2 to print tree | 3 for inorder traversal | Input Choice: 0
*/
