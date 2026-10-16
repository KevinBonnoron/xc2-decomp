#include "ui/ui_str.h"

#include "mm_mtl/allocator.h"
#include "ui/text/ui_text_manager.h"
#include "ui/ui_util.h"

namespace ui {

UIStr::UIStr() { init(); }

void UIStr::init() {
  type = TYPE_NONE;
  option = 0;
  allocatedSize = 0;
  reference = nullptr;
}

UIStr::UIStr(const UIStr &other) {
  init();
  copy(other);
}

UIStr::UIStr(u8 *data, u32 id) {
  allocatedSize = 0;
  reference = nullptr;
  type = TYPE_NONE;
  option = 0;
  if (data != nullptr && id != 0) {
    mstxt.fileId = UITextManager::get()->registTextFile(data);
    mstxt.msgId = id;
    type = TYPE_MSTXT;
  }
}

void UIStr::setupMstxt(u8 *data, u32 id) {
  release();
  if (data != nullptr && id != 0) {
    mstxt.fileId = UITextManager::get()->registTextFile(data);
    mstxt.msgId = id;
    type = TYPE_MSTXT;
  }
}

UIStr::UIStr(const char *string, bool allocate) {
  init();
  if (string != nullptr && *string != '\0') {
    if (allocate) {
      this->allocate(string);
    } else {
      setupReference(string);
    }
  }
}

void UIStr::setupAllocated(const char *string) { allocate(string); }

void UIStr::setupReference(const char *string) {
  release();
  reference = string;
  type = TYPE_REFERENCE;
}

UIStr::~UIStr() { release(); }

void UIStr::release() {
  if (type == TYPE_ALLOCATED && allocated != nullptr && allocatedSize != 0) {
    UIUtil::getProgAllocator()->deallocate(allocated);
  }
  if (type == TYPE_MSTXT && mstxt.fileId != 0) {
    UITextManager::get()->unregistTextFile(mstxt.fileId);
  }
  init();
}

u8 *UIStr::getMsgFP() const {
  if (type == TYPE_MSTXT) {
    return UITextManager::get()->getTextFile(mstxt.fileId);
  }
  return nullptr;
}

u32 UIStr::getMsgID() const {
  if (type == TYPE_MSTXT) {
    return mstxt.msgId;
  }
  return 0;
}

} // namespace ui
