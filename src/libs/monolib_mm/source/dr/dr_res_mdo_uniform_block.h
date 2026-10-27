#pragma once
#include "types.h"

namespace ml {

class DrResMdoUniformBlock {
public:
  enum VarType {
    VAR_TYPE_VIEW = 2,
    VAR_TYPE_PROJ = 3,
    VAR_TYPE_VIEW_PROJ = 4,
    VAR_TYPE_INV_VIEW = 6,
    VAR_TYPE_VIEW_Y_VEC = 8,
    VAR_TYPE_TEX_MATRIX = 17,
    VAR_TYPE_WORK_FLOAT4 = 18,
    VAR_TYPE_WORK_COLOR = 19,
    VAR_TYPE_PROJECTION_MAT = 20,
    VAR_TYPE_UNKNOWN_25 = 25,
    VAR_TYPE_UNKNOWN_30 = 30,
    VAR_TYPE_BILLBOARD_DEF = 45,
    VAR_TYPE_BILLBOARD_Y_VEC = 46,
    VAR_TYPE_NOM_PROJECTION_MAT = 50,
    VAR_TYPE_UNKNOWN_58 = 58,
    VAR_TYPE_JITTER = 73,
    VAR_TYPE_LIGHT_NOT_USE = 77,
    VAR_TYPE_DITHER_TMAA_VAL = 93,
    VAR_TYPE_PROJ_NON_JITTER = 115,
    VAR_TYPE_DIFF_PRE_ORIJ_MAT = 120,
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
