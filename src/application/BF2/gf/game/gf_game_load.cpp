#include "gf/game/gf_game_load.h"

#include <new>
#include <string.h>

#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "ml/dev_file_th.h"
#include "ml/path_util.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

GfGameLoad::GfGameLoad(SAVESLOT slot)
    : unknown08(slot), unknown110(nullptr), unknown118(nullptr), unknown120(0), unknown128(nullptr), unknown130(0), unknown134(-1), unknown138(nullptr), unknown140(nullptr), unknown148(nullptr),
      unknown150(0) {}

GfGameLoad::GfGameLoad(const char *path)
    : unknown08(SAVESLOT_NONE), unknown110(nullptr), unknown118(nullptr), unknown120(0), unknown128(nullptr), unknown130(0), unknown134(-1), unknown138(nullptr), unknown140(nullptr),
      unknown148(nullptr), unknown150(0) {
  unknown0c = path;
}

GfGameLoad::~GfGameLoad() { ; }

bool GfGameLoad::isBusy() const { return unknown120 != 0; }

void GfGameLoad::terminateNonBlock() {
  phaseBinData();
  unknown120 = 0;
}

void GfGameLoad::waitNonBlockBin() {
  while (unknown128 != nullptr) {
    GfSleep(1);
  }
}

void GfGameLoad::endNonBlockBin() { phaseBinData(); }

void GfGameLoad::phaseBinData() {
  if (unknown138 != nullptr) {
    memcpy(unknown138, unknown148, unknown150);
    _gfgsv::s_SDataSave.unknown00 = unknown138->unknown00;
    _gfgsv::s_SDataSave.unknown08 = unknown138->unknown08;
    _gfgsv::s_SDataSave.unknown10 = unknown138->unknown10;
    unknown138 = nullptr;
  } else if (unknown140 != nullptr) {
    memcpy(unknown140, unknown148, unknown150);
    memcpy(&_gfgsv::s_SDataOption, unknown140, sizeof(SDataOption));
    unknown140 = nullptr;
  }
  SDataSave *saveData = unknown110;
  if (saveData != nullptr) {
    saveData->unknown10.unknown109b30.clear();
    saveData->unknown10.unknown1098c8.unknown00.clear();
    getAllocator(ALLOCATOR_DEFAULT)->deallocate(unknown110);
    unknown110 = nullptr;
  }
  if (unknown118 != nullptr) {
    getAllocator(ALLOCATOR_DEFAULT)->deallocate(unknown118);
    unknown118 = nullptr;
  }
  unknown148 = nullptr;
  unknown150 = 0;
}

void GfGameLoad::startNonBlockBin(mm::mtl::FixStr<256> &path) {
  ml::DevFileParamTh param;
  unknown001(param, path);
  param.unknown60 = this;
  unknown128 = ml::DevFileTh::readFile(param);
}

void GfGameLoad::createGameLoadDataBin(SDataSave &saveData, mm::mtl::FixStr<256> &path) {
  unknown138 = &saveData;
  saveData.unknown00 = 0;
  void *buffer = getAllocator(ALLOCATOR_DEFAULT)->allocate(sizeof(SDataSave), 16);
  unknown110 = new (buffer) SDataSave();
  unknown110->unknown00 = 0;
  unknown148 = unknown110;
  unknown150 = sizeof(SDataSave);
  getGameFileNameBin(path);
}

void GfGameLoad::execGameLoadNonBlock(SDataSave &saveData) {
  unknown120 = 2;
  mm::mtl::FixStr<256> path;
  createGameLoadDataBin(saveData, path);
  startNonBlockBin(path);
}

void GfGameLoad::createOptionLoadDataBin(SDataOption &optionData, mm::mtl::FixStr<256> &path) {
  unknown140 = &optionData;
  optionData.unknown00 = 0;
  void *buffer = getAllocator(ALLOCATOR_DEFAULT)->allocate((sizeof(SDataOption) + 15) & ~15, 16);
  unknown118 = new (buffer) SDataOption();
  unknown118->unknown00 = 0;
  unknown148 = unknown118;
  unknown150 = sizeof(SDataOption);
  getOptionFileNameBin(path);
}

void GfGameLoad::execOptionLoadNonBlock(SDataOption &optionData) {
  unknown120 = 2;
  mm::mtl::FixStr<256> path;
  createOptionLoadDataBin(optionData, path);
  startNonBlockBin(path);
}

bool GfGameLoad::execGameLoadBlockForDebug(SDataSave &saveData) {
  unknown120 = 3;
  mm::mtl::FixStr<256> path;
  createGameLoadDataBin(saveData, path);
  {
    ml::DevFileParamTh param;
    unknown001(param, path);
    ml::DevFileTh::readFileBlock(param, &unknown134, nullptr);
    endNonBlockBin();
  }
  unknown120 = 0;
  return saveData.unknown00 == SAVE_DATA_VERSION;
}

bool GfGameLoad::execOptionLoadBlockForDebug(SDataOption &optionData) {
  unknown120 = 3;
  mm::mtl::FixStr<256> path;
  createOptionLoadDataBin(optionData, path);
  {
    ml::DevFileParamTh param;
    unknown001(param, path);
    ml::DevFileTh::readFileBlock(param, &unknown134, nullptr);
    endNonBlockBin();
  }
  unknown120 = 0;
  return optionData.unknown00 == SAVE_DATA_VERSION;
}

void GfGameLoad::getGameFileNameBin(mm::mtl::FixStr<256> &path) {
  mm::mtl::FixStr<256> fileName;
  if (unknown0c.empty()) {
    GfDataSave::getFileNameForLoad(fileName, unknown08);
  } else {
    fileName = unknown0c;
  }
  ml::PathUtil::getNoExtName(path, fileName.c_str());
  path += GfDataSave::getSaveDataExtNameForBin();
}

void GfGameLoad::getOptionFileNameBin(mm::mtl::FixStr<256> &path) {
  mm::mtl::FixStr<256> fileName;
  GfDataSave::getFileNameForOption(fileName);
  ml::PathUtil::getNoExtName(path, fileName.c_str());
  path += GfDataSave::getSaveDataExtNameForBin();
}

bool GfGameLoad::OnFileEvent(ml::EventFileTh *event) {
  if (unknown128 == event->unknown08) {
    unknown130 = event->type;
    if (unknown130 == ml::EventFileTh::TYPE_COMPLETE) {
      unknown134 = event->unknown30;
    }
    unknown128 = nullptr;
  }
  if (unknown120 == 1 && unknown128 == nullptr) {
    phaseBinData();
    unknown120 = 0;
  }
  return true;
}

} // namespace gf
