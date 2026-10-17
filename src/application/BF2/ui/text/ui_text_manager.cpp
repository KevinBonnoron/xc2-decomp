#include "ui/text/ui_text_manager.h"

#include "bdat.h"
#include "mm_mtl/hash.h"
#include "ui/text/ui_text_file.h"
#include "ui/ui_util.h"

namespace ui {

UITextManager::UITextManager() { fileMap.reserve(UIUtil::getProgAllocator(), 256); }

UITextManager::~UITextManager() {
  for (FileInfo *it = files.begin(); it != files.end(); ++it) {
    delete static_cast<UITextFile *>(fileMap.getPtr(it->handle));
  }
  files.clear();
}

u32 UITextManager::registTextFile(u8 *data) {
  u32 hash = mm::mtl::hashStrCrc(Bdat::getSheetName(data));
  for (FileInfo *it = files.begin(); it != files.end(); ++it) {
    if (it->hash == hash) {
      it->refCount++;
      return it->handle;
    }
  }

  u32 handle = fileMap.regist(UITextFile::create(data));
  if (handle != 0) {
    FileInfo info;
    info.hash = hash;
    info.handle = handle;
    info.refCount = 1;
    files.push_back(info);
  }
  return handle;
}

void UITextManager::unregistTextFile(u32 handle) {
  for (FileInfo *it = files.begin(); it != files.end(); ++it) {
    if (it->handle == handle && (it->refCount == 0 || --it->refCount == 0)) {
      delete static_cast<UITextFile *>(fileMap.getPtr(handle));
      fileMap.remove(it->handle);
      files.erase(it);
      return;
    }
  }
}

void UITextManager::reloadAll() {
  for (FileInfo *it = files.begin(); it != files.end(); ++it) {
    UITextFile *file = static_cast<UITextFile *>(fileMap.getPtr(it->handle));
    if (file != nullptr) {
      file->reload();
    }
  }
}

void UITextManager::reload(u32 handle) {
  UITextFile *file = static_cast<UITextFile *>(fileMap.getPtr(handle));
  if (file != nullptr) {
    file->reload();
  }
}

const char *UITextManager::getText(u32 handle, u32 id) const {
  UITextFile *file = static_cast<UITextFile *>(fileMap.getPtr(handle));
  if (file != nullptr) {
    return file->getText(id);
  }
  return nullptr;
}

u16 UITextManager::getStyle(u32 handle, u32 id) const {
  UITextFile *file = static_cast<UITextFile *>(fileMap.getPtr(handle));
  if (file != nullptr) {
    return file->getStyle(id);
  }
  return 0;
}

u8 *UITextManager::getTextFile(u32 handle) const {
  UITextFile *file = static_cast<UITextFile *>(fileMap.getPtr(handle));
  return file != nullptr ? file->data : nullptr;
}

} // namespace ui
