#include "ui/text/ui_text_manager.h"

#include "bdat.h"
#include "mm_mtl/hash.h"
#include "ui/text/ui_text_file.h"
#include "ui/ui_util.h"

namespace ui {

UITextManager::UITextManager() { unknownc10.reserve(UIUtil::getProgAllocator(), 256); }

UITextManager::~UITextManager() {
  for (FileInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    delete static_cast<UITextFile *>(unknownc10.getPtr(it->unknown04));
  }
  unknown08.clear();
}

u32 UITextManager::registTextFile(u8 *data) {
  u32 hash = mm::mtl::hashStrCrc(Bdat::getSheetName(data));
  for (FileInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown00 == hash) {
      it->unknown08++;
      return it->unknown04;
    }
  }

  u32 handle = unknownc10.regist(UITextFile::create(data));
  if (handle != 0) {
    FileInfo info;
    info.unknown00 = hash;
    info.unknown04 = handle;
    info.unknown08 = 1;
    unknown08.push_back(info);
  }
  return handle;
}

void UITextManager::unregistTextFile(u32 handle) {
  for (FileInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown04 == handle && (it->unknown08 == 0 || --it->unknown08 == 0)) {
      delete static_cast<UITextFile *>(unknownc10.getPtr(handle));
      unknownc10.remove(it->unknown04);
      unknown08.erase(it);
      return;
    }
  }
}

void UITextManager::reloadAll() {
  for (FileInfo *it = unknown08.begin(); it != unknown08.end(); ++it) {
    UITextFile *file = static_cast<UITextFile *>(unknownc10.getPtr(it->unknown04));
    if (file != nullptr) {
      file->reload();
    }
  }
}

void UITextManager::reload(u32 handle) {
  UITextFile *file = static_cast<UITextFile *>(unknownc10.getPtr(handle));
  if (file != nullptr) {
    file->reload();
  }
}

const char *UITextManager::getText(u32 handle, u32 id) const {
  UITextFile *file = static_cast<UITextFile *>(unknownc10.getPtr(handle));
  if (file != nullptr) {
    return file->getText(id);
  }
  return nullptr;
}

u16 UITextManager::getStyle(u32 handle, u32 id) const {
  UITextFile *file = static_cast<UITextFile *>(unknownc10.getPtr(handle));
  if (file != nullptr) {
    return file->getStyle(id);
  }
  return 0;
}

u8 *UITextManager::getTextFile(u32 handle) const {
  UITextFile *file = static_cast<UITextFile *>(unknownc10.getPtr(handle));
  return file != nullptr ? file->unknown08 : nullptr;
}

} // namespace ui
