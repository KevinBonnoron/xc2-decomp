#include "dr/dr_mdo_ctl.h"

#include "grlib/cglib_ctl_shader.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {

const mm::Mat44 &DrMdoCtl::getMatrix() const { return m_matrix; }

void DrMdoCtl::setMatrix(const mm::Mat44 &matrix) { m_matrix = matrix; }

void DrMdoCtl::setOffsetPos(const mm::Vec3 &position) { m_offsetPos = position; }

void DrMdoCtl::partsInstanceThicknessBillRender(const MdoInstancePrePassArg &) {}

void DrMdoCtl::createMaterialOneDisplayList(MdoWrkMatRes *, int) {}

void DrMdoCtl::waitWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(0x21); }

void DrMdoCtl::waitBeginWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(1); }

} // namespace ml
