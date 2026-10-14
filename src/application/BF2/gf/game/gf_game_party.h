#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameParty {
public:
  static u32 getPartyId(u32 objectType, u32 id);
  static GF_OBJ_HANDLE *getHandleDriver(u32 partyId);
  static GF_OBJ_HANDLE *getHandleBlade(u32 member, int slot);
  static bool isPartyMemberInGameObj();
};

class GfPartySelect {
public:
  enum LIST_TYPE {
    LIST_TYPE_PARTY,
    LIST_TYPE_RESERVER,
    LIST_TYPE_PARTY_AND_RESERVER,
  };

  static bool getDriverList(mm::mtl::FixedVector<u16, 16> &drivers, LIST_TYPE listType, u32 option);
};

} // namespace gf
