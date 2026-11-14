#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct RQ_SETUP_PARTY;

// Layout from GfGameUnit::createParty (0x7100347b9c) and SCOM_CREATE_PARTY_OBJ::exec.
struct PartyLeaderInfo {
  f32 unknown00;      // Inferred role: value copied into GfInitParamDriver::unknown1a8 of the leader; original member name unknown.
  bool unknown04;     // Inferred role: the position and the rotation are set; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: leader position; original member name unknown.
  f32 unknown20;      // Inferred role: leader rotation around y; original member name unknown.
};

static_assert(offsetof(PartyLeaderInfo, unknown04) == 0x04, "");
static_assert(offsetof(PartyLeaderInfo, unknown10) == 0x10, "");
static_assert(offsetof(PartyLeaderInfo, unknown20) == 0x20, "");

class GfGameUnit {
public:
  static void createParty(PartyLeaderInfo &info);
  static void destroyParty(const RQ_SETUP_PARTY &info, mm::mtl::FixedVector<GF_OBJ_HANDLE *, 32> *handles);
};

} // namespace gf
