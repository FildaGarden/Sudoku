#include "Sudoku.h"
#include "stdio.h"
#include <Windows.h>
#include "Generate.h"

using namespace std;

char games_file_path[] = "D:/Sudoku/games.txt";
char folder_path[] = "D:/Sudoku/";

int play_sudoku() {
    CreateDirectoryA(folder_path,NULL);
    while (1) {
        switch (menu()) {
        case 'h':
            games_list();
            break;
        case 'n':
            create_game();
            break;
        case 'g':
            generate_board();
            break;
        case 'a':
            load_game_from_file();
            break;
        case 'x':
            return 0;
            break;
        default:
            break;
        }
    }
}

char menu() {
    char choice;
    printf("[h] Hry\n");
    printf("[n] Nova hra\n");
    printf("[g] Vygenerovat hru\n");
    printf("[a] Nahrat hru\n");
    printf("[x] Koniec\n");
    printf("> ");
    scanf_s(" %c", &choice);
    return choice;
}

int create_game() {
    FILE* games_file;
    SUDOKU game;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            game.sudoku_map[i][j] = 0;
        }
    }
    char game_name[30];
    printf("Zadajte meno hry: ");
    scanf_s("%s", game_name);
    game.game_name = game_name;
    if ((games_file = fopen(games_file_path, "a")) == NULL) {
        return 0;
    }
    else {
        print_map(game.sudoku_map);
        while (input(&game) != -1) {

        }
        fprintf(games_file, "%s\n", game.game_name);
        fclose(games_file);
    }
    
    return 1;
}
int generate_board() {
    int k;
    printf("Zadejte pocet chybejicich cislic(1-64): ");
    scanf_s("%d", &k);
    fillValues(k);
    saveGame();
    printf("Hra byla vygenerovana do 'C:/Sudoku/sudoku.txt'\n\n");

    
    return 1;
}

int save_game(SUDOKU* game, char* folder_path) {
    int folder_path_lenght = strlen(folder_path);
    char *game_path = new char[folder_path_lenght];
    for (int i = 0; i < folder_path_lenght; i++) {
        game_path[i] = folder_path[i];
    }
    strcat(game_path, game->game_name);
    strcat(game_path, ".txt");
    FILE* file;
    if ((file = fopen(game_path, "w")) == NULL) {
        return 0;
    }
    else {
        for (int i = 0; i < 9; i++) {
            fprintf(file, "%d %d %d %d %d %d %d %d %d\n", game->sudoku_map[i][0], game->sudoku_map[i][1], game->sudoku_map[i][2], game->sudoku_map[i][3], game->sudoku_map[i][4], game->sudoku_map[i][5], game->sudoku_map[i][6], game->sudoku_map[i][7], game->sudoku_map[i][8]);
        }
        fclose(file);
    }
    return 1;
}

int load_game_from_file() {
    FILE* games_file;
    FILE* game_map_file;
    SUDOKU game;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            game.sudoku_map[i][j] = 0;
        }
    }
    char game_name[30];
    printf("Zadajte meno hry: ");
    scanf_s("%s", game_name);
    game.game_name = game_name;
    if ((games_file = fopen(games_file_path, "a")) == NULL) {
        return 0;
    }
    else {
        char game_file_path[2000];
        printf("Zadajte cestu k mape hry: ");
        scanf_s("%s", game_file_path);
        if ((game_map_file = fopen(game_file_path, "r")) == NULL) {
            return 0;
        }
        else {
            load_map(game_map_file, game.sudoku_map);
            save_game(&game, folder_path);
            fprintf(games_file, "%s\n", game.game_name);
            fclose(games_file);
            fclose(game_map_file);
        }
    }
    return 1;
}

int play_game(SUDOKU* game) {
    print_map(game->sudoku_map);
    while (!solved(game->sudoku_map)) {
        if (input(game) == -1) {
            break;
        }
    }
    return 1;
}

int games_list() {
    int games_count = lines_count(games_file_path);
    SUDOKU *games = new SUDOKU[games_count];

    if (fill_gmaes(games, folder_path) && games_count > 0) {
        for (int i = 0; i < games_count; i++) {
            printf("[%d] %s\n", i + 1, games[i].game_name);
        }
        int game_id;
        printf("> ");
        scanf_s("%d", &game_id);
        if (game_id > 0 && game_id <= games_count) {
            play_game(&games[game_id - 1]);
        }
    }

    return 0;
}

int lines_count(char* file_path) {
    int lines = 0;
    FILE* file;
    if ((file = fopen(file_path, "r")) == NULL) {
        return 0;
    }
    else {
        char ch;
        while ((ch = getc(file)) != EOF) {
            if (ch == '\n') {
                lines++;
            }
        }
    }
    fclose(file);
    return lines;
}

int fill_gmaes(SUDOKU games[], char* folder_path) {
    FILE* games_file;
    if ((games_file = fopen(games_file_path, "r")) == NULL) {
        return 0;
    }
    else {
        int size = 0;
        char game_name[20];
        while (fgets(game_name, 20, games_file)) {
            games[size].game_name = strdup(game_name);
            games[size].game_name[strlen(game_name) - 1] = '\0';
            int folder_path_lenght = strlen(folder_path);
            char *sudoku_map_file_path = new char[folder_path_lenght];
            for (int i = 0; i < folder_path_lenght; i++) {
                sudoku_map_file_path[i] = folder_path[i];
            }
            strcat(sudoku_map_file_path, games[size].game_name);
            strcat(sudoku_map_file_path, ".txt");
            FILE* sudoku_map_file;
            if ((sudoku_map_file = fopen(sudoku_map_file_path, "r")) == NULL) {

            }
            else {
                load_map(sudoku_map_file, games[size].sudoku_map);
                fclose(sudoku_map_file);
            }
            size++;
        }
    }
    fclose(games_file);
    return 1;
}

int input(SUDOKU* game) {
    int x, y, number;
    printf("Zadajte -1 -1 -1 pre uloženie hry [%s].\n", game->game_name);
    printf("Zadajte cislo v tvare - X Y CISLO: ");
    scanf_s("%d %d %d", &x, &y, &number);
    if (x < -1 || x > 8) {
        input(game);
    }
    else if (y < -1 || y > 8) {
        input(game);
    }
    else if (number < -1 || number > 9) {
        input(game);
    }
    else {
        if (x != -1) {
            insert(x, y, number, game->sudoku_map);
            print_map(game->sudoku_map);
        }
        else {
            save_game(game, folder_path);
            return -1;
        }
    }
    return 1;
}

int insert(int x, int y, int number, int sudoku_map[9][9]) {
    return sudoku_map[x][y] = number;
}

void print_map(int sudoku_map[9][9]) {
    printf("   0 1 2 3 4 5 6 7 8\n");
    printf("  -------------------\n");
    for (int x = 0; x < 9; x++) {
        printf("%d |", x);
        for (int y = 0; y < 9; y++) {
            int number = sudoku_map[x][y];
            number != 0 ? printf("%d|", number) : printf(" |");
        }
        printf("\n  -------------------\n");
    }
}

int load_map(FILE* file, int sudoku_map[9][9]) {
    int a, b, c, d, e, f, g, h, i;
    int row = 0;
    while (!feof(file)) {
        fscanf_s(file, "%d %d %d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g, &h, &i);
        sudoku_map[row][0] = a;
        sudoku_map[row][1] = b;
        sudoku_map[row][2] = c;
        sudoku_map[row][3] = d;
        sudoku_map[row][4] = e;
        sudoku_map[row][5] = f;
        sudoku_map[row][6] = g;
        sudoku_map[row][7] = h;
        sudoku_map[row][8] = i;

        row++;

        if (row == 9) {
            break;
        }
    }
    return 1;
}

int check_row(int x, int sudoku_map[9][9]) {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;
    int n7 = 0;
    int n8 = 0;
    int n9 = 0;
    for (int y = 0; y < 9; y++) {
        int number = sudoku_map[x][y];
        switch (number) {
        case 0:
            return 0;
            break;
        case 1:
            if (n1) {
                return 0;
            }
            else {
                n1 = 1;
            }
            break;
        case 2:
            if (n2) {
                return 0;
            }
            else {
                n2 = 1;
            }
            break;
        case 3:
            if (n3) {
                return 0;
            }
            else {
                n3 = 1;
            }
            break;
        case 4:
            if (n4) {
                return 0;
            }
            else {
                n4 = 1;
            }
            break;
        case 5:
            if (n5) {
                return 0;
            }
            else {
                n5 = 1;
            }
            break;
        case 6:
            if (n6) {
                return 0;
            }
            else {
                n6 = 1;
            }
            break;
        case 7:
            if (n7) {
                return 0;
            }
            else {
                n7 = 1;
            }
            break;
        case 8:
            if (n8) {
                return 0;
            }
            else {
                n8 = 1;
            }
            break;
        case 9:
            if (n9) {
                return 0;
            }
            else {
                n9 = 1;
            }
            break;
        }
    }
    return 1;
}

int check_column(int y, int sudoku_map[9][9]) {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;
    int n7 = 0;
    int n8 = 0;
    int n9 = 0;
    for (int x = 0; x < 9; x++) {
        int number = sudoku_map[x][y];
        switch (number) {
        case 0:
            return 0;
            break;
        case 1:
            if (n1) {
                return 0;
            }
            else {
                n1 = 1;
            }
            break;
        case 2:
            if (n2) {
                return 0;
            }
            else {
                n2 = 1;
            }
            break;
        case 3:
            if (n3) {
                return 0;
            }
            else {
                n3 = 1;
            }
            break;
        case 4:
            if (n4) {
                return 0;
            }
            else {
                n4 = 1;
            }
            break;
        case 5:
            if (n5) {
                return 0;
            }
            else {
                n5 = 1;
            }
            break;
        case 6:
            if (n6) {
                return 0;
            }
            else {
                n6 = 1;
            }
            break;
        case 7:
            if (n7) {
                return 0;
            }
            else {
                n7 = 1;
            }
            break;
        case 8:
            if (n8) {
                return 0;
            }
            else {
                n8 = 1;
            }
            break;
        case 9:
            if (n9) {
                return 0;
            }
            else {
                n9 = 1;
            }
            break;
        }
    }
    return 1;
}

int check_q(int x, int y, int sudoku_map[9][9]) {
    x *= 3;
    y *= 3;
    int q[9] = { sudoku_map[0 + x][0 + y], sudoku_map[0 + x][1 + y], sudoku_map[0 + x][2 + y], sudoku_map[1 + x][0 + y], sudoku_map[1 + x][1 + y], sudoku_map[1 + x][2 + y], sudoku_map[2 + x][0 + y], sudoku_map[2 + x][1 + y], sudoku_map[2 + x][2 + y] };
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    int n6 = 0;
    int n7 = 0;
    int n8 = 0;
    int n9 = 0;
    for (int i = 0; i < 9; i++) {
        int number = q[i];
        switch (number) {
        case 0:
            return 0;
            break;
        case 1:
            if (n1) {
                return 0;
            }
            else {
                n1 = 1;
            }
            break;
        case 2:
            if (n2) {
                return 0;
            }
            else {
                n2 = 1;
            }
            break;
        case 3:
            if (n3) {
                return 0;
            }
            else {
                n3 = 1;
            }
            break;
        case 4:
            if (n4) {
                return 0;
            }
            else {
                n4 = 1;
            }
            break;
        case 5:
            if (n5) {
                return 0;
            }
            else {
                n5 = 1;
            }
            break;
        case 6:
            if (n6) {
                return 0;
            }
            else {
                n6 = 1;
            }
            break;
        case 7:
            if (n7) {
                return 0;
            }
            else {
                n7 = 1;
            }
            break;
        case 8:
            if (n8) {
                return 0;
            }
            else {
                n8 = 1;
            }
            break;
        case 9:
            if (n9) {
                return 0;
            }
            else {
                n9 = 1;
            }
            break;
        }
    }
    return 1;
}

int rows_solved(int sudoku_map[9][9]) {
    for (int x = 0; x < 9; x++) {
        if (!check_row(x, sudoku_map)) {
            return 0;
        }
    }
    return 1;
}

int columns_solved(int sudoku_map[9][9]) {
    for (int y = 0; y < 9; y++) {
        if (!check_column(y, sudoku_map)) {
            return 0;
        }
    }
    return 1;
}

int q_solved(int sudoku_map[9][9]) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (!check_q(x, y, sudoku_map)) {
                return 0;
            }
        }
    }
    return 1;
}

int solved(int sudoku_map[9][9]) {
    return rows_solved(sudoku_map) && columns_solved(sudoku_map) && q_solved(sudoku_map);
}