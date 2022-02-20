#include "tetris.hpp"

//ミリ秒からナノ秒に変換する関数
long milisec_to_nanosec(double milisec) {
  return 1000000 * milisec;
}


// フィールド外にもテトリミノを描画する関数
void printTetrimino(int tetrimino[4][2], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      M5.Lcd.drawString(" ", x + j, y + i);
    }
  }

  for (int th = 0; th < 4; th++) {
    int x_ = tetrimino[th][0];
    int y_ = tetrimino[th][1];
    M5.Lcd.drawString("#", x + x_, y + y_);
  }
}

void draw() {
  put_tetrimino(tetriminos(opTet.kind, opTet.rotation_id)->tet, opTet.x, opTet.y);
  // printTetrimino(tetriminos(nextOpTet.kind, 0)->tet, 15, 2);
  print_field();
  clear_operated_tetrimino();
}

// 毎秒60フレームで実行
double frame_freq = (1.0 / 80.0) * 1000;
int frame_count = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setTextSize(1);
  nextOpTet.kind = kinds[rand() % 7];
  nextOpTet.rotation_id = 0;

  // initscr();
  // keypad(stdscr, true);
  // timeout(0);
  init_field();

  reset_operated_tetrimino();
}

void loop() {
  M5.update();
  // put your main code here, to run repeatedly:
  // 60フレームごとに落下処理
  if (frame_count % 60 == 0) {
    fall_proc();
    frame_count = 0;
  }
  draw();
  
  if (M5.BtnA.isPressed()) {
    left_proc();
  } else if (M5.BtnC.isPressed()) {
    right_proc();
  } else if (M5.BtnB.isPressed()) {
    if (opTet.rotation_id < 3) {
      opTet.rotation_id++;
      if (!setable_operated_tet(opTet)) {
        opTet.rotation_id--;
      }
    } else {
      opTet.rotation_id = 0;
      if (!setable_operated_tet(opTet)) {
        opTet.rotation_id = 3;
      }
    }
  }

  frame_count++;
  delay(frame_freq);
}
