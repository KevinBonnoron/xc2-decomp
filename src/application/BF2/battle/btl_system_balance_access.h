#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace btl {

class BtlSystemBalanceAccess : public mm::mtl::PtrSingleton<BtlSystemBalanceAccess> {
public:
  BtlSystemBalanceAccess();
  ~BtlSystemBalanceAccess();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  bool IsOneBoundEnemy(u32 enemy) const;
  int IsSpSizeEnemy(u32 enemy) const;
  bool IsSpKizunaLineEnemy(u32 enemy) const;
  bool IsSpForceLandEnemy(u32 enemy) const;
  bool IsSpBenkeiWeapondEnemy(u32 enemy) const;

  u8 _08[0x10 - 0x08];
  f32 unknown10; // Inferred role: resistant attribute damage rate; original member name unknown.
  u8 _14[0x20 - 0x14];
  f32 unknown20; // Inferred role: critical damage rate; original member name unknown.
  f32 unknown24; // Role and original member name unknown.
  u8 _28[0x34 - 0x28];
  u8 unknown34; // Inferred role: elemental value max; original member name unknown.
  u8 _35[0x40 - 0x35];
  u8 unknown40;  // Inferred role: resistant attribute max HP; original member name unknown.
  u8 unknown41;  // Inferred role: ball scale min; original member name unknown.
  u16 unknown42; // Inferred role: ball scale max; original member name unknown.
  u8 _44[0x68 - 0x44];
  u8 unknown68; // Inferred role: chain attack seconds; original member name unknown.
  u8 _69[0x76 - 0x69];
  u16 unknown76; // Inferred role: chain attack bonus rate; original member name unknown.
  u8 _78[0xa6 - 0x78];
  u16 unknowna6; // Inferred role: blow land height rate; original member name unknown.
  u8 _a8[0xaa - 0xa8];
  u16 unknownaa; // Role and original member name unknown.
  u8 _ac[0xaf - 0xac];
  u8 unknownaf; // Inferred role: blade timer 2; original member name unknown.
  u8 unknownb0; // Inferred role: blade timer 3; original member name unknown.
  u8 _b1[0xb6 - 0xb1];
  u16 unknownb6[2];  // Inferred role: one bound enemy ids; original member name unknown.
  u16 unknownba[1];  // Inferred role: SP size enemy ids; original member name unknown.
  u16 unknownbc[2];  // Inferred role: SP kizuna line enemy ids; original member name unknown.
  u16 unknownc0[2];  // Inferred role: SP force land enemy ids; original member name unknown.
  u16 unknownc4[1];  // Inferred role: SP benkei weapon enemy ids; original member name unknown.
  u16 unknownc6[11]; // Inferred role: system message text ids; original member name unknown.
  f32 unknowndc;     // Inferred role: dying HP rate; original member name unknown.
  u8 _e0[0xea - 0xe0];
  u8 unknownea; // Role and original member name unknown.
  u8 _eb[0xf0 - 0xeb];
};

static_assert(offsetof(BtlSystemBalanceAccess, unknown20) == 0x20, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknown24) == 0x24, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknown40) == 0x40, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknown68) == 0x68, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknown76) == 0x76, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknowna6) == 0xa6, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownaa) == 0xaa, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownaf) == 0xaf, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownb0) == 0xb0, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownb6) == 0xb6, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownba) == 0xba, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownbc) == 0xbc, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownc0) == 0xc0, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownc4) == 0xc4, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownc6) == 0xc6, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknowndc) == 0xdc, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownea) == 0xea, "");
static_assert(sizeof(BtlSystemBalanceAccess) == 0xf0, "");

} // namespace btl
