#include "desktop_manager.h"

void DesktopManager::savePositions(PCWSTR pszFile) {
  CComPtr<IFolderView> spView;
  findDesktopFolderView(IID_PPV_ARGS(&spView));

  CComPtr<IStream> spStream;
  SHCreateStreamOnFileEx(pszFile, STGM_CREATE | STGM_WRITE,
                         FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &spStream);
  CComPtr<IEnumIDList> spEnum;
  spView->Items(SVGIO_ALLVIEW, IID_PPV_ARGS(&spEnum));
  for (CComHeapPtr<ITEMID_CHILD> spidl;
       spEnum->Next(1, &spidl, nullptr) == S_OK; spidl.Free()) {
    IStream_WritePidl(spStream, spidl);
    POINT pt;
    spView->GetItemPosition(spidl, &pt);
    spStream->Write(&pt, sizeof(pt), nullptr);
  }
}

void DesktopManager::restorePositions(PCWSTR pszFile) {
  CComPtr<IFolderView> spView;
  findDesktopFolderView(IID_PPV_ARGS(&spView));

  CComPtr<IStream> spStream;
  SHCreateStreamOnFileEx(pszFile, STGM_READ, FILE_ATTRIBUTE_NORMAL, FALSE,
                         nullptr, &spStream);
  POINT pt;
  for (CComHeapPtr<ITEMID_CHILD> spidl;
       SUCCEEDED(IStream_ReadPidl(spStream, &spidl)) &&
       SUCCEEDED(spStream->Read(&pt, sizeof(pt), nullptr));
       spidl.Free()) {
    PCITEMID_CHILD apidl[1] = {spidl};
    spView->SelectAndPositionItems(1, apidl, &pt, SVSI_POSITIONITEM);
  }
}

void DesktopManager::findDesktopFolderView(REFIID riid, void **ppv) {
  CComPtr<IShellWindows> spShellWindows;
  spShellWindows.CoCreateInstance(CLSID_ShellWindows);

  CComVariant vtLoc(CSIDL_DESKTOP);
  CComVariant vtEmpty;
  long lhwnd;
  CComPtr<IDispatch> spdisp;
  spShellWindows->FindWindowSW(&vtLoc, &vtEmpty, SWC_DESKTOP, &lhwnd,
                               SWFO_NEEDDISPATCH, &spdisp);

  CComPtr<IShellBrowser> spBrowser;
  CComQIPtr<IServiceProvider>(spdisp)->QueryService(SID_STopLevelBrowser,
                                                    IID_PPV_ARGS(&spBrowser));

  CComPtr<IShellView> spView;
  spBrowser->QueryActiveShellView(&spView);

  spView->QueryInterface(riid, ppv);
}
