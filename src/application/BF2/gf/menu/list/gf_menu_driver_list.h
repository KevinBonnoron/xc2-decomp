#pragma once
#include <stddef.h>

#include "gf/game/gf_game_party.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuDriverInfo {
  u32 unknown00; // Inferred role: driver; original member name unknown.
};

static_assert(sizeof(MenuDriverInfo) == 0x4, "");

class GfMenuDriverList : public ui::UIListInfo<MenuDriverInfo> {
public:
  struct PartySetup {
    SetupParam unknown00;               // Inferred role: param; original member name unknown.
    GfPartySelect::LIST_TYPE unknown14; // Inferred role: list type; original member name unknown.
    bool unknown18;                     // Inferred role: option; original member name unknown.
  };

  GfMenuDriverList();
  ~GfMenuDriverList() override;
  static GfMenuDriverList *create();
  void setupFromParty(const PartySetup &setup);
};

static_assert(offsetof(GfMenuDriverList::PartySetup, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuDriverList::PartySetup, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuDriverList) == 0x68, "");

} // namespace gf
