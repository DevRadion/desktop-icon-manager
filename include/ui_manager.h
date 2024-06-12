#pragma once

#include "framework.h"
#include <string>

class UIManager {
 public:
  UIManager(HWND hWnd) : hWnd(hWnd) {}

  HWND AddButton(LPCWSTR text, int x, int y, int width, int height, int id);

  HWND AddEditBox(int x, int y, int width, int height, int id);

  HWND AddStaticText(LPCWSTR text, int x, int y, int width, int height, int id);

  static std::wstring GetEditBoxText(HWND hWnd, int id);

 private:
  HWND hWnd;
};