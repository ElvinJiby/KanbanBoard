#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 19/04/2023
 * Software Engineering Project 1 - Assignment 3
 * Made by Elvin Jiby & Harshit Mittal
 *
 * A simple Kanban board made in C!
 * Features:
 *  - A display of the current board
 *  - Loading board data from an existing file
 *  - Editing a list within the currently loaded board
 *  - Editing the currently loaded board
 *  - Saving board data to a file
 *
 *  Note:
 *  - When asked to enter the name of a list/board/etc. you wish to modify,
 *    please enter the name as it is shown when displaying the board
 *    e.g. the default board data appends ':' to the names, so if you wanted
 *    to modify the list of Tom, you would enter Tom: when asked for the name
 *    of the list you wish to change.
 *  - The provide README.pdf contains some extra details about this program.
 *    I highly recommend you to check it out. (Originally made as part of a report
 *    for this assignment)
 */

void clear_screen() // Clears the screen depending on OS
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printMenuOptions(Board **head) // Prints some options for the user to do
{
    int choice;

    printf("\nMenu:\n");
    printf("1.Display board\n");
    printf("2.Load board from a file\n");
    printf("3.Edit list\n");
    printf("4.Edit Board\n");
    printf("5.Save board to a file\n");
    printf("6.Quit\n");

    printf("Enter your choice (1-6):\n");
    scanf("%d", &choice);

    while(choice < 1 || choice > 6) // Error handling
    {
        printf("Invalid choice.\n");
        printf("Enter your choice (1-6):\n");
        scanf("%d", &choice);
    }

    getchar();
    clear_screen();

    switch (choice)
    {
        case 1: // Display board
            clear_screen();
            print_boards(head);
            printMenuOptions(head);
            break;
        case 2: // Load board from a file
            loadBoard(head);
            printMenuOptions(head);
            break;
        case 3: // Edit list
            printListOptions(head);
            printMenuOptions(head);
            break;
        case 4: // Edit Board
            printBoardOptions(head);
            printMenuOptions(head);
            break;
        case 5: // Save board to a file
            saveBoard(head);
            printMenuOptions(head);
            break;
        case 6: // Quit
            exit(EXIT_SUCCESS);
    }
}


void loadBoard(Board **board) // Loads board data from a file
{
    FILE *filep;
    char *x; // Variable used to store strings separated using strtok function
    char file[100]; // Name of the file
    char line[80]; // String that contains each line read by file
    BoardPtr firstBoard = NULL; // Pointer to the first board

    printf("Enter filename: ");
    fgets(file, sizeof(file), stdin); // Read up to \n of file
    int strlength = strlen(file);
    file[strlength-1] = '\0'; // Remove \n at the end

    filep = fopen(file,"r");
    if (filep == NULL) { // Error handling
        printf("Error: Could not open file %s.\n", file);
        return;
    }

    printf("File successfully opened.\n");

    while (!feof(filep)) { // Read until end of file
        fgets(line, sizeof(line), filep); // Read up to \n of file
        strlength = strlen(line);
        line[strlength-1] = '\0'; // Remove \n at the end

        BoardPtr newBoard = malloc(sizeof(Board)); //Creates new board
        x = strtok(line,","); // Get the first string up to the next ','

        strcpy(newBoard->name, x); // Copy the board name

        ItemPtr currentItem = NULL;
        char *item = strtok(NULL, ","); // Get the first item

        while (item != NULL) {
            ItemPtr newItem = malloc(sizeof(Item));
            strcpy(newItem->data, item); // Copy the item name
            newItem->nextPtr = NULL;
            newItem->prevPtr = NULL;
            if (currentItem == NULL) {
                newBoard->listPtr = newItem; // If that's the only item, set the first item of the board to that
                currentItem = newItem;
            } else {
                currentItem->nextPtr = newItem; // Otherwise create new nodes to store another upcoming item
                newItem->prevPtr = currentItem;
                currentItem = newItem;
            }

            item = strtok(NULL, ",");
        }

        newBoard->nextPtr = NULL; // Update nodes
        newBoard->prevPtr = NULL;

        if (firstBoard == NULL) {
            firstBoard = newBoard; //If there's only 1 board
        } else { //If there's more than one board, set relevant node pointers and whatnot
            BoardPtr currentBoard = firstBoard;
            while (currentBoard->nextPtr != NULL) {
                currentBoard = currentBoard->nextPtr;
            }
            currentBoard->nextPtr = newBoard;
            newBoard->prevPtr = currentBoard;
        }
    }

    *board = firstBoard; // Update the head to point to the first board of this data
    printf("Board data successfully loaded.\n");
    fclose(filep); // Close the file
}




void printBoardOptions(Board **board) // Prints some options for modifying a board
{
    int choice;
    clear_screen();

    printf("Options:\n");
    printf("1. Edit the name of a list\n");
    printf("2. Add a new list\n");
    printf("3. Delete a list\n");
    printf("4. Return to main menu\n");

    printf("Enter your choice (1-4):\n");
    scanf("%d", &choice);

    while(choice < 1 || choice > 4) // Error handling
    {
        printf("Invalid choice.\n");
        printf("Enter your choice (1-4):\n");
        scanf("%d", &choice);
    }

    getchar();

    switch (choice)
    {
        case 1: // Edit the name of a list
            editBoardName(board);
            break;
        case 2: // Add a new list
            addnewBoard(board);
            break;
        case 3: // Delete a list
            deleteBoard(board);
            break;
        case 4: // Return to main menu
            clear_screen();
            break;
    }
}

void ASCII() // Simple code that prints our ascii art
{
    printf("            ^^^^****\n");
    printf("           ****  ^^^^\n");
    printf("          ^^^^    ****\n");
    printf("         ****      ^^^^\n");
    printf("        ^^^^        ****\n");
    printf("       ****          ^^^^\n");
    printf("      ^^^^          ****\n");
    printf("     ****          ^^^^\n");
    printf("    ^^^^          ****\n");
    printf("   ****          ^^^^\n");
    printf("   ^^^^          ****\n");
    printf("    ****          ^^^^\n");
    printf("     ^^^^          ****\n");
    printf("      ****          ^^^^\n");
    printf("       ^^^^          ****\n");
    printf("        ****        ^^^^\n");
    printf("         ^^^^      ****\n");
    printf("          ****    ^^^^\n");
    printf("           ^^^^  ****\n");
    printf("            ****^^^^\n");

    printf("\n\n");
    printf("          ______________________ \n");
    printf("         /                    /| \n");
    printf("        /                    / | \n");
    printf("       /                    /  | \n");
    printf("       |___________________|   | \n");
    printf("       |       ______      |   | \n");
    printf("       |      /      \\     |   | \n");
    printf("       |      |       |    |   | \n");
    printf("       |              |    |   | \n");
    printf("       |             /     |   | \n");
    printf("       |          ---      |   | \n");
    printf("       |          |        |  / \n");
    printf("       |          *        | /   \n");
    printf("       |___________________|/     \n");

    printf("\n Ascii art by Harshit Mittal and Elvin Jiby\n");
    system("pause");
}

void printListOptions(Board **board) // Function that prints the options for modifying items in a list
{
    char boardName[100]; // Array to hold the name of the board
    int flag = -1;

    printf("Enter the name of the list you wish to edit: ");
    fgets(boardName, sizeof(boardName), stdin); // Read up to \n of file
    int strlength = strlen(boardName);
    boardName[strlength-1] = '\0'; // Remove \n at the end

    BoardPtr currentBoard = *board; // Make pointer to the head pointer
    BoardPtr selectedBoard = NULL;

    while (currentBoard != NULL) {
        if (strcmp(currentBoard->name, boardName) == 0) // If the board is found
        {
            selectedBoard = currentBoard;
            flag = 0;
        }
        currentBoard = currentBoard->nextPtr; // Moves to the next board if current board doesn't match
    }

    if (flag == -1) // If board name doesn't match any of the match
    {
        printf("List not found.\n");
        return;
    }
    printf("List found.\n\n");

    printf("Options:\n");
    printf("1. Edit an item\n");
    printf("2. Add a new item\n");
    printf("3. Delete an item\n");
    printf("4. Return to main menu\n");
    printf("Please enter your option:\n");

    int choice;
    scanf("%d", &choice);

    while (choice < 1 || choice > 4)
    {
        printf("Invalid input.\n");
        printf("Please enter your option:\n");
        scanf("%d", &choice);
    }

    getchar();

    switch (choice)
    {
        case 1: // Edit an item
            editItem(selectedBoard);
            break;
        case 2: // Add a new item
            addItem(selectedBoard);
            break;
        case 3: // Delete an item
            deleteItem(selectedBoard);
            break;
        case 4: // Return to main menu
            clear_screen();
            break;
    }
}

void load_test_data(Board **board) // Function that loads sample board data on start
{
    /* Board 1 */
    // Memory Allocation
    Board *board1 = malloc(sizeof(Board));
    if(board1 == NULL)
    {
        printf("Error: No memory available to create sample boards.\n");
        free(board1);
        exit(EXIT_FAILURE);
    }

    // Set the name of the board
    strcpy(board1->name, "Nick:");
    board1->nextPtr = NULL;

    // Create some items and add them to the board's linked list
    Item *item1_1 = malloc(sizeof(Item));
    if (item1_1 == NULL)
    {
        printf("Error: No memory available to create item.\n");
        free(board1);
        free(item1_1);
        exit(EXIT_FAILURE);
    }

    strcpy(item1_1->data, "3070 RTX");
    item1_1->nextPtr = NULL;
    item1_1->prevPtr = NULL;

    // Set the board's linked list pointer to the first item
    board1->listPtr = item1_1;


    /* Board 2 */
    Board *board2 = malloc(sizeof(Board));
    if(board2 == NULL)
    {
        printf("Error: No memory available to create sample boards.\n");
        free(board2);
        exit(EXIT_FAILURE);
    }

    strcpy(board2->name, "Tim:");
    board2->nextPtr = NULL;

    Item *item1_2 = malloc(sizeof(Item));
    if (item1_2 == NULL)
    {
        printf("Error: No memory available to create item.\n");
        free(board2);
        free(item1_2);
        exit(EXIT_FAILURE);
    }

    strcpy(item1_2->data, "Oculus Quest 2");
    item1_2->nextPtr = NULL;
    item1_2->prevPtr = NULL;
    board2->listPtr = item1_2;

    /* Board 3 */
    Board *board3 = malloc(sizeof(Board));
    if(board3 == NULL)
    {
        printf("Error: No memory available to create sample boards.\n");
        free(board3);
        exit(EXIT_FAILURE);
    }
    strcpy(board3->name, "Dante:");
    board3->nextPtr = NULL;

    Item *item1_3 = malloc(sizeof(Item));
    if (item1_3 == NULL)
    {
        printf("Error: No memory available to create item.\n");
        free(board3);
        free(item1_3);
        exit(EXIT_FAILURE);
    }
    strcpy(item1_3->data, "Oculus Quest 1");
    item1_3->nextPtr = NULL;
    item1_3->prevPtr = NULL;

    Item *item2_3 = malloc(sizeof(Item));
    if (item2_3 == NULL)
    {
        printf("Error: No memory available to create item.\n");
        free(board3);
        free(item1_3);
        free(item2_3);
        exit(EXIT_FAILURE);
    }
    strcpy(item2_3->data, "3070 RTX");
    item2_3->nextPtr = NULL;
    item2_3->prevPtr = item1_3;
    item1_3->nextPtr = item2_3;

    board3->listPtr = item1_3;

    /* Board 4 */
    Board *board4 = malloc(sizeof(Board));
    if(board4 == NULL)
    {
        printf("Error: No memory available to create sample boards.\n");
        free(board4);
        exit(EXIT_FAILURE);
    }

    strcpy(board4->name, "Abey:");
    board4->nextPtr = NULL;

    Item *item1_4 = malloc(sizeof(Item));
    if (item1_4 == NULL)
    {
        printf("Error: No memory available to create item.\n");
        free(board4);
        free(item1_4);
        exit(EXIT_FAILURE);
    }
    strcpy(item1_4->data, "Oculus Pro");
    item1_4->nextPtr = NULL;
    item1_4->prevPtr = NULL;

    Item *item2_4 = malloc(sizeof(Item));
    if (item2_4 == NULL)
    {
        printf("Error: No memory available to create item.\n");
        free(board4);
        free(item1_4);
        free(item2_4);
        exit(EXIT_FAILURE);
    }
    strcpy(item2_4->data, "Oculus Quest 1");
    item2_4->nextPtr = NULL;
    item2_4->prevPtr = item1_4;
    item1_4->nextPtr = item2_4;
    board4->listPtr = item1_4;

    // NextPtrs //
    board1->nextPtr = board2;
    board2->nextPtr = board3;
    board3->nextPtr = board4;

    *board = board1; //Sets pointer to the first board
}

void print_boards(Board **board) // Prints whatever boards that are stored
{
    BoardPtr currentBoard = *board; // Create a pointer that points to the head
    while (currentBoard != NULL) {
        printf("%s\n", currentBoard->name); // prints the name of the current board
        ItemPtr currentItem = currentBoard->listPtr;
        while (currentItem != NULL) {
            printf(" %s\n", currentItem->data); // prints the items of said board
            currentItem = currentItem->nextPtr;
        }
        currentBoard = currentBoard->nextPtr; // Moves to the next board
    }
}

void editBoardName(Board **board) // Function to modify the name of an existing board
{
    char oldName[80]; // Array to store the new name
    char newName[80]; // Array to store the old name
    int flag = -1; // Flag that determines if board was found or not

    printf("Enter the name of the list you wish to edit: ");
    fgets(oldName, sizeof(oldName), stdin); // Read up to \n of file
    int strlength = strlen(oldName);
    oldName[strlength-1] = '\0'; // Remove \n at the end

    BoardPtr currentBoard = *board; // Make pointer to the head pointer

    while (currentBoard != NULL) {
        if (strcmp(currentBoard->name, oldName) == 0) // If the board is found
        {
            printf("Enter the new name for list '%s': ", currentBoard->name);
            fgets(newName, sizeof(newName), stdin);
            strlength = strlen(newName);
            newName[strlength-1] = '\0'; // Removes new line from name
            strcpy(currentBoard->name, newName); // Copies name to the board
            flag = 0;
            break;
        }

        currentBoard = currentBoard->nextPtr; // Moves to the next board if current board doesn't match
    }

    if (flag == -1) // If board name doesn't match any of the match
    {
        printf("List not found.\n");
    }
    return;
}

void addnewBoard(Board **board) // Function that creates a new board
{
    // Memory Allocation //
    Board *newBoard = malloc(sizeof(Board));
    if (newBoard == NULL) // Error handling
    {
        printf("Error: No memory available to create new board.\n");
        free(newBoard);
        return;
    }

    // Entering new name //
    printf("Enter the name of the new list: ");
    char newName[80]; // Array to store new board name
    fgets(newName, sizeof(newName), stdin);
    int strlength = strlen(newName);
    newName[strlength-1] = '\0'; // Removes new line from name
    strcpy(newBoard->name, newName);

    // Updating Nodes and Pointers //
    newBoard->listPtr = NULL;
    newBoard->prevPtr = NULL;
    newBoard->nextPtr = *board;

    if (*board != NULL)  // Set the previous board of the head to the new board
    {
        (*board)->prevPtr = newBoard;
    }

    *board = newBoard; // Update the first board of the head to the new board
    return;
}

void deleteBoard(Board **board) // Function to delete a specific board
{
    char Name[80]; // Array to store the name

    printf("Enter the name of the list you wish to delete: ");
    fgets(Name, sizeof(Name), stdin); // Read up to \n of file
    int strlength = strlen(Name);
    Name[strlength-1] = '\0'; // Remove \n at the end

    BoardPtr currentBoard = *board; // Set the current board to the head
    BoardPtr previousBoard = NULL; // There's no previous board to the head so set that to NULL

    while (currentBoard != NULL && strcmp(currentBoard->name, Name) != 0) { // Find the correct board
        previousBoard = currentBoard;
        currentBoard = currentBoard->nextPtr;
    }

    if (currentBoard != NULL ) { // If the board is found
        if (previousBoard != NULL) {
            previousBoard->nextPtr = currentBoard->nextPtr;
        }
        else { //If the first board in the head is the board we want to delete
            *board = currentBoard->nextPtr;
        }

        Item *currentItem = currentBoard->listPtr;
        while (currentItem != NULL) // Iterate through each item and free its memory
        {
            Item *nextItem = currentItem->nextPtr;
            free(currentItem);
            currentItem = nextItem;
        }

        free(currentBoard); // Free the board's memory to avoid memory leak
        printf("List successfully deleted.\n");
    }

    else { // If the board is not found
        printf("Error: List not found.\n");
        return;
    }
}

void editItem(BoardPtr selectedBoard) // Edits the name of an item
{
    char oldName[100]; // Array to hold the old name of the item
    char newName[100]; // Array to hold the new name of the item

    if (selectedBoard == NULL) { // If the board is empty
        printf("Error: List is empty.\n");
        return;
    }

    printf("Enter the name of the item you wish to edit: ");
    fgets(oldName, sizeof(oldName), stdin);
    int strlength = strlen(oldName);
    oldName[strlength-1] = '\0'; // Remove \n at the end

    ItemPtr currentItem = selectedBoard->listPtr;
    ItemPtr prevItem = NULL;
    while (currentItem != NULL) { // Find the item
        if (strcmp(currentItem->data, oldName) == 0) { // Item found
            printf("Item found.\n");
            printf("Enter the new name for item '%s': ", oldName);
            fgets(newName, sizeof(newName), stdin);
            strlength = strlen(newName);
            newName[strlength-1] = '\0'; // Remove \n at the end

            strcpy(currentItem->data, newName);
            printf("Item renamed successfully.\n");
            return; // Exit the function
        }
        prevItem = currentItem;
        currentItem = currentItem->nextPtr;
    }
    printf("Error: Item %s not found.\n", oldName); // If item is not found
}

void addItem(BoardPtr selectedBoard) // Creates a new item
{
    // Memory Allocation //
    Item *newItem = malloc(sizeof(Item));
    if (newItem == NULL) // Error handling
    {
        printf("Error: No memory available to create new item.\n");
        free(newItem);
        return;
    }

    // Entering new name //
    printf("Enter the name of the new list: ");
    char newName[80]; // Array to store new item name
    fgets(newName, sizeof(newName), stdin);
    int strlength = strlen(newName);
    newName[strlength-1] = '\0'; // Removes new line from name

    strcpy(newItem->data, newName); // Copy the name

    // Updating Nodes and Pointers //
    newItem->nextPtr = selectedBoard->listPtr; // Set the next pointer of this new item to the current item of the board
    selectedBoard->listPtr = newItem; // Set the new first item of the board to this new item

    printf("Item '%s' added to list '%s' successfully.\n",newName, selectedBoard->name);
}

void deleteItem(BoardPtr selectedBoard) // Deletes an item
{
    char itemName[100]; // Array to hold the name of the item

    if (selectedBoard == NULL) { // If the board is empty
        printf("Error: List is empty.\n");
        return;
    }

    printf("Enter the name of the item to delete: ");
    fgets(itemName, sizeof(itemName), stdin);
    int strlength = strlen(itemName);
    itemName[strlength-1] = '\0'; // Remove \n at the end

    ItemPtr currentItem = selectedBoard->listPtr;
    ItemPtr prevItem = NULL;
    while (currentItem != NULL) { // Find the item
        if (strcmp(currentItem->data, itemName) == 0) { // Item found
            printf("Item found.\n");
            if (prevItem == NULL) { // If it's the first item in the list
                selectedBoard->listPtr = currentItem->nextPtr;
            } else { // If it's not the first item in the list
                prevItem->nextPtr = currentItem->nextPtr;
            }
            free(currentItem); // Free memory
            printf("Item %s deleted successfully.\n", itemName);
            return; // Exit the function
        }
        prevItem = currentItem;
        currentItem = currentItem->nextPtr;
    }
    printf("Error: Item %s not found.\n", itemName); // If item is not found
    return; // Exit the function
}

void saveBoard(Board **board)
{
    FILE *filep;
    char file[100]; // Name of the file

    printf("Enter filename: ");
    fgets(file, sizeof(file), stdin); // Read up to \n of file
    int strlength = strlen(file);
    file[strlength-1] = '\0'; // Remove \n at the end

    filep = fopen(file,"w");
    if (filep == NULL) { // Error handling
        printf("Error: Could not open file %s.\n", file);
        return;
    }

    printf("File successfully opened.\n");

    BoardPtr currentBoard = *board; // Create a pointer that points to the head
    while (currentBoard != NULL) {
        fprintf(filep,"%s", currentBoard->name); // prints the name of the current board
        ItemPtr currentItem = currentBoard->listPtr; // Create a pointer that points to the first item

        if (currentItem != NULL) { // If the board contains items, print a comma only
            fprintf(filep, ",");
        }
        else { // If there are no items, then print a comma and a space and move on to next board
            fprintf(filep, ", ");
            currentBoard = currentBoard->nextPtr;
            if (currentBoard != NULL) {
                fprintf(filep, "\n");
            }
            continue; // Go to next board
        }

        while (currentItem != NULL) {
            fprintf(filep,"%s,", currentItem->data); // prints the items of said board
            currentItem = currentItem->nextPtr;
        }

        currentBoard = currentBoard->nextPtr; // Moves to the next board

        if (currentBoard != NULL) {
            fprintf(filep, "\n"); // Print a new line if there are more boards
        }
    }

    printf("Board data successfully saved to file '%s'.\n", file);
    fclose(filep);
}