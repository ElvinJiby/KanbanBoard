#ifndef ASSIGNMENT_3_GROUPS_CB_FUNCTIONS_H
#define ASSIGNMENT_3_GROUPS_CB_FUNCTIONS_H

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

struct item {
    char data[80]; /* each item contains a character */
    struct item *nextPtr; /* pointer to next node */
    struct item *prevPtr; /* pointer to prev node */
};

typedef struct item Item; /* synonym for struct item */
typedef Item *ItemPtr; /* synonym for Item* */

struct board {
    char name[80]; /* each board contains a name */
    ItemPtr listPtr; /* pointer to the first item */
    struct board *nextPtr; /* pointer to next board */
    struct board *prevPtr; /* pointer to prev board */
};

typedef struct board Board; /* synonym for struct board */
typedef Board *BoardPtr; /* synonym for struct Board */

/* Prototype functions */
void load_test_data(Board **board); // Loads sample board data at program startup
void printMenuOptions(Board **board); // Prints the menu options
void loadBoard(Board **board); // Loads a board from a file
void saveBoard(Board **board); // Saves a board to a file
void print_boards(Board **board); // Displays whatever board is loaded

void printListOptions(Board **board); // Prints the options for modifying an item on a list
void editItem(BoardPtr selectedBoard); // Edits the name of an item
void addItem(BoardPtr selectedBoard); // Adds a new item
void deleteItem(BoardPtr selectedBoard); // Deletes an item

void printBoardOptions(Board **board); // Prints the options for modifying a list on the board
void editBoardName(Board **board); // Edits the name of a board
void addnewBoard(Board **board); // Adds a new board
void deleteBoard(Board **board); // Removes a board

void clear_screen(); // Clears the screen depending on OS
void ASCII(); // Displays ASCII art

#endif //ASSIGNMENT_3_GROUPS_CB_FUNCTIONS_H
