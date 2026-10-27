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
#include "gmk/gmk_grave.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/array.h"

namespace gf {

constexpr u32 OBJ_ATTRIBUTE_TARGETABLE = 7;
constexpr u16 COMMON_WINDOW_GRAVE = 0x33;
const ml::FILE_PRIO GMK_TUTORIAL_FILE_PRIO = static_cast<ml::FILE_PRIO>(7);

AFieldSeq::AFieldSeq(const GfSetupParam &) : unknown08(INVALID_HANDLE), unknown10(nullptr), m_end(false), unknown21(false) {}

void AFieldSeq::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    dispose();
  }
}

gmk::AGmkBase *AFieldSeq::findBindedGmk() const { return gmk::getBindedGmkInst(unknown08); }

void AFieldSeq::create(GF_OBJ_HANDLE *handle) {
  dispose();
  this->unknown08 = handle;
  unknown10 = &AFieldSeq::seqCheckFs;
}

void AFieldSeq::dispose() {
  m_end = false;
  unknown21 = false;
  unknown08 = INVALID_HANDLE;
  unknown10 = nullptr;
}

void AFieldSeq::update(f32 deltaTime) {
  if (unknown08 != INVALID_HANDLE && unknown10) {
    (this->*unknown10)(deltaTime);
  }
}

void AFieldSeq::setTargetable(bool isTargetable) {
  GfObj *obj = GfObjUtil::getObj(unknown08);
  if (obj != nullptr) {
    if (isTargetable) {
      obj->unknown110 |= OBJ_ATTRIBUTE_TARGETABLE;
    } else {
      obj->unknown110 &= ~OBJ_ATTRIBUTE_TARGETABLE;
    }
  }
}

bool AFieldSeq::isTargetable() const {
  GfObj *obj = GfObjUtil::getObj(unknown08);
  return obj != nullptr ? (obj->unknown110 >> 2) & 1 : false;
}

void AFieldSeq::seqWaitUIEnd(f32) {
  if (GfMenuFieldSkill::isRunning()) {
    return;
  }

  if (unknown21) {
    GfObjAcc acc(unknown08);
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
  unknown10 = nullptr;
  m_end = true;
}

GfFieldGrave::GfFieldGrave(const GfSetupParam &) : unknown10(INVALID_HANDLE), unknown20(nullptr) {}

void GfFieldGrave::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    dispose();
  }
}

void GfFieldGrave::create(GF_OBJ_HANDLE *handle) {
  dispose();
  this->unknown10 = handle;
  GfMenuManager::openCommonWindow(COMMON_WINDOW_GRAVE);
  unknown20 = &GfFieldGrave::seqWaitToSelect;
}

void GfFieldGrave::seqWaitToSelect(f32) {
  if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      gmk::GmkGrave *grave = static_cast<gmk::GmkGrave *>(gmk::getBindedGmkInst(unknown10));
      if (grave == nullptr) {
        dispose();
      } else {
        grave->reqPopEnemy();
      }
    }
    unknown20 = nullptr;
    m_end = true;
  }
}

void GfFieldGrave::dispose() {
  if (GfMenuManager::isOpenCommonWindow()) {
    GfMenuManager::closeCommonWindow();
  }
  m_end = false;
  unknown10 = INVALID_HANDLE;
  unknown20 = nullptr;
}

void GfFieldGrave::update(f32 deltaTime) {
  if (unknown20) {
    (this->*unknown20)(deltaTime);
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
  unknown50 = 0;
  unknown0c.clear();
}

void GfFieldGmkTutorial::create(const char *name, u32 tutorial) {
  dispose();
  unknown0c = name;
  this->unknown50 = tutorial;
  fw::ScriptManager::get()->loadScript(unknown08, name, GMK_TUTORIAL_FILE_PRIO);
  fw::ScriptManager::get()->unknown20[unknown08].start();
}

bool GfFieldGmkTutorial::isEnd() const { return fw::ScriptManager::get()->unknown20[unknown08].isFinish(); }

void GfFieldGmkTutorial::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    dispose();
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldMapGimmick>::~PtrSingleton();
