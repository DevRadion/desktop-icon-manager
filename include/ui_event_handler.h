#pragma once

#include "desktop_manager.h"
#include "framework.h"
#include "resource.h"
#include "ui_manager.h"

class UIEventHandler {
 public:
  static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

  // Handlers
  static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

 private:
  static LRESULT CALLBACK HandleMenuSelection(HWND hWnd, UINT message,
                                              WPARAM wParam,
                                       LPARAM lParam);
  static bool validatePath(std::wstring path);
};