#include "tetris.hpp"

TetriminoKind kinds[7] = {
        Tet_I,
        Tet_O,
        Tet_S,
        Tet_Z,
        Tet_J,
        Tet_L,
        Tet_T
};

BlockKind field[HEIGHT][WIDTH] = {};
BlockKind prevField[HEIGHT][WIDTH] = {};

struct OperateTet opTet;
struct OperateTet nextOpTet;

int i_tet[4][4][2] = {
        {{0, 0},
         {1, 0},
         {2, 0},
         {3, 0}},
        {{0, 0},
         {0, 1},
         {0, 2},
         {0, 3}},
        {{0, 0},
         {1, 0},
         {2, 0},
         {3, 0}},
        {{0, 0},
         {0, 1},
         {0, 2},
         {0, 3}},
};

int o_tet[4][4][2] = {
        {{0, 0},
         {1, 0},
         {0, 1},
         {1, 1}},
        {{0, 0},
         {1, 0},
         {0, 1},
         {1, 1}},
        {{0, 0},
         {1, 0},
         {0, 1},
         {1, 1}},
        {{0, 0},
         {1, 0},
         {0, 1},
         {1, 1}}
};

int s_tet[4][4][2] = {
        {{1, 0},
         {2, 0},
         {0, 1},
         {1, 1}},
        {{0, 0},
         {0, 1},
         {1, 1},
         {1, 2}},
        {{1, 0},
         {2, 0},
         {0, 1},
         {1, 1}},
        {{0, 0},
         {0, 1},
         {1, 1},
         {1, 2}}
};

int z_tet[4][4][2] = {
        {{0, 0},
         {1, 0},
         {1, 1},
         {2, 1}},
        {{1, 0},
         {0, 1},
         {1, 1},
         {0, 2}},
        {{0, 0},
         {1, 0},
         {1, 1},
         {2, 1}},
        {{1, 0},
         {0, 1},
         {1, 1},
         {0, 2}}
};

int j_tet[4][4][2] = {
        {{0, 0},
         {1, 0},
         {2, 0},
         {2, 1}},
        {{1, 0},
         {1, 1},
         {1, 2},
         {0, 2}},
        {{0, 0},
         {0, 1},
         {1, 1},
         {2, 1}},
        {{0, 0},
         {1, 0},
         {0, 1},
         {0, 2}}
};

int l_tet[4][4][2] = {
        {{0, 0},
         {1, 0},
         {2, 0},
         {0, 1}},
        {{0, 0},
         {1, 0},
         {1, 1},
         {1, 2}},
        {{2, 0},
         {0, 1},
         {1, 1},
         {2, 1}},
        {{0, 0},
         {0, 1},
         {0, 2},
         {1, 2}}
};

int t_tet[4][4][2] = {
        {{0, 0},
         {1, 0},
         {2, 0},
         {1, 1}},
        {{1, 0},
         {0, 1},
         {1, 1},
         {1, 2}},
        {{1, 1},
         {0, 2},
         {1, 2},
         {2, 2}},
        {{2, 1},
         {1, 0},
         {1, 1},
         {1, 2}}
};


struct Tetrimino *tetriminos(TetriminoKind kind, int rotation_id) {
        struct Tetrimino *tetrimino = (struct Tetrimino *)calloc(1, sizeof(struct Tetrimino));
        
        switch(kind) {
                case Tet_I:
                        memcpy(tetrimino->tet, i_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                case Tet_O:
                        memcpy(tetrimino->tet, o_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                case Tet_S:
                        memcpy(tetrimino->tet, s_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                case Tet_Z:
                        memcpy(tetrimino->tet, z_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                case Tet_J:
                        memcpy(tetrimino->tet, j_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                case Tet_L:
                        memcpy(tetrimino->tet, l_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                case Tet_T:
                        memcpy(tetrimino->tet, t_tet[rotation_id], sizeof(tetrimino->tet));
                        return tetrimino;
                default:
                        return tetrimino;
        }
}


void init_field() {
        for(int h = 0; h < HEIGHT; h++) {
                for(int w = 0; w < WIDTH; w++) {
                        if(w == 0 || w == WIDTH-1 || h == HEIGHT-1) {
                                field[h][w] = Wall;
                        } else {
                                field[h][w] = Space;
                        }
                }
        }
}

void put_tetrimino(int tetrimino[4][2], int x, int y) {
        for(int th=0; th < 4; th++) {
                int x_ = tetrimino[th][0];
                int y_ = tetrimino[th][1];
                field[y+y_][x+x_] = Operating;
        }
}



void print_field() {
        String text = "";
        M5.Lcd.setCursor(0, 0);
        for(int h = 0; h < HEIGHT; h++) {
                for(int w = 0; w < WIDTH; w++) {
                        if(field[h][w] == Block) {
                                text.concat("#");
                                // M5.Lcd.drawString("#", w*2, h*2, 2);
                        }
                        else if (field[h][w] == Operating) {
                                text.concat("!");
                                // M5.Lcd.drawString("!", w*2, h*2, 2);
                        } else if (field[h][w] == Wall) {
                                text.concat("+");
                                // M5.Lcd.drawString("+", w*2, h*2, 2);
                        } else {
                                text.concat("_");
                                // M5.Lcd.drawString("_", w*2, h*2, 2);
                        }
                }
                text.concat("\n");
        }
        M5.Lcd.print(text);
}

void clear_operated_tetrimino() {
        for(int h = 0; h < HEIGHT; h++) {
                for(int w = 0; w < WIDTH; w++) {
                        if(field[h][w] == Operating) {
                                field[h][w] = Space;
                        }
                }
        }
}


bool setable_operated_tet(struct OperateTet opTet) {
        struct Tetrimino *tetrimino = tetriminos(opTet.kind, opTet.rotation_id);
        int (*tet)[2] = tetrimino->tet;
        int x = opTet.x;
        int y = opTet.y;

        if((field[y+tet[0][1]][x+tet[0][0]] == Block) ||
           (field[y+tet[1][1]][x+tet[1][0]] == Block) ||
           (field[y+tet[2][1]][x+tet[2][0]] == Block) ||
           (field[y+tet[3][1]][x+tet[3][0]] == Block) ||
           (field[y+tet[0][1]][x+tet[0][0]] == Wall) ||
           (field[y+tet[1][1]][x+tet[1][0]] == Wall) ||
           (field[y+tet[2][1]][x+tet[2][0]] == Wall) ||
           (field[y+tet[3][1]][x+tet[3][0]] == Wall)

           ) {
                return false;
        }

        return true;
}


void change_to_block(struct OperateTet opTet) {
        struct Tetrimino *tetrimino = tetriminos(opTet.kind, opTet.rotation_id);
        int (*tet)[2] = tetrimino->tet;
        for(int th = 0; th < 4; th ++) {
                int x_ = tet[th][0];
                int y_ = tet[th][1];

                field[opTet.y+y_][opTet.x+x_] = Block;
        }
}

void move_all_block(int pivot, int step) {
        for(int h = HEIGHT; h > 0; h--) {
                for(int w = 0; w < WIDTH; w++) {
                        if(field[h][w] == Block && h < pivot) {
                                field[h][w] = Space;
                                field[h + step][w] = Block;
                        }
                }
        }
}

void delete_line(int line_num) {
        for(int w = 0; w < WIDTH; w++) {
                if(field[line_num][w] == Block) {
                        field[line_num][w] = Space;
                }
        }
}

bool is_full_line(int line_num) {
        int ret = 0;
        for(int w = 0; w < WIDTH; w++) {
                if(field[line_num][w] == Block)
                        ret++;
        }
        if(ret == 10) return true;
        return false;
}

void reset_game() {
        for(int h = 0; h < HEIGHT; h++) {
                for(int w = 0; w < WIDTH; w++) {
                        if(field[h][w] != Wall) {
                                field[h][w] = Space;
                        }
                }
        }
}


void reset_operated_tetrimino() {
        opTet.x = 5;
        opTet.y = 0;
        opTet.kind = nextOpTet.kind;
        opTet.rotation_id = 0;

        int nextOpKindIdx = rand()%7;
        nextOpTet.kind = kinds[nextOpKindIdx];

        struct timespec ts;
        ts.tv_sec = 1;
        ts.tv_nsec = 0;

        if(!setable_operated_tet(opTet)) {
                M5.Lcd.drawString("gameover!!", 40, 20);
                delay(1000);
                reset_game();
        }
}

// 左入力処理
void left_proc() {
        opTet.x--;
        if(!setable_operated_tet(opTet)) {
                opTet.x++;
        }
}

// 右入力処理
void right_proc() {
        opTet.x++;
        if(!setable_operated_tet(opTet)) {
                opTet.x--;
        }
}

void remove_line_proc() {
        for(int h = 0; h < HEIGHT; h++) {
                if(is_full_line(h)) {
                        delete_line(h);
                        move_all_block(h, 1);
                }
        }
}

// テトリミノの落下処理と床当たり判定処理
void fall_proc() {
        opTet.y ++;
        if(!setable_operated_tet(opTet)) {
                opTet.y--;
                change_to_block(opTet);
                remove_line_proc();
                reset_operated_tetrimino();
        }
}

// 上入力処理
void up_proc() {
        while(setable_operated_tet(opTet)) {
                opTet.y++;
        }
        opTet.y--;
        change_to_block(opTet);
        remove_line_proc();
        reset_operated_tetrimino();
}
