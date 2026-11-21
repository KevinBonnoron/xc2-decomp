#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibDblUniformArray;
class CGLibOneUniformArray;
class CGLibTriUniformArray;
class CGLibTriUniformBlock;
} // namespace grlib

namespace ml {
class DrResMdoVertex;
struct MdsMatInfoHeader;
struct MdsMatTechnique;

struct MdsMpfMatTopHeader {
  u32 unknown00; // Inferred role: offset of the material infos; original member name unknown.
  u32 unknown04; // Inferred role: material count, copied to MdoWrkMatRes::unknown30 and also the sampler count and the size of the bit table; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: unknown value copied to MdoWrkMatRes::unknown34; original member name unknown.
  u8 _10[0x14 - 0x10];
  s32 unknown14; // Inferred role: material count; original member name unknown.
};

static_assert(offsetof(MdsMpfMatTopHeader, unknown00) == 0x00, "");
static_assert(offsetof(MdsMpfMatTopHeader, unknown04) == 0x04, "");
static_assert(offsetof(MdsMpfMatTopHeader, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMpfMatTopHeader, unknown14) == 0x14, "");

class DrShdUniformBlockMan {
public:
  static void createUniformMaterialObj(grlib::CGLibDblUniformArray *uniforms, const MdsMatTechnique *techniques, const u8 *variables, const u8 *shaders, const MdsMatInfoHeader *headers, int matNum);
  static void createUniformMdlObj(grlib::CGLibTriUniformArray *uniforms, int num);
  static void createUniformBoneObj(grlib::CGLibTriUniformBlock *uniform, int boneNum);
  static void createMotionBlendObj(grlib::CGLibOneUniformArray *uniforms, const u8 *data, DrResMdoVertex *vertex);
  static void changeMotionBlendObj(grlib::CGLibOneUniformArray *uniforms, const u8 *data, DrResMdoVertex *vertex);
  static void createUniformVolTexCalcObj(grlib::CGLibDblUniformArray *uniforms, u32 num);
  static void createUniformRimBloomCalcObj(grlib::CGLibDblUniformArray *uniforms);
  static void createUniformMpfMaterialObj(grlib::CGLibDblUniformArray *uniforms, const MdsMpfMatTopHeader *header);

  static const u16 s_nMatChackTbl[10]; // Name from the game symbol _ZN2ml20DrShdUniformBlockMan14s_nMatChackTblE; also in torna and xc1de.
};

} // namespace ml
