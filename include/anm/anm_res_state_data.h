#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_asm_listener.h"  // IWYU pragma: keep
#include "anm/anm_res_clip_data.h" // IWYU pragma: keep
#include "anm/anm_string_ptr.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

class ResResolver;

enum InterpolateType {
  INTERPOLATE_TYPE_UNKNOWN_0,
  INTERPOLATE_TYPE_UNKNOWN_1,
};
enum InterpolateCurve {
  INTERPOLATE_CURVE_UNKNOWN_0,
  INTERPOLATE_CURVE_UNKNOWN_1,
};

struct TransInfo {
  s32 unknown00; // Inferred role: start time kind (0 offset, 1 current time, 2 random, 3 current time minus the start); original member name unknown.
  f32 unknown04; // Inferred role: start time or its minimum; original member name unknown.
  f32 unknown08; // Inferred role: random range of the start time; original member name unknown.
};

struct InterpolateInfo {
  f32 unknown00;              // Inferred role: interpolate time; original member name unknown.
  InterpolateType unknown04;  // Inferred role: interpolate type; original member name unknown.
  InterpolateCurve unknown08; // Inferred role: interpolate curve; original member name unknown.
};

// Inferred role: res loop count; original type name unknown.
struct unknown102 {
  const char *unknown00; // Inferred role: name of the next state; original member name unknown.
  s32 min;
  u32 range;
  TransInfo unknown10;       // Inferred role: start time of the next state; original member name unknown.
  InterpolateInfo unknown1c; // Inferred role: interpolation to the next state; original member name unknown.
};

static_assert(offsetof(unknown102, unknown10) == 0x10, "");
static_assert(offsetof(unknown102, unknown1c) == 0x1c, "");
static_assert(sizeof(unknown102) == 0x28, "");

// Inferred role: state type; original type name unknown.
enum unknown103 {
  unknown103_0, // Inferred role: simple; original name unknown.
  unknown103_1, // Inferred role: frozen; original name unknown.
  unknown103_2, // Inferred role: complex; original name unknown.
};

// Inferred element of the target list of a command of kind 1 (stride 0x38); original name unknown.
struct unknown005 {
  u8 _00[0x10];
  StringPtr unknown10;       // Inferred role: target state name; original member name unknown.
  f32 unknown18;             // Inferred role: minimum local time of the current state, negative if unbounded; original member name unknown.
  f32 unknown1c;             // Inferred role: maximum local time of the current state, negative if unbounded; original member name unknown.
  TransInfo unknown20;       // Inferred role: start time of the target; original member name unknown.
  InterpolateInfo unknown2c; // Inferred role: interpolation to the target; original member name unknown.
};

struct SelectNode {
  s32 unknown00; // Inferred role: variable value selecting the node; original member name unknown.
  u8 _04[0x8 - 0x4];
  StringPtr unknown08;       // Inferred role: target state name; original member name unknown.
  f32 unknown10;             // Inferred role: minimum local time of the current state, negative if unbounded; original member name unknown.
  f32 unknown14;             // Inferred role: maximum local time of the current state, negative if unbounded; original member name unknown.
  TransInfo unknown18;       // Inferred role: start time of the target; original member name unknown.
  InterpolateInfo unknown24; // Inferred role: interpolation to the target; original member name unknown.
};

struct ResCmd {
  const char *unknown00; // Inferred role: command name; original member name unknown.
  s32 unknown08;         // Inferred role: kind (0 single target, 1 and 2 target lists); original member name unknown.
};

// Inferred state command of kind 0; original name unknown.
struct unknown008 : ResCmd {
  StringPtr unknown10;       // Inferred role: target state name; original member name unknown.
  f32 unknown18;             // Inferred role: minimum local time of the current state, negative if unbounded; original member name unknown.
  f32 unknown1c;             // Inferred role: maximum local time of the current state, negative if unbounded; original member name unknown.
  TransInfo unknown20;       // Inferred role: start time of the target; original member name unknown.
  InterpolateInfo unknown2c; // Inferred role: interpolation to the target; original member name unknown.
};

// Inferred state command of kind 1; original name unknown.
struct unknown009 : ResCmd {
  Array<unknown005> unknown10; // Inferred role: targets; original member name unknown.
};

// Inferred state command of kind 2; original name unknown.
struct unknown00a : ResCmd {
  u32 unknown10;               // Inferred role: index of the selecting variable; original member name unknown.
  Array<SelectNode> unknown18; // Inferred role: targets; original member name unknown.
};

// Inferred common head of the resources of the complex states; the kind selects the real resource type; original name unknown.
struct unknown00c {
  s32 unknown00; // Inferred role: kind (0 lerp, 2 speed lerp, 3 add, 4 lerp add); original member name unknown.
};

struct ResState {
  unknown103 type;
  u8 _04[0x8 - 0x4];
  const char *name;
  u64 attribute;
  u32 unknown18; // Inferred role: layer; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  Array<ResCmd *> unknown20; // Inferred role: commands; original member name unknown.
  const unknown102 *loopCount;
  u8 _38[0x68 - 0x38];
  const unknown00c *unknown68; // Inferred role: p resource of a complex state; original member name unknown.
};

static_assert(offsetof(ResState, unknown18) == 0x18, "");
static_assert(offsetof(ResState, unknown20) == 0x20, "");
static_assert(offsetof(ResState, loopCount) == 0x30, "");
static_assert(offsetof(ResState, unknown68) == 0x68, "");
static_assert(sizeof(unknown005) == 0x38, "");
static_assert(sizeof(SelectNode) == 0x30, "");
static_assert(sizeof(ResCmd) == 0x10, "");
static_assert(sizeof(TransInfo) == 0xc, "");
static_assert(sizeof(InterpolateInfo) == 0xc, "");
static_assert(offsetof(unknown008, unknown18) == 0x18, "");
static_assert(offsetof(unknown008, unknown2c) == 0x2c, "");
static_assert(offsetof(unknown005, unknown2c) == 0x2c, "");
static_assert(offsetof(SelectNode, unknown24) == 0x24, "");
static_assert(sizeof(unknown008) == 0x38, "");
static_assert(offsetof(unknown009, unknown10) == 0x10, "");
static_assert(offsetof(unknown00a, unknown18) == 0x18, "");

class ResStateData {
public:
  ResStateData();
  void cleanup();
  void restore(const ResResolver &resolver);
  void sortAnnotation(u32 type);
  void clearFrameAnnotation(u32 type);

  // __LINE__ must be 47 as in the original header: it is the line argument of the assert.
#line 46
  void setAttribute(u32 category, u64 attribute) {
    MM_ASSERT(category > 0);
    unknown30[category - 1] = attribute;
  }
  // Inferred helper: clears the enter annotations of a type; original name unknown.
  void unknown001(u32 type) { unknown50[type].clear(); }
  // Inferred helper: clears the leave annotations of a type; original name unknown.
  void unknown002(u32 type) { unknown118[type].clear(); }
  void setFrameAnnotation(u32 type, u32 clip, f32 frame, const AsmAnnotetion &annotation);
  const ResState *unknown00;                                         // Inferred role: p res state; original member name unknown.
  mm::mtl::Vector<ResClipData> unknown08;                            // Inferred role: clips; original member name unknown.
  u64 unknown30[4];                                                  // Inferred role: attributes; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> unknown50;  // Inferred role: enter annotations; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> unknown118; // Inferred role: leave annotations; original member name unknown.
};

static_assert(offsetof(ResStateData, unknown08) == 0x8, "");
static_assert(offsetof(ResStateData, unknown50) == 0x50, "");
static_assert(offsetof(ResStateData, unknown118) == 0x118, "");
static_assert(sizeof(ResStateData) == 0x1e0, "");

} // namespace anm
