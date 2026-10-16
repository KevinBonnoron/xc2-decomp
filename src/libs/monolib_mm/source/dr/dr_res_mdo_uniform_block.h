#pragma once
#include "types.h"

namespace ml {

class DrResMdoUniformBlock {
public:
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
