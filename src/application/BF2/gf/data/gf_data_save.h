#pragma once
#include "mm_mtl/fixstr.h"

namespace gf {

class GfDataSave {
public:
  static void getSaveDataPath(mm::mtl::FixStr<256> &path);
  static const char *getSaveDataFileName();
  static const char *getOptionSaveDataFileName();
  static const char *getChapterSaveDataFileName();
  static const char *getSaveDataExtNameForBin();
  static const char *getSaveDataExtNameForXml();
};

} // namespace gf
