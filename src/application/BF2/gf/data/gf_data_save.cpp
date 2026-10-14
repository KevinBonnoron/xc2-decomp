#include "gf/data/gf_data_save.h"

namespace gf {

void GfDataSave::getSaveDataPath(mm::mtl::FixStr<256> &path) { path = "save:/"; }

const char *GfDataSave::getSaveDataFileName() { return "bf2savefile"; }

const char *GfDataSave::getOptionSaveDataFileName() { return "bf2option"; }

const char *GfDataSave::getChapterSaveDataFileName() { return "bf2chapter"; }

const char *GfDataSave::getSaveDataExtNameForBin() { return ".sav"; }

const char *GfDataSave::getSaveDataExtNameForXml() { return ".xml"; }

} // namespace gf
