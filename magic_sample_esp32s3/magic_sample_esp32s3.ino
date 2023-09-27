#include <Arduino.h>

// 有線キーボード
#include "src/lib/usb_keyboard.h"
CustomHIDDevice bleKeyboard = CustomHIDDevice();

int key_a_flag = 0;
int key_b_flag = 0;
int key_c_flag = 0;

void setup() {
  // Serial.begin(115200);
  // IOピン初期化
  // ジョイスティック
  pinMode(6, ANALOG);
  pinMode(3, ANALOG);
  pinMode(5, ANALOG);
  pinMode(2, ANALOG);
  // キー
  pinMode(7, ANALOG);
  pinMode(1, ANALOG);
  pinMode(4, ANALOG);
  delay(100);
  key_a_flag = 0;
  key_b_flag = 0;
  key_c_flag = 0;
  // キーボード初期化
  bleKeyboard.begin("azmagic");

}

void loop() {
  int i, j, k, l;
  int o, p, q, r;
  int s, t, u, v;
  int w, x, y;
  int ts, te;
  ts = micros();
  i = analogRead(6);
  j = analogRead(3);
  k = analogRead(5);
  l = analogRead(2);
  o = analogRead(7);
  p = analogRead(1);
  q = analogRead(4);
  te = micros();
  // ↓ここで上下左右の中央位置調節
  x = k - j + 10;
  y = l - i + 300;
  w = (i + j + k + l) / 4;
  if (w < 970) { // ←ここでどこまで押し込まれたらマウス動き出すか調節
    // Serial.printf("%04d %04d %04d %04d  %04d x:%d y:%d\n", i, j, k, l, w, x, y);
    bleKeyboard.mouse_move((x / 45), (y / 40), 0, 0);
  }
  // Serial.printf("%04d %04d %04d\n", o, p, q);
  if (o > 2000) {
    bleKeyboard.press_raw(4); // A 押す
    key_a_flag = 1;
  } else if (key_a_flag) {
    bleKeyboard.release_raw(4); // A 離す
    key_a_flag = 0;
  }
  if (p > 2000) {
    bleKeyboard.mouse_press(1); // 左クリック 押す
    key_b_flag = 1;
  } else if (key_b_flag) {
    bleKeyboard.mouse_release(1); // 左クリック 離す
    key_b_flag = 0;
  }
  if (q > 2000) {
    bleKeyboard.mouse_press(2); // 右クリック 押す
    key_c_flag = 1;
  } else if (key_c_flag) {
    bleKeyboard.mouse_release(2); // 右クリック 離す
    key_c_flag = 0;
  }

  delay(10);

}
