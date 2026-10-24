#include "ui/text/ui_text_file.h"

#include "bdat.h"
#include "framework/memory/framework_memory.h"
#include "ui/ui_util.h"

namespace ui {

UITextFile::UITextFile(u8 *data) : unknown08(data) { unknown10 = Bdat::getSheetName(data); }

UITextFile::~UITextFile() { ; }

UITextFile *UITextFile::create(u8 *data) {
// __LINE__ is the line argument of the operator new call.
#line 42
  return new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UITextFile(data);
}

void UITextFile::reload() { unknown08 = Bdat::getFP(unknown10.c_str()); }

const char *UITextFile::getText(u32 id) const {
  if (unknown08 != nullptr) {
    return Bdat::getMSText(unknown08, id);
  }
  return nullptr;
}

u16 UITextFile::getStyle(u32 id) const {
  if (unknown08 != nullptr) {
    return Bdat::getMSStyle(unknown08, id);
  }
  return 0xffff;
}

} // namespace ui
