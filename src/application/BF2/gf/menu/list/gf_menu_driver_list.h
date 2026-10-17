#pragma once
#include <stddef.h>

#include "gf/game/gf_game_party.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuDriverInfo {
  u32 driver;
};

static_assert(sizeof(MenuDriverInfo) == 0x4, "");

class GfMenuDriverList : public ui::UIListInfo<MenuDriverInfo> {
public:
  struct PartySetup {
    SetupParam param;
    GfPartySelect::LIST_TYPE listType;
    bool option;
  };

  GfMenuDriverList();
  ~GfMenuDriverList() override;
  static GfMenuDriverList *create();
  void setupFromParty(const PartySetup &setup);
};

static_assert(offsetof(GfMenuDriverList::PartySetup, listType) == 0x14, "");
static_assert(offsetof(GfMenuDriverList::PartySetup, option) == 0x18, "");
static_assert(sizeof(GfMenuDriverList) == 0x68, "");

} // namespace gf
