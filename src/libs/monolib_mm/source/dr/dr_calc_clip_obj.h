#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_man.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrCalcViewWork;
class DrMan;

struct MdsClipListTreeData {
  f32 unknown00[3]; // Inferred role: maximum of the bounding box; original member name unknown.
  f32 unknown0c[3]; // Inferred role: minimum of the bounding box; original member name unknown.
  u32 unknown18;    // Inferred role: offset of the child node indices; original member name unknown.
  u32 unknown1c;    // Inferred role: offset of the clip data indices; original member name unknown.
  u16 unknown20;    // Inferred role: child node count; original member name unknown.
  u16 unknown22;    // Inferred role: clip data count; original member name unknown.
};

static_assert(sizeof(MdsClipListTreeData) == 0x24, "");
static_assert(offsetof(MdsClipListTreeData, unknown18) == 0x18, "");
static_assert(offsetof(MdsClipListTreeData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsClipListTreeData, unknown20) == 0x20, "");
static_assert(offsetof(MdsClipListTreeData, unknown22) == 0x22, "");

class DrCalcClipObj : public DrCalcClipMan::unknown009<DrCalcClipObj> {
public:
  // Inferred role: clip data header of the clip data file; original type name unknown.
  struct unknown005 {
    u32 unknown00; // Inferred role: offset of the clip data; original member name unknown.
    u16 unknown04; // Inferred role: clip flag index; original member name unknown.
    s16 unknown06; // Inferred role: clip data type; original member name unknown.
  };

  // Inferred role: clip flag data; original type name unknown.
  struct unknown006 {
    f32 unknown00; // Inferred role: minimum radius; original member name unknown.
    u16 unknown04; // Inferred role: state flags; original member name unknown.
    s16 unknown06; // Inferred role: priority; original member name unknown.
  };

  // Inferred role: clip data group; original type name unknown.
  struct unknown007 {
    u16 unknown00; // Inferred role: unknown; original member name unknown.
    u16 unknown02; // Inferred role: global index; original member name unknown.
  };

  // Inferred role: header of the clip data file; original type name unknown.
  struct unknown008 {
    u8 _00[0x0c];
    u32 unknown0c; // Inferred role: offset of the clip data headers; original member name unknown.
    u8 _10[0x3c - 0x10];
    u32 unknown3c; // Inferred role: offset of the clip tree; original member name unknown.
    u32 unknown40; // Inferred role: unknown; original member name unknown.
    u8 _44[0x48 - 0x44];
    u32 unknown48; // Inferred role: offset of the clip data groups; original member name unknown.
    s32 unknown4c; // Inferred role: clip flag data count; original member name unknown.
    u32 unknown50; // Inferred role: offset of the clip flag data; original member name unknown.
    u8 _54[0x58 - 0x54];
    u32 unknown58; // Inferred role: offset of the clip tree of the flagged clip data; original member name unknown.
    u8 _5c[0x60 - 0x5c];
    u32 unknown60; // Inferred role: offset of the clip tree of the cleared clip data; original member name unknown.
  };

  DrCalcClipObj(const void *data, DrMan *man);
  ~DrCalcClipObj();
  void setupClip(const u8 *data, DrMan *man);
  void update(DrCalcViewWork *viewWork, u32 *flags);
  void release();
  void seachTree(const MdsClipListTreeData *node, const mm::Vec3 &position);
  void seachCheckTree(const MdsClipListTreeData *node, const mm::Vec3 &position, f32 radius);
  void seachOffTree(const MdsClipListTreeData *node, const mm::Vec3 &position, f32 radius);
  bool clipcoli_sphere(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_notrot_box(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_cylinder(const u8 *data, const mm::Vec3 &pos);
  bool clipcoli_box(const u8 *data, const mm::Vec3 &pos);

  bool testObjectClip(const mm::Vec3 &position, f32 radius, u32 *flags);

  static bool (DrCalcClipObj::*s_pColiCheck[5])(const u8 *data, const mm::Vec3 &pos);

  const unknown008 *unknown10;          // Inferred role: clip data file; original member name unknown.
  const unknown005 *unknown18;          // Inferred role: clip data headers; original member name unknown.
  const MdsClipListTreeData *unknown20; // Inferred role: clip tree; original member name unknown.
  const unknown006 *unknown28;          // Inferred role: clip flag data; original member name unknown.
  const unknown007 *unknown30;          // Inferred role: clip data groups; original member name unknown.
  s32 unknown38;                        // Inferred role: clip flag count; original member name unknown.
  u32 unknown3c;                        // Inferred role: state flags; original member name unknown.
  s16 unknown40;                        // Inferred role: size of the flag table; original member name unknown.
  s16 unknown42;                        // Inferred role: priority of the flagged clip data; original member name unknown.
  s16 unknown44;                        // Inferred role: flagged clip data count; original member name unknown.
  u16 unknown46[8];                     // Inferred role: flagged clip data indices; original member name unknown.
  u32 *unknown58;                       // Inferred role: flag table; original member name unknown.
  u32 *unknown60;                       // Inferred role: visibility flags; original member name unknown.
};

static_assert(offsetof(DrCalcClipObj, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcClipObj, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcClipObj, unknown18) == 0x18, "");
static_assert(offsetof(DrCalcClipObj, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcClipObj, unknown28) == 0x28, "");
static_assert(offsetof(DrCalcClipObj, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcClipObj, unknown38) == 0x38, "");
static_assert(offsetof(DrCalcClipObj, unknown3c) == 0x3c, "");
static_assert(offsetof(DrCalcClipObj, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcClipObj, unknown42) == 0x42, "");
static_assert(offsetof(DrCalcClipObj, unknown44) == 0x44, "");
static_assert(offsetof(DrCalcClipObj, unknown46) == 0x46, "");
static_assert(offsetof(DrCalcClipObj, unknown58) == 0x58, "");
static_assert(offsetof(DrCalcClipObj, unknown60) == 0x60, "");

} // namespace ml
