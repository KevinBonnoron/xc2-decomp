#pragma once
#include <stddef.h>

#include "dr/dr_mdl_base.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibOneUniformBlock;
class CGLibTextureBuffer;
class CGLibTriUniformBlock;
class CGLibOneUniformArray;
} // namespace grlib

namespace ml {

class DrResMdoMat;
class DrShdMdoExtTblObj;
class DrMan;
class DrMdoSmlShadowObj;
struct MdsMatCharMkTexTbl;
class DrResMdoSampler;
class DrResMdoTexList;
class DrResMdoVertex;
class DrShdMdoDecExtTbl;
class DrShdMdoDecShdObj;
struct DrResMpfSampler;

struct MdsMatTopHeader {
  // Inferred role: material data flag of unknown44; original type name unknown.
  enum Flag {
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: has the display call table; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: has the fur shader table; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: has the avatar map color table; original name unknown.
  };

  u32 unknown00; // Inferred role: offset of the material infos; original member name unknown.
  u8 _04[0x10 - 0x04];
  u32 unknown10; // Inferred role: offset of the base values; original member name unknown.
  s32 unknown14; // Inferred role: base value count; original member name unknown.
  u8 _18[0x20 - 0x18];
  u32 unknown20; // Inferred role: offset of the material callbacks; original member name unknown.
  u8 _24[0x28 - 0x24];
  u32 unknown28; // Inferred role: offset of the techniques; original member name unknown.
  u8 _2c[0x34 - 0x2c];
  u32 unknown34; // Inferred role: offset of the timer table; original member name unknown.
  u8 _38[0x3c - 0x38];
  u32 unknown3c; // Inferred role: offset of the texture infos; original member name unknown.
  u8 _40[0x44 - 0x40];
  u32 unknown44; // Inferred role: flags; original member name unknown.
  u8 _48[0x4c - 0x48];
  u32 unknown4c; // Inferred role: offset of the display call table; original member name unknown.
  u32 unknown50; // Inferred role: offset of the fur shader table; original member name unknown.
  u32 unknown54; // Inferred role: offset of the avatar map color table; original member name unknown.
};

static_assert(offsetof(MdsMatTopHeader, unknown00) == 0x00, "");
static_assert(offsetof(MdsMatTopHeader, unknown10) == 0x10, "");
static_assert(offsetof(MdsMatTopHeader, unknown14) == 0x14, "");
static_assert(offsetof(MdsMatTopHeader, unknown20) == 0x20, "");
static_assert(offsetof(MdsMatTopHeader, unknown28) == 0x28, "");
static_assert(offsetof(MdsMatTopHeader, unknown34) == 0x34, "");
static_assert(offsetof(MdsMatTopHeader, unknown3c) == 0x3c, "");
static_assert(offsetof(MdsMatTopHeader, unknown44) == 0x44, "");
static_assert(offsetof(MdsMatTopHeader, unknown4c) == 0x4c, "");
static_assert(offsetof(MdsMatTopHeader, unknown50) == 0x50, "");
static_assert(offsetof(MdsMatTopHeader, unknown54) == 0x54, "");

struct MdsMatTextureInfo {
  u16 unknown00; // Inferred role: texture index; original member name unknown.
  u16 unknown02; // Inferred role: sampler index of a mipmapped texture; original member name unknown.
  u16 unknown04; // Inferred role: sampler index of a texture without mipmap; original member name unknown.
  u8 _06[0x08 - 0x06];
};

static_assert(sizeof(MdsMatTextureInfo) == 0x08, "");

struct MdsMatInfoHeader {
  // Inferred role: material flag; original type name unknown.
  enum unknown015 {
    unknown015_2 = 1 << 2,   // Inferred role: alpha test material; original name unknown.
    unknown015_3 = 1 << 3,   // Inferred role: unknown, selects another shadow shader of an alpha test material; original name unknown.
    unknown015_13 = 1 << 13, // Inferred role: unknown, selects the mesh parts shadow shaders; original name unknown.
    unknown015_15 = 1 << 15, // Inferred role: seam material; original name unknown.
    unknown015_16 = 1 << 16, // Inferred role: uv animation; original name unknown.
    unknown015_17 = 1 << 17, // Inferred role: animation of the category at unknown34; original name unknown.
    unknown015_18 = 1 << 18, // Inferred role: material animation; original name unknown.
    unknown015_19 = 1 << 19, // Inferred role: plane matrix animation of the category at unknown3c; original name unknown.
  };

  u32 unknown00; // Inferred role: offset of the material name; original member name unknown.
  union {
    u32 unknown04; // Inferred role: flags; original member name unknown.
    struct {
      u8 _04;
      u8 unknown05; // Inferred role: flags, bit 7 is the seam material; original member name unknown.
    };
  };
  u8 _08[0x09 - 0x08];
  u8 unknown09; // Inferred role: flags; original member name unknown.
  u8 _0a[0x0c - 0x0a];
  f32 unknown0c; // Inferred role: color r; original member name unknown.
  f32 unknown10; // Inferred role: color g; original member name unknown.
  f32 unknown14; // Inferred role: color b; original member name unknown.
  f32 unknown18; // Inferred role: color a; original member name unknown.
  f32 unknown1c; // Inferred role: alpha test reference; original member name unknown.
  u32 unknown20; // Inferred role: texture index offset; original member name unknown.
  u32 unknown24; // Inferred role: unknown, tested against zero by the position shadow render; original member name unknown.
  u8 _28[0x2a - 0x28];
  u8 unknown2a; // Inferred role: culling type; original member name unknown.
  u8 _2b[0x30 - 0x2b];
  u32 unknown30; // Inferred role: uv animation category; original member name unknown.
  u32 unknown34; // Inferred role: animation category applied directly to the values (flag 17); original member name unknown.
  u32 unknown38; // Inferred role: material animation category; original member name unknown.
  u32 unknown3c; // Inferred role: plane matrix animation category (flag 19); original member name unknown.
  u32 unknown40; // Inferred role: value offset; original member name unknown.
  u8 _44[0x4c - 0x44];
  u32 unknown4c; // Inferred role: shader table offset; original member name unknown.
  s32 unknown50; // Inferred role: shader table count; original member name unknown.
  u8 _54[0x56 - 0x54];
  u16 unknown56; // Inferred role: avatar map color index; original member name unknown.
  u16 unknown58; // Inferred role: first material callback; original member name unknown.
  u16 unknown5a; // Inferred role: material callback count; original member name unknown.
  u8 _5c[0x62 - 0x5c];
  u16 unknown62; // Inferred role: texture index; original member name unknown.
  u16 unknown64; // Inferred role: time value index; original member name unknown.
  u8 _66[0x74 - 0x66];
};

static_assert(offsetof(MdsMatInfoHeader, unknown00) == 0x00, "");
static_assert(offsetof(MdsMatInfoHeader, unknown04) == 0x04, "");
static_assert(offsetof(MdsMatInfoHeader, unknown05) == 0x05, "");
static_assert(offsetof(MdsMatInfoHeader, unknown09) == 0x09, "");
static_assert(offsetof(MdsMatInfoHeader, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMatInfoHeader, unknown18) == 0x18, "");
static_assert(offsetof(MdsMatInfoHeader, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsMatInfoHeader, unknown20) == 0x20, "");
static_assert(offsetof(MdsMatInfoHeader, unknown24) == 0x24, "");
static_assert(offsetof(MdsMatInfoHeader, unknown2a) == 0x2a, "");
static_assert(offsetof(MdsMatInfoHeader, unknown30) == 0x30, "");
static_assert(offsetof(MdsMatInfoHeader, unknown38) == 0x38, "");
static_assert(offsetof(MdsMatInfoHeader, unknown40) == 0x40, "");
static_assert(offsetof(MdsMatInfoHeader, unknown4c) == 0x4c, "");
static_assert(offsetof(MdsMatInfoHeader, unknown50) == 0x50, "");
static_assert(offsetof(MdsMatInfoHeader, unknown56) == 0x56, "");
static_assert(offsetof(MdsMatInfoHeader, unknown58) == 0x58, "");
static_assert(offsetof(MdsMatInfoHeader, unknown5a) == 0x5a, "");
static_assert(offsetof(MdsMatInfoHeader, unknown62) == 0x62, "");
static_assert(offsetof(MdsMatInfoHeader, unknown64) == 0x64, "");

static_assert(sizeof(MdsMatInfoHeader) == 0x74, "");

struct MdsMatShaderTbl {
  u32 unknown00; // Inferred role: technique index; original member name unknown.
  u16 unknown04; // Inferred role: render pass type; original member name unknown.
  u16 unknown06; // Inferred role: material uniform index; original member name unknown.
  u32 unknown08; // Inferred role: flags, bit 0 has uniform values; original member name unknown.
};

static_assert(offsetof(MdsMatShaderTbl, unknown04) == 0x04, "");
static_assert(offsetof(MdsMatShaderTbl, unknown06) == 0x06, "");
static_assert(offsetof(MdsMatShaderTbl, unknown08) == 0x08, "");
static_assert(sizeof(MdsMatShaderTbl) == 0x0c, "");

struct MdsMatTechnique {
  u8 _00[0x10 - 0x00];
  u32 unknown10; // Inferred role: variable table offset; original member name unknown.
  s32 unknown14; // Inferred role: variable count; original member name unknown.
  u8 _18[0x44 - 0x18];
};

static_assert(offsetof(MdsMatTechnique, unknown10) == 0x10, "");
static_assert(offsetof(MdsMatTechnique, unknown14) == 0x14, "");
static_assert(sizeof(MdsMatTechnique) == 0x44, "");

struct unknown091;
struct MdoWrkVanishEffect;

// Inferred role: model data mesh parts info; original type name unknown.
struct unknown020 {
  u8 _00[0x08 - 0x00];
  u8 unknown08; // Inferred role: flags; original member name unknown.
  u8 _09[0x10 - 0x09];
};

static_assert(sizeof(unknown020) == 0x10, "");

// Inferred role: model data mesh header; original type name unknown.
struct unknown022 {
  enum Flag {
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: has billboard uniforms; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: has billboard work; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3,
    FLAG_UNKNOWN_13 = 1 << 13, // Inferred role: vanish effect; original name unknown.
  };

  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x1c - 0x04];
  u32 unknown1c; // Inferred role: mdl entry offset; original member name unknown.
  u32 unknown20; // Inferred role: mdl entry count; original member name unknown.
  u8 _24[0x28 - 0x24];
  u32 unknown28; // Inferred role: offset of the node table; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  u32 unknown30; // Inferred role: offset of the second table; original member name unknown.
  s32 unknown34; // Inferred role: count of the second table; original member name unknown.
  u8 _38[0x64 - 0x38];
  u32 unknown64; // Inferred role: parts info offset; original member name unknown.
  u8 _68[0x74 - 0x68];
  u32 unknown74; // Inferred role: offset of the billboard table; original member name unknown.
  u32 unknown78; // Inferred role: offset of the node animation table; original member name unknown.
  u8 _7c[0x94 - 0x7c];
  u8 unknown94; // Inferred role: vanish effect num; original member name unknown.
};

static_assert(offsetof(unknown022, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown022, unknown20) == 0x20, "");
static_assert(offsetof(unknown022, unknown28) == 0x28, "");
static_assert(offsetof(unknown022, unknown30) == 0x30, "");
static_assert(offsetof(unknown022, unknown34) == 0x34, "");
static_assert(offsetof(unknown022, unknown64) == 0x64, "");
static_assert(offsetof(unknown022, unknown78) == 0x78, "");
static_assert(offsetof(unknown022, unknown74) == 0x74, "");
static_assert(offsetof(unknown022, unknown94) == 0x94, "");

// Inferred role: node animation table header; original type name unknown.
struct unknown701 {
  u32 unknown00; // Inferred role: count; original member name unknown.
  u32 unknown04; // Inferred role: offset of the data; original member name unknown.
};

static_assert(sizeof(unknown701) == 0x08, "");

// Inferred role: node animation work; original type name unknown.
struct unknown702 {
  const unknown701 *unknown00; // Inferred role: table; original member name unknown.
  const unknown701 *unknown08; // Inferred role: table; original member name unknown.
  u32 unknown10;               // Inferred role: count; original member name unknown.
  const u8 *unknown18;         // Inferred role: data; original member name unknown.
  s32 unknown20;               // Inferred role: etc uniform index; original member name unknown.
  u8 _24[0x28 - 0x24];
};

static_assert(offsetof(unknown702, unknown10) == 0x10, "");
static_assert(offsetof(unknown702, unknown20) == 0x20, "");
static_assert(offsetof(unknown702, unknown18) == 0x18, "");
static_assert(sizeof(unknown702) == 0x28, "");

struct _MdoWrkDispCallTemp {
  u8 _00[0x08];
};

static_assert(sizeof(_MdoWrkDispCallTemp) == 0x08, "");

struct MdsMatDispCCData {
  u8 _00[0x04 - 0x00];
  u16 unknown04; // Inferred role: seam material bit index; original member name unknown.
  u8 _06[0x0c - 0x06];
};

static_assert(offsetof(MdsMatDispCCData, unknown04) == 0x04, "");

static_assert(sizeof(MdsMatDispCCData) == 0x0c, "");

// Inferred role: display call work, followed by one 8 byte slot per entry; original type name unknown.
struct unknown703 {
  s32 unknown00; // Inferred role: entry count; original member name unknown.
  u8 _04[0x08 - 0x04];
  _MdoWrkDispCallTemp *unknown08;    // Inferred role: entries; original member name unknown.
  const MdsMatDispCCData *unknown10; // Inferred role: data; original member name unknown.
};

static_assert(offsetof(unknown703, unknown08) == 0x08, "");
static_assert(offsetof(unknown703, unknown10) == 0x10, "");

// Inferred role: display call table header; original type name unknown.
struct unknown704 {
  u32 unknown00; // Inferred role: entry count; original member name unknown.
  u32 unknown04; // Inferred role: offset of the data; original member name unknown.
};

static_assert(sizeof(unknown704) == 0x08, "");

// Inferred role: fur shader source entry; original type name unknown.
struct unknown005 {
  u32 unknown00;
  u32 unknown04;
  u32 unknown08;
  u32 unknown0c;
  u32 unknown10;
};

static_assert(sizeof(unknown005) == 0x14, "");

// Inferred role: fur shader work entry; original type name unknown.
struct unknown006 {
  u32 unknown00;
  u32 unknown04;
  u32 unknown08;
  u32 unknown0c;
  u32 unknown10;
  u32 unknown14;
};

static_assert(sizeof(unknown006) == 0x18, "");

// Inferred role: fur shader work, followed by the work entries; original type name unknown.
struct unknown007 {
  const u8 *unknown00;         // Inferred role: first data; original member name unknown.
  const unknown005 *unknown08; // Inferred role: source entries; original member name unknown.
  unknown006 *unknown10;       // Inferred role: work entries; original member name unknown.
};

static_assert(offsetof(unknown007, unknown08) == 0x08, "");
static_assert(offsetof(unknown007, unknown10) == 0x10, "");

// Inferred role: fur shader table header; original type name unknown.
struct unknown008 {
  u32 unknown00; // Inferred role: offset of the first data; original member name unknown.
  u32 unknown04; // Inferred role: offset of the source entries; original member name unknown.
  s32 unknown08; // Inferred role: entry count; original member name unknown.
};

static_assert(sizeof(unknown008) == 0x0c, "");

// Inferred role: model work avatar; original type name unknown.
struct unknown023 {
  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x08 - 0x04];
  grlib::CGLibTextureBuffer *unknown08[2]; // Inferred role: base textures; original member name unknown.
  void *unknown18[2];                      // Inferred role: textures; original member name unknown.
  grlib::CGLibTextureBuffer *unknown28;    // Inferred role: eye base texture; original member name unknown.
  void *unknown30;                         // Inferred role: eye texture; original member name unknown.
  bool unknown38;                          // Inferred role: doll mat; original member name unknown.
  u8 _39[0x40 - 0x39];
  grlib::CGLibOneUniformBlock *unknown40; // Inferred role: char colors; original member name unknown.
  grlib::CGLibOneUniformBlock *unknown48; // Inferred role: doll colors; original member name unknown.
};

static_assert(offsetof(unknown023, unknown08) == 0x08, "");
static_assert(offsetof(unknown023, unknown18) == 0x18, "");
static_assert(offsetof(unknown023, unknown28) == 0x28, "");
static_assert(offsetof(unknown023, unknown30) == 0x30, "");
static_assert(offsetof(unknown023, unknown38) == 0x38, "");
static_assert(offsetof(unknown023, unknown40) == 0x40, "");
static_assert(offsetof(unknown023, unknown48) == 0x48, "");

// Inferred role: model work shader parm; original type name unknown.
struct unknown024 {
  mm::Col3 unknown00[4]; // Inferred role: colors; original member name unknown.
  f32 unknown30[1];      // Inferred role: values; original member name unknown.
};

static_assert(offsetof(unknown024, unknown30) == 0x30, "");

// Inferred role: fixed animation data header; original type name unknown.
struct unknown025 {
  u8 _00[0x04 - 0x00];
  u32 unknown04; // Inferred role: offset of the category ranges; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: offset of the categories; original member name unknown.
  u8 _10[0x14 - 0x10];
  u32 unknown14;
  u8 _18[0x1c - 0x18];
  u32 unknown1c;
  u8 _20[0x24 - 0x20];
  u32 unknown24;
};

static_assert(offsetof(unknown025, unknown04) == 0x04, "");
static_assert(offsetof(unknown025, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown025, unknown14) == 0x14, "");
static_assert(offsetof(unknown025, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown025, unknown24) == 0x24, "");

// Inferred role: fixed animation category range; original type name unknown.
struct unknown016 {
  u16 unknown00; // Inferred role: first category; original member name unknown.
  u16 unknown02; // Inferred role: category num; original member name unknown.
};

static_assert(sizeof(unknown016) == 0x04, "");

struct MdsMdlInfoHeader {
  // Inferred role: mdl info flag; original type name unknown.
  enum Flag {
    FLAG_UNKNOWN_8 = 1 << 8,   // Inferred role: has mesh parts; original name unknown.
    FLAG_UNKNOWN_13 = 1 << 13, // Inferred role: renders with the mesh parts render index; original name unknown.
    FLAG_UNKNOWN_17 = 1 << 17, // Inferred role: skinned mesh, excluded from the base shadow render; original name unknown.
    FLAG_UNKNOWN_24 = 1 << 24, // Inferred role: has mof blend vertices; original name unknown.
  };

  // Inferred role: render pass flag of unknown04; original type name unknown.
  enum PassFlag {
    PASS_FLAG_UNKNOWN_14 = 1 << 14, // Inferred role: renders into the shadow map; original name unknown.
  };

  u32 unknown00; // Inferred role: flags; original member name unknown.
  u32 unknown04; // Inferred role: render pass flags; original member name unknown.
  u16 unknown08; // Inferred role: vertex bind index; original member name unknown.
  u16 unknown0a; // Inferred role: render index; original member name unknown.
  u16 unknown0c; // Inferred role: render index of the mesh parts; original member name unknown.
  u16 unknown0e; // Inferred role: material index; original member name unknown.
  u8 _10[0x16 - 0x10];
  u16 unknown16; // Inferred role: mesh parts index; original member name unknown.
  u8 _18[0x1c - 0x18];
  u16 unknown1c; // Inferred role: shader parameter; original member name unknown.
  u8 _1e[0x30 - 0x1e];
};

static_assert(offsetof(MdsMdlInfoHeader, unknown04) == 0x04, "");
static_assert(offsetof(MdsMdlInfoHeader, unknown08) == 0x08, "");
static_assert(offsetof(MdsMdlInfoHeader, unknown0a) == 0x0a, "");
static_assert(offsetof(MdsMdlInfoHeader, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMdlInfoHeader, unknown0e) == 0x0e, "");
static_assert(offsetof(MdsMdlInfoHeader, unknown16) == 0x16, "");
static_assert(offsetof(MdsMdlInfoHeader, unknown1c) == 0x1c, "");

static_assert(sizeof(MdsMdlInfoHeader) == 0x30, "");

// Model data mdl entry, named from DrMdoCtlNom::nomRender(const MdsMdlTopHeader *, DrResChkList *).
struct MdsMdlTopHeader {
  u32 unknown00; // Inferred role: info offset; original member name unknown.
  s32 unknown04; // Inferred role: info count; original member name unknown.
  u8 _08[0x0c - 0x08];
  f32 unknown0c[3]; // Inferred role: aabb max; original member name unknown.
  f32 unknown18[3]; // Inferred role: aabb min; original member name unknown.
  u8 _24[0x44 - 0x24];
};

static_assert(offsetof(MdsMdlTopHeader, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMdlTopHeader, unknown18) == 0x18, "");
static_assert(sizeof(MdsMdlTopHeader) == 0x44, "");

// Inferred role: flag wave uniform table; original type name unknown.
struct unknown009 {
  const u16 *unknown00; // Inferred role: uniform index per wave; original member name unknown.
  u8 _08[0x18 - 0x08];
  grlib::CGLibUniformArray<grlib::CGLibTriUniformBlock> *unknown18; // Inferred role: uniforms; original member name unknown.
};

static_assert(offsetof(unknown009, unknown18) == 0x18, "");

// Inferred role: material callback table header; original type name unknown.
struct unknown010 {
  u32 unknown00; // Inferred role: offset of the callbacks; original member name unknown.
  u8 _04[0x08 - 0x04];
  u32 unknown08; // Inferred role: offset of the material indices; original member name unknown.
  s32 unknown0c; // Inferred role: material count; original member name unknown.
  u32 unknown10; // Inferred role: offset of the first callback entries; original member name unknown.
  s32 unknown14; // Inferred role: first callback entry count; original member name unknown.
};

static_assert(offsetof(unknown010, unknown08) == 0x08, "");
static_assert(offsetof(unknown010, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown010, unknown10) == 0x10, "");
static_assert(offsetof(unknown010, unknown14) == 0x14, "");
static_assert(sizeof(unknown010) == 0x18, "");

// Inferred role: material callback; original type name unknown.
struct unknown011 {
  u16 unknown00; // Inferred role: callback index; original member name unknown.
  u16 unknown02; // Inferred role: value index; original member name unknown.
};

static_assert(sizeof(unknown011) == 0x04, "");

// Inferred role: first material callback entry; original type name unknown.
struct unknown012 {
  u32 unknown00;      // Inferred role: material index; original member name unknown.
  u32 unknown04 : 16; // Inferred role: callback count; original member name unknown.
  u32 unknown06 : 16; // Inferred role: first callback; original member name unknown.
};

static_assert(sizeof(unknown012) == 0x08, "");

struct MdsFixAnmInf {
  u32 unknown00_0 : 29; // Inferred role: first key; original member name unknown.
  u32 unknown00_29 : 1; // Inferred role: inverted parameter; original member name unknown.
  u32 unknown00_30 : 1; // Inferred role: parameter driven; original member name unknown.
  u32 unknown00_31 : 1; // Inferred role: timer driven; original member name unknown.
  u32 unknown04;        // Inferred role: key num or parameter index; original member name unknown.
  u32 unknown08;        // Inferred role: callback index in the low half, work offset in the high half; original member name unknown.
  u16 unknown0c;        // Inferred role: start frame; original member name unknown.
  u16 unknown0e;        // Inferred role: end frame; original member name unknown.
};

static_assert(offsetof(MdsFixAnmInf, unknown04) == 0x04, "");
static_assert(offsetof(MdsFixAnmInf, unknown08) == 0x08, "");
static_assert(offsetof(MdsFixAnmInf, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsFixAnmInf, unknown0e) == 0x0e, "");
static_assert(sizeof(MdsFixAnmInf) == 0x10, "");

// Inferred role: fixed animation hermite key; original type name unknown.
struct unknown013 {
  f32 unknown00; // Inferred role: out slope; original member name unknown.
  f32 unknown04; // Inferred role: in slope; original member name unknown.
  f32 unknown08; // Inferred role: value; original member name unknown.
  u16 unknown0c; // Inferred role: frame; original member name unknown.
  u8 unknown0e;  // Inferred role: flags, bit 0 is a step key; original member name unknown.
  u8 _0f;
};

static_assert(offsetof(unknown013, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown013, unknown0e) == 0x0e, "");
static_assert(sizeof(unknown013) == 0x10, "");

// Inferred role: billboard entry of the model data; original type name unknown.
struct unknown719;

// Inferred role: billboard position of the model data; original type name unknown.
struct unknown720;

// Inferred role: billboard uniform work; original type name unknown.
struct unknown712 {
  u8 _00[0x08 - 0x00];
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknown08; // Inferred role: uniforms; original member name unknown.
  u8 _10[0x18 - 0x10];
  const unknown719 *unknown18; // Inferred role: billboard entries in the model data; original member name unknown.
  const unknown720 *unknown20; // Inferred role: billboard positions in the model data; original member name unknown.
};

static_assert(offsetof(unknown712, unknown08) == 0x08, "");
static_assert(offsetof(unknown712, unknown18) == 0x18, "");
static_assert(offsetof(unknown712, unknown20) == 0x20, "");

// Inferred role: billboard table header of the model data; original type name unknown.
struct unknown714 {
  u32 unknown00; // Inferred role: offset of the billboard entries; original member name unknown.
  u8 _04[0x08 - 0x04];
  u32 unknown08; // Inferred role: offset of the billboard positions; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u32 unknown10; // Inferred role: offset of the matrices; original member name unknown.
  u8 _14[0x18 - 0x14];
};

static_assert(offsetof(unknown714, unknown00) == 0x00, "");
static_assert(offsetof(unknown714, unknown08) == 0x08, "");
static_assert(offsetof(unknown714, unknown10) == 0x10, "");

// Inferred role: billboard matrix work of the base map; original type name unknown.
struct unknown715 {
  u8 _00[0x10 - 0x00];
  const u8 *unknown10; // Inferred role: matrices in the model data; original member name unknown.
};

static_assert(offsetof(unknown715, unknown10) == 0x10, "");

// Inferred role: billboard matrix work of the instance map; original type name unknown.
struct unknown716 {
  u8 _00[0x08 - 0x00];
  const u8 *unknown08; // Inferred role: matrices in the model data; original member name unknown.
};

static_assert(offsetof(unknown716, unknown08) == 0x08, "");

// Inferred role: timer work; original type name unknown.
struct unknown717 {
  const u8 *unknown00; // Inferred role: timer table in the material data; original member name unknown.
};

static_assert(offsetof(unknown717, unknown00) == 0x00, "");

// Inferred role: avatar map color table header; original type name unknown.
struct unknown718 {
  u32 unknown00; // Inferred role: offset of the avatar map color indices; original member name unknown.
};

static_assert(offsetof(unknown718, unknown00) == 0x00, "");

// Inferred role: instance map uniform work; original type name unknown.
struct unknown713 {
  u8 _00[0x08 - 0x00];
  grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock> *unknown08; // Inferred role: uniforms; original member name unknown.
};

static_assert(offsetof(unknown713, unknown08) == 0x08, "");

struct MdoWrkMatRes {
  const u8 *unknown00;               // Inferred role: vertex data; original member name unknown.
  const u8 *unknown08;               // Inferred role: texture data; original member name unknown.
  const u8 *unknown10;               // Inferred role: texture indices; original member name unknown.
  const u8 *unknown18;               // Inferred role: model data; original member name unknown.
  const unknown022 *unknown20;       // Inferred role: mesh header; original member name unknown.
  const MdsMatInfoHeader *unknown28; // Inferred role: mat data; original member name unknown.
  s32 unknown30;                     // Inferred role: mat count; original member name unknown.
  u8 _034[0x038 - 0x034];
  const f32 *unknown38;                                             // Inferred role: base values; original member name unknown.
  const unknown010 *unknown40;                                      // Inferred role: material callbacks; original member name unknown.
  const u8 *unknown48;                                              // Inferred role: avatar map color indices; original member name unknown.
  const u8 *unknown50;                                              // Inferred role: fixed anim data; original member name unknown.
  const MdsFixAnmInf *unknown58;                                    // Inferred role: fixed anim infos; original member name unknown.
  const unknown013 *unknown60;                                      // Inferred role: fixed anim keys; original member name unknown.
  const u8 *unknown68;                                              // Inferred role: fixed anim arrays; original member name unknown.
  const MdsMatTechnique *unknown70;                                 // Inferred role: techniques; original member name unknown.
  const u8 *unknown78;                                              // Inferred role: variable tables; original member name unknown.
  DrShdMdoDecShdObj *unknown80;                                     // Inferred role: dec shader object; original member name unknown.
  DrShdMdoExtTblObj *unknown88;                                     // Inferred role: shader extension tables; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknown90; // Inferred role: material uniforms; original member name unknown.
  u8 _098[0x0a0 - 0x098];
  grlib::CGLibUniformArray<grlib::CGLibTriUniformBlock> *unknowna0; // Inferred role: mdl uniforms; original member name unknown.
  grlib::CGLibOneUniformArray *unknowna8;                           // Inferred role: mof blend uniforms; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknownb0; // Inferred role: vol tex uniforms; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknownb8; // Inferred role: rim bloom uniforms; original member name unknown.
  DrResMdoMat *unknownc0;                                           // Inferred role: mat entries; original member name unknown.
  DrResMdoVertex *unknownc8;                                        // Inferred role: vertex; original member name unknown.
  DrResMdoTexList *unknownd0;                                       // Inferred role: texture list; original member name unknown.
  DrResMdoSampler *unknownd8;                                       // Inferred role: samplers; original member name unknown.
  DrResMpfSampler *unknowne0;                                       // Inferred role: mpf samplers, one per material; original member name unknown.
  grlib::CGLibTextureBuffer **unknowne8;                            // Inferred role: textures; original member name unknown.
  s32 unknownf0;                                                    // Inferred role: texture count; original member name unknown.
  u8 _0f4[0x0f8 - 0x0f4];
  f32 *unknownf8;  // Inferred role: values; original member name unknown.
  f32 *unknown100; // Inferred role: fixed anim frames; original member name unknown.
  u8 _108[0x110 - 0x108];
  unknown023 *unknown110; // Inferred role: avatar; original member name unknown.
  unknown024 *unknown118; // Inferred role: shader parm; original member name unknown.
  union {
    unknown712 *unknown120;   // Inferred role: billboard uniforms of the base map; original member name unknown.
    unknown713 *unknown120_1; // Inferred role: uniforms of the instance map; original member name unknown.
  };
  unknown717 *unknown128;         // Inferred role: timer; original member name unknown.
  unknown703 *unknown130;         // Inferred role: display call; original member name unknown.
  unknown007 *unknown138;         // Inferred role: fur shader; original member name unknown.
  unknown009 *unknown140;         // Inferred role: flag wave uniforms; original member name unknown.
  unknown702 *unknown148;         // Inferred role: node animation; original member name unknown.
  MdoWrkVanishEffect *unknown150; // Inferred role: vanish effects; original member name unknown.
  unknown091 *unknown158;         // Inferred role: rim blooms; original member name unknown.
  union {
    unknown715 *unknown160;   // Inferred role: billboard matrices of the base map; original member name unknown.
    unknown716 *unknown160_1; // Inferred role: billboard matrices of the instance map; original member name unknown.
  };
  const MdsMdlTopHeader *unknown168; // Inferred role: mdl entries; original member name unknown.
  s32 unknown170;                    // Inferred role: mdl entry count; original member name unknown.
  u8 _174[0x178 - 0x174];
  const u8 *unknown178; // Inferred role: second table; original member name unknown.
};

static_assert(offsetof(MdoWrkMatRes, unknown00) == 0x000, "");
static_assert(offsetof(MdoWrkMatRes, unknown08) == 0x008, "");
static_assert(offsetof(MdoWrkMatRes, unknown10) == 0x010, "");
static_assert(offsetof(MdoWrkMatRes, unknown50) == 0x050, "");
static_assert(offsetof(MdoWrkMatRes, unknown68) == 0x068, "");
static_assert(offsetof(MdoWrkMatRes, unknown70) == 0x070, "");
static_assert(offsetof(MdoWrkMatRes, unknown78) == 0x078, "");
static_assert(offsetof(MdoWrkMatRes, unknown18) == 0x018, "");
static_assert(offsetof(MdoWrkMatRes, unknown20) == 0x020, "");
static_assert(offsetof(MdoWrkMatRes, unknown28) == 0x028, "");
static_assert(offsetof(MdoWrkMatRes, unknown30) == 0x030, "");
static_assert(offsetof(MdoWrkMatRes, unknown38) == 0x038, "");
static_assert(offsetof(MdoWrkMatRes, unknown40) == 0x040, "");
static_assert(offsetof(MdoWrkMatRes, unknown48) == 0x048, "");
static_assert(offsetof(MdoWrkMatRes, unknown58) == 0x058, "");
static_assert(offsetof(MdoWrkMatRes, unknown60) == 0x060, "");
static_assert(offsetof(MdoWrkMatRes, unknown88) == 0x088, "");
static_assert(offsetof(MdoWrkMatRes, unknown90) == 0x090, "");
static_assert(offsetof(MdoWrkMatRes, unknowna0) == 0x0a0, "");
static_assert(offsetof(MdoWrkMatRes, unknowna8) == 0x0a8, "");
static_assert(offsetof(MdoWrkMatRes, unknownb0) == 0x0b0, "");
static_assert(offsetof(MdoWrkMatRes, unknownb8) == 0x0b8, "");
static_assert(offsetof(MdoWrkMatRes, unknownc0) == 0x0c0, "");
static_assert(offsetof(MdoWrkMatRes, unknownc8) == 0x0c8, "");
static_assert(offsetof(MdoWrkMatRes, unknownd0) == 0x0d0, "");
static_assert(offsetof(MdoWrkMatRes, unknownd8) == 0x0d8, "");
static_assert(offsetof(MdoWrkMatRes, unknowne8) == 0x0e8, "");
static_assert(offsetof(MdoWrkMatRes, unknownf0) == 0x0f0, "");
static_assert(offsetof(MdoWrkMatRes, unknownf8) == 0x0f8, "");
static_assert(offsetof(MdoWrkMatRes, unknown100) == 0x100, "");
static_assert(offsetof(MdoWrkMatRes, unknown110) == 0x110, "");
static_assert(offsetof(MdoWrkMatRes, unknown118) == 0x118, "");
static_assert(offsetof(MdoWrkMatRes, unknown128) == 0x128, "");
static_assert(offsetof(MdoWrkMatRes, unknown130) == 0x130, "");
static_assert(offsetof(MdoWrkMatRes, unknown138) == 0x138, "");
static_assert(offsetof(MdoWrkMatRes, unknown140) == 0x140, "");
static_assert(offsetof(MdoWrkMatRes, unknown148) == 0x148, "");
static_assert(offsetof(MdoWrkMatRes, unknown150) == 0x150, "");
static_assert(offsetof(MdoWrkMatRes, unknown158) == 0x158, "");
static_assert(offsetof(MdoWrkMatRes, unknown160) == 0x160, "");
static_assert(offsetof(MdoWrkMatRes, unknown168) == 0x168, "");
static_assert(offsetof(MdoWrkMatRes, unknown170) == 0x170, "");
static_assert(offsetof(MdoWrkMatRes, unknown178) == 0x178, "");

// Layout evidence: ScnObjAccVolumeFade::setParams copies VolumeFadeParams into 0x00..0xa0 and its member at 0xa4 to 0xa8.
struct MdoWrkVanishEffect {
  mm::Col3 unknown00[5]; // Inferred role: colors; original member name unknown.
  mm::Vec3 unknown40;    // Inferred role: position; original member name unknown.
  mm::Vec3 unknown50;    // Inferred role: scale; original member name unknown.
  f32 unknown60[5];      // Inferred role: first group of five floats; original member name unknown.
  f32 unknown74[5];      // Inferred role: second group of five floats; original member name unknown.
  f32 unknown88[5];      // Inferred role: third group of five floats; original member name unknown.
  f32 unknown9c;         // Inferred role: frame; original member name unknown.
  f32 unknowna0;         // Inferred role: rate; original member name unknown.
  f32 unknowna4;         // Inferred role: ratio; original member name unknown.
  f32 unknowna8;         // Role and original member name unknown.
  u8 _ac[0xd0 - 0xac];
  f32 unknownd0; // Inferred role: base ratio; original member name unknown.
  u32 unknownd4; // Inferred role: flags; original member name unknown.
  u8 _d8[0xe0 - 0xd8];
};

static_assert(offsetof(MdoWrkVanishEffect, unknown40) == 0x40, "");
static_assert(offsetof(MdoWrkVanishEffect, unknown50) == 0x50, "");
static_assert(offsetof(MdoWrkVanishEffect, unknown60) == 0x60, "");
static_assert(offsetof(MdoWrkVanishEffect, unknown74) == 0x74, "");
static_assert(offsetof(MdoWrkVanishEffect, unknown88) == 0x88, "");
static_assert(offsetof(MdoWrkVanishEffect, unknown9c) == 0x9c, "");
static_assert(offsetof(MdoWrkVanishEffect, unknowna0) == 0xa0, "");
static_assert(offsetof(MdoWrkVanishEffect, unknowna4) == 0xa4, "");
static_assert(offsetof(MdoWrkVanishEffect, unknowna8) == 0xa8, "");
static_assert(offsetof(MdoWrkVanishEffect, unknownd0) == 0xd0, "");
static_assert(offsetof(MdoWrkVanishEffect, unknownd4) == 0xd4, "");
static_assert(sizeof(MdoWrkVanishEffect) == 0xe0, "");

class DrMdoMat : public DrMdlBase {
public:
  // Inferred role: draw flag; original type name unknown.
  enum unknown027 {
    unknown027_0 = 1 << 0,    // Inferred role: resource ready; original name unknown.
    unknown027_2 = 1 << 2,    // Inferred role: always tex stm; original name unknown.
    unknown027_4 = 1 << 4,    // Inferred role: write stencil; original name unknown.
    unknown027_6 = 1 << 6,    // Inferred role: flag wave; original name unknown.
    unknown027_8 = 1 << 8,    // Inferred role: registered in the shadow cache update; original name unknown.
    unknown027_10 = 1 << 10,  // Inferred role: simple shadow; original name unknown.
    unknown027_14 = 1 << 14,  // Inferred role: sp alpha mode; original name unknown.
    unknown027_15 = 1 << 15,  // Inferred role: sp blur off; original name unknown.
    unknown027_16 = 1 << 16,  // Inferred role: gpu clip off; original name unknown.
    unknown027_17 = 1 << 17,  // Inferred role: always middle tex stm; original name unknown.
    unknown027_18 = 1 << 18,  // Inferred role: occlusion query off; original name unknown.
    unknown027_20 = 1 << 20,  // Inferred role: express draw mode; original name unknown.
    unknown027_22 = 1 << 22,  // Inferred role: updated render list; original name unknown.
    unknown027_23 = 1 << 23,  // Inferred role: unknown, cleared while the display is off; original name unknown.
    unknown027_26 = 1 << 26,  // Inferred role: model matrix is updated; original name unknown.
    unknown027_28 = 1 << 28,  // Inferred role: cam check mode; original name unknown.
    unknown027_29 = 1 << 29,  // Inferred role: cam check resl; original name unknown.
    unknown027_30 = 1 << 30,  // Inferred role: debug delete; original name unknown.
    unknown027_31 = 1u << 31, // Inferred role: debug window; original name unknown.
  };

  // Inferred role: mdl flag; original type name unknown.
  enum unknown028 {
    unknown028_0 = 1 << 0,
    unknown028_1 = 1 << 1,
    unknown028_2 = 1 << 2,
    unknown028_3 = 1 << 3,
    unknown028_4 = 1 << 4,
    unknown028_5 = 1 << 5,
    unknown028_6 = 1 << 6,
    unknown028_7 = 1 << 7, // Inferred role: bounding box is valid, merged by the group update; original name unknown.
    unknown028_8 = 1 << 8,
    unknown028_9 = 1 << 9,
    unknown028_20 = 1 << 20,
    unknown028_11 = 1 << 11, // Inferred role: shadow map of the first cascade; original name unknown.
    unknown028_12 = 1 << 12, // Inferred role: shadow map of the second cascade; original name unknown.
    unknown028_13 = 1 << 13, // Inferred role: shadow map of the third cascade; original name unknown.
    unknown028_21 = 1 << 21, // Inferred role: no z pre pass before the opaque render; original name unknown.
    unknown028_15 = 1 << 15, // Inferred role: bloom; original name unknown.
    unknown028_16 = 1 << 16, // Inferred role: alpha bloom; original name unknown.
    unknown028_17 = 1 << 17, // Inferred role: volume; original name unknown.
    unknown028_18 = 1 << 18, // Inferred role: full screen shadow; original name unknown.
    unknown028_25 = 1 << 25,
    unknown028_26 = 1 << 26,
    unknown028_27 = 1 << 27,
    unknown028_28 = 1 << 28,
    unknown028_31 = 1u << 31,
  };

  // Inferred role: alpha flag; original type name unknown.
  enum unknown029 {
    unknown029_16 = 1 << 16, // Inferred role: updated; original name unknown.
    unknown029_18 = 1 << 18, // Inferred role: single buffer; original name unknown.
  };

  DrMdoMat(int viewNum);

  void initMdlInfo(const u8 *data, MdoWrkMatRes *matRes);
  void initMaterial(const u8 *matData, const u8 *shaderData, const u8 *mdlData, const u8 *texData, bool isStm);
  void initMpfMaterial(const u8 *matData, const u8 *vertexData, const u8 *mdlData, const u8 *texData, bool isStm);
  void setupResource(bool isStm);
  void oneTextureStream();
  void updateBillTbl();
  u32 calcBillMdlInfo(const u8 *data, int, bool isInstance);
  void resetBillMdlInfo(MdoWrkMatRes *matRes, const u8 *data, bool isInstance);
  void resetMpfMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *vertexData, const u8 *mdlData, const u8 *texData);
  int getNodeAnmWrkRes(const u8 *data, u8 *work, MdoWrkMatRes *matRes);
  void resetNodeAnmWrkRes(const u8 *data, MdoWrkMatRes *matRes);
  int getDispCallRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes);
  void resetDispCallRes(const u8 *data, u32 offset, MdoWrkMatRes *matRes);
  void setupMpfResource();
  int getFlagWaveRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes);
  void updateFlagWaveTbl();
  bool checkCallBackParam(_MdoWrkDispCallTemp *temp, const MdsMatDispCCData *data);
  void updateSeamDispCall(MdoWrkMatRes *matRes, u32 *flags, const u32 *seamFlags);
  void setupAvatarTbl(const MdsMatTopHeader *header);
  void updateAvatarTbl();
  void updateDispCall();
  bool updateDispEnvCall(MdoWrkMatRes *matRes);
  int getFurShaderRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes);
  void resetFurShaderRes(const u8 *data, u32 offset, MdoWrkMatRes *matRes);
  void releaseMat();
  void initBaseMapMaterial(MdoWrkMatRes *&matRes, const u8 *data0, const u8 *data1, const u8 *data2, const u8 *data3, const u8 *data4, int count);
  void initInstMapMaterial(MdoWrkMatRes *&matRes, const u8 *matData, const u8 *mdlData, const u8 *shaderData, const u8 *texData, int skipTexList);
  void resetBaseMapMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *mdlData, const u8 *vertexData, const u8 *shaderData, const u8 *texData, int skipTexList);
  void resetInstMapMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *mdlData, const u8 *shaderData, const u8 *texData, int skipTexList);
  void releaseBaseMapSeamMat(MdoWrkMatRes *matRes);
  void releaseInstMapSeamMat(MdoWrkMatRes *matRes);
  void releaseMpfMapSeamMat(MdoWrkMatRes *matRes);
  void setDrMan(DrMan *drMan);
  void updateAlphaCall();
  bool isBloomMdl() const;
  bool isAlphaBloomMdl() const;
  u32 getVanishEffectMax() const;
  bool isFullScreenShadowMdl() const;
  MdoWrkVanishEffect *getVanishEffectWrk(u32 index, u32 bufferIndex);
  bool isVolumeMdl() const;
  void setFlagWaveOn(bool isOn);
  void setExtraShaderSetup(const void *shader);
  void releaseExtraShader();
  void matCall_BaseColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_BaseVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_TransVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_CalcColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_EmissiveTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_RgbTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_RTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_WaterFog(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_CalcBloom(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_OutLineVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_ToonId(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_VolumeTest(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_MatxView(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_MatxInvView(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void updateMatFstCallBack();
  void updateMatCallBack(const u32 *flags);
  void updateTimerCalc(const u32 *flags);

  static const f32 MDL_SCALE_PARAMS; // Name from the game symbol _ZN2ml8DrMdoMat16MDL_SCALE_PARAMSE; the game value is 0x3f13cd3f (0.57735055f).

  static void (DrMdoMat::*s_pCallFstMatVal[])(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  static void (DrMdoMat::*s_pCallMatVal[])(const MdsMatInfoHeader *header, int valueIndex, int matIndex);

  u8 _24[0x28 - 0x24];
  DrMan *m_drMan;
  MdoWrkMatRes *unknown30;             // Inferred role: mat res; original member name unknown.
  DrShdMdoDecExtTbl *unknown38;        // Inferred role: dec ext tbl; original member name unknown.
  mm::Col3 *unknown40;                 // Inferred role: avatar map colors; original member name unknown.
  const MdsMatCharMkTexTbl *unknown48; // Inferred role: char mk textures; original member name unknown.
  const void *unknown50;               // Inferred role: dammy data; original member name unknown.
  DrMdoSmlShadowObj *unknown58;        // Inferred role: sml shadow; original member name unknown.
  mm::Mat44 *unknown60[2];             // Inferred role: matrix of each buffer; original member name unknown.
  mm::Mat44 m_matrix;
  mm::Vec3 m_offsetPos;
  u8 _c0[0xd0 - 0xc0];
  f32 unknownd0[2]; // Inferred role: alphas; original member name unknown.
  f32 unknownd8;    // Inferred role: bloom; original member name unknown.
  f32 unknowndc;    // Inferred role: frame spd; original member name unknown.
  f32 unknowne0;    // Inferred role: alpha; original member name unknown.
  f32 unknowne4;    // Inferred role: outline value time; original member name unknown.
  f32 unknowne8;    // Inferred role: scale; original member name unknown.
  u32 unknownec;    // Inferred role: screen share limit that keeps the gpu render flag on; original member name unknown.
  bool m_gpuRender;
  u8 _f1;
  s16 unknownf2; // Inferred role: render pass id; original member name unknown.
  s16 unknownf4; // Inferred role: render pass index; original member name unknown.
  u8 _f6[0xf8 - 0xf6];
  u32 unknownf8;  // Inferred role: mdl flags; original member name unknown.
  u32 unknownfc;  // Inferred role: draw flags; original member name unknown.
  u32 unknown100; // Inferred role: alpha flags; original member name unknown.
  u8 _104[0x110 - 0x104];
  mm::Vec3 m_AABBMax;
  mm::Vec3 m_AABBMin;
  mm::Vec3 unknown130; // Inferred role: center; original member name unknown.
  u8 _140[0x160 - 0x140];
  f32 unknown160; // Inferred role: length; original member name unknown.
  u8 _164[0x168 - 0x164];
  u16 unknown168; // Inferred role: update flags; original member name unknown.
  u8 unknown16a;  // Inferred role: char mk texture count; original member name unknown.
  s8 unknown16b;  // Inferred role: gpu render hold count; original member name unknown.
};

static_assert(offsetof(DrMdoMat, m_drMan) == 0x28, "");
static_assert(offsetof(DrMdoMat, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoMat, unknown38) == 0x38, "");
static_assert(offsetof(DrMdoMat, unknown40) == 0x40, "");
static_assert(offsetof(DrMdoMat, unknown48) == 0x48, "");
static_assert(offsetof(DrMdoMat, unknown50) == 0x50, "");
static_assert(offsetof(DrMdoMat, unknown58) == 0x58, "");
static_assert(offsetof(DrMdoMat, m_matrix) == 0x70, "");
static_assert(offsetof(DrMdoMat, m_offsetPos) == 0xb0, "");
static_assert(offsetof(DrMdoMat, unknownd0) == 0xd0, "");
static_assert(offsetof(DrMdoMat, unknownd8) == 0xd8, "");
static_assert(offsetof(DrMdoMat, unknowndc) == 0xdc, "");
static_assert(offsetof(DrMdoMat, unknowne0) == 0xe0, "");
static_assert(offsetof(DrMdoMat, unknowne4) == 0xe4, "");
static_assert(offsetof(DrMdoMat, unknowne8) == 0xe8, "");
static_assert(offsetof(DrMdoMat, m_gpuRender) == 0xf0, "");
static_assert(offsetof(DrMdoMat, unknownf2) == 0xf2, "");
static_assert(offsetof(DrMdoMat, unknownf4) == 0xf4, "");
static_assert(offsetof(DrMdoMat, unknownf8) == 0xf8, "");
static_assert(offsetof(DrMdoMat, unknownfc) == 0xfc, "");
static_assert(offsetof(DrMdoMat, unknown100) == 0x100, "");
static_assert(offsetof(DrMdoMat, m_AABBMax) == 0x110, "");
static_assert(offsetof(DrMdoMat, unknown168) == 0x168, "");
static_assert(offsetof(DrMdoMat, m_AABBMin) == 0x120, "");
static_assert(offsetof(DrMdoMat, unknown130) == 0x130, "");
static_assert(offsetof(DrMdoMat, unknown160) == 0x160, "");
static_assert(offsetof(DrMdoMat, unknown16a) == 0x16a, "");

} // namespace ml
