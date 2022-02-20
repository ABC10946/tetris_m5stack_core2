#pragma once
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <stdbool.h>
#include <M5Core2.h>
#define WIDTH 12
#define HEIGHT 21

enum TetriminoKind {
        Tet_I,
        Tet_O,
        Tet_S,
        Tet_Z,
        Tet_J,
        Tet_L,
        Tet_T
};


enum BlockKind {
        Space,
        Block,
        Operating,
        Wall
};


enum Direction {
        Up,
        Down,
        Left,
        Right
};

extern int i_tet[4][4][2];
extern int o_tet[4][4][2];
extern int s_tet[4][4][2];
extern int z_tet[4][4][2];
extern int j_tet[4][4][2];
extern int l_tet[4][4][2];
extern int t_tet[4][4][2];

extern TetriminoKind kinds[7];

extern BlockKind field[HEIGHT][WIDTH];
extern BlockKind prevField[HEIGHT][WIDTH];

extern struct OperateTet opTet;
extern struct OperateTet nextOpTet;

struct Tetrimino {
        int tet[4][2];
};

struct OperateTet {
        int x;
        int y;
        TetriminoKind kind;
        int rotation_id;
};

struct Tetrimino *tetriminos(TetriminoKind, int);


void init_field();

void put_tetrimino(int tetrimino[4][2], int x, int y);

void print_field();

void clear_operated_tetrimino();

bool setable_operated_tet(struct OperateTet);

void change_to_block(struct OperateTet);

void move_all_block(int, int);

void delete_line(int);

bool is_full_line(int);

void reset_game();

void reset_operated_tetrimino();

void left_proc();

void right_proc();

void fall_proc();

void up_proc();
