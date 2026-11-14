#include "gf/menu/tag/gf_menu_tag_link.h"

#include <stdlib.h>
#include <string.h>

#include "bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/map.h"

namespace gf {

const char *GfMenuTagLink::getTagName() { return "ML:link"; }

const char *GfMenuTagLink::convBegin(const ParamList &params, u16 id) {
  const char *kind = nullptr;
  u32 name = 0;
  for (const mm::mtl::MapPair<const char *, const char *> *it = params.begin(); it != params.end(); ++it) {
    if (strcmp(it->first, "kind") == 0) {
      kind = it->second;
    } else if (strcmp(it->first, "id") == 0) {
      name = atoi(it->second);
    }
  }

  if (name != 0 && kind != nullptr) {
    if (strcmp(kind, "ene") == 0) {
      u8 *bdat = Bdat::getFP("CHR_EnArrange");
      int top = Bdat::getIdTop(bdat);
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        u32 row = top + i;
        if ((Bdat::getVal(bdat, "Name", row).valueU32 & 0xffff) == name) {
          if (row != 0) {
            GfMenuReference::addEnemyLink(row);
          }
          return nullptr;
        }
      }
    } else if (strcmp(kind, "colle") == 0) {
      u8 *bdat = Bdat::getFP("ITM_CollectionList");
      int top = Bdat::getIdTop(bdat);
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        int row = top + i;
        if ((Bdat::getVal(bdat, "Name", row).valueU32 & 0xffff) == name) {
          if (row != 0) {
            MenuItemInfo info;
            info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_7;
            info.unknown04 = row;
            GfMenuReference::addItemLink(info);
          }
          return nullptr;
        }
      }
    }
  }
  return nullptr;
}

} // namespace gf
