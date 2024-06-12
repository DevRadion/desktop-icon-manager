#include "ui_manager.h"

HWND UIManager::AddButton(LPCWSTR text, int x, int y, int width, int height, int id) {
  return CreateWindow(L"BUTTON", text,
                      WS_TABSTOP | WS_VISIBLE | WS_CHILD |
                          BS_FLAT,
                      x,
                      y, width, height, hWnd, (HMENU)id,
                      (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
}

HWND UIManager::AddEditBox(int x, int y, int width, int height, int id) {
  return CreateWindow(L"EDIT", NULL,
                      WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                      x, y, width, height, hWnd, (HMENU)id,
                      (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
}

HWND UIManager::AddStaticText(LPCWSTR text, int x, int y, int width, int height,
                              int id) {
  return CreateWindow(L"STATIC", text,
                      WS_VISIBLE | WS_CHILD | SS_LEFT | SS_SIMPLE, x, y,
                      width, height, hWnd, (HMENU)id,
                      (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
}

std::wstring UIManager::GetEditBoxText(HWND hWnd, int id) {
  HWND hWndEdit = GetDlgItem(hWnd, id);
  int length = GetWindowTextLength(hWndEdit);
  if (length == 0) {
    return L"";
  }
  std::wstring text(length, L'\0');
  GetWindowText(hWndEdit, &text[0], length + 1);
  return text;
}