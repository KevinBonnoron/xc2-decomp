#include "ui/list/ui_list_info.h" // IWYU pragma: keep

#include "gf/menu/list/gf_menu_arts_list.h"     // IWYU pragma: keep
#include "gf/menu/list/gf_menu_blade_list.h"    // IWYU pragma: keep
#include "gf/menu/list/gf_menu_driver_list.h"   // IWYU pragma: keep
#include "gf/menu/list/gf_menu_enemy_list.h"    // IWYU pragma: keep
#include "gf/menu/list/gf_menu_msg_list.h"      // IWYU pragma: keep
#include "gf/menu/list/gf_menu_zone_map_list.h" // IWYU pragma: keep

namespace ui {

template void UIListInfo<gf::MenuArtsInfo>::addContents(const gf::MenuArtsInfo &);
template void UIListInfo<gf::MenuArtsInfo>::swapContents(u32, u32);
template void UIListInfo<gf::MenuBladeInfo>::addContents(const gf::MenuBladeInfo &);
template void UIListInfo<gf::MenuDriverInfo>::addContents(const gf::MenuDriverInfo &);
template void UIListInfo<gf::MenuDriverInfo>::swapContents(u32, u32);
template void UIListInfo<gf::MenuDriverInfo>::swapContents(u32, UIListInfo<gf::MenuDriverInfo> *, u32);
template void UIListInfo<gf::MenuEnemyInfo>::addContents(const gf::MenuEnemyInfo &);
template void UIListInfo<gf::MenuZoneMapInfo>::addContents(const gf::MenuZoneMapInfo &);
template void UIListInfo<gf::MsgID>::addContents(const gf::MsgID &);

} // namespace ui
