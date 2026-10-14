#include "gf/data/gf_data_salvage.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"

namespace gf {

enum {
  FIELD_SKILL_SALVAGING = 9,
};

constexpr u32 SALVAGE_MEMBER_COUNT = 5;

static bool hasSalvageSkill(const SDataBlade &dataBlade) {
  for (u32 index = 0; index < 3; index++) {
    if (dataBlade.fieldSkills[index].id == FIELD_SKILL_SALVAGING && dataBlade.fieldSkills[index].level != 0) {
      return true;
    }
  }

  return false;
}

bool GfDataSalvage::getSalvageSkillBlade(mm::mtl::FixedVector<u16, 422> &blades) {
  blades.clear();
  for (u32 member = 0; member < SALVAGE_MEMBER_COUNT; member++) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, GfDataManager::getDataGame()->party.members[member].driver, static_cast<GimmickType>(0));
    if (dataParamAcc.isValid() && dataParamAcc.isValid() && dataParamAcc.getObjType() == OBJECT_TYPE_DRIVER) {
      int setBladeNum = GfDataDriver::getMaxSetBladeNum(dataParamAcc.getBdatId());
      for (int slot = 0; slot < setBladeNum; slot++) {
        u32 blade = dataParamAcc.getBlade(slot, false);
        if (blade != 0 && hasSalvageSkill(*GfDataBlade::getSDataBlade(blade))) {
          blades.push_back(blade);
        }
      }
    }
  }

  return !blades.empty();
}

u8 GfDataSalvage::getSalvageSkillLevel(u32 blade) {
  u8 level = 0;
  if (blade != 0) {
    SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
    for (u32 index = 0; index < 3; index++) {
      if (dataBlade->fieldSkills[index].id == FIELD_SKILL_SALVAGING && level < dataBlade->fieldSkills[index].level) {
        level = dataBlade->fieldSkills[index].level;
      }
    }
  }

  return level;
}

} // namespace gf
