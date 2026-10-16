#include "dr/dr_res_mdo_uniform_block.h"

namespace ml {

u32 DrResMdoUniformBlock::getStaticUniformBlockSize() { return 0x290; }

u32 DrResMdoUniformBlock::getMdlUniformBlockSize() { return 0xf0; }

u32 DrResMdoUniformBlock::getAVACharUniformBlockSize() { return 0xe0; }

u32 DrResMdoUniformBlock::getAVADollUniformBlockSize() { return 0x100; }

u32 DrResMdoUniformBlock::getToonUniformBlockSize() { return 0x70; }

u32 DrResMdoUniformBlock::getToon2UniformBlockSize() { return 0x40; }

u32 DrResMdoUniformBlock::getLightUniformBlockSize() { return 0x130; }

u32 DrResMdoUniformBlock::getVolTexCalcUniformBlockSize() { return 0xa0; }

u32 DrResMdoUniformBlock::getRimBloomCalcUniformBlockSize() { return 0x20; }

u32 DrResMdoUniformBlock::getMpfMaterialUniformBlockSize() { return 0x30; }

int DrResMdoUniformBlock::getValWork(int type, int count) { return s_nVarSizeTbl[type] * (count == 0 ? 1 : count) * 4; }

} // namespace ml
