#include "gf/data/gf_data_save.h"

namespace gf {

constexpr int CHAPTER_NUMBER_OFFSET = 8;

void GfDataSave::getSaveDataPath(mm::mtl::FixStr<256> &path) { path = "save:/"; }

const char *GfDataSave::getSaveDataFileName() { return "bf2savefile"; }

const char *GfDataSave::getOptionSaveDataFileName() { return "bf2option"; }

const char *GfDataSave::getChapterSaveDataFileName() { return "bf2chapter"; }

const char *GfDataSave::getSaveDataExtNameForBin() { return ".sav"; }

const char *GfDataSave::getSaveDataExtNameForXml() { return ".xml"; }

void GfDataSave::addSaveDataPrefix(mm::mtl::FixStr<256> &path, int number) {
  char prefix[2] = {static_cast<char>('0' + (number < 0 ? 0 : number)), '\0'};
  path += prefix;
}

void GfDataSave::getFileNameForLoad(mm::mtl::FixStr<256> &path, SAVESLOT slot) {
  if (slot == SAVESLOT_NONE) {
    path.clear();
  } else if (slot == SAVESLOT_DEFAULT) {
    getSaveDataPath(path);
    path += getSaveDataFileName();
  } else if (slot < SAVESLOT_CHAPTER_FIRST) {
    getSaveDataPath(path);
    path += getSaveDataFileName();
    mm::mtl::FixStr<16> number;
    number.format("%d", slot);
    path += number.c_str();
  } else {
    mm::mtl::FixStr<16> number;
    number.format("%d", slot - CHAPTER_NUMBER_OFFSET);
    path.format("/work/gf_select/%s%s", getChapterSaveDataFileName(), number.c_str());
  }
}

void GfDataSave::getFileNameForSave(mm::mtl::FixStr<256> &path, SAVESLOT slot) {
  if (slot == SAVESLOT_NONE) {
    path.clear();
  } else if (slot == SAVESLOT_DEFAULT) {
    getSaveDataPath(path);
    path += getSaveDataFileName();
  } else if (slot < SAVESLOT_CHAPTER_FIRST) {
    getSaveDataPath(path);
    path += getSaveDataFileName();
    mm::mtl::FixStr<16> number;
    number.format("%d", slot);
    path += number.c_str();
  } else {
    getSaveDataPath(path);
    mm::mtl::FixStr<16> number;
    number.format("%d", slot - CHAPTER_NUMBER_OFFSET);
    path += getChapterSaveDataFileName();
    path += number.c_str();
  }
}

void GfDataSave::getFileNameForOption(mm::mtl::FixStr<256> &path) {
  getSaveDataPath(path);
  path += getOptionSaveDataFileName();
}

void GfDataSave::getFileNameForLoadBin(mm::mtl::FixStr<256> &path, SAVESLOT slot) {
  getFileNameForLoad(path, slot);
  path += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForLoadXml(mm::mtl::FixStr<256> &path, SAVESLOT slot) {
  getFileNameForLoad(path, slot);
  path += getSaveDataExtNameForXml();
}

void GfDataSave::getFileNameForSaveBin(mm::mtl::FixStr<256> &path, SAVESLOT slot) {
  getFileNameForSave(path, slot);
  path += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForSaveXml(mm::mtl::FixStr<256> &path, SAVESLOT slot) {
  getFileNameForSave(path, slot);
  path += getSaveDataExtNameForXml();
}

void GfDataSave::getFileNameForOptionBin(mm::mtl::FixStr<256> &path) {
  getFileNameForOption(path);
  path += getSaveDataExtNameForBin();
}

void GfDataSave::getFileNameForOptionXml(mm::mtl::FixStr<256> &path) {
  getFileNameForOption(path);
  path += getSaveDataExtNameForXml();
}

} // namespace gf
