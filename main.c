#include "functions.h"

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

int main()
{
    atexit(ASCII); // Calls ASCII art function upon termination of program

    // Struct //
    Board *head = NULL; // Creates empty board
    load_test_data(&head); // Loads sample board data

    // Display Menu Options //
    printMenuOptions(&head);
    return 0;
}
