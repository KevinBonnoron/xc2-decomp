#include "dr/dr_mdo_ctl.h"

#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_shd_mdo_dec_ext_tbl.h"
#include "dr/dr_shd_mdo_ext_tbl_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrMdoCtl::bindShader(int index) {
  if (unknown17c == index) {
    unknown178 &= ~1;
    return;
  }
  unknown17c = index;
  unknown178 |= 1;
  unknown38 = &unknown30->unknown88->unknown08[index];
  unknown38->bindShader();
}

void DrMdoCtl::updateMdl() {
  if (unknown168 & 8) {
    unknownfc |= 0x4000000;
  } else {
    unknownfc &= ~0x4000000;
  }
  unknownf8 = 0;
  unknown168 = 0;
  updateMdlPos();
}

void DrMdoCtl::beginSetup() {
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
}

void DrMdoCtl::partsBaseMdlRender(const MdsMdlInfoHeader *header) {
  unknown30->unknownc8->setVertexBind(header->unknown08);
  unknown30->unknownc8->render(header->unknown0a);
}

const mm::Mat44 &DrMdoCtl::getMatrix() const { return m_matrix; }

void DrMdoCtl::setMatrix(const mm::Mat44 &matrix) { m_matrix = matrix; }

void DrMdoCtl::setOffsetPos(const mm::Vec3 &position) { m_offsetPos = position; }

void DrMdoCtl::partsInstanceThicknessBillRender(const MdoInstancePrePassArg &) {}

void DrMdoCtl::createMaterialOneDisplayList(MdoWrkMatRes *, int) {}

void DrMdoCtl::waitWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(0x21); }

void DrMdoCtl::waitBeginWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(1); }

} // namespace ml
