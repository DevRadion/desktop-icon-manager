#include "ui_event_handler.h"

// Main Window event processor
LRESULT CALLBACK UIEventHandler::WndProc(HWND hWnd, UINT message, WPARAM wParam,
                                         LPARAM lParam) {
  switch (message) {
    case WM_COMMAND:
      HandleMenuSelection(hWnd, message, wParam, lParam);
      break;
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      // TODO: Add any drawing code that uses hdc here...
      EndPaint(hWnd, &ps);
    } break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// UI Handlers

// Message handler for about box.
INT_PTR CALLBACK UIEventHandler::About(HWND hDlg, UINT message, WPARAM wParam,
                                       LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);
  switch (message) {
    case WM_INITDIALOG:
      return (INT_PTR)TRUE;

    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
      }
      break;
  }
  return (INT_PTR)FALSE;
}

bool UIEventHandler::validatePath(std::wstring path) {
  return !path.empty() && path.find(L".dat") != NULL && path.length() > 4;
}

LRESULT CALLBACK UIEventHandler::HandleMenuSelection(HWND hWnd, UINT message,
                                                     WPARAM wParam,
                                                     LPARAM lParam) {
  int wmId = LOWORD(wParam);
  std::wstring path;

  switch (wmId) {
    case IDM_ABOUT:
      DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd,
                UIEventHandler::About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    case IDC_SAVE_LAYOUT_BUTTON:
    case IDC_RESTORE_LAYOUT_BUTTON:
      path = UIManager::GetEditBoxText(hWnd, IDC_PATH_EDIT_BOX);
      if (validatePath(path)) {
        DesktopManager desktop_manager;

        if (wmId == IDC_SAVE_LAYOUT_BUTTON)
          desktop_manager.savePositions((PCWSTR)path.c_str());
        else
          desktop_manager.restorePositions((PCWSTR)path.c_str());

        MessageBox(
            hWnd,
            (wmId == IDC_SAVE_LAYOUT_BUTTON ? (L"Saved to " + path).c_str()
                                            : (L"Restored from " + path))
                .c_str(),
            (wmId == IDC_SAVE_LAYOUT_BUTTON ? L"Save" : L"Restore"), MB_OK);
      } else {
        MessageBox(hWnd, L"Please enter a valid path", L"Error", MB_OK);
      }
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
}
