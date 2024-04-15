
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include <chrono>
#include <iostream>
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 30

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_HEIGHT][BOARD_WIDTH];
  Tetromino arr[8]={Tetromino::I,Tetromino::O,Tetromino::T,Tetromino::S,Tetromino::O,Tetromino::Z,Tetromino::J,Tetromino::L};
  Tetromino mainT ;
  Tetromino nextT;
  Tetromino holdT;
  Tetromino shadowT;
  int tx;
  int ty;
  int leftLine;
  bool hold;
  bool resultw;
  int holdcount;
  bool resultl;
  std::chrono::steady_clock::time_point start;
  void handleInput();
  bool contact(Tetromino t,int y,int x);
  void lineCheck();
  void timePrint();

public:
  
  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();

  Game();
};
#endif