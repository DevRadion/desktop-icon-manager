#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <comutil.h>
#include <exdisp.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <windows.h>

class DesktopManager {
public:
  void savePositions(PCWSTR pszFile);

  void restorePositions(PCWSTR pszFile);

private:
  void findDesktopFolderView(REFIID riid, void **ppv);
};