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
  u8 _00[0x14 - 0x00];
  s32 unknown14; // Inferred role: material count; original member name unknown.
};

static_assert(offsetof(MdsMpfMatTopHeader, unknown14) == 0x14, "");

class DrShdUniformBlockMan {
public:
  static void createUniformMaterialObj(grlib::CGLibDblUniformArray *uniforms, const MdsMatTechnique *techniques, const u8 *variables, const u8 *shaders, const MdsMatInfoHeader *headers, int matNum);
  static void createUniformMdlObj(grlib::CGLibTriUniformArray *uniforms, int num);
  static void createUniformBoneObj(grlib::CGLibTriUniformBlock *uniform, int boneNum);
  static void changeMotionBlendObj(grlib::CGLibOneUniformArray *uniforms, const u8 *data, DrResMdoVertex *vertex);
  static void createUniformVolTexCalcObj(grlib::CGLibDblUniformArray *uniforms, u32 num);
  static void createUniformRimBloomCalcObj(grlib::CGLibDblUniformArray *uniforms);
  static void createUniformMpfMaterialObj(grlib::CGLibDblUniformArray *uniforms, const MdsMpfMatTopHeader *header);

  static const u16 s_nMatChackTbl[10]; // Name from the game symbol _ZN2ml20DrShdUniformBlockMan14s_nMatChackTblE; also in torna and xc1de.
};

} // namespace ml
