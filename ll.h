#include <string.h>
// self-referential structure
struct Node {
   int id; // unique identifier for the node
   char name[50]; // name associated with the node
   struct Node *nextPtr;
   struct Node *pPtr; // pointer to next node
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void printList( LLPtr currentPtr );
void printListR( LLPtr currentPtr );
void instructions( void );


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert(LLPtr *sPtr, int id, char name[]) {
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr = (LLPtr)malloc(sizeof(struct Node)); // create node

   if (newPtr != NULL) { // is space available
      newPtr->id = id; // place id in node
      strcpy(newPtr->name, name); // copy name into node
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr = NULL;

      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while (currentPtr != NULL && id > currentPtr->id) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      }

      // insert new node at beginning of list
      if (previousPtr == NULL) {
         newPtr->nextPtr = *sPtr;
         if (*sPtr) (*sPtr)->pPtr = newPtr;
         *sPtr = newPtr;
      } else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr = previousPtr;
         newPtr->nextPtr = currentPtr;
         if (currentPtr) currentPtr->pPtr = newPtr;
      }
   } else {
      printf("%d not inserted. No memory available.\n", id);
   }
}
int isEmpty(LLPtr sPtr){
   return sPtr==NULL;
}

// delete a list element
int deletes(LLPtr *sPtr, int id) {
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if (*sPtr != NULL && id == (*sPtr)->id) {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = (*sPtr)->nextPtr; // de-thread the node
      if (*sPtr != NULL) {
         (*sPtr)->pPtr = NULL;
      }
      free(tempPtr); // free the de-threaded node
      return id;
   } else {
      previousPtr = *sPtr;
      currentPtr = (*sPtr) ? (*sPtr)->nextPtr : NULL;

      // loop to find the correct location in the list
      while (currentPtr != NULL && currentPtr->id != id) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      }

      // delete node at currentPtr
      if (currentPtr != NULL) {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         if (currentPtr->nextPtr != NULL) {
            currentPtr->nextPtr->pPtr = previousPtr;
         }
         free(tempPtr);
         return id;
      }
   }
   return -1; // return -1 if not found
}

void printList(LLPtr currentPtr) {
   if (currentPtr == NULL) {
      puts("List is empty.\n");
      return;
   }

   while (currentPtr != NULL) {
      printf("%d %s --> ", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->nextPtr;
   }
   printf("NULL\n");
}

void printListReverse(LLPtr currentPtr) {
   if (currentPtr == NULL) {
      puts("List is empty.\n");
      return;
   }
   while (currentPtr->nextPtr != NULL) {
      currentPtr = currentPtr->nextPtr;
   }
   while (currentPtr != NULL) {
      printf("%d %s --> ", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->pPtr;
   }
   printf("NULL\n");
}

void clearAllNodes(LLPtr *sPtr) {

   printf("Clear all nodes\n");

   if (*sPtr == NULL) {
      printf("The list is already empty.\n");
   }

   while (*sPtr != NULL) {
       printf("Delete %d\n", (*sPtr)->id);
       deletes(sPtr, (*sPtr)->id);
   }

   printf("End of run\n");
}
