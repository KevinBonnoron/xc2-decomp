#include "ui/text/ui_text_file.h"

#include "bdat.h"
#include "framework/memory/framework_memory.h"
#include "ui/ui_util.h"

namespace ui {

UITextFile::UITextFile(u8 *data) : data(data) { name = Bdat::getSheetName(data); }

UITextFile::~UITextFile() { ; }

UITextFile *UITextFile::create(u8 *data) {
// __LINE__ is the line argument of the operator new call.
#line 42
  return new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UITextFile(data);
}

void UITextFile::reload() { data = Bdat::getFP(name.c_str()); }

const char *UITextFile::getText(u32 id) const {
  if (data != nullptr) {
    return Bdat::getMSText(data, id);
  }
  return nullptr;
}

u16 UITextFile::getStyle(u32 id) const {
  if (data != nullptr) {
    return Bdat::getMSStyle(data, id);
  }
  return 0xffff;
}

} // namespace ui
