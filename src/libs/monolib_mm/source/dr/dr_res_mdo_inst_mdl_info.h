#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoInstMdlObj;

// Inferred role: instance model group of the resource; original type name unknown.
struct unknown761 {
  u32 unknown00; // Inferred role: model data offset; original member name unknown.
  u32 unknown04; // Inferred role: model name offset; original member name unknown.
  u32 unknown08; // Inferred role: first model object index; original member name unknown.
  s32 unknown0c; // Inferred role: model object count; original member name unknown.
  u8 _10[0x1c - 0x10];
};

static_assert(offsetof(unknown761, unknown0c) == 0x0c, "");
static_assert(sizeof(unknown761) == 0x1c, "");

// Inferred role: instance model object info of the resource; original type name unknown. Layout from
// DrResMdoInstMdlObj::update (1.0.0: 0x7100875c98), which reads it through DrResMdlInstMdlArg::unknown48: bit 0 of the
// byte at 0x0 is tested (0x7100875c98), and the u32 at 0x4 (0x7100875ca0, 0x7100875cbc) and at 0x8 (0x7100875ce0,
// 0x7100875cfc) are bit indices tested in the bit table at DrMan 0x1d20 (word index >> 5, bit 1 << (index & 0x1f)).
struct unknown762 {
  u8 unknown00;  // Inferred role: flags, bit 0 enables the two bit table tests; original member name unknown.
  u32 unknown04; // Inferred role: index of the first bit tested in the DrMan bit table; original member name unknown.
  u32 unknown08; // Inferred role: index of the second bit tested in the DrMan bit table; original member name unknown.
};

static_assert(offsetof(unknown762, unknown04) == 0x04, "");
static_assert(offsetof(unknown762, unknown08) == 0x08, "");
static_assert(sizeof(unknown762) == 0x0c, "");

struct DrResMdlInstMdlArg {
  const mm::Vec3 *unknown00;   // Inferred role: view pos; original member name unknown.
  const mm::Vec3 *unknown08;   // Inferred role: second view pos, nullptr when there is none; original member name unknown.
  bool unknown10;              // Inferred role: disp; original member name unknown.
  s32 unknown14;               // Inferred role: view num; original member name unknown.
  f32 unknown18;               // Inferred role: frame spd; original member name unknown.
  const char *unknown20;       // Inferred role: resource folder path; original member name unknown.
  const u8 *unknown28;         // Inferred role: resource; original member name unknown.
  const char *unknown30;       // Inferred role: model name; original member name unknown.
  const u8 *unknown38;         // Inferred role: model data; original member name unknown.
  const unknown761 *unknown40; // Inferred role: current group; original member name unknown.
  const unknown762 *unknown48; // Inferred role: current model object info; original member name unknown.
  const mm::Mat44 *unknown50;  // Inferred role: current model object matrix; original member name unknown.
};

static_assert(offsetof(DrResMdlInstMdlArg, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown14) == 0x14, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown50) == 0x50, "");
static_assert(sizeof(DrResMdlInstMdlArg) == 0x58, "");

class DrResMdoInstMdlInfo {
public:
  // Inferred role: instance model resource header; original type name unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: group offset; original member name unknown.
    s32 unknown04; // Inferred role: group count; original member name unknown.
    s32 unknown08; // Inferred role: model object count; original member name unknown.
    u32 unknown0c; // Inferred role: model object matrix offset; original member name unknown.
    u32 unknown10; // Inferred role: model object info offset; original member name unknown.
  };

  DrResMdoInstMdlInfo();
  ~DrResMdoInstMdlInfo();
  void releaseWork();
  void releaseCall();
  void update(DrResMdlInstMdlArg &arg);
  static int calcWorkSize(const u8 *resource);
  static void release(DrResMdoInstMdlInfo *&info);

  s32 unknown00;                  // Inferred role: model object count; original member name unknown.
  DrResMdoInstMdlObj *unknown08;  // Inferred role: model objects; original member name unknown.
  mm::mtl::FixStr<256> unknown10; // Inferred role: resource folder path; original member name unknown.
  const u8 *unknown118;           // Inferred role: resource; original member name unknown.
  u32 unknown120;                 // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrResMdoInstMdlInfo, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown118) == 0x118, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown120) == 0x120, "");
static_assert(sizeof(DrResMdoInstMdlInfo) == 0x128, "");

} // namespace ml
