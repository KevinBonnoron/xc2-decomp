#include "gf/data/gf_debug_save.h"

#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_system.h"
#include "gf/field/gf_real_time.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/fixstr.h"

namespace gf {

bool GfDebugSave::isExist(SAVESLOT slot) {
  _gfdsv::s_tempSav.unknown00 = 0;
  mm::mtl::FixStr<256> path;
  GfDataSave::getFileNameForLoadBin(path, slot);
  {
    ml::DevFileParamTh param;
    param.unknown40 = &_gfdsv::s_tempSav;
    param.unknown48 = sizeof(SDataSave);
    param.unknown50 = sizeof(SDataSave);
    param.unknown00 = path.c_str();
    ml::DevFileTh::readFileBlock(param, nullptr, nullptr);
  }
  return _gfdsv::s_tempSav.unknown00 == SAVE_UNKNOWN_237915;
}

bool GfDebugSave::loadSavedTime(RealTime &realTime, SAVESLOT slot) {
  _gfdsv::s_tempSav.unknown00 = 0;
  mm::mtl::FixStr<256> path;
  GfDataSave::getFileNameForLoadBin(path, slot);
  {
    ml::DevFileParamTh param;
    param.unknown40 = &_gfdsv::s_tempSav;
    param.unknown48 = sizeof(SDataSave);
    param.unknown50 = sizeof(SDataSave);
    param.unknown00 = path.c_str();
    ml::DevFileTh::readFileBlock(param, nullptr, nullptr);
  }
  realTime = _gfdsv::s_tempSav.unknown08;
  return _gfdsv::s_tempSav.unknown00 == SAVE_UNKNOWN_237915;
}

} // namespace gf
