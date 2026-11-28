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
  // Inferred role: parameter groups present in the post data; original names unknown.
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: inside.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: cloud plane colors.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: color filter with a separate far texture.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: cloud sky colors.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: cloud model colors.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: cloud light colors.
  };

  u32 unknown00; // Inferred role: post parameter index; original member name unknown.
  u32 unknown04; // Inferred role: weather mask; original member name unknown.
  u32 unknown08; // Inferred role: parameter group flags; original member name unknown.
  u16 unknown0c; // Inferred role: light num; original member name unknown.
  u8 _0e[0x10 - 0x0e];
  u16 unknown10; // Inferred role: start time in minutes; original member name unknown.
  u16 unknown12; // Inferred role: duration in minutes; original member name unknown.
  u8 _14[0x1e - 0x14];
  u16 unknown1e; // Inferred role: color filter texture id; original member name unknown.
  u8 _20[0x24 - 0x20];
  u16 unknown24; // Inferred role: color filter far texture id; original member name unknown.
  u16 unknown26; // Inferred role: wind id; original member name unknown.
  u8 _28[0x2c - 0x28];
  u16 unknown2c; // Inferred role: cloud parameter index; original member name unknown.
  u8 _2e[0x30 - 0x2e];
  u16 unknown30; // Inferred role: rain drop fade frames, the weather frame of the post parm when 0; original member name unknown.
  u8 _32[0x34 - 0x32];
};

static_assert(offsetof(EnvColiPostData, unknown04) == 0x04, "");
static_assert(offsetof(EnvColiPostData, unknown08) == 0x08, "");
static_assert(offsetof(EnvColiPostData, unknown0c) == 0x0c, "");
static_assert(offsetof(EnvColiPostData, unknown10) == 0x10, "");
static_assert(offsetof(EnvColiPostData, unknown12) == 0x12, "");
static_assert(offsetof(EnvColiPostData, unknown1e) == 0x1e, "");
static_assert(offsetof(EnvColiPostData, unknown24) == 0x24, "");
static_assert(offsetof(EnvColiPostData, unknown26) == 0x26, "");
static_assert(offsetof(EnvColiPostData, unknown2c) == 0x2c, "");
static_assert(offsetof(EnvColiPostData, unknown30) == 0x30, "");
static_assert(sizeof(EnvColiPostData) == 0x34, "");

// Inferred role: three floats of a post parameter (vector or color); original type name unknown.
struct unknown300 {
  f32 unknown00[3]; // Inferred role: components; original member name unknown.
};

// Inferred role: five floats of a post parameter group; original type name unknown.
struct unknown301 {
  f32 unknown00[5]; // Inferred role: values; original member name unknown.
};

// Inferred role: twelve floats of a post parameter group; original type name unknown.
struct unknown302 {
  f32 unknown00[12]; // Inferred role: values; original member name unknown.
};

// Inferred role: two floats of a post parameter; original type name unknown.
struct unknown303 {
  f32 unknown00[2]; // Inferred role: values; original member name unknown.
};

static_assert(sizeof(unknown300) == 0x0c, "");
static_assert(sizeof(unknown301) == 0x14, "");
static_assert(sizeof(unknown302) == 0x30, "");
static_assert(sizeof(unknown303) == 0x08, "");

template <int Version> struct EnvColiPostParameterVer;

// Layouts of the post parameter records of the environment collision resource. Evidence: the three convertEnvColiPostParameterVer functions copy the words, 12, 20 and 48 byte groups at
// these offsets (0x71007d1cd8, 0x71007d20d8, 0x71007d2408); the versions 10003 and 10004 are only known through them. The members up to 0x1f0 of 10006 are the values calcParams blends into the
// DrPixlPostParm (0x71007d2790), the three u32 and s32 members are converted through float there.
template <> struct EnvColiPostParameterVer<10003> {
  f32 unknown00;            // Inferred role: tone max; original member name unknown.
  f32 unknown04;            // Inferred role: tone min; original member name unknown.
  f32 unknown08;            // Inferred role: tone ratio; original member name unknown.
  f32 unknown0c;            // Inferred role: tone ratio last; original member name unknown.
  f32 unknown10;            // Inferred role: tone blm max; original member name unknown.
  f32 unknown14;            // Inferred role: tone blm min; original member name unknown.
  f32 unknown18;            // Inferred role: tone blm ratio; original member name unknown.
  f32 unknown1c;            // Inferred role: tone blm ratio last; original member name unknown.
  f32 unknown20;            // Inferred role: tone ave min rate; original member name unknown.
  f32 unknown24;            // Inferred role: tone ave max rate; original member name unknown.
  f32 unknown28;            // Inferred role: tone map parameter written with the tone ave max rate by resetToneMapParams; original member name unknown.
  f32 unknown2c[5];         // Inferred role: border blm parameters; original member name unknown.
  unknown301 unknown40[5];  // Inferred role: blm parameter groups; original member name unknown.
  f32 unknowna4;            // Inferred role: bloom parameter, DrPixlPostParm::unknownc0[0]; original member name unknown.
  f32 unknowna8[2];         // Inferred role: parameters dropped by version 10004; original member name unknown.
  u32 unknownb0;            // Inferred role: bloom parameter converted through float, DrPixlPostParm::unknownc0[1]; original member name unknown.
  f32 unknownb4[2];         // Inferred role: blm lens sub and mul; original member name unknown.
  s32 unknownbc;            // Inferred role: blm lens max, converted through float; original member name unknown.
  f32 unknownc0[6];         // Inferred role: blm lens rot, weight, decay, strength, parm max and uv decay; original member name unknown.
  f32 unknownd8[3];         // Inferred role: god ray weight, decay and strength; original member name unknown.
  f32 unknowne4[6];         // Inferred role: tssao parameters; original member name unknown.
  f32 unknownfc[8];         // Inferred role: parameters dropped by version 10005; original member name unknown.
  f32 unknown11c[6];        // Inferred role: dof parameters; original member name unknown.
  s32 unknown134[2];        // Inferred role: dof pixl lv and focus num; original member name unknown.
  f32 unknown13c[2];        // Inferred role: dof focus ratio and focus min; original member name unknown.
  unknown300 unknown144[2]; // Inferred role: vectors; original member name unknown.
  f32 unknown15c;           // Inferred role: shadow parameter; original member name unknown.
  unknown300 unknown160[3]; // Inferred role: vectors; original member name unknown.
};

template <> struct EnvColiPostParameterVer<10004> {
  f32 unknown00;            // Inferred role: tone max; original member name unknown.
  f32 unknown04;            // Inferred role: tone min; original member name unknown.
  f32 unknown08;            // Inferred role: tone ratio; original member name unknown.
  f32 unknown0c;            // Inferred role: tone ratio last; original member name unknown.
  f32 unknown10;            // Inferred role: tone blm max; original member name unknown.
  f32 unknown14;            // Inferred role: tone blm min; original member name unknown.
  f32 unknown18;            // Inferred role: tone blm ratio; original member name unknown.
  f32 unknown1c;            // Inferred role: tone blm ratio last; original member name unknown.
  f32 unknown20;            // Inferred role: tone ave min rate; original member name unknown.
  f32 unknown24;            // Inferred role: tone ave max rate; original member name unknown.
  f32 unknown28;            // Inferred role: tone map parameter written with the tone ave max rate by resetToneMapParams; original member name unknown.
  f32 unknown2c[5];         // Inferred role: border blm parameters; original member name unknown.
  unknown301 unknown40[5];  // Inferred role: blm parameter groups; original member name unknown.
  f32 unknowna4;            // Inferred role: bloom parameter, DrPixlPostParm::unknownc0[0]; original member name unknown.
  u32 unknowna8;            // Inferred role: bloom parameter converted through float, DrPixlPostParm::unknownc0[1]; original member name unknown.
  f32 unknownac[2];         // Inferred role: blm lens sub and mul; original member name unknown.
  s32 unknownb4;            // Inferred role: blm lens max, converted through float; original member name unknown.
  f32 unknownb8[6];         // Inferred role: blm lens rot, weight, decay, strength, parm max and uv decay; original member name unknown.
  f32 unknownd0[3];         // Inferred role: god ray weight, decay and strength; original member name unknown.
  f32 unknowndc[6];         // Inferred role: tssao parameters; original member name unknown.
  f32 unknownf4[8];         // Inferred role: parameters dropped by version 10005; original member name unknown.
  f32 unknown114[6];        // Inferred role: dof parameters; original member name unknown.
  s32 unknown12c[2];        // Inferred role: dof pixl lv and focus num; original member name unknown.
  f32 unknown134[2];        // Inferred role: dof focus ratio and focus min; original member name unknown.
  unknown300 unknown13c[2]; // Inferred role: vectors; original member name unknown.
  f32 unknown154;           // Inferred role: shadow parameter; original member name unknown.
  unknown300 unknown158[3]; // Inferred role: vectors; original member name unknown.
  f32 unknown17c;           // Inferred role: rain drop parameter; original member name unknown.
  f32 unknown180[4];        // Inferred role: parameters dropped by version 10005; original member name unknown.
  unknown302 unknown190;    // Inferred role: values; original member name unknown.
  unknown300 unknown1c0[5]; // Inferred role: rain drop layer values; original member name unknown.
};

template <> struct EnvColiPostParameterVer<10005> {
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: dof flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: dof hlv flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: dof auto focus flag; original name unknown.
  };

  f32 unknown00;            // Inferred role: tone max; original member name unknown.
  f32 unknown04;            // Inferred role: tone min; original member name unknown.
  f32 unknown08;            // Inferred role: tone ratio; original member name unknown.
  f32 unknown0c;            // Inferred role: tone ratio last; original member name unknown.
  f32 unknown10;            // Inferred role: tone blm max; original member name unknown.
  f32 unknown14;            // Inferred role: tone blm min; original member name unknown.
  f32 unknown18;            // Inferred role: tone blm ratio; original member name unknown.
  f32 unknown1c;            // Inferred role: tone blm ratio last; original member name unknown.
  f32 unknown20;            // Inferred role: tone ave min rate; original member name unknown.
  f32 unknown24;            // Inferred role: tone ave max rate; original member name unknown.
  f32 unknown28;            // Inferred role: tone map parameter written with the tone ave max rate by resetToneMapParams; original member name unknown.
  f32 unknown2c[5];         // Inferred role: border blm parameters; original member name unknown.
  unknown301 unknown40[5];  // Inferred role: blm parameter groups; original member name unknown.
  f32 unknowna4;            // Inferred role: bloom parameter, DrPixlPostParm::unknownc0[0]; original member name unknown.
  u32 unknowna8;            // Inferred role: bloom parameter converted through float, DrPixlPostParm::unknownc0[1]; original member name unknown.
  f32 unknownac[2];         // Inferred role: blm lens sub and mul; original member name unknown.
  s32 unknownb4;            // Inferred role: blm lens max, converted through float; original member name unknown.
  f32 unknownb8[6];         // Inferred role: blm lens rot, weight, decay, strength, parm max and uv decay; original member name unknown.
  f32 unknownd0[3];         // Inferred role: god ray weight, decay and strength; original member name unknown.
  f32 unknowndc[6];         // Inferred role: tssao parameters; original member name unknown.
  f32 unknownf4[6];         // Inferred role: dof parameters; original member name unknown.
  s32 unknown10c[2];        // Inferred role: dof pixl lv and focus num; original member name unknown.
  f32 unknown114[2];        // Inferred role: dof focus ratio and focus min; original member name unknown.
  unknown303 unknown11c[2]; // Inferred role: parameters added by version 10005, two pairs; original member name unknown. See convertEnvColiPostParameterVer<10004, 10005>.
  unknown300 unknown12c[2]; // Inferred role: vectors; original member name unknown.
  f32 unknown144;           // Inferred role: shadow parameter; original member name unknown.
  unknown300 unknown148[3]; // Inferred role: vectors; original member name unknown.
  f32 unknown16c[5];        // Inferred role: rain drop parameters; original member name unknown.
  unknown302 unknown180;    // Inferred role: values; original member name unknown.
  unknown300 unknown1b0[5]; // Inferred role: rain drop layer values; original member name unknown.
  u32 unknown1ec;           // Inferred role: flags of the dof parameters; original member name unknown. The game reads and writes the whole word (0x71007d2288, 0x71007d25b8).
};

// The members of 0x00 to 0x28 are the tone map parameters known from resetToneMapParams.
template <> struct EnvColiPostParameterVer<10006> {
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: dof flag (DrPixlPostParm 0x218); original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: dof hlv flag (DrPixlPostParm 0x21a); original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: dof auto focus flag (DrPixlPostParm 0x21c); original name unknown.
  };

  f32 unknown00;            // Inferred role: tone max; original member name unknown.
  f32 unknown04;            // Inferred role: tone min; original member name unknown.
  f32 unknown08;            // Inferred role: tone ratio; original member name unknown.
  f32 unknown0c;            // Inferred role: tone ratio last; original member name unknown.
  f32 unknown10;            // Inferred role: tone blm max; original member name unknown.
  f32 unknown14;            // Inferred role: tone blm min; original member name unknown.
  f32 unknown18;            // Inferred role: tone blm ratio; original member name unknown.
  f32 unknown1c;            // Inferred role: tone blm ratio last; original member name unknown.
  f32 unknown20;            // Inferred role: tone ave min rate; original member name unknown.
  f32 unknown24;            // Inferred role: tone ave max rate; original member name unknown.
  f32 unknown28;            // Inferred role: tone map parameter written with the tone ave max rate by resetToneMapParams; original member name unknown.
  f32 unknown2c[5];         // Inferred role: border blm parameters, blended into DrPixlPostParm 0x40 to 0x50; original member name unknown.
  unknown301 unknown40[5];  // Inferred role: blm parameter groups, blended into DrPixlPostParm 0x54 to 0xb8; original member name unknown.
  f32 unknowna4;            // Inferred role: bloom parameter, DrPixlPostParm::unknownc0[0] (0xc0); original member name unknown.
  u32 unknowna8;            // Inferred role: bloom parameter converted through float, DrPixlPostParm::unknownc0[1] (0xc4); original member name unknown.
  f32 unknownac[2];         // Inferred role: blm lens sub and mul, DrPixlPostParm 0xc8; original member name unknown.
  s32 unknownb4;            // Inferred role: blm lens max converted through float, DrPixlPostParm 0xd0; original member name unknown.
  f32 unknownb8[6];         // Inferred role: blm lens rot, weight, decay, strength, parm max and uv decay, DrPixlPostParm 0xd4; original member name unknown.
  f32 unknownd0[3];         // Inferred role: god ray weight, decay and strength, DrPixlPostParm 0xf0; original member name unknown.
  f32 unknowndc[6];         // Inferred role: tssao parameters, DrPixlPostParm 0x178; original member name unknown.
  f32 unknownf4[6];         // Inferred role: dof parameters, DrPixlPostParm 0x220; original member name unknown.
  s32 unknown10c[2];        // Inferred role: dof pixl lv and focus num, DrPixlPostParm 0x238; original member name unknown.
  f32 unknown114[2];        // Inferred role: dof focus ratio and focus min, DrPixlPostParm 0x240; original member name unknown.
  f32 unknown11c[4];        // Inferred role: color filter parameters, DrPixlPostParm 0x27c; original member name unknown.
  unknown300 unknown12c[2]; // Inferred role: vectors not blended by calcParams; original member name unknown.
  f32 unknown144;           // Inferred role: shadow parameter, DrPixlPostParm 0x37c; original member name unknown.
  unknown300 unknown148[3]; // Inferred role: shadow vectors, DrPixlPostParm 0x380; original member name unknown.
  f32 unknown16c[5];        // Inferred role: rain drop parameters, DrPixlPostParm 0x3c4; original member name unknown.
  unknown302 unknown180;    // Inferred role: rain drop values, DrPixlPostParm 0x3dc; original member name unknown.
  unknown300 unknown1b0[5]; // Inferred role: rain drop layer values, DrPixlPostParm 0x40c; original member name unknown.
  f32 unknown1ec;           // Inferred role: rain drop parameter added by version 10006, blended into DrPixlPostParm 0x45c; original member name unknown.
  u32 unknown1f0;           // Inferred role: flags of the dof parameters, DrPixlPostParm 0x218, 0x21a and 0x21c; original member name unknown. The game reads and writes the whole word (0x71007d25b8,
                            // 0x71007d3860).
};

static_assert(offsetof(EnvColiPostParameterVer<10003>, unknown40) == 0x40, "");
static_assert(offsetof(EnvColiPostParameterVer<10003>, unknowna4) == 0xa4, "");
static_assert(offsetof(EnvColiPostParameterVer<10003>, unknownb0) == 0xb0, "");
static_assert(offsetof(EnvColiPostParameterVer<10003>, unknownfc) == 0xfc, "");
static_assert(offsetof(EnvColiPostParameterVer<10003>, unknown11c) == 0x11c, "");
static_assert(offsetof(EnvColiPostParameterVer<10003>, unknown144) == 0x144, "");
static_assert(offsetof(EnvColiPostParameterVer<10003>, unknown160) == 0x160, "");
static_assert(sizeof(EnvColiPostParameterVer<10003>) == 0x184, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknown40) == 0x40, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknowna4) == 0xa4, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknownf4) == 0xf4, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknown114) == 0x114, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknown13c) == 0x13c, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknown17c) == 0x17c, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknown190) == 0x190, "");
static_assert(offsetof(EnvColiPostParameterVer<10004>, unknown1c0) == 0x1c0, "");
static_assert(sizeof(EnvColiPostParameterVer<10004>) == 0x1fc, "");
static_assert(offsetof(EnvColiPostParameterVer<10005>, unknown40) == 0x40, "");
static_assert(offsetof(EnvColiPostParameterVer<10005>, unknownf4) == 0xf4, "");
static_assert(offsetof(EnvColiPostParameterVer<10005>, unknown11c) == 0x11c, "");
static_assert(offsetof(EnvColiPostParameterVer<10005>, unknown12c) == 0x12c, "");
static_assert(offsetof(EnvColiPostParameterVer<10005>, unknown180) == 0x180, "");
static_assert(offsetof(EnvColiPostParameterVer<10005>, unknown1b0) == 0x1b0, "");
static_assert(sizeof(EnvColiPostParameterVer<10005>) == 0x1f0, "");
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
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown2c) == 0x2c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown40) == 0x40, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknowna4) == 0xa4, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknownd0) == 0xd0, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknowndc) == 0xdc, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknownf4) == 0xf4, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown10c) == 0x10c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown11c) == 0x11c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown12c) == 0x12c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown144) == 0x144, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown148) == 0x148, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown16c) == 0x16c, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown180) == 0x180, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown1b0) == 0x1b0, "");
static_assert(offsetof(EnvColiPostParameterVer<10006>, unknown1ec) == 0x1ec, "");
static_assert(sizeof(EnvColiPostParameterVer<10006>) == 0x1f4, "");

template <int From, int To> void convertEnvColiPostParameterVer(const EnvColiPostParameterVer<From> &from, EnvColiPostParameterVer<To> &to);
template <> void convertEnvColiPostParameterVer<10003, 10004>(const EnvColiPostParameterVer<10003> &from, EnvColiPostParameterVer<10004> &to);
template <> void convertEnvColiPostParameterVer<10004, 10005>(const EnvColiPostParameterVer<10004> &from, EnvColiPostParameterVer<10005> &to);
template <> void convertEnvColiPostParameterVer<10005, 10006>(const EnvColiPostParameterVer<10005> &from, EnvColiPostParameterVer<10006> &to);

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

  DrEnvColiObj *unknown00;                          // Inferred role: previous object; original member name unknown.
  DrEnvColiObj *unknown08;                          // Inferred role: next object; original member name unknown.
  const u8 *unknown10;                              // Inferred role: env coli data; original member name unknown.
  const unknown005 *unknown18;                      // Inferred role: primitives; original member name unknown.
  const EnvColiListTreeData *m_envColiListTreeData; // Inferred role: collision tree; original member name unknown.
  mm::Vec3 (*unknown28)[3];                         // Inferred role: primitive work (axes or center); original member name unknown.
  DrMan *m_drMan;                                   // Inferred role: dr man; original member name unknown.
  u32 unknown38;                                    // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrEnvColiObj::unknown005, unknown06) == 0x06, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown0c) == 0x0c, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown14) == 0x14, "");
static_assert(offsetof(DrEnvColiObj::unknown005, unknown16) == 0x16, "");
static_assert(sizeof(DrEnvColiObj::unknown005) == 0x20, "");
static_assert(offsetof(DrEnvColiObj, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiObj, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvColiObj, m_envColiListTreeData) == 0x20, "");
static_assert(offsetof(DrEnvColiObj, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvColiObj, m_drMan) == 0x30, "");
static_assert(offsetof(DrEnvColiObj, unknown38) == 0x38, "");

} // namespace ml
