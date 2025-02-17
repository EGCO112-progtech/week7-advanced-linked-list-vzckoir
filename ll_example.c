// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
   int item,id; // char entered by user
   char name[50];

   instructions(); // display the menu
   choice=0; 

   // loop while user does not choose 3
   while ( choice != 3 ) { 
      printf( "%s", "? " );
      scanf( "%u", &choice );
      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter ID and Name: " );
            scanf( "%d %s", &id, name );
            insert( &startPtr, id, name ); // insert item in list
            printf( "the list is: \n" );
            printList( startPtr );
            printListReverse( startPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter number to be deleted: " );
               scanf( "%d", &item );

               // if character is found, remove it
               if ( deletes( &startPtr, item ) ) { // remove item
                  printf( "%d deleted.\n", item );
                  printList( startPtr );
                  printListReverse( startPtr );
               } // end if
               else {
                  printf( "%d not found.\n\n", item );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         case 3:
          
                clearAllNodes(&startPtr);  // Call function to clear all nodes
          
            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

     
   } // end while
  /* Clear all nodes at the end of nodes*/

} // end main
