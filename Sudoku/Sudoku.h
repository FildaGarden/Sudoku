#pragma once

#include "stdio.h"
#include "string.h"



typedef struct {
    char* game_name;
    int sudoku_map[9][9];
}SUDOKU;

int play_sudoku(void);
void print_map(int sudoku_map[9][9]);
int load_map(FILE* file, int sudkou_map[9][9]);
int input(SUDOKU* game);
int insert(int x, int y, int number, int sudoku_map[9][9]);
int solved(int sudoku_map[9][9]);
int create_game(void);
char menu(void);
int lines_count(char* file_path);
int fill_gmaes(SUDOKU games[], char* folder_path);
int games_list(void);
int save_game(SUDOKU* game, char* folder_path);
int load_game_from_file(void);
int generate_board();
