#include "ui/ui_str.h"

#include <string.h>

#include "mm_mtl/allocator.h"
#include "ui/text/ui_text_manager.h"
#include "ui/ui_util.h"

namespace ui {

// Original name unknown: tests whether a message reference names both a text
// file and a message.
static inline bool unknown001(UIStr::Mstxt mstxt) { return mstxt.unknown00 != 0 && mstxt.unknown04 != 0; }

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

void UIStr::copy(const UIStr &other) {
  if (!other.isValid()) {
    return;
  }
  if (unknown10 != other.unknown10) {
    release();
  }
  if (other.unknown10 == TYPE_MSTXT) {
    setupMstxt(other.getMsgFP(), other.mstxt.unknown04);
  } else if (other.unknown10 == TYPE_REFERENCE) {
    setupReference(other.reference);
  } else if (other.unknown10 == TYPE_ALLOCATED) {
    allocate(other.allocated);
  }
  unknown10 = other.unknown10;
  unknown12 = other.unknown12;
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

const char *UIStr::c_str() const {
  if (unknown10 == TYPE_MSTXT) {
    if (unknown001(mstxt)) {
      return UITextManager::get()->getText(mstxt.unknown00, mstxt.unknown04);
    }
    return nullptr;
  } else if (unknown10 == TYPE_REFERENCE) {
    return reference;
  } else if (unknown10 == TYPE_ALLOCATED) {
    return (allocated != nullptr && unknown08 != 0) ? allocated : nullptr;
  }
  return nullptr;
}

bool UIStr::isValid() const {
  if (unknown10 == TYPE_MSTXT) {
    return mstxt.unknown00 != 0 && mstxt.unknown04 != 0;
  } else if (unknown10 == TYPE_REFERENCE) {
    return reference != nullptr;
  } else if (unknown10 == TYPE_ALLOCATED) {
    return allocated != nullptr && unknown08 != 0;
  }
  return false;
}

u32 UIStr::size() const {
  if (!isValid()) {
    return 0;
  }
  if (c_str() == nullptr) {
    return 0;
  }
  return strlen(c_str());
}

void UIStr::deepcopy(const UIStr &other) {
  if (!other.isValid()) {
    return;
  }
  allocate(other.c_str());
}

bool UIStr::compare(const UIStr &other) {
  if (!isValid() || !other.isValid()) {
    return false;
  }
  if (unknown10 == other.unknown10) {
    if (unknown10 == TYPE_MSTXT) {
      if (mstxt.unknown00 != other.mstxt.unknown00) {
        return false;
      }
      return mstxt.unknown04 == other.mstxt.unknown04 && unknown12 == other.unknown12;
    }
    if (unknown10 == TYPE_ALLOCATED) {
      return strcmp(allocated, other.allocated) == 0;
    }
    if (unknown10 == TYPE_REFERENCE) {
      return strcmp(reference, other.reference) == 0;
    }
  }
  return strcmp(c_str(), other.c_str()) == 0;
}

u16 UIStr::getStyle() const {
  if (unknown10 == TYPE_MSTXT) {
    if (unknown001(mstxt)) {
      return UITextManager::get()->getStyle(mstxt.unknown00, mstxt.unknown04);
    }
  }
  return 0;
}

} // namespace ui
