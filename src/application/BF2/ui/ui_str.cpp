#include "ui/ui_str.h"

#include "mm_mtl/allocator.h"
#include "ui/text/ui_text_manager.h"
#include "ui/ui_util.h"

namespace ui {

UIStr::UIStr() { init(); }

void UIStr::init() {
  unknown10 = TYPE_NONE;
  unknown12 = 0;
  unknown08 = 0;
  reference = nullptr;
}

UIStr::UIStr(const UIStr &other) {
  init();
  copy(other);
}

UIStr::UIStr(u8 *data, u32 id) {
  unknown08 = 0;
  reference = nullptr;
  unknown10 = TYPE_NONE;
  unknown12 = 0;
  if (data != nullptr && id != 0) {
    mstxt.unknown00 = UITextManager::get()->registTextFile(data);
    mstxt.unknown04 = id;
    unknown10 = TYPE_MSTXT;
  }
}

void UIStr::setupMstxt(u8 *data, u32 id) {
  release();
  if (data != nullptr && id != 0) {
    mstxt.unknown00 = UITextManager::get()->registTextFile(data);
    mstxt.unknown04 = id;
    unknown10 = TYPE_MSTXT;
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
  unknown10 = TYPE_REFERENCE;
}

UIStr::~UIStr() { release(); }

void UIStr::release() {
  if (unknown10 == TYPE_ALLOCATED && allocated != nullptr && unknown08 != 0) {
    UIUtil::getProgAllocator()->deallocate(allocated);
  }
  if (unknown10 == TYPE_MSTXT && mstxt.unknown00 != 0) {
    UITextManager::get()->unregistTextFile(mstxt.unknown00);
  }
  init();
}

u8 *UIStr::getMsgFP() const {
  if (unknown10 == TYPE_MSTXT) {
    return UITextManager::get()->getTextFile(mstxt.unknown00);
  }
  return nullptr;
}

u32 UIStr::getMsgID() const {
  if (unknown10 == TYPE_MSTXT) {
    return mstxt.unknown04;
  }
  return 0;
}

} // namespace ui
