#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrMan;
struct DrEnvColiResult;

struct EnvColiListTreeData {
  f32 unknown00[3]; // Inferred role: upper bound; original member name unknown.
  f32 unknown0c[3]; // Inferred role: lower bound; original member name unknown.
  u32 unknown18;    // Inferred role: child index list offset; original member name unknown.
  u32 unknown1c;    // Inferred role: primitive index list offset; original member name unknown.
  u16 unknown20;    // Inferred role: child num; original member name unknown.
  u16 unknown22;    // Inferred role: primitive num; original member name unknown.
};

static_assert(offsetof(EnvColiListTreeData, unknown0c) == 0x0c, "");
static_assert(offsetof(EnvColiListTreeData, unknown18) == 0x18, "");
static_assert(offsetof(EnvColiListTreeData, unknown22) == 0x22, "");
static_assert(sizeof(EnvColiListTreeData) == 0x24, "");

struct EnvColiPostData {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: weather mask; original member name unknown.
  u8 _08[0x10 - 0x08];
  u16 unknown10; // Inferred role: start time in minutes; original member name unknown.
  u8 _12[0x26 - 0x12];
  u16 unknown26; // Inferred role: wind id; original member name unknown.
  u8 _28[0x34 - 0x28];
};

static_assert(offsetof(EnvColiPostData, unknown10) == 0x10, "");
static_assert(offsetof(EnvColiPostData, unknown26) == 0x26, "");
static_assert(sizeof(EnvColiPostData) == 0x34, "");

template <int Version> struct EnvColiPostParameterVer;

// Only the leading tone map parameters are known (resetToneMapParams); the layout of the rest of the post parameters is not. The size is the 500 byte stride of calcParams.
template <> struct EnvColiPostParameterVer<10006> {
  f32 unknown00; // Inferred role: tone max; original member name unknown.
  f32 unknown04; // Inferred role: tone min; original member name unknown.
  f32 unknown08; // Inferred role: tone ratio; original member name unknown.
  f32 unknown0c; // Inferred role: tone ratio last; original member name unknown.
  f32 unknown10; // Inferred role: tone blm max; original member name unknown.
  f32 unknown14; // Inferred role: tone blm min; original member name unknown.
  f32 unknown18; // Inferred role: tone blm ratio; original member name unknown.
  f32 unknown1c; // Inferred role: tone blm ratio last; original member name unknown.
  f32 unknown20; // Inferred role: tone ave min rate; original member name unknown.
  f32 unknown24; // Inferred role: tone ave max rate; original member name unknown.
  f32 unknown28; // Inferred role: tone map parameter written with the tone ave max rate by resetToneMapParams; original member name unknown.
  u8 _2c[0x1f4 - 0x2c];
};

static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown04) == 0x04, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown08) == 0x08, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown0c) == 0x0c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown10) == 0x10, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown14) == 0x14, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown18) == 0x18, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown1c) == 0x1c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown20) == 0x20, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown24) == 0x24, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown28) == 0x28, "");
static_assert(sizeof(EnvColiPostParameterVer<10006>) == 0x1f4, "");

class DrEnvColiObj {
public:
  // Inferred role: env coli primitive header; original type name unknown.
  struct unknown005 {
    u32 unknown00; // Inferred role: collision data offset; original member name unknown.
    u16 unknown04; // Inferred role: collision type; original member name unknown.
    u16 unknown06; // Inferred role: result flags; original member name unknown.
    s16 unknown08; // Inferred role: priority; original member name unknown.
    s16 unknown0a; // Inferred role: sub priority; original member name unknown.
    u16 unknown0c; // Inferred role: gbl id; original member name unknown.
    s16 unknown0e; // Inferred role: bgm id; original member name unknown.
    u8 unknown10;  // Inferred role: layer id; original member name unknown.
    u8 unknown11;  // Inferred role: reverb id; original member name unknown.
    u8 unknown12;  // Inferred role: cave id; original member name unknown.
    u8 _13[0x14 - 0x13];
    u16 unknown14; // Inferred role: area id; original member name unknown.
    u16 unknown16; // Inferred role: post parameter index; original member name unknown.
    u8 _18[0x20 - 0x18];
  };

  typedef bool (DrEnvColiObj::*COLITEST)(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *work);

  DrEnvColiObj(DrMan *man);
  DrEnvColiObj(DrMan *man, const void *data);
  void setDataAdd(const void *data);
  ~DrEnvColiObj();
  void release();
  void setPause(bool isPause);
  bool isPause() const;
  u32 isDeleteCall() const;
  u32 isDeleteAll() const;
  const u8 *getPostParams() const;
  bool testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius);
  bool testTreeColi(DrEnvColiResult *result, const EnvColiListTreeData *tree, const mm::Vec3 &position, f32 radius);
  bool envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes);
  bool envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center);
  bool envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes);
  bool envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center);
  bool envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center);

  static COLITEST s_pColiTest[5];

  DrEnvColiObj *unknown00;              // Inferred role: previous object; original member name unknown.
  DrEnvColiObj *unknown08;              // Inferred role: next object; original member name unknown.
  const u8 *unknown10;                  // Inferred role: env coli data; original member name unknown.
  const unknown005 *unknown18;          // Inferred role: primitives; original member name unknown.
  const EnvColiListTreeData *unknown20; // Inferred role: collision tree; original member name unknown.
  mm::Vec3 (*unknown28)[3];             // Inferred role: primitive work (axes or center); original member name unknown.
  DrMan *unknown30;                     // Inferred role: dr man; original member name unknown.
  u32 unknown38;                        // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrEnvColiObj::unknown005, unknown06) == 0x06, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown0c) == 0x0c, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown14) == 0x14, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown16) == 0x16, "");
static_assert(sizeof(DrEnvColiObj::unknown005) == 0x20, "");
static_assert(offsetof(DrEnvColiObj, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiObj, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvColiObj, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvColiObj, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvColiObj, unknown30) == 0x30, "");
static_assert(offsetof(DrEnvColiObj, unknown38) == 0x38, "");

} // namespace ml
