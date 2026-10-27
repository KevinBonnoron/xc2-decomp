#include "grlib/cglib_dbl_uniform_block.h"
#include "ptlib/emitter/compute/particle_emitter_compute.h"
#include "types.h"

namespace ptlib {
namespace emitter {

int ComputeUniform::s_nUniformBlockSize[5] = {32, 512, 496, 560, 560};

ComputeUniform::ComputeUniform() {}

ComputeUniform::~ComputeUniform() { unknown08.release(); }

void ComputeUniform::releaseUniform() { unknown08.release(); }

void ComputeUniform::createUniform(u32 type, u32 count) {
  unknown00 = type;
  unknown08.release();
  unknown08.setup(s_nUniformBlockSize[unknown00] * count);
}

void ComputeUniform::updateData(u32 offset, u32 size) { unknown08.updateData(offset, size); }

void ComputeUniform::updateData() { unknown08.updateData(); }

} // namespace emitter
} // namespace ptlib
