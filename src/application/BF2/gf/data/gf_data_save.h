#pragma once
#include "mm_mtl/fixstr.h"

namespace gf {

struct SDataOption;
struct SDataSave;

namespace _gfgsv {
extern SDataSave s_SDataSave;
extern SDataOption s_SDataOption;
} // namespace _gfgsv

namespace _gfdsv {
extern SDataSave s_tempSav;
} // namespace _gfdsv

enum SAVESLOT {
  SAVESLOT_UNKNOWN_FFFFFFFF = -1, // Inferred role: saveslot none; original name unknown.
  SAVESLOT_UNKNOWN_10 = 10,       // Inferred role: saveslot chapter first; original name unknown.
  SAVESLOT_UNKNOWN_22 = 22,       // Inferred role: saveslot default; original name unknown.
};

class GfDataSave {
public:
  static void getSaveDataPath(mm::mtl::FixStr<256> &path);
  static const char *getSaveDataFileName();
  static const char *getOptionSaveDataFileName();
  static const char *getChapterSaveDataFileName();
  static const char *getSaveDataExtNameForBin();
  static const char *getSaveDataExtNameForXml();
  static void addSaveDataPrefix(mm::mtl::FixStr<256> &path, int number);
  static void getFileNameForLoad(mm::mtl::FixStr<256> &path, SAVESLOT slot);
  static void getFileNameForSave(mm::mtl::FixStr<256> &path, SAVESLOT slot);
  static void getFileNameForOption(mm::mtl::FixStr<256> &path);
  static void getFileNameForLoadBin(mm::mtl::FixStr<256> &path, SAVESLOT slot);
  static void getFileNameForLoadXml(mm::mtl::FixStr<256> &path, SAVESLOT slot);
  static void getFileNameForSaveBin(mm::mtl::FixStr<256> &path, SAVESLOT slot);
  static void getFileNameForSaveXml(mm::mtl::FixStr<256> &path, SAVESLOT slot);
  static void getFileNameForOptionBin(mm::mtl::FixStr<256> &path);
  static void getFileNameForOptionXml(mm::mtl::FixStr<256> &path);
};

} // namespace gf
