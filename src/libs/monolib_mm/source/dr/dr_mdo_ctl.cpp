#include "dr/dr_mdo_ctl.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_shd_mdo_dec_ext_tbl.h"
#include "dr/dr_shd_mdo_ext_tbl_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class DrShdDataList;

inline void DrMdoCtl::unknown004(int index) { unknown38 = &unknown30->unknown88->unknown08[index]; }

inline void DrMdoCtl::unknown005(const MdsMdlInfoHeader *info) {
  if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_13) {
    unknown30->unknownc8->render(info->unknown0c);
  } else {
    unknown30->unknownc8->render(info->unknown0a);
  }
}

void DrMdoCtl::bindShader(int index) {
  if (unknown17c == index) {
    unknown178 &= ~1;
    return;
  }
  unknown17c = index;
  unknown178 |= 1;
  unknown004(index);
  unknown38->bindShader();
}

u32 DrMdoCtl::getShdIdx(u32 &uniformIndex, const MdsMatShaderTbl *table, int count) {
  uniformIndex = table->unknown06;
  u32 index = table->unknown00;
  const MdsMatShaderTbl *entry = table;
  for (int i = 0; i < count; i++, entry++) {
    if (unknownf2 == entry->unknown04) {
      uniformIndex = entry->unknown06;
      return entry->unknown00;
    }
  }
  return index;
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

void DrMdoCtl::beginSeamSetup() { beginMatInfo(); }

void DrMdoCtl::changeSeamBaseMapMdlInfo() {
  changeSeamMatInfo();
  unknown30->unknownc8->beginVertexSetup();
}

DrResChkList *DrMdoCtl::stockRenderList(DrResChkList *&head, DrResChkList *prev, u32 mdlIndex) {
  DrResChkList *entry = &unknown198[unknown1a0];
  if (prev != nullptr) {
    prev->unknown02 = unknown1a0 + 1;
  }
  if (head == nullptr) {
    head = entry;
  }
  entry->unknown00 = mdlIndex;
  entry->unknown02 = 0;
  unknown1a0++;
  return entry;
}

void DrMdoCtl::partsBaseMdlRender(const MdsMdlInfoHeader *header) {
  unknown30->unknownc8->setVertexBind(header->unknown08);
  unknown30->unknownc8->render(header->unknown0a);
}

const mm::Mat44 &DrMdoCtl::getMatrix() const { return m_matrix; }

void DrMdoCtl::setMatrix(const mm::Mat44 &matrix) { m_matrix = matrix; }

void DrMdoCtl::setOffsetPos(const mm::Vec3 &position) { m_offsetPos = position; }

void DrMdoCtl::partsInstanceThicknessBillRender(const MdoInstancePrePassArg &) {}

void DrMdoCtl::partsShadowBaseRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if ((info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_2)) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        setupShadowShader(shaderList, 3, mat, 0, info->unknown0e);
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsShadowNukiBaseRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if ((info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if (mat->unknown04 & MdsMatInfoHeader::unknown015_2) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_3)) {
          setupShadowShader(shaderList, 4, mat, 0, info->unknown0e);
        } else {
          setupShadowShader(shaderList, 5, mat, 0, info->unknown0e);
        }
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsPosShadowRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  DrAPCache *apCache = m_drMan->unknown5c0;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_2) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        if (unknown168 & 0x80) {
          apCache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
        } else {
          apCache->setupCulling(static_cast<DrApCullType>(mat->unknown2a));
        }
        setupShadowShader(shaderList, 3, mat, 0, info->unknown0e);
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsPosNukiShadowRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  DrAPCache *apCache = m_drMan->unknown5c0;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if ((mat->unknown04 & MdsMatInfoHeader::unknown015_2) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17) && unknown30->unknowne8 != nullptr && mat->unknown24 != 0) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        if (unknown168 & 0x80) {
          apCache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
        } else {
          apCache->setupCulling(static_cast<DrApCullType>(mat->unknown2a));
        }
        setupShadowShader(shaderList, (mat->unknown04 & MdsMatInfoHeader::unknown015_3) ? 5 : 4, mat, 0, info->unknown0e);
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsPosNoamShadowRender(const MdsMdlTopHeader *top, grlib::CGLibVtxInstans *instans, u32 offset, u32 stride, u32 instanceCount) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  DrAPCache *apCache = m_drMan->unknown5c0;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if ((info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17) && (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14)) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      unknown30->unknownc8->setVertexBind(info->unknown08);
      apCache->setupCulling(static_cast<DrApCullType>(mat->unknown2a));
      if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_2)) {
        setupShadowShader(shaderList, 9, mat, 0, info->unknown0e);
      } else if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_3)) {
        setupShadowShader(shaderList, 10, mat, 0, info->unknown0e);
      } else {
        setupShadowShader(shaderList, 11, mat, 0, info->unknown0e);
      }
      grlib::CGLibCtlVertex::setInstanceVertex(*instans, stride, offset, 1, 1);
      if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_13) {
        unknown30->unknownc8->renderIns(info->unknown0c, instanceCount);
      } else {
        unknown30->unknownc8->renderIns(info->unknown0a, instanceCount);
      }
    }
  }
}

void DrMdoCtl::createMaterialDisplayList(u8 **table, int count, MdoWrkMatRes *matRes) {
  for (int i = 0; i < count; i++) {
    table[i] = nullptr;
  }
}

void DrMdoCtl::createMaterialOneDisplayList(MdoWrkMatRes *, int) {}

void DrMdoCtl::createInstBillPrepass(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c) + 1;
  unknown004(shader->unknown00);
  (*unknown30->unknown120_1->unknown08)[index].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
}

void DrMdoCtl::createBaseBillPrepass(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c) + 1;
  unknown004(shader->unknown00);
  (*unknown30->unknown120->unknown08)[index].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
}

void DrMdoCtl::createInstanceDefRender(const MdsMdlInfoHeader *header, grlib::CGLibVtxInstans *instans, u32 offset, u32 stride, u32 instanceCount) {
  unknown30->unknownc8->setVertexBind(header->unknown08);
  grlib::CGLibCtlVertex::setInstanceVertex(*instans, stride, offset, 1, 1);
  unknown30->unknownc8->renderIns(header->unknown0a, instanceCount);
}

void DrMdoCtl::waitWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(0x21); }

void DrMdoCtl::waitBeginWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(1); }

} // namespace ml
