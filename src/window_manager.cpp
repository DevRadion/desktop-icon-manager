#include "window_manager.h"

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM WindowManager::MyRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = UIEventHandler::WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DESKTOPICONMANAGER));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DESKTOPICONMANAGER);
  wcex.lpszClassName = *szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL WindowManager::InitInstance(HINSTANCE hInstance, int nCmdShow) {
  *hInst = hInstance; // Store instance handle in our global variable

  RECT centered_window_rect = getCenteredWindowRect(WINDOW_WIDTH, WINDOW_HEIGHT);
  HWND hWnd = CreateWindowW(
      *szWindowClass, *szTitle,
      WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
      centered_window_rect.left, centered_window_rect.top, WINDOW_WIDTH,
      WINDOW_HEIGHT, nullptr,
      nullptr, hInstance, nullptr);

  if (!hWnd)
    return FALSE;

  ui_manager = new UIManager(hWnd);
  SetupUI(hWnd);

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

RECT WindowManager::getCenteredWindowRect(int width, int height) {
  RECT rc;
  GetWindowRect(GetDesktopWindow(), &rc);
  int xPos = (rc.right - rc.left - width) / 2;
  int yPos = (rc.bottom - rc.top - height) / 2;
  return {xPos, yPos, xPos + width, yPos + height};
}

void WindowManager::SetupUI(HWND hWnd) {
  ui_manager->AddStaticText(L"Filename to save/restore layout", 10, 10, 250, 20,
                            IDC_PATH_STATIC_TEXT);
  ui_manager->AddEditBox(10, 30, 250, 20, IDC_PATH_EDIT_BOX);
  ui_manager->AddButton(L"Save current layout", 10, 60, 250, 30,
                        IDC_SAVE_LAYOUT_BUTTON);
  ui_manager->AddButton(L"Restore layout from file", 10, 100, 250, 30,
                        IDC_RESTORE_LAYOUT_BUTTON);
}