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
  u8 _14[0x34 - 0x14];
  u8 unknown34; // Inferred role: elemental value max; original member name unknown.
  u8 _35[0x40 - 0x35];
  u8 unknown40;  // Inferred role: resistant attribute max HP; original member name unknown.
  u8 unknown41;  // Inferred role: ball scale min; original member name unknown.
  u16 unknown42; // Inferred role: ball scale max; original member name unknown.
  u8 _44[0xb6 - 0x44];
  u16 unknownb6[2]; // Inferred role: one bound enemy ids; original member name unknown.
  u16 unknownba[1]; // Inferred role: SP size enemy ids; original member name unknown.
  u16 unknownbc[2]; // Inferred role: SP kizuna line enemy ids; original member name unknown.
  u16 unknownc0[2]; // Inferred role: SP force land enemy ids; original member name unknown.
  u16 unknownc4[1]; // Inferred role: SP benkei weapon enemy ids; original member name unknown.
  u8 _c6[0xdc - 0xc6];
  f32 unknowndc; // Inferred role: dying HP rate; original member name unknown.
  u8 _e0[0xf0 - 0xe0];
};

static_assert(offsetof(BtlSystemBalanceAccess, unknown40) == 0x40, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownb6) == 0xb6, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownba) == 0xba, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownbc) == 0xbc, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownc0) == 0xc0, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknownc4) == 0xc4, "");
static_assert(offsetof(BtlSystemBalanceAccess, unknowndc) == 0xdc, "");
static_assert(sizeof(BtlSystemBalanceAccess) == 0xf0, "");

} // namespace btl
