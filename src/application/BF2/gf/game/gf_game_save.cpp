#include "gf/game/gf_game_save.h"

#include <new>

#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_option.h"
#include "gf/field/gf_real_time.h"
#include "gf/game/gf_game_util_save_data.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

GfGameSave::GfGameSave(SAVESLOT slot) : unknown08(0), unknown0c(slot), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(0), unknown30(nullptr), unknown38(0) {}

GfGameSave::~GfGameSave() { destroySaveData(); }

void GfGameSave::destroySaveData() {
  unknown20 = nullptr;
  unknown28 = 0;
  SDataSave *saveData = unknown10;
  if (saveData != nullptr) {
    saveData->unknown10.unknown109b30.clear();
    saveData->unknown10.unknown1098c8.unknown00.clear();
    getAllocator(ALLOCATOR_UNKNOWN_0)->deallocate(unknown10);
    unknown10 = nullptr;
  }
  if (unknown18 != nullptr) {
    getAllocator(ALLOCATOR_UNKNOWN_0)->deallocate(unknown18);
    unknown18 = nullptr;
  }
}

void GfGameSave::flushSaveData() { ml::DevFileTh::flushSave(); }

void GfGameSave::terminateNonBlock() {
  ml::DevFileTh::flushSave();
  destroySaveData();
  unknown08 = 0;
}

void GfGameSave::startNonBlockBin(mm::mtl::FixStr<256> &path) { unknown30 = ml::DevFileTh::writeFile(path.c_str(), this, unknown20, unknown28, 0); }

void GfGameSave::waitNonBlockBin() {
  while (unknown30 != nullptr) {
    GfSleep(1);
  }
}

void GfGameSave::execGameSaveNonBlock() {
  unknown08 = 1;
  mm::mtl::FixStr<256> path;
  createGameSaveData(path);
  unknown30 = ml::DevFileTh::writeFile(path.c_str(), this, unknown20, unknown28, 0);
}

void GfGameSave::execOptionSaveNonBlock() {
  unknown08 = 1;
  mm::mtl::FixStr<256> path;
  createOptionSaveData(path);
  unknown30 = ml::DevFileTh::writeFile(path.c_str(), this, unknown20, unknown28, 0);
}

void GfGameSave::execGameSaveWithMicroThread() {
  unknown08 = 2;
  mm::mtl::FixStr<256> path;
  createGameSaveData(path);
  unknown30 = ml::DevFileTh::writeFile(path.c_str(), this, unknown20, unknown28, 0);
  waitNonBlockBin();
  terminateNonBlock();
}

void GfGameSave::createGameSaveData(mm::mtl::FixStr<256> &path) {
  void *buffer = getAllocator(ALLOCATOR_UNKNOWN_0)->allocate(sizeof(SDataSave), 16);
  unknown10 = new (buffer) SDataSave();
  GfGameUtilSaveData::setupGameSaveData(*unknown10);
  unknown20 = unknown10;
  unknown28 = sizeof(SDataSave);
  GfDataSave::getFileNameForSaveBin(path, unknown0c);
  GfDataManager::setupGame(unknown10, &unknown10->unknown10, nullptr);
  _gfgsv::s_SDataSave.unknown00 = unknown10->unknown00;
  _gfgsv::s_SDataSave.unknown08 = unknown10->unknown08;
  _gfgsv::s_SDataSave.unknown10 = unknown10->unknown10;
  if (unknown0c == SAVESLOT_UNKNOWN_22) {
    GfManager::setSaveDataCreated();
    GfGameUtilSaveData::setTitleSaveData(_gfgsv::s_SDataSave);
  }
}

void GfGameSave::execOptionSaveWithMicroThread() {
  unknown08 = 2;
  mm::mtl::FixStr<256> path;
  createOptionSaveData(path);
  unknown30 = ml::DevFileTh::writeFile(path.c_str(), this, unknown20, unknown28, 0);
  waitNonBlockBin();
  terminateNonBlock();
}

void GfGameSave::createOptionSaveData(mm::mtl::FixStr<256> &path) {
  void *buffer = getAllocator(ALLOCATOR_UNKNOWN_0)->allocate((sizeof(SDataOption) + 15) & ~15, 16);
  unknown18 = new (buffer) SDataOption();
  if (!GfManager::isExecModeThater() && !GfManager::isExecModeAdvertize()) {
    GfGameUtilSaveData::setupOptionSaveData(*unknown18);
  } else {
    *unknown18 = *GfGameUtilSaveData::getValidOptionData();
  }
  unknown20 = unknown18;
  unknown28 = sizeof(SDataOption);
  GfDataSave::getFileNameForOptionBin(path);
  GfDataManager::setupOptionData(*unknown18);
  _gfgsv::s_SDataOption = *unknown18;
}

void GfGameSave::execGameSaveBlockForDebug() {
  unknown08 = 3;
  mm::mtl::FixStr<256> path;
  createGameSaveData(path);
  ml::DevFileTh::writeFileBlock(path.c_str(), unknown20, unknown28, 0);
  terminateNonBlock();
}

void GfGameSave::execOptionSaveBlockForDebug() {
  unknown08 = 3;
  mm::mtl::FixStr<256> path;
  createOptionSaveData(path);
  ml::DevFileTh::writeFileBlock(path.c_str(), unknown20, unknown28, 0);
  terminateNonBlock();
}

void GfGameSave::endNonBlockBin() {}

bool GfGameSave::isBusy() const { return unknown08 != 0; }

SDataSave *GfGameSave::getGameSaveData() { return &_gfgsv::s_SDataSave; }

SDataOption *GfGameSave::getGameOptionData() { return &_gfgsv::s_SDataOption; }

void GfGameSave::makeNewGameSaveData() {
  if (GfDataManager::get() != nullptr) {
    new (&_gfgsv::s_SDataSave) SDataSave();
    _gfgsv::s_SDataOption = *GfDataManager::getDataOption();
  }
}

bool GfGameSave::OnFileEvent(ml::EventFileTh *event) {
  if (unknown30 == event->unknown08) {
    s32 type = event->type;
    unknown30 = nullptr;
    unknown38 = type;
  }
  if (unknown08 == 1 && unknown30 == nullptr) {
    terminateNonBlock();
  }
  return true;
}

} // namespace gf
