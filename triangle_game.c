/* Triangle Game
 * This program will take a given placement of pes for the triangle game 
 * and determine if it can be solved.
 * The user will follow the given directions to input the pegs.
 * The program will print whether or not the board can possibly be solved. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "triangle_routines.h"

#define SPOTS 15
#define NMOVES 36

int moves[NMOVES][3] = 
{
    {0, 1, 3}, 
    {3, 1, 0}, 
    {0, 2, 5},
    {5, 2, 0},
    {1, 3, 6},
    {6, 3, 1},
    {1, 4, 8},
    {8, 4, 1},
    {2, 4, 7},
    {7, 4, 2},
    {2, 5, 9},
    {9, 5, 2},
    {3, 4, 5},
    {5, 4, 3},
    {3, 6, 10},
    {10, 6, 3},
    {3, 7, 12},
    {12, 7, 3},
    {4, 7, 11},
    {11, 7, 4},
    {4, 8, 13},
    {13, 8, 4},
    {5, 8, 12},
    {12, 8, 5},
    {5, 9, 14},
    {14, 9, 5},
    {6, 7, 8},
    {8, 7, 6},
    {7, 8, 9},
    {9, 8, 7},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12}
};



/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
int make_move(int board[], int move[]);

/* Unmake this move on this board. */
int unmake_move(int board[], int move[]);

/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order. 
 */
int solve(int board[]);

/* This function counts the number of pegs left on the board.
 * Input is the current board.
 * The output is an int with the number of pegs. 
 */
int npegs(int board[]) {
    int i = 0;
    int pegs = 0;

    for(i = 0; i < SPOTS; i ++) {
        if(board[i] > 0) {
            pegs ++;
        }
    }
    return pegs;
}

/* Determines if a move is valid.
 * Input is the current and the move to be tested.
 * Output is 1 if valid and 0 is not valid. 
 */

int valid_move(int board[], int move[]) {
    int start = move[0];
    int jump = move[1];
    int end = move[2];

    if(board[start] == 0) { /* check that there is a peg to move. */
        return 0;
    }
    if(board[jump] == 0) { /* check there is a peg to jump over */
        return 0;
    }
    if(board[end] == 1) { /* check that the ending spot is empty. */
        return 0;
    }
    return 1; /* when all conditions are ment. */
}

/* Makes a move.
 * Input is the current board and the move.
 */

int make_move(int board[], int move[]) {
    int start = move[0];
    int jump = move[1];
    int finish = move[2];
    if(valid_move(board, move)  == 1) {
        board[start] = 0;
        board[jump] = 0;
        board[finish] = 1;
        return 1;
    }
    return 0;
}

/* Unmakes a move.
 * input is the current board and the move to be reversed.
 */
int unmake_move(int board[], int move[]) {
    int start = move[0];
    int finish = move[2];
    int jump = move[1];
    board[start] = 1;
    board[jump] = 1;
    board[finish] = 0;
    return 0;
}

/* determines if there is a valid way to solve the puzzle.
 * Uses recursion.
 * Input is the board.
 * Output is 1 is there is a vaild way to solve the board. 0 is not.
 */

int solve(int board[]) {
    int move_index = 0;
    int board_solvable = 0;
    if(npegs(board) == 0) {
        return 0; /* Not solvable with no pegs. */
    }
    if(npegs(board) == 1) {
        return 1; /* Solved with only one pegs. */
    }

    for(move_index = 0; move_index < NMOVES; move_index ++) {
        if(valid_move(board, moves[move_index])) {
            make_move(board, moves[move_index]);
            board_solvable = solve(board);
            unmake_move(board, moves[move_index]);
            if(board_solvable == 1) {
                return 1;
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int board[SPOTS];
    int solvable = 0;
    triangle_input(board);

    solvable = solve(board);

    if(solvable) {
        printf("This board was solved!!!\n");
    } else {
        printf("This board was not solved. :(\n");
    }

    return(0);
}

