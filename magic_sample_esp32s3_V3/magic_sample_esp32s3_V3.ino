#include <Arduino.h>

// 有線キーボード
#include "src/lib/usb_keyboard.h"
CustomHIDDevice bleKeyboard = CustomHIDDevice();

int key_a_flag = 0;
int key_b_flag = 0;
int key_c_flag = 0;

int mouse_index = 0;
int mouse_x = 0;
int mouse_y = 0;


int read_x_min = 0;
int read_x_max = 0;
int read_y_min = 0;
int read_y_max = 0;
int wide_x = 0;
int wide_y = 0;
int rang_x = 0;
int rang_y = 0;

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
  x = k - j - rang_x;
  y = l - i - rang_y;
  w = (i + j + k + l) / 4;
  // if (w < 980) {
  if (key_b_flag == 0 && w < 1300) {
    // if (mouse_index < 30) mouse_index++;
    v = 1300 - w;
    mouse_x = x * v;
    mouse_y = y * v;
    // Serial.printf("%04d %04d %04d %04d  %04d x:%04d y:%04d %d %d\n", i, j, k, l, w, x, y, mouse_x, mouse_y);
    bleKeyboard.mouse_move((mouse_x / 7000), (mouse_y / 8000), 0, 0);
  }
  // Serial.printf("%04d %04d %04d\n", o, p, q);
  if (p > 2000) {
    if (key_b_flag == 0) {
      read_x_min = 0;
      read_x_max = 0;
      read_y_min = 0;
      read_y_max = 0;
      wide_x = 0;
      wide_y = 0;
      rang_x = 0;
      rang_y = 0;
    }
    key_b_flag = 1;
  } else if (key_b_flag) {
    key_b_flag = 0;
  }
  /*
  if (o > 2000) {
    bleKeyboard.press_raw(4); // A 押す
    key_a_flag = 1;
  } else if (key_a_flag) {
    bleKeyboard.release_raw(4); // A 離す
    key_a_flag = 0;
  }
  if (q > 2000) {
    bleKeyboard.mouse_press(2); // 右クリック 押す
    key_c_flag = 1;
  } else if (key_c_flag) {
    bleKeyboard.mouse_release(2); // 右クリック 離す
    key_c_flag = 0;
  }
  */
  if (key_b_flag) {
    x = k - j;
    y = l - i;
    if (x < read_x_min) read_x_min = x;
    if (x > read_x_max) read_x_max = x;
    if (y < read_y_min) read_y_min = y;
    if (y > read_y_max) read_y_max = y;
    wide_x = read_x_max - read_x_min;
    wide_y = read_y_max - read_y_min;
    rang_x = read_x_min + (wide_x / 2);
    rang_y = read_y_min + (wide_y / 2);
    // Serial.printf("x: %04d %04d  y: %04d %04d  wide: %04d %04d rang: %04d %04d\n", read_x_min, read_x_max, read_y_min, read_y_max, wide_x, wide_y, rang_x, rang_y);
  }

  delay(10);

}
