#pragma once
#include "types.h"

namespace ml {

class DrResMdoUniformBlock {
public:
  enum VarType {
    VAR_TYPE_UNKNOWN_2 = 2,   // Inferred role: view; original name unknown.
    VAR_TYPE_UNKNOWN_3 = 3,   // Inferred role: proj; original name unknown.
    VAR_TYPE_UNKNOWN_4 = 4,   // Inferred role: view proj; original name unknown.
    VAR_TYPE_UNKNOWN_6 = 6,   // Inferred role: inv view; original name unknown.
    VAR_TYPE_UNKNOWN_8 = 8,   // Inferred role: view y vec; original name unknown.
    VAR_TYPE_UNKNOWN_17 = 17, // Inferred role: tex matrix; original name unknown.
    VAR_TYPE_UNKNOWN_18 = 18, // Inferred role: work float4; original name unknown.
    VAR_TYPE_UNKNOWN_19 = 19, // Inferred role: work color; original name unknown.
    VAR_TYPE_UNKNOWN_20 = 20, // Inferred role: projection mat; original name unknown.
    VAR_TYPE_UNKNOWN_23 = 23,
    VAR_TYPE_UNKNOWN_24 = 24,
    VAR_TYPE_UNKNOWN_25 = 25,
    VAR_TYPE_UNKNOWN_26 = 26,
    VAR_TYPE_UNKNOWN_29 = 29,
    VAR_TYPE_UNKNOWN_30 = 30,
    VAR_TYPE_UNKNOWN_45 = 45, // Inferred role: billboard def; original name unknown.
    VAR_TYPE_UNKNOWN_46 = 46, // Inferred role: billboard y vec; original name unknown.
    VAR_TYPE_UNKNOWN_50 = 50, // Inferred role: nom projection mat; original name unknown.
    VAR_TYPE_UNKNOWN_51 = 51,
    VAR_TYPE_UNKNOWN_58 = 58,
    VAR_TYPE_UNKNOWN_59 = 59,
    VAR_TYPE_UNKNOWN_62 = 62,
    VAR_TYPE_UNKNOWN_68 = 68,
    VAR_TYPE_UNKNOWN_73 = 73,   // Inferred role: jitter; original name unknown.
    VAR_TYPE_UNKNOWN_77 = 77,   // Inferred role: light not use; original name unknown.
    VAR_TYPE_UNKNOWN_93 = 93,   // Inferred role: dither tmaa val; original name unknown.
    VAR_TYPE_UNKNOWN_115 = 115, // Inferred role: proj non jitter; original name unknown.
    VAR_TYPE_UNKNOWN_120 = 120, // Inferred role: diff pre orij mat; original name unknown.
  };

  static u32 getStaticUniformBlockSize();
  static u32 getMdlUniformBlockSize();
  static u32 getAVACharUniformBlockSize();
  static u32 getAVADollUniformBlockSize();
  static u32 getToonUniformBlockSize();
  static u32 getToon2UniformBlockSize();
  static u32 getLightUniformBlockSize();
  static u32 getVolTexCalcUniformBlockSize();
  static u32 getRimBloomCalcUniformBlockSize();
  static u32 getMpfMaterialUniformBlockSize();
  static int getValWork(int type, int count);

  static const s16 s_nVarSizeTbl[]; // Name from the game symbol _ZN2ml20DrResMdoUniformBlock13s_nVarSizeTblE; also in torna and xc1de.
};

} // namespace ml
