#include "gf/menu/object/gf_menu_obj_zone_map.h"

#include <string.h>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_map.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/field/gf_gmk_locator_atlas.h"
#include "gf/game/gf_game_cond.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_world_map_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_map_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_zone_map_list.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_aabb.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_sync_plugin.h"
#include "ui/stream/ui_stream_manager.h"
#include "ui/ui_object_acc.h"

namespace gmo_zone_map {

const char *nd_lay_icon_node_tbl[8] = {"LAY_icon_mapjump", "LAY_icon_enemy", "LAY_icon_collect", "LAY_icon_kizuna", "LAY_icon_shop", "LAY_icon_quest", "LAY_icon_scenario", "LAY_icon_salvage"};
const char *nd_lay_icon_always = "LAY_icon_always";

} // namespace gmo_zone_map

namespace gf {

GfMenuObjZoneMap::GfMenuObjZoneMap(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(1.0f), unknown48(nullptr), unknown50(nullptr), unknown70(false), unknown98(nullptr), unknown3100(0),
      unknown3124(false), unknown3125(false), unknown3128(nullptr), unknown3130(this), unknown33c0(false), unknown33c8(nullptr), unknown33d0(0) {
  unknown58.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
}

GfMenuObjZoneMap::~GfMenuObjZoneMap() {
  if (unknown58.size() != 0) {
    unknown58.destroy();
  }
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown98);
  mm::mtl::safeRelease(unknown3128);
}

void GfMenuObjZoneMap::finalize() {
  ui::UIObjectAcc acc(unknown18);
  if (unknown70 && unknown74.length() != 0) {
    ui::UIStreamManager::get()->deleteImage(unknown74, acc.searchChild("LAY_floor"));
    unknown70 = false;
    unknown74.clear();
  }
  GfFieldGimmick::get()->unknownf4c0.dispose();
  GfMenuObject::finalize();
}

void GfMenuObjZoneMap::update() {
  unknown3130.unknown003();
  GfFieldGimmick::get()->unknownf4c0.update(0.0f);
  GfMenuObject::update();
}

void GfMenuObjZoneMap::setupMain(ui::UIObjectAcc &acc) { GfMenuWorldMapAdapter::createFromReference(acc.searchChild("TXT_areaindex"), 0, false); }

int GfMenuObjZoneMap::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjZoneMap::setDispIconNode(ui::UIObjectAcc &acc, u32 node) {
  if (node == 0) {
    for (u32 i = 0; i < 8; i++) {
      ui::UIObjectAcc icon(acc.searchChild(gmo_zone_map::nd_lay_icon_node_tbl[i]));
      icon.setDisp(true);
    }
  } else {
    for (u32 i = 0; i < 8; i++) {
      ui::UIObjectAcc icon(acc.searchChild(gmo_zone_map::nd_lay_icon_node_tbl[i]));
      icon.setDisp(node - 1 == i);
    }
  }
}

void GfMenuObjZoneMap::sendEvent(u32 handle, u32 type, u32 param) { unknown163(handle, type, param); }

int GfMenuObjZoneMap::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjZoneMap::setDispMapCursor(ui::UIObjectAcc &acc, bool isDisp) {
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_cursor", isDisp);
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_cursorline_w", isDisp);
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_cursorline_h", isDisp);
}

void GfMenuObjZoneMap::setupMapSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 8; i++) {
    name.format("TXT_zonename_@%02d", i + 1);
    GfMenuZoneMapAdapter *adapter = GfMenuZoneMapAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, true, false);
    name.format("LAY_zonespot@%02d", i + 1);
    if (adapter != nullptr) {
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_sonestay_@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  }
  ui::UIObjectAcc arrow1(acc.searchChild("IMG_zonearrow@01"));
  arrow1.startAnimation("loop", false);
  ui::UIObjectAcc arrow2(acc.searchChild("IMG_zonearrow@02"));
  arrow2.startAnimation("loop", false);
}

void GfMenuObjZoneMap::refreshMapSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, u32 map) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    u32 id = list->getContents(list->getPageIndex(i)).unknown00;
    name.format("IMG_zone_base_@%02d", i + 1);
    ui::UIObjectAcc base(acc.searchChild(name.c_str()));
    name.format("TXT_zonename@%02d", i + 1);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    if (id == map) {
      base.setImageIndex(1);
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_bl_index");
    } else {
      base.setImageIndex(0);
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_dr_index");
    }
  }
  bool isDispPrev = list->getPageIndex(0) != 0;
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_zonearrow@01", isDispPrev);
  bool isDispNext = false;
  if (list->getSize() != 0) {
    isDispNext = list->getPageIndex(objects->getSize() - 1) != list->getSize() - 1;
  }
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_zonearrow@02", isDispNext);
}

void GfMenuObjZoneMap::setupPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 8; i++) {
    name.format("TXT_pointname_@%02d", i + 1);
    GfMenuZoneMapAdapter *adapter = GfMenuZoneMapAdapter::createFromList(acc.searchChild(name.c_str()), 1, list, i, true, false);
    name.format("LAY_pointspot@%02d", i + 1);
    if (adapter != nullptr) {
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_pointstay_@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  }
  ui::UIObjectAcc arrow1(acc.searchChild("IMG_pointarrow@01"));
  arrow1.startAnimation("loop", false);
  ui::UIObjectAcc arrow2(acc.searchChild("IMG_pointarrow@02"));
  arrow2.startAnimation("loop", false);
}

void GfMenuObjZoneMap::refreshPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, u32 point) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    u32 id = list->getContents(list->getPageIndex(i)).unknown00;
    name.format("IMG_point_base_@%02d", i + 1);
    ui::UIObjectAcc base(acc.searchChild(name.c_str()));
    name.format("TXT_pointname_@%02d", i + 1);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    if (id == point) {
      base.setImageIndex(1);
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_bl_index");
    } else {
      base.setImageIndex(0);
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_dr_index");
    }
    if (!isEnableJump(list->getContents(list->getPageIndex(i)))) {
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_disable");
    }
  }
  bool isDispPrev = list->getPageIndex(0) != 0;
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_pointarrow@01", isDispPrev);
  bool isDispNext = false;
  if (list->getSize() != 0) {
    isDispNext = list->getPageIndex(objects->getSize() - 1) != list->getSize() - 1;
  }
  GfMenuObjUtil::setChildDisp(acc.unknown10, "IMG_pointarrow@02", isDispNext);
}

bool GfMenuObjZoneMap::isEnableJump(const MenuZoneMapInfo &info) {
  u32 worldMap = GfMenuReference::getReferenceWorldMapID();
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_MAPLIST);
  u32 allOffCondition = Bdat::getVal(bdat, "st_allOFF_cndID", worldMap).valueU16;
  u16 offCondition = Bdat::getVal(bdat, "st_OFF_cndID", worldMap).valueU16;
  if (allOffCondition != 0 && GfGameCond::isGameCond(allOffCondition)) {
    return false;
  }
  if (offCondition != 0 && GfGameCond::isGameCond(offCondition)) {
    return false;
  }
  if (info.unknown08 != 0 && GfGameCond::isGameCond(info.unknown08)) {
    return false;
  }
  return true;
}

bool GfMenuObjZoneMap::setupMapList(GfMenuZoneMapList *list) {
  const char *mapName = GfDataMap::getMapResourceNameByMapID(GfMenuReference::getReferenceWorldMapID());
  list->clear();
  u8 *group = GfDataBdat::getFP(BDAT_MNU_MAP_GROUP);
  int top = Bdat::getIdTop(group);
  for (u32 i = 0; i < Bdat::getIdCount(group); i++) {
    const char *includeMap = Bdat::getVal(group, "include_map", top + i).valueString;
    if (includeMap != nullptr && strcmp(mapName, includeMap) == 0) {
      MenuZoneMapInfo info;
      info.unknown00 = top + i;
      list->addContents(info);
    }
  }
  u32 size = list->getSize();
  if (size == 0) {
    u8 *mapInfo = GfDataBdat::getFP(BDAT_MNU_MAP_INFO);
    int infoTop = Bdat::getIdTop(mapInfo);
    for (u32 i = 0; i < Bdat::getIdCount(mapInfo); i++) {
      const char *levelName = Bdat::getVal(mapInfo, "level_name", infoTop + i).valueString;
      if (levelName != nullptr && strncmp(mapName, levelName, 5) == 0) {
        MenuZoneMapInfo info;
        info.unknown00 = infoTop + i;
        list->addContents(info);
      }
    }
  }
  return size != 0;
}

void GfMenuObjZoneMap::setupZoneMap(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, bool) {
  for (u32 i = 0; i < list->getSize(); i++) {
    mm::mtl::FixStr<32> name;
    name.format("LAY_zonespot@%02d", i + 1);
    u32 object = acc.searchChild(name.c_str());
    if (object != 0) {
      objects->addObject(object);
    }
    if (i + 1 >= 8) {
      break;
    }
  }
  ui::UIObjectAcc cursor(acc.searchChild("IMG_cursor"));
  cursor.startAnimation("loop", false);
  ui::UIObjectSyncPlugin *plugin = ui::UIObjectSyncPlugin::create(acc.searchChild("IMG_cursorline_w"));
  plugin->setTargetObject(acc.searchChild("IMG_cursor"));
  plugin->setTargetFlag(ui::UIObjectSyncPlugin::TARGET_POS_CENTER);
  mm::mtl::safeRelease(plugin);
  plugin = ui::UIObjectSyncPlugin::create(acc.searchChild("IMG_cursorline_h"));
  plugin->setTargetObject(acc.searchChild("IMG_cursor"));
  plugin->setTargetFlag(ui::UIObjectSyncPlugin::TARGET_POS_CENTER);
  mm::mtl::safeRelease(plugin);
}

void GfMenuObjZoneMap::clearTex() {
  unknown3130.unknown005();
  unknown3130.unknown002(&GfMenuObjZoneMap::seqTexDelete);
  unknown3130.unknown002(&GfMenuObjZoneMap::seqTexDeleteWait);
}

void GfMenuObjZoneMap::setupPoint(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects) {
  objects->clear();
  for (u32 i = 0; i < list->getSize(); i++) {
    mm::mtl::FixStr<32> name;
    name.format("LAY_pointspot@%02d", i + 1);
    u32 object = acc.searchChild(name.c_str());
    if (object != 0) {
      objects->addObject(object);
    }
    if (i + 1 >= 8) {
      break;
    }
  }
}

void GfMenuObjZoneMap::setupHelp(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 12; i++) {
    name.format("IMG_hp_zoneicon@%02d", i + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    icon.setImageIndex(i);
  }
}

bool GfMenuObjZoneMap::chkFloor(u32, u32) { return true; }

u32 GfMenuObjZoneMap::setupIconTableSub(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 256> &icons, u32 type, mm::Pnt<s16> pos, mm::Vec2) {
  // Inferred role: image index of the icon of each type; original name unknown.
  static const u32 unknown002[12] = {11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  if (icons.size() == icons.capacity()) {
    return 0;
  }
  const char *name = getIconNodeName(type);
  ui::UIObjectAcc layout(acc.searchChild("LAY_icon"));
  u32 handle = ui::UIObjectAcc(layout.searchChild("IMG_zoneicon")).duplicate(layout.searchChild(name));
  ui::UIObjectAcc icon(handle);
  if (icon.isValid()) {
    icon.setDisp(true);
    icon.setPosCenter(pos);
    icon.setImageIndex(unknown002[type]);
    icons.push_back(handle);
    if (type == 1) {
      icon.setMulColor("yellow");
    }
  }
  return handle;
}

const char *GfMenuObjZoneMap::getIconNodeName(u32 type) {
  switch (type) {
  case 0:
    return gmo_zone_map::nd_lay_icon_node_tbl[0];
  case 5:
    return gmo_zone_map::nd_lay_icon_node_tbl[5];
  case 6:
    return gmo_zone_map::nd_lay_icon_node_tbl[6];
  case 7:
    return gmo_zone_map::nd_lay_icon_node_tbl[7];
  case 9:
    return gmo_zone_map::nd_lay_icon_node_tbl[9];
  case 10:
    return gmo_zone_map::nd_lay_icon_node_tbl[10];
  case 11:
    return gmo_zone_map::nd_lay_icon_node_tbl[11];
  default:
    return gmo_zone_map::nd_lay_icon_always;
  }
}

void GfMenuObjZoneMap::closeIconTable(ui::UIObjectAcc &, mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 12> &icons) {
  for (mm::mtl::FixedVector<u32, 256> *floor = icons.begin(); floor != icons.end(); ++floor) {
    for (u32 *it = floor->begin(); it != floor->end(); ++it) {
      ui::UIObjectAcc icon(*it);
      if (icon.isValid() && !icon.isTerm()) {
        icon.setTerm();
      }
    }
    floor->clear();
  }
}

u32 GfMenuObjZoneMap::getFloor() {
  if (!unknown28->unknown79) {
    return unknown28->getContents(unknown28->getIndex(false)).unknown00;
  }
  u16 image = unknown48->getContents(unknown48->getIndex(false)).unknown00;
  return Bdat::getVal(unknown33c8, "menuMapImage", image).valueU16;
}

bool GfMenuObjZoneMap::seqTexDelete() {
  ui::UIObjectAcc main(ui::UIObjectAcc(unknown18).searchChild("LAY_main"));
  if (unknown70) {
    GfMenuObjUtil::setChildDisp(main.unknown10, unknown74.c_str(), false);
    unknown98->clear();
    closeIconTable(main, unknown0a0);
    ui::UIStreamManager::get()->deleteImage(unknown74, main.searchChild("LAY_floor"));
    GfFieldGimmick::get()->unknownf4c0.dispose();
    mm::mtl::safeRelease(unknown38);
    unknown70 = false;
  }
  ui::UIObjectAcc(main.searchChild("LAY_floor")).setDisp(false);
  GfMenuObjUtil::setChildDisp(main.unknown10, "IMG_cursor", false);
  GfMenuObjUtil::setChildDisp(main.unknown10, "IMG_cursorline_w", false);
  GfMenuObjUtil::setChildDisp(main.unknown10, "IMG_cursorline_h", false);
  return true;
}

bool GfMenuObjZoneMap::seqTexDeleteWait() { return true; }

bool GfMenuObjZoneMap::seqTexLoadWait() {
  ui::UIObjectAcc main(ui::UIObjectAcc(unknown18).searchChild("LAY_main"));
  ui::UIObjectAcc floor(main.searchChild("LAY_floor"));
  return !floor.isStreaming();
}

void GfMenuObjZoneMap::getFloorAABB(u32 map, u32 floor, mm::Aabb &aabb, mm::Pnt<s16> &center) {
  int index = GfMenuMapInfo::getMapInfoIndex(GfDataMap::getMapResourceNameByMapID(map));
  if (index != -1) {
    GfMenuMapInfo::MapAreaInfo area;
    if (GfMenuMapInfo::getMapAreaFromName(index, Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MAP_INFO), "level_name", floor).valueString, area)) {
      mm::Vec3 min;
      min.x = area.unknown20;
      min.y = area.unknown24;
      min.z = area.unknown28;
      mm::Vec3 max;
      max.x = area.unknown2c;
      max.y = area.unknown30;
      max.z = area.unknown34;
      aabb.set(min, max);
      center.x = static_cast<s16>((min.x + max.x) * 0.5f);
      center.y = static_cast<s16>((min.z + max.z) * 0.5f);
    }
  }
}

void GfMenuObjZoneMap::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(handle, acc.searchChild("LAY_zonemap"), 0, 0);
    setupMain(acc);
    setFadeIn(handle);
    GfMenuObject::enableInput(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(handle, acc.searchChild("LAY_zonemap"), 0, 0);
      acc.setDisp(false);
      acc.setTerm();
    }
    break;
  case 8:
    if (event.unknown0c == 9) {
      unknown20->unknown3100++;
      if (unknown20->unknown3100 > 8) {
        unknown20->unknown3100 = 0;
      }
      setDispIconNode(acc, unknown20->unknown3100);
    } else if (event.unknown0c == 10) {
      unknown158(acc.searchChild("LAY_helpmenu"), GfMenuTypes::unknown003_260, 0, 0.0f);
    }
    break;
  case 0x21:
    acc.setDisp(true);
    break;
  case 0x22:
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjZoneMap::HelpListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupHelp(acc);
    unknown20->unknown3125 = false;
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_260:
    if (!unknown20->unknown3125) {
      int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
      GfMenuObject::hookCtrlEvent(handle, ctrl);
      unknown20->unknown3125 = true;
    } else {
      int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
      GfMenuObject::hookCtrlEvent(handle, ctrl);
      unknown20->unknown3125 = false;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjZoneMap::MapSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMapSelect(acc, unknown20->unknown28);
    GfMenuObject::setupInputSelection(handle, 0, unknown20->unknown28->getSize());
    GfMenuObject::enableInput(handle);
    return;
  case 6: {
    u32 index = event.unknown08;
    if (unknown20->unknown28->getSize() != 0) {
      unknown20->unknown28->setIndex(index);
      u32 map = unknown20->unknown28->getContents(index).unknown00;
      refreshMapSelect(acc, unknown20->unknown28, unknown20->unknown30, map);
      return;
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      if (unknown20->unknown28->getSize() != 0) {
        u8 *bdat = unknown20->unknown33c8;
        u32 top = Bdat::getIdTop(bdat);
        u32 count = Bdat::getIdCount(bdat);
        unknown20->unknown48->clear();
        for (u32 i = 0; i < count; i++) {
          Bdat::uVal group = Bdat::getVal(bdat, "menuGroup", top + i);
          if (Bdat::getVal(bdat, "MAPJUMPID", top + i).valueU16 != 0) {
            if (group.valueU16 == unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00) {
              MenuZoneMapInfo info;
              info.unknown00 = top + i;
              info.unknown04 = Bdat::getVal(bdat, "MSGID", top + i).valueU16;
              unknown20->unknown48->addContents(info);
            }
          }
        }
        if (unknown20->unknown58.size() != 0) {
          unknown20->unknown58.destroy();
          unknown20->unknown58.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
        }
        if (unknown20->unknown48->getSize() != 0) {
          unknown20->unknown58.reserve(unknown20->unknown48->getSize());
          unknown20->unknown58.fill(MapJumpInfo());
        }
        unknown164(owner.searchChild("LAY_zonemap"), GfMenuTypes::unknown003_258);
        unknown163(owner.searchChild("LAY_point_sellect"), GfMenuTypes::unknown003_258, 0);
        unknown163(handle, GfMenuTypes::unknown003_259, 0);
      }
    } else if (event.unknown0c == 2) {
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      GfMenuObject::disableInput(owner.searchChild("LAY_zonemap"));
      GfMenuObject::disableInput(owner.searchChild("LAY_point_sellect"));
      GfMenuObject::disableInput(owner.searchChild("LAY_helpmenu"));
      GfMenuObject::disableInput(handle);
    }
    return;
  case GfMenuTypes::unknown003_258:
    acc.setDisp(true);
    GfMenuObject::enableInput(handle);
    break;
  case GfMenuTypes::unknown003_259:
    acc.setDisp(false);
    GfMenuObject::disableInput(handle);
    break;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjZoneMap>(const mm::mtl::Delegate<bool()> *);
