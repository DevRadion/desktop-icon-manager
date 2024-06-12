#pragma once

#include "framework.h"
#include "resource.h"
#include "ui_event_handler.h"
#include "ui_manager.h"

#define MAX_LOADSTRING 100
#define WINDOW_WIDTH 290
#define WINDOW_HEIGHT 200

class WindowManager {
public:
  WindowManager(HINSTANCE *hInst, WCHAR (*szTitle)[MAX_LOADSTRING],
                WCHAR (*szWindowClass)[MAX_LOADSTRING])
      : hInst(hInst), szTitle(szTitle), szWindowClass(szWindowClass) {}

  ATOM MyRegisterClass(HINSTANCE hInstance);
  BOOL InitInstance(HINSTANCE, int);

private:
  RECT getCenteredWindowRect(int width, int height);
  void SetupUI(HWND hWnd);
  UIManager *ui_manager;

  HINSTANCE *hInst;                       // current instance
  WCHAR (*szTitle)[MAX_LOADSTRING];       // The title bar text
  WCHAR (*szWindowClass)[MAX_LOADSTRING]; // the main window class name
};