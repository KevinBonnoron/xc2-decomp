#include "gf/field/gf_field_map_gimmick.h"

#include "dr/dr_man.h"
#include "framework/script/script_manager.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/array.h"

namespace gf {

constexpr u32 OBJ_ATTRIBUTE_TARGETABLE = 7;
constexpr u16 COMMON_WINDOW_GRAVE = 0x33;
const ml::FILE_PRIO GMK_TUTORIAL_FILE_PRIO = static_cast<ml::FILE_PRIO>(7);

AFieldSeq::AFieldSeq(const GfSetupParam &) : handle(INVALID_HANDLE), sequence(nullptr), isEndSeq(false), isFsSucceeded(false) {}

void AFieldSeq::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    dispose();
  }
}

gmk::AGmkBase *AFieldSeq::findBindedGmk() const { return gmk::getBindedGmkInst(handle); }

void AFieldSeq::create(GF_OBJ_HANDLE *handle) {
  dispose();
  this->handle = handle;
  sequence = &AFieldSeq::seqCheckFs;
}

void AFieldSeq::dispose() {
  isEndSeq = false;
  isFsSucceeded = false;
  handle = INVALID_HANDLE;
  sequence = nullptr;
}

void AFieldSeq::update(f32 deltaTime) {
  if (handle != INVALID_HANDLE && sequence) {
    (this->*sequence)(deltaTime);
  }
}

void AFieldSeq::setTargetable(bool isTargetable) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    if (isTargetable) {
      obj->unknown110 |= OBJ_ATTRIBUTE_TARGETABLE;
    } else {
      obj->unknown110 &= ~OBJ_ATTRIBUTE_TARGETABLE;
    }
  }
}

bool AFieldSeq::isTargetable() const {
  GfObj *obj = GfObjUtil::getObj(handle);
  return obj != nullptr ? (obj->unknown110 >> 2) & 1 : false;
}

void AFieldSeq::seqWaitUIEnd(f32) {
  if (GfMenuFieldSkill::isRunning()) {
    return;
  }

  if (isFsSucceeded) {
    GfObjAcc acc(handle);
    if (acc.isValid()) {
      GfComBehaviorGmk *behavior = acc.getObj()->getComponent<GfComBehaviorGmk>();
      if (behavior != nullptr) {
        behavior->disposeMenuObj();
      }
    }
    onFsSucceeded();
  } else {
    onFsFailed();
  }
  sequence = nullptr;
  isEndSeq = true;
}

GfFieldGrave::GfFieldGrave(const GfSetupParam &) : handle(INVALID_HANDLE), sequence(nullptr) {}

void GfFieldGrave::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    dispose();
  }
}

void GfFieldGrave::create(GF_OBJ_HANDLE *handle) {
  dispose();
  this->handle = handle;
  GfMenuManager::openCommonWindow(COMMON_WINDOW_GRAVE);
  sequence = &GfFieldGrave::seqWaitToSelect;
}

void GfFieldGrave::dispose() {
  if (GfMenuManager::isOpenCommonWindow()) {
    GfMenuManager::closeCommonWindow();
  }
  isEndSeq = false;
  handle = INVALID_HANDLE;
  sequence = nullptr;
}

void GfFieldGrave::update(f32 deltaTime) {
  if (sequence) {
    (this->*sequence)(deltaTime);
  }
}

void GfFieldGmkTutorial::build(const GfSetupParam &) {
  // __LINE__ must be 1226 as in the original file: its value changes the instruction order.
#line 1226
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldGmkTutorial();
}

void GfFieldGmkTutorial::destroy() {
  GfFieldGmkTutorial *gmkTutorial = get();
  gmkTutorial->dispose();
  delete gmkTutorial;
}

void GfFieldGmkTutorial::dispose() {
  tutorial = 0;
  scriptName.clear();
}

void GfFieldGmkTutorial::create(const char *name, u32 tutorial) {
  dispose();
  scriptName = name;
  this->tutorial = tutorial;
  fw::ScriptManager::get()->loadScript(scriptSlot, name, GMK_TUTORIAL_FILE_PRIO);
  fw::ScriptManager::get()->scripts[scriptSlot].start();
}

bool GfFieldGmkTutorial::isEnd() const { return fw::ScriptManager::get()->scripts[scriptSlot].isFinish(); }

void GfFieldGmkTutorial::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    dispose();
  }
}

} // namespace gf
