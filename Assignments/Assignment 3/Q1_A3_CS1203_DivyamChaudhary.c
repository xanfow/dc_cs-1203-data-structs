// implementing the AVL Tree deletion routine

#include <stdio.h>
#include <stdlib.h>

struct Node // AVL tree node pointer structure definition
{
  int key;
  // recursively (kind of) appends AVL node pointers on left and right to create an AVL Tree
  struct Node *left;
  struct Node *right;
  int height;
};

int getHeight(struct Node *n) // getter function for the height of a particular AVL node
{
  if (n == NULL)
  {
    return 0;
  }
  return n->height;
}

struct Node *createNode(int key) // utility function used by insert() to create a new AVL node pointer for the element that is to be added to the existing AVL tree
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node)); // dynamic memory allocation for the new element's AVL node pointer
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

void displayTree(struct Node *root, int space) // function to print the entire AVL tree
{
  int i;

  if (root == NULL) // meaning that the previous node that was printed was a leaf node in the tree
    return;

  space += 10;

  displayTree(root->right, space); // recursively printing the right side of the tree/sub-tree first, as the tree is being printed left to right in the terminal, instead of top to bottom

  printf("\n");
  for (i = 10; i < space; i++)
  {
    printf(" ");
  }

  printf("%d\n", root->key); // after recursively printing nodes on the right of the current node printing the current node

  displayTree(root->left, space); // lastly recursively printing the left side of the tree/sub-tree
}

int max(int a, int b) // utility function that receives two arguments and returns the greater one
{
  return (a > b) ? a : b;
}

int getBalanceFactor(struct Node *n) // getter function that calculates and returns the balance factor of a particular AVL node
{
  if (n == NULL)
  {
    return 0;
  }
  return getHeight(n->left) - getHeight(n->right); // (height of left subtree) - (height of right subtree)
}

struct Node *rightRotate(struct Node *y) // utility function used by insert() and delete() to correct any imbalances in the tree after inserting or deleting an element by rotating the tree in the right direction
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
  y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

  return x;
}

struct Node *leftRotate(struct Node *x) // utility function used by insert() and delete() to correct any imbalances in the tree after inserting or deleting an element by rotating the tree in the left direction
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
  y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

  return y;
}

struct Node *insert(struct Node *node, int key) // function for inserting an element to the tree
{
  if (node == NULL)         // meaning that the tree is empty at the current node which may or may not be the root node
    return createNode(key); // when the tree is empty at the current node and this is the appropriate position to add the new element in the tree, then the new AVL node will be added here

  // recursively finding the correct position to add the new element into the tree
  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);

  // correcting the current node's height and recalculating its balance factor while unwraping every recursion to detect imbalances after adding the new element's node
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int bf = getBalanceFactor(node);

  // fixing the left-left imbalance case
  if (bf > 1 && key < node->left->key)
  {
    return rightRotate(node);
  }
  // fixing the right-right imbalance case
  if (bf < -1 && key > node->right->key)
  {
    return leftRotate(node);
  }
  // fixing the left-right imbalance case
  if (bf > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  // fixing the right-left imbalance case
  if (bf < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // returning the current AVL node and its subtrees after ensuring proper height balancing
  return node;
}

struct Node *leftmostNode(struct Node *node) // utility function used by delete() to recursively search and return the left-most node (leaf / non-leaf) starting from any given node (may / may not be the root node) which helps in getting the inorder successor's node pointer which is used when a node with two non-null subtrees is to be deleted
{
  if (node->left == NULL)
  {
    return node;
  }
  else
  {
    leftmostNode(node->left);
  }
}

struct Node *delete(struct Node *node, int key) // function for deleting an element from the tree
{
  if (node == NULL) // meaning that the AVL tree is empty at the current node which may or may not be the root node
  {
    return NULL; // when the tree is empty at the current node, there is nothing to be deleted
  }
  else if (key == node->key) // meaning that the current node is the one that is to be deleted from the tree
  {
    if ((node->left == NULL) && (node->right == NULL)) // meaning that this node is a leaf node
    {
      node = NULL; // a leaf node can be deleted without requiring any adjustments to maintain the BST property
    }
    else if ((node->left != NULL) && (node->right == NULL)) // meaning that this node's left subtree is non-empty
    {
      node = node->left; // the current node will be deleted and its left subtree will get connected to its parent
    }
    else if ((node->left == NULL) && (node->right != NULL)) // meaning that this node's right subtree is non-empty
    {
      node = node->right; // the current node will be deleted and its right subtree will get connected to its parent
    }
    else // meaning both subtrees of the current node are non-empty
    {
      struct Node *inOrderSucc = leftmostNode(node->right); // when both subtrees of the current node are non-empty and we want to delete the current node, we need to find the inorder successor of the current node
      node->key = inOrderSucc->key;                         // replacing the current node with its inorder successor
      node->right = delete (node->right, inOrderSucc->key); // recursively deleting the inorder successor from the right subtree after replacement to avoid duplicate nodes, while also maintaining height balancing
    }
  }
  else if (key < node->key) // meaning that the element that is to be deleted can only be in the left subtree of the current node
  {
    node->left = delete (node->left, key);
  }
  else // meaning (key > node->key) or that the element that is to be deleted can only be in the right subtree of the current node
  {
    node->right = delete (node->right, key);
  }

  if (node == NULL) // if the current node that was just deleted was a leaf node then the control can simply return to the previous recursion as the node is now empty and doesn't require any height balancing
  {
    return NULL;
  }

  // correcting the current node's height and recalculating its balance factor while unwraping every recursion to detect imbalances after deleting the desired element's node
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int bf = getBalanceFactor(node);

  // fixing the left-left imbalance case
  if (bf > 1 && key < node->left->key)
  {
    return rightRotate(node);
  }
  // fixing the right-right imbalance case
  if (bf < -1 && key > node->right->key)
  {
    return leftRotate(node);
  }
  // fixing the left-right imbalance case
  if (bf > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  // fixing the right-left imbalance case
  if (bf < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // returning the current AVL node and its subtrees after ensuring proper height balancing
  return node;
}

void preOrder(struct Node *root) // function to print the pre-order traversal of the AVL tree
{
  if (root != NULL)
  {
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(struct Node *root) // function to print the in-order traversal of the AVL tree
{
  if (root != NULL)
  {
    preOrder(root->left);
    printf("%d ", root->key);
    preOrder(root->right);
  }
}

void main()
{
  struct Node *root = NULL;
  int elm, menu;

  while (1)
  {
    printf("Please choose a task to perform on the binary tree from the following list.\n");
    printf("0 to exit | 1 for initializing the tree | 2 for inserting an element  | 3 to delete an element | 4 for inorder traversal | 5 for preorder traversal | 6 to print tree | Input Choice: ");
    scanf("%d", &menu);

    switch (menu)
    {
    case 0:
      exit(0);
    case 1:
      root = NULL;
      printf("\n");

      break;
    case 2:
      printf("\nGive element to insert: ");
      scanf("%d", &elm);

      root = insert(root, elm);
      printf("\n");

      break;
    case 3:
      printf("\nGive element to delete: ");
      scanf("%d", &elm);

      if (root == NULL)
      {
        printf("Nothing to delete! Tree is empty.\n");
      }
      else
      {
        root = delete (root, elm);
        printf("\n");
      }

      break;
    case 4:
      printf("\n");
      inOrder(root);
      printf("\n\n");

      break;
    case 5:
      printf("\n");
      preOrder(root);
      printf("\n\n");

      break;
    case 6:
      if (root == NULL)
      {
        printf("\nNothing to print! Tree is empty.\n");
      }

      displayTree(root, 0);
      printf("\n");

      break;
    default:
      printf("\nInvalid choice, please try again!\n\n");
    } // extra new line escape sequences have been added to the printf() commands to provide sufficient separation in the outputs for clarity of reading
  }
}
