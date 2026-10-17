#pragma once
#include "types.h"

namespace ml {

class DrResMdoUniformBlock {
public:
  enum VarType {
    VAR_TYPE_TEX_MATRIX = 17,
    VAR_TYPE_WORK_FLOAT4 = 18,
    VAR_TYPE_WORK_COLOR = 19,
    VAR_TYPE_PROJECTION_MAT = 20,
    VAR_TYPE_NOM_PROJECTION_MAT = 50,
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

  static const s16 s_nVarSizeTbl[];
};

} // namespace ml
