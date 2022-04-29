#include <stdio.h>
#include <stdlib.h>
#include <string.h>
      struct Data {
            char title[45];
            char author[40];
            int stockNumber;
            float wholesalePrice;
            float retailPrice;
            int wholesaleQuantity;
            int retailQuantity;
};
      typedef struct Node {
            struct Data book;
            struct Node *next;
      } Node;
void getDataAndBuildList(Node **listHeadPtr);
Node *createNodeAndGetData(void);
void insertNode(Node **listHeadPtr, Node *newNodePtr);
void deleteNode(Node **listHeadPtr, int prodNumberToDelete);
void getUserOption(Node **listHead);
double calculateTotalRevenue(const Node *listHead);
double calculateInvestmentInInventory(const Node *listHead);
double calculateTotalWholesaleCost(const Node *listHead);
double calculateTotalProfit(const Node *listHead);
int calculateTotalBooksSold(const Node *listHead);
double calculateAverageProfit(const Node *listHead);
void printList(const Node *listHead);
void freeAllNodes(Node **listHeadPtr);
int main() {
      Node *listHead = NULL;
      getDataAndBuildList(&listHead);
      getUserOption(&listHead);
      return 0;
}
void getDataAndBuildList(Node **listHeadPtr) {
      Node *newNodePtr;
      printf("Please enter data about the books.\n\n");
      while (newNodePtr = createNodeAndGetData()) {
            insertNode(listHeadPtr, newNodePtr);
      }
}
Node *createNodeAndGetData(void) {
      Node *newNodePtr;
      newNodePtr = malloc (sizeof(Node));
      if (newNodePtr == NULL) {
            printf("Error: memory could not be allocated for enough nodes. ");
            printf("Terminating program!\n");
            exit (0);
} else {
            scanf("%[^\n]", newNodePtr->book.title);
            if (strcmp(newNodePtr->book.title, "END_DATA") == 0) {
                  /* free Node if end of book data detected */
                  free(newNodePtr);
                  return NULL;
} else {
                  /* consume newline before author string */
                  getchar();
                  scanf("%[^\n]s", newNodePtr->book.author);
                  scanf("%i", &newNodePtr->book.stockNumber);
                  scanf("%f", &newNodePtr->book.wholesalePrice);
                  scanf("%f", &newNodePtr->book.retailPrice);
                  scanf("%i", &newNodePtr->book.wholesaleQuantity);
                  scanf("%i", &newNodePtr->book.retailQuantity);
                  /* consume newline before next title string */
                  getchar();
}
            return newNodePtr;
      }
}
void insertNode(Node **listHeadPtr, Node *newNodePtr) {
      Node *traversePtr = *listHeadPtr;
      /* WRITE THE CODE FOR THIS FUNCTION - SEE COMMENTS BELOW */
      if (traversePtr == NULL) {
            /* WRITE CODE FOR CASE 1: INSERTION INTO EMPTY LIST */
            *listHeadPtr = newNodePtr;
            newNodePtr->next = NULL;
      }
      else if (newNodePtr->book.stockNumber < traversePtr->book.stockNumber) {
            /* WRITE CODE FOR CASE 2: INSERTION BEFORE CURRENT 1ST NODE */
            newNodePtr->next = *listHeadPtr;
            *listHeadPtr = newNodePtr;
} else {
            Node *priorNodePtr = traversePtr;
            traversePtr = traversePtr->next;
            /* while loop until the end of the list */
            while (traversePtr!=NULL && newNodePtr->book.stockNumber > traversePtr-
>book.stockNumber) {
            /* MOVE BOTH POINTERS, IF BOTH CONDITIONS ARE TRUE */
            priorNodePtr = traversePtr;
            traversePtr = traversePtr->next;
            }
      /* Put code to insert Node for case 3 below, after while loop */
      /* above finds Node before which to insert.                  */
      newNodePtr->next = traversePtr;
      priorNodePtr->next = newNodePtr;
      printf("Book stock number %i added to the inventory.\n", newNodePtr-
>book.stockNumber);
} }

void getUserOption(Node **listHeadPtr) {
      int option;
      Node *newNodePtr;
      int bookNumToDelete;
      do {
            printf("\nPlease enter an integer between 1 and 10 to select an
operation on the data:\n");
            scanf("%i", &option);
            getchar();
            switch (option){
                  case 1:
                        printList (*listHeadPtr);
                        break;
                  case 2:
                        printf("\nTotal revenue: %.2f\n",
calculateTotalRevenue(*listHeadPtr));
                        break;
                  case 3:
                        printf("\nTotal wholesale cost: %.2f\n",
calculateTotalWholesaleCost(*listHeadPtr));
                        break;
                  case 4:
                        printf("\nTotal investment in inventory: %.2f\n",
calculateInvestmentInInventory(*listHeadPtr));
                        break;
                  case 5:
                        printf("\nTotal profit: %.2f\n",
calculateTotalProfit(*listHeadPtr));
                        break;
                  case 6:
                        printf("\nTotal number of books sold = %i\n",
calculateTotalBooksSold(*listHeadPtr));
                        break;
                  case 7:
                        printf("\nAverage profit: %.2f\n",
calculateAverageProfit(*listHeadPtr));
                        break;
add:\n\n");
case 8:
      printf("\nPlease enter the data for the book you wish to
      newNodePtr = createNodeAndGetData();
      insertNode(listHeadPtr, newNodePtr);
      break;
case 9:
      printf("\nPlease enter the book stock number of the book
you wish to delete, ");
printf("followed by enter.\n");
scanf("%i", &bookNumToDelete);
deleteNode(listHeadPtr, bookNumToDelete);
break;
again!\n");
            }
case 10:
      freeAllNodes(listHeadPtr);
      break;
default:
      printf("Valid option choices are 1 to 10. Please choose
break;

      } while (option != 10);
}
double calculateTotalRevenue(const Node *listHead) {
/* WRITE THE CODE FOR THIS FUNCTION */
      const Node *traversePtr = listHead;
      double total = 0.0;
      /* while loop until the end of the list */
      while (traversePtr != NULL) {
            total += traversePtr->book.retailPrice * traversePtr-
>book.retailQuantity;
            traversePtr = traversePtr -> next;
      }
      return total;
}
double calculateInvestmentInInventory(const Node *listHead) {
/* WRITE THE CODE FOR THIS FUNCTION */
      const Node *traversePtr = listHead;
      double total = 0.0;
      /* while loop until the end of the list */
      while (traversePtr != NULL) {
            total += ((traversePtr->book.wholesaleQuantity - traversePtr-
>book.retailQuantity) * traversePtr->book.wholesalePrice);
            traversePtr = traversePtr->next;
      }
      return total;
}
double calculateTotalWholesaleCost(const Node *listHead) {
/* WRITE THE CODE FOR THIS FUNCTION */
      const Node *traversePtr = listHead;
      double total = 0.0;
      /* while loop until the end of the list */
      while (traversePtr != NULL) {
            total += traversePtr->book.wholesalePrice * traversePtr-
>book.wholesaleQuantity;
            traversePtr = traversePtr->next;
      }
      return total;
}
double calculateTotalProfit(const Node *listHead) {
/* WRITE THE CODE FOR THIS FUNCTION */
      const Node *traversePtr = listHead;
      double total = 0.0;
      /* calculate total profit by calling other functions */
      total += (calculateTotalRevenue(traversePtr) -
calculateTotalWholesaleCost(traversePtr)) +
calculateInvestmentInInventory(traversePtr);

      return total;
}
int calculateTotalBooksSold(const Node *listHead) {
/* WRITE THE CODE FOR THIS FUNCTION */
      const Node *traversePtr = listHead;
      int total = 0;
      /* while loop until the end of the list */
      while (traversePtr != NULL) {
            total += traversePtr->book.retailQuantity;
            traversePtr = traversePtr->next;
      }
      return total;
}
double calculateAverageProfit(const Node *listHead) {
/* WRITE THE CODE FOR THIS FUNCTION */
      const Node *traversePtr = listHead;
      double total = 0.0;
      /* calculate average profit by calling other functions */
      total += calculateTotalProfit(traversePtr) /
calculateTotalBooksSold(traversePtr);
      return total;
}
void deleteNode(Node **listHeadPtr, int stockNumToDelete) {
      Node *traversePtr = *listHeadPtr;
      /* WRITE THE CODE FOR THIS FUNCTION - SEE COMMENTS BELOW */
      if (traversePtr == NULL) {
            /* WRITE CODE FOR CASE 1: DELETION FROM EMPTY LIST */
            printf("ERROR, this is an empty list.\n");
      }
      else if (traversePtr->book.stockNumber==stockNumToDelete) {
            /* WRITE CODE FOR CASE 2: DELETION OF CURRENT 1ST NODE */
            *listHeadPtr = traversePtr->next;
            free(traversePtr);
            /* Print a message that a book is deletede. */
            printf("Book stock number %i deleted from the inventory.\n",
stockNumToDelete);
      }
      else {
            Node *priorNodePtr = traversePtr;
            traversePtr = traversePtr->next;
            /* while loop until the end of the list */
            while (traversePtr!=NULL && traversePtr->book.stockNumber <
stockNumToDelete) {
            /* MOVE BOTH POINTERS, IF BOTH CONDITIONS ARE TRUE */
            priorNodePtr = traversePtr;
            traversePtr = traversePtr->next;
            }

/* Print error if end of list reached, or if not, write code */
            /* to delete Node for case 3 below, if Node to delete found,*/
            /* and print message confirming deletion of Node.            */
            if (traversePtr != NULL && traversePtr-
>book.stockNumber==stockNumToDelete) {
                  priorNodePtr->next = traversePtr->next;
                  free(traversePtr);
                  /* Print a message that a book is deletede. */
                  printf("Book stock number %i deleted from the inventory.\n",
stockNumToDelete);
            }
            else {
                  /* Print a message that a book doesn't exist. */
                  printf("ERROR: Book stock number %i was not found in the list.\
n", stockNumToDelete);
            }
} }
void printList(const Node *listHead) {
      const Node *traversePtr = listHead;
      printf("\nBook list:\n");
      while (traversePtr != NULL) {
                              /* determine not at end of list */
printf("%s\n", traversePtr->book.title);
            traversePtr = traversePtr->next;
      }
      printf("\n");
}
void freeAllNodes(Node **listHeadPtr) {
      Node *traversePtr = *listHeadPtr;
      Node *restOfListPtr = *listHeadPtr;
      while (restOfListPtr != NULL) {
                                  /* determine list is not empty */
restOfListPtr = restOfListPtr->next;
            free(traversePtr);
            traversePtr = restOfListPtr;
      }
      *listHeadPtr = NULL; /* set listHeadPtr back to NULL after space freed */
}
