#include "gf/menu/list/gf_menu_field_skill_list.h"

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

constexpr u8 FIELD_SKILL_LEVEL_MAX = 99;
constexpr u32 BLADE_FIELD_SKILL_COUNT = 3;
constexpr int DRIVER_BLADE_COUNT = 3;

GfMenuFieldSkillList::GfMenuFieldSkillList() {}

GfMenuFieldSkillList::~GfMenuFieldSkillList() {
  // A body that is not empty keeps the vtable pointer store that the game does.
  ;
}

GfMenuFieldSkillList *GfMenuFieldSkillList::create() {
  // __LINE__ must be 41 as in the original source: it is the line argument of operator new.
#line 41
  GfMenuFieldSkillList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuFieldSkillList();
  list->addRef();
  return list;
}

void GfMenuFieldSkillList::addFieldSkill(const MenuFieldSkill &fieldSkill) {
  for (u32 i = 0; i < getSize(); i++) {
    MenuFieldSkill &current = getContents(i);
    if (current.fieldSkill == fieldSkill.fieldSkill) {
      u8 level = fieldSkill.level + current.level;
      current.level = level > FIELD_SKILL_LEVEL_MAX ? FIELD_SKILL_LEVEL_MAX : level;
      return;
    }
  }
  addContents(fieldSkill);
}

void GfMenuFieldSkillList::addFieldSkillFromBlade(u32 blade) {
  if (!GfMenuObjUtil::isValidBlade(blade)) {
    return;
  }
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    for (u32 i = 0; i < BLADE_FIELD_SKILL_COUNT; i++) {
      if (acc.getFieldSkill(i, false) != 0) {
        MenuFieldSkill fieldSkill;
        fieldSkill.fieldSkill = acc.getFieldSkill(i, false);
        fieldSkill.level = acc.getFieldSkillLevel(i, false);
        addFieldSkill(fieldSkill);
      }
    }
  }
}

void GfMenuFieldSkillList::addFieldSkillFromBladeList(const GfMenuBladeList *list) {
  if (list == nullptr) {
    return;
  }
  for (u32 i = 0; i < list->getSize(); i++) {
    addFieldSkillFromBlade(list->getContents(i).blade);
  }
}

void GfMenuFieldSkillList::addFieldSkillFromParty() {
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_PARTY_AND_RESERVER, 0);
  for (u32 i = 0; i < drivers.size(); i++) {
    DataParamAcc acc(OBJECT_TYPE_DRIVER, drivers[i], GIMMICK_TYPE_NONE);
    if (acc.isValid()) {
      for (int slot = 0; slot < DRIVER_BLADE_COUNT; slot++) {
        addFieldSkillFromBlade(acc.getBlade(slot, false));
      }
    }
  }
}

} // namespace gf
