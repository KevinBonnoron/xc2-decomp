#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuMercenariesAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuMercenariesAdapter::update_TeamName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamBlFace, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamStat, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamStatColor, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamWait, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisInfo, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisZone, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisZoneIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisTime, {GfMenuAdapter::unknown004_7, 3, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisComplete, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamStrength, {GfMenuAdapter::unknown004_0, 0, 9999}},
    {&GfMenuMercenariesAdapter::update_TeamMale, {GfMenuAdapter::unknown004_0, 0, 18}},
    {&GfMenuMercenariesAdapter::update_TeamFemale, {GfMenuAdapter::unknown004_0, 0, 18}},
    {&GfMenuMercenariesAdapter::update_TeamAnimal, {GfMenuAdapter::unknown004_0, 0, 18}},
    {&GfMenuMercenariesAdapter::update_TeamStrengthDiffIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamFieldSkillDiffIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamNameRes, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamIconRes, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamIconResFace, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamDispNum1, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuMercenariesAdapter::GfMenuMercenariesAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5a(0), unknown60(nullptr), unknown68(nullptr) {}

GfMenuMercenariesAdapter::~GfMenuMercenariesAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown68);
}

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::create(u32 handle, u32 type, u32 teamId, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 150 as in the original source: it is the line argument of operator new.
#line 150
      GfMenuMercenariesAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuMercenariesAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = teamId;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuMercenariesAdapter::update_TeamIcon() {
  setNumber(unknown58 - 1);
  return true;
}

bool GfMenuMercenariesAdapter::update_TeamStat() {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_MERCENARIES);
  u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_MS);
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    int stat;
    if (mission != 0 && (GfDataMercenaries::isMissionOrderTeam(mission) || GfDataMercenaries::isMissionOrderParty(mission))) {
      stat = 12;
      if (GfDataMercenaries::isTeamStateReward(unknown58)) {
        stat = 13;
      }
    } else {
      stat = 11;
    }
    u16 name = Bdat::getVal(bdat, "name", stat).valueU16;
    setText(ui::UIStr(msBdat, name));
    return true;
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamStatColor() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    if (mission != 0 && (GfDataMercenaries::isMissionOrderTeam(mission) || GfDataMercenaries::isMissionOrderParty(mission))) {
      setAddColor("mer_unit_active");
    } else {
      setAddColor("mer_unit_ready");
    }
    return true;
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamWait() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    if (mission != 0) {
      if (GfDataMercenaries::isMissionOrderTeam(mission)) {
        return false;
      }
      if (GfDataMercenaries::isMissionOrderParty(mission)) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamMisInfo() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    if (mission != 0) {
      if (GfDataMercenaries::isMissionOrderTeam(mission)) {
        return true;
      }
      if (GfDataMercenaries::isMissionOrderParty(mission)) {
        return true;
      }
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamMisZone() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    if (mission != 0) {
      u8 *bdat;
      u32 textId;
      GfDataMercenaries::getMsgZoneName(bdat, textId, mission);
      setText(ui::UIStr(bdat, textId));
      return true;
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamMisZoneIcon() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    if (mission != 0) {
      u32 zone = GfDataMercenaries::getMissionZoneID(mission);
      if (zone != 0) {
        setNumber(zone - 1);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamMisName() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    u32 mission = GfDataMercenaries::getTeamMission(unknown58);
    if (mission != 0) {
      u8 *bdat;
      u32 textId;
      GfDataMercenaries::getMsgTitleName(bdat, textId, mission);
      setText(ui::UIStr(bdat, textId));
      return true;
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamMisComplete() {
  if (GfDataMercenaries::isValidTeamID(unknown58)) {
    return GfDataMercenaries::isTeamStateReward(unknown58);
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamStrength() {
  int power;
  if (unknown60 != nullptr) {
    power = 0;
    for (u16 i = 0; i < unknown60->getSize(); i++) {
      power += GfDataBlade::getBladePower(unknown60->getContents(i).unknown00);
    }
  } else {
    if (!GfDataMercenaries::isValidTeamID(unknown58)) {
      return false;
    }
    power = GfDataMercenaries::getTeamPower(unknown58);
  }
  setNumber(power);
  return true;
}

bool GfMenuMercenariesAdapter::update_TeamMale() {
  int count;
  if (unknown60 != nullptr) {
    count = 0;
    for (u16 i = 0; i < unknown60->getSize(); i++) {
      count += GfDataBlade::isMale(unknown60->getContents(i).unknown00);
    }
  } else {
    if (!GfDataMercenaries::isValidTeamID(unknown58)) {
      return false;
    }
    count = GfDataMercenaries::getTeamMaleNum(unknown58);
  }
  setNumber(count);
  return true;
}

bool GfMenuMercenariesAdapter::update_TeamFemale() {
  int count;
  if (unknown60 != nullptr) {
    count = 0;
    for (u16 i = 0; i < unknown60->getSize(); i++) {
      count += GfDataBlade::isFemale(unknown60->getContents(i).unknown00);
    }
  } else {
    if (!GfDataMercenaries::isValidTeamID(unknown58)) {
      return false;
    }
    count = GfDataMercenaries::getTeamFemaleNum(unknown58);
  }
  setNumber(count);
  return true;
}

bool GfMenuMercenariesAdapter::update_TeamStrengthDiffIcon() {
  if (unknown60 != nullptr) {
    u32 power = 0;
    for (u16 i = 0; i < unknown60->getSize(); i++) {
      power += GfDataBlade::getBladePower(unknown60->getContents(i).unknown00);
    }
    if (GfDataMercenaries::isValidTeamID(unknown58)) {
      u32 teamPower = GfDataMercenaries::getTeamPower(unknown58);
      if (power != teamPower) {
        setNumber(power <= teamPower);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamFieldSkillDiffIcon() {
  if (unknown68 != nullptr && GfDataMercenaries::isValidTeamID(unknown58)) {
    unknown120 *team = GfDataMercenaries::getTeamMember(unknown58);
    if (team != nullptr) {
      GfMenuFieldSkillList *list = GfMenuFieldSkillList::create();
      if (list != nullptr) {
        ui::UIListInfoBase::SetupParam param;
        list->setup(getAllocator(ALLOCATOR_DEFAULT), param);
        for (u16 member : team->unknown00) {
          list->addFieldSkillFromBlade(member);
        }
        u32 icon = 0;
        for (u16 i = 0; i < list->getSize(); i++) {
          if (unknown68->getContents(unknown70).unknown00 == list->getContents(i).unknown00) {
            if (unknown68->getContents(unknown70).unknown02 == list->getContents(i).unknown02) {
              list->release();
              return false;
            }
            icon = unknown68->getContents(unknown70).unknown02 <= list->getContents(i).unknown02;
            break;
          }
        }
        list->release();
        setNumber(icon);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamIconRes() {
  if (unknown60 != nullptr) {
    u32 offset = unknown60->getRowOffset();
    u32 index = unknown70;
    int referenceNumber = GfMenuReference::getReferenceNumber(0);
    if (referenceNumber == 2) {
      index = 10;
    } else if (referenceNumber == 1) {
      index = index + offset;
    } else {
      return false;
    }
    setNumber(index);
    return true;
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamIconResFace() {
  if (unknown60 != nullptr) {
    u32 offset = unknown60->getRowOffset();
    u32 index = unknown70;
    if (GfMenuReference::getReferenceNumber(0) == 0) {
      DataParamAcc acc(OBJECT_TYPE_DRIVER, GfDataParty::getPartyMember(index + offset)->unknown00, GIMMICK_TYPE_NONE);
      if (acc.isValid()) {
        setNumber(GfMenuBdat::getIconImageIndex(acc.getIconData()));
        return true;
      }
    }
  }
  return false;
}

bool GfMenuMercenariesAdapter::update_TeamDispNum1() { return GfDataMercenaries::getTeamNum() > 1; }

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuMercenariesAdapter *adapter = create(handle, type, converter->getTeamId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::createFromReferenceTeam(u32 handle, u32 type, bool isUpdateAlways) {
  // __LINE__ must be 178 as in the original source: it is the line argument of operator new.
#line 178
  ReferenceTeamConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceTeamConverter();
  GfMenuMercenariesAdapter *adapter = create(handle, type, GfMenuReference::getReferenceTeamID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::createFromReferenceTeamBladeList(u32 handle, u32 type, GfMenuBladeList *list, bool isUpdateAlways) {
  // __LINE__ must be 186 as in the original source: it is the line argument of operator new.
#line 186
  ReferenceTeamConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceTeamConverter();
  GfMenuMercenariesAdapter *adapter = create(handle, type, GfMenuReference::getReferenceTeamID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
    list->addRef();
    adapter->unknown60 = list;
  }
  return adapter;
}

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::createFromReferenceTeamFieldSkillList(u32 handle, u32 type, GfMenuFieldSkillList *list, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 200 as in the original source: it is the line argument of operator new.
#line 200
  ReferenceTeamConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceTeamConverter();
  GfMenuMercenariesAdapter *adapter = create(handle, type, GfMenuReference::getReferenceTeamID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
    list->addRef();
    adapter->unknown68 = list;
    adapter->unknown70 = index;
  }
  return adapter;
}

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::createFromBladeList(u32 handle, u32 type, GfMenuBladeList *list, u32 index, bool isUpdateAlways) {
  GfMenuMercenariesAdapter *adapter = create(handle, type, 0, isUpdateAlways);
  if (adapter != nullptr) {
    list->addRef();
    adapter->unknown60 = list;
    adapter->unknown70 = index;
  }
  return adapter;
}

GfMenuMercenariesAdapter *GfMenuMercenariesAdapter::createFromReferenceBlade(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 232 as in the original source: it is the line argument of operator new.
#line 232
  ReferenceBladeConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceBladeConverter(index);
  u32 blade = GfMenuReference::getReferenceBladeID(index);
  u32 teamId = 0;
  if (blade != 0) {
    teamId = GfDataMercenaries::getTeamID(blade);
  }
  GfMenuMercenariesAdapter *adapter = create(handle, type, teamId, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

void GfMenuMercenariesAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newTeamId = unknown50->getTeamId();
    if (unknown58 != newTeamId) {
      unknown58 = newTeamId;
      setChange();
    }
  }
  u32 newMission = GfDataMercenaries::getTeamMission(unknown58);
  if (unknown5a != newMission) {
    unknown5a = newMission;
    setChange();
  }
  if (unknown60 != nullptr && (unknown60->contentsChanged || unknown60->unknown30)) {
    setChange();
  }
  if (unknown68 != nullptr && (unknown68->contentsChanged || unknown68->unknown30)) {
    setChange();
  }
  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(unknown58 != 0 ? unknown30() : false);
    unknown20 &= ~FLAG_CHANGED;
  }
}

bool GfMenuMercenariesAdapter::isOrder(u32 teamId) {
  u32 mission = GfDataMercenaries::getTeamMission(teamId);
  if (mission != 0) {
    if (GfDataMercenaries::isMissionOrderTeam(mission)) {
      return true;
    }
    if (GfDataMercenaries::isMissionOrderParty(mission)) {
      return true;
    }
  }
  return false;
}

u32 GfMenuMercenariesAdapter::ReferenceTeamConverter::getTeamId() { return GfMenuReference::getReferenceTeamID(); }

u32 GfMenuMercenariesAdapter::ReferenceBladeConverter::getTeamId() {
  u32 blade = GfMenuReference::getReferenceBladeID(index);
  if (blade != 0) {
    return GfDataMercenaries::getTeamID(blade);
  }
  return 0;
}

} // namespace gf
