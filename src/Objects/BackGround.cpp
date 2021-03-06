﻿
#include "BackGround.h"
#include <iostream>


BackGround::BackGround(const float posX) :
  backGround("res/back_ground.png"),
  ground("res/ground.png"),
  pos(posX, 0),
  checkCount(0),
  texSize(BG_WIDTH, BG_HEIGHT),
  blockSize(128, 128) {
}


// 背景を２枚表示
void BackGround::Draw(const Vec2f& camera) {
  // TIPS: カメラと自分の相対座標を求める
  const Vec2f DrawPos = pos - camera;

  // １枚目
  drawTextureBox(DrawPos.x(), DrawPos.y(), texSize.x(), texSize.y(),
                 0, 0, texSize.x(), texSize.y(),
                 backGround, Color::white);

  // ２枚目
  drawTextureBox(DrawPos.x() + BG_WIDTH, DrawPos.y(), texSize.x(), texSize.y(),
                 0, 0, texSize.x(), texSize.y(),
                 backGround, Color::white);

  // ステージの床
  const int count = BG_WIDTH / (int)blockSize.x();
  for (int i = 0; i < count * 2; ++i) {
    drawTextureBox(DrawPos.x() + i * blockSize.x(), DrawPos.y(),
                   blockSize.x(), blockSize.y(),
                   0, 0, blockSize.x(), blockSize.y(),
                   ground, Color::white);
  }
}


// 背景の位置をずらす
const bool BackGround::checkPoint(const float playerX) {
  DOUT << "bg pos.x = " << pos.x() << std::endl;
  DOUT << "bg pos.y = " << pos.y() << std::endl << std::endl;

  const auto width = static_cast<float>(BG_WIDTH);
  const auto offset = width * 0.5f;
  const auto newPosX = width * (checkCount + 1) + offset;
  if (playerX < newPosX) { return false; }

  ++checkCount;
  pos.x() = newPosX - offset;
  return true;
}
