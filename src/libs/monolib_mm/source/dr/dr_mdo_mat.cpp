#include "dr/dr_mdo_mat.h"

#include <math.h>
#include <new>
#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_sampler_man.h"
#include "dr/dr_mdo_shd_set.h"
#include "dr/dr_mdo_texture_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_mpf_sampler.h"
#include "dr/dr_res_query_acc.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_shd_mdo_dec_shd_obj.h"
#include "dr/dr_shd_mdo_man.h"
#include "dr/dr_shd_uniform_block_man.h"
#include "grlib/cglib_dbl_uniform_block.h" // IWYU pragma: keep
#include "grlib/cglib_one_uniform_block.h" // IWYU pragma: keep
#include "grlib/cglib_tri_uniform_block.h" // IWYU pragma: keep
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

const f32 DrMdoMat::MDL_SCALE_PARAMS = 0.57735055f;

void DrMdoMat::initMdlInfo(const u8 *data, MdoWrkMatRes *matRes) {
  const unknown022 *header = reinterpret_cast<const unknown022 *>(data);
  matRes->unknown18 = data;
  matRes->unknown20 = header;
  matRes->unknown170 = header->unknown20;
  matRes->m_mdsMdlTopHeader = reinterpret_cast<const MdsMdlTopHeader *>(data + header->unknown1c);
  if (header->unknown34 != 0) {
    matRes->unknown178 = data + header->unknown30;
  }
}

int DrMdoMat::getNodeAnmWrkRes(const u8 *data, u8 *work, MdoWrkMatRes *matRes) {
  const unknown022 *header = reinterpret_cast<const unknown022 *>(data);
  if (!(header->unknown00 & unknown022::FLAG_UNKNOWN_3)) {
    return 0;
  }
  if (work != nullptr) {
    const unknown701 *table = reinterpret_cast<const unknown701 *>(data + header->unknown78);
    unknown702 *nodeAnm = reinterpret_cast<unknown702 *>(work);
    u32 dataOffset = table->unknown04;
    nodeAnm->unknown00 = table;
    nodeAnm->unknown08 = table;
    nodeAnm->unknown10 = table->unknown00;
    nodeAnm->unknown18 = reinterpret_cast<const u8 *>(table) + dataOffset;
    matRes->unknown148 = nodeAnm;
  }
  return sizeof(unknown702);
}

void DrMdoMat::resetNodeAnmWrkRes(const u8 *data, MdoWrkMatRes *matRes) {
  const unknown022 *header = reinterpret_cast<const unknown022 *>(data);
  if (header->unknown00 & unknown022::FLAG_UNKNOWN_3) {
    const unknown701 *table = reinterpret_cast<const unknown701 *>(data + header->unknown78);
    matRes->unknown148->unknown00 = table;
    matRes->unknown148->unknown08 = table;
    matRes->unknown148->unknown18 = reinterpret_cast<const u8 *>(table) + table->unknown04;
  }
}

void DrMdoMat::resetBillMdlInfo(MdoWrkMatRes *matRes, const u8 *data, bool isInstance) {
  const unknown022 *header = reinterpret_cast<const unknown022 *>(data);
  if (header->unknown00 & (unknown022::FLAG_UNKNOWN_1 | unknown022::FLAG_UNKNOWN_2)) {
    const unknown714 *table = reinterpret_cast<const unknown714 *>(data + header->unknown74);
    if (header->unknown00 & unknown022::FLAG_UNKNOWN_1) {
      matRes->unknown120->unknown18 = reinterpret_cast<const unknown719 *>(data + table->unknown00);
      matRes->unknown120->unknown20 = reinterpret_cast<const unknown720 *>(data + table->unknown08);
    }
    if (header->unknown00 & unknown022::FLAG_UNKNOWN_2) {
      if (isInstance) {
        matRes->unknown160_1->unknown08 = data + table->unknown10;
        return;
      }
      matRes->unknown160->unknown10 = data + table->unknown10;
    }
  }
}

void DrMdoMat::resetMpfMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *vertexData, const u8 *mdlData, const u8 *texData) {
  matRes->unknown10 = matData;
  matRes->unknown08 = texData;
  matRes->unknown00 = vertexData;
  matRes->unknown28 = reinterpret_cast<const MdsMatInfoHeader *>(matData + reinterpret_cast<const MdsMatTopHeader *>(matData)->unknown00);
  if (matRes->unknownf0 != 0) {
    matRes->m_drResMdoTexList->changeMemTexList(texData);
  }
  initMdlInfo(mdlData, matRes);
  if (matRes->unknown00 != nullptr && matRes->m_drResMdoVertex != nullptr) {
    matRes->m_drResMdoVertex->changeMemVertex(matRes->unknown00);
  }
}

void DrMdoMat::resetBaseMapMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *mdlData, const u8 *vertexData, const u8 *shaderData, const u8 *texData, int skipTexList) {
  const MdsMatTopHeader *header = reinterpret_cast<const MdsMatTopHeader *>(matData);
  const MdsMatTechnique *techniques = reinterpret_cast<const MdsMatTechnique *>(matData + header->unknown28);
  initMdlInfo(mdlData, matRes);
  matRes->unknown10 = matData;
  matRes->unknown08 = texData;
  matRes->unknown00 = vertexData;
  matRes->m_mdsMatTechnique = techniques;
  matRes->unknown78 = matData;
  matRes->unknown28 = reinterpret_cast<const MdsMatInfoHeader *>(matData + header->unknown00);
  if (header->unknown20 != 0) {
    matRes->unknown40 = reinterpret_cast<const unknown010 *>(matData + header->unknown20);
  }
  DrResMdoMat *names = matRes->m_materialRes;
  const MdsMatInfoHeader *infos = matRes->unknown28;
  for (int i = 0; i < matRes->unknown30; i++) {
    names->setName(reinterpret_cast<const char *>(matRes->unknown10 + infos->unknown00));
    names++;
    infos++;
  }
  if (header->unknown14 != 0) {
    matRes->unknown38 = reinterpret_cast<const f32 *>(matRes->unknown10 + header->unknown10);
  }
  if (header->unknown34 != 0) {
    matRes->unknown128->unknown00 = matData + header->unknown34;
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_1) {
    resetDispCallRes(matData, header->unknown4c, matRes);
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_2) {
    resetFurShaderRes(matData, header->unknown50, matRes);
  }
  resetNodeAnmWrkRes(mdlData, matRes);
  resetBillMdlInfo(matRes, mdlData, false);
  if (skipTexList == 0 && matRes->unknownf0 != 0) {
    matRes->m_drResMdoTexList->changeMemTexList(matRes->unknown08);
  }
  if (matRes->unknown00 != nullptr && matRes->m_drResMdoVertex != nullptr) {
    matRes->m_drResMdoVertex->changeMemVertex(matRes->unknown00);
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_3) {
    matRes->unknown48 = matData + reinterpret_cast<const unknown718 *>(matData + header->unknown54)->unknown00;
  }
  matRes->m_drShdMdoDecShdObj->changeMemShader(shaderData, matData, techniques);
}

void DrMdoMat::resetInstMapMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *mdlData, const u8 *shaderData, const u8 *texData, int skipTexList) {
  const MdsMatTopHeader *header = reinterpret_cast<const MdsMatTopHeader *>(matData);
  const MdsMatTechnique *techniques = reinterpret_cast<const MdsMatTechnique *>(matData + header->unknown28);
  initMdlInfo(mdlData, matRes);
  matRes->unknown08 = texData;
  matRes->unknown10 = matData;
  matRes->m_mdsMatTechnique = techniques;
  matRes->unknown78 = matData;
  matRes->unknown28 = reinterpret_cast<const MdsMatInfoHeader *>(matData + header->unknown00);
  if (header->unknown20 != 0) {
    matRes->unknown40 = reinterpret_cast<const unknown010 *>(matData + header->unknown20);
  }
  DrResMdoMat *names = matRes->m_materialRes;
  const MdsMatInfoHeader *infos = matRes->unknown28;
  for (int i = 0; i < matRes->unknown30; i++) {
    names->setName(reinterpret_cast<const char *>(matRes->unknown10 + infos->unknown00));
    names++;
    infos++;
  }
  if (header->unknown14 != 0) {
    matRes->unknown38 = reinterpret_cast<const f32 *>(matRes->unknown10 + header->unknown10);
  }
  if (header->unknown34 != 0) {
    matRes->unknown128->unknown00 = matData + header->unknown34;
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_1) {
    resetDispCallRes(matData, header->unknown4c, matRes);
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_2) {
    resetFurShaderRes(matData, header->unknown50, matRes);
  }
  resetNodeAnmWrkRes(mdlData, matRes);
  resetBillMdlInfo(matRes, mdlData, true);
  if (skipTexList == 0 && matRes->unknownf0 != 0) {
    matRes->m_drResMdoTexList->changeMemTexList(matRes->unknown08);
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_3) {
    matRes->unknown48 = matData + reinterpret_cast<const unknown718 *>(matData + header->unknown54)->unknown00;
  }
  if (matRes->m_drShdMdoDecShdObj != nullptr) {
    matRes->m_drShdMdoDecShdObj->changeMemShader(shaderData, matData, techniques);
  }
}

int DrMdoMat::getDispCallRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes) {
  const unknown704 *table = reinterpret_cast<const unknown704 *>(data + offset);
  if (work != nullptr) {
    unknown703 *dispCall = reinterpret_cast<unknown703 *>(work);
    dispCall->unknown00 = table->unknown00;
    dispCall->m_mdsMatDispCCData = reinterpret_cast<const MdsMatDispCCData *>(data + table->unknown04);
    dispCall->m_mdoWrkDispCallTemp = reinterpret_cast<_MdoWrkDispCallTemp *>(work + sizeof(unknown703));
    memset(dispCall->m_mdoWrkDispCallTemp, 0, static_cast<u64>(table->unknown00) * 8);
    matRes->unknown130 = dispCall;
  }
  return table->unknown00 * 8 + sizeof(unknown703);
}

void DrMdoMat::resetDispCallRes(const u8 *data, u32 offset, MdoWrkMatRes *matRes) {
  const unknown704 *table = reinterpret_cast<const unknown704 *>(data + offset);
  matRes->unknown130->m_mdsMatDispCCData = reinterpret_cast<const MdsMatDispCCData *>(data + table->unknown04);
}

// One allocation holds the work (0x180 bytes), the texture table, the material bit table, the uniform array and the samplers, each part aligned to 32 bytes (0x71007f8388).
// The game computes the sizes twice: once for the allocation and once to place the parts. The allocation size is a signed int (sxtw), hence the int sampler count.
void DrMdoMat::initMpfMaterial(const u8 *matData, const u8 *vertexData, const u8 *mdlData, const u8 *texData, bool isStm) {
  const MdsMpfMatTopHeader *header = reinterpret_cast<const MdsMpfMatTopHeader *>(matData);
  int texCount = 0;
  int size = 0x180;
  if (texData != nullptr) {
    texCount = DrResMdoTexList::calcTextureMax(texData);
    size = texCount * 8 + 0x180;
  }
  size += (32 - size % 32) % 32;
  size += (header->unknown04 / 32 + 1) * 4;
  size += (32 - size % 32) % 32;
  if (header->unknown14 != 0) {
    size += 0x28;
  }
  int samplerCount = header->unknown04;
  if (samplerCount == 0) {
    samplerCount = reinterpret_cast<const unknown022 *>(mdlData)->unknown20;
  }
  void *block = mtl::MemManager::allocate(m_drMan->unknown14, size + samplerCount * 0x20, 0x10, false, "no name", 0);
  u8 *work = static_cast<u8 *>(block);
  unknown30 = static_cast<MdoWrkMatRes *>(block);
  memset(unknown30, 0, sizeof(MdoWrkMatRes));
  unknown30->unknown10 = matData;
  unknown30->unknown00 = vertexData;
  unknown30->unknown08 = texData;
  unknown30->unknownf0 = texCount;
  unknown30->unknown30 = header->unknown04;
  unknown30->unknown34 = header->unknown0c;
  unknown30->unknown28_1 = reinterpret_cast<const MdsMpfMatInfoHeader *>(matData + header->unknown00);
  size = sizeof(MdoWrkMatRes);
  if (unknown30->unknownf0 != 0) {
    unknown30->unknowne8 = static_cast<grlib::CGLibTextureBuffer **>(static_cast<void *>(work + sizeof(MdoWrkMatRes)));
    size = unknown30->unknownf0 * 8 + sizeof(MdoWrkMatRes);
    if (isStm) {
      unknown30->m_drResMdoTexList = new (m_drMan->unknown10) DrResMdoTexList(unknown30->unknown08);
      for (s32 i = 0; i < unknown30->m_drResMdoTexList->unknown68; i++) {
        unknown30->unknowne8[i] = unknown30->m_drResMdoTexList->getTexObj(i);
      }
    } else {
      for (s32 i = 0; i < unknown30->unknownf0; i++) {
        unknown30->unknowne8[i] = m_drMan->m_drPixlMan->getDammyTexObj();
      }
    }
  }
  size += (32 - size % 32) % 32;
  unknown30->unknown108 = static_cast<u32 *>(static_cast<void *>(work + size));
  size += (header->unknown04 / 32 + 1) * 4;
  size += (32 - size % 32) % 32;
  if (header->unknown14 != 0) {
    unknown30->unknown90 = static_cast<grlib::CGLibDblUniformArray *>(static_cast<void *>(work + size));
    size += 0x28;
    DrShdUniformBlockMan::createUniformMpfMaterialObj(unknown30->unknown90, header);
  }
  if (samplerCount != 0) {
    unknown30->m_drResMpfSampler = static_cast<DrResMpfSampler *>(static_cast<void *>(work + size));
    for (u32 i = 0; i < samplerCount; i++) {
      // Ruling 2: the game loads the material info pointer before the sampler address (0x71007f86b4); inline the call form puts the sampler address first.
      const MdsMpfMatInfoHeader *info = &unknown30->unknown28_1[i];
      new (&unknown30->m_drResMpfSampler[i]) DrResMpfSampler(info);
    }
  }
  initMdlInfo(mdlData, unknown30);
  if (isStm) {
    unknown30->m_drResMdoVertex = new (m_drMan->unknown10) DrResMdoVertex(unknown30->unknown00);
  }
}

void DrMdoMat::oneTextureStream() {
  if ((unknownfc & (unknown027_0 | unknown027_1)) != (unknown027_0 | unknown027_1)) {
    return;
  }
  if (unknown30->m_drResMdoTexList == nullptr) {
    return;
  }
  if (((static_cast<f32>(unknownec) / static_cast<f32>(m_drMan->unknown5b8->unknown30) >= 0.01f && unknowne4 >= 0.1f) || (unknownfc & unknown027_2)) && !m_drMan->m_mdlHeightTexSkip &&
      !m_drMan->m_heightTexSkip) {
    unknown30->m_drResMdoTexList->callStmRead(2);
  } else if (0.007f <= unknowne4 || (unknownfc & unknown027_17)) {
    unknown30->m_drResMdoTexList->callStmRead(1);
  }
  u32 state = unknown30->m_drResMdoTexList->unknown70;
  if (!(state & 1)) {
    if ((state & 2) && !(unknownfc & unknown027_5)) {
      unknownfc |= unknown027_5;
      for (s32 i = 0; i < unknown30->m_drResMdoTexList->unknown68; i++) {
        unknown30->unknowne8[i] = unknown30->m_drResMdoTexList->getStmTexObj(i);
      }
      m_disp &= ~0x60;
    }
  } else if (unknownfc & unknown027_5) {
    unknownfc &= ~unknown027_5;
    if (unknown30->m_drResMdoTexList != nullptr) {
      for (s32 i = 0; i < unknown30->m_drResMdoTexList->unknown68; i++) {
        unknown30->unknowne8[i] = unknown30->m_drResMdoTexList->getTexObj(i);
      }
      m_disp &= ~0x60;
    }
  }
  if (!(state & 4)) {
    if (unknownfc & unknown027_13) {
      unknownfc &= ~unknown027_13;
      m_disp &= ~0x60;
    }
  } else if (!(unknownfc & unknown027_13)) {
    unknownfc |= unknown027_13;
    m_disp &= ~0x60;
  }
}

void DrMdoMat::updateMatFstCallBack() {
  const unknown010 *callBack = unknown30->unknown40;
  if (callBack == nullptr) {
    return;
  }
  s32 count = callBack->unknown14;
  if (count == 0) {
    return;
  }
  const unknown011 *calls = reinterpret_cast<const unknown011 *>(unknown30->unknown10 + callBack->unknown00);
  const unknown012 *entry = reinterpret_cast<const unknown012 *>(unknown30->unknown10 + callBack->unknown10);
  for (s32 i = 0; i < count; i++, entry++) {
    const MdsMatInfoHeader *header = &unknown30->unknown28[entry->unknown00];
    u32 num = entry->unknown04;
    if (num != 0) {
      const unknown011 *call = &calls[entry->unknown06];
      for (u32 j = 0; j < num; j++, call++) {
        (this->*s_pCallFstMatVal[call->unknown00])(header, call->unknown02, entry->unknown00);
      }
    }
  }
}

void DrMdoMat::updateMatCallBack(const u32 *flags) {
  const unknown010 *callBack = unknown30->unknown40;
  if (callBack == nullptr) {
    return;
  }
  s32 count = callBack->unknown0c;
  if (count == 0) {
    return;
  }
  const unknown011 *calls = reinterpret_cast<const unknown011 *>(unknown30->unknown10 + callBack->unknown00);
  const u16 *matIndices = reinterpret_cast<const u16 *>(unknown30->unknown10 + callBack->unknown08);
  for (s32 i = 0; i < count; i++) {
    u16 matIndex = matIndices[i];
    if (flags[matIndex >> 5] & (1 << (matIndex & 31))) {
      const MdsMatInfoHeader *header = &unknown30->unknown28[matIndex];
      u32 num = header->unknown5a;
      if (num != 0) {
        const unknown011 *call = &calls[unknown30->unknown28[matIndex].unknown58];
        for (u32 j = 0; j < num; j++, call++) {
          (this->*s_pCallMatVal[call->unknown00])(header, call->unknown02, matIndices[i]);
        }
      }
    }
  }
}

void DrMdoMat::updateDispCall() {
  unknown703 *dispCall = unknown30->unknown130;
  if (dispCall != nullptr && dispCall->unknown00 > 0) {
    _MdoWrkDispCallTemp *temp = dispCall->m_mdoWrkDispCallTemp;
    const MdsMatDispCCData *data = dispCall->m_mdsMatDispCCData;
    for (s32 i = 0; i < dispCall->unknown00; i++, data++, temp++) {
      if (checkCallBackParam(temp, data)) {
        m_disp &= ~0x60;
      }
    }
  }
}

bool DrMdoMat::updateDispEnvCall(MdoWrkMatRes *matRes) {
  unknown703 *dispCall = matRes->unknown130;
  if (dispCall == nullptr || dispCall->unknown00 < 1) {
    return false;
  }
  _MdoWrkDispCallTemp *temp = dispCall->m_mdoWrkDispCallTemp;
  const MdsMatDispCCData *data = dispCall->m_mdsMatDispCCData;
  s32 i = 0;
  u8 result = 0;
  do {
    result = checkCallBackParam(temp, data) | result;
    i++;
    data++;
    temp++;
  } while (i < dispCall->unknown00);
  return result != 0;
}

void DrMdoMat::updateSeamDispCall(MdoWrkMatRes *matRes, u32 *flags, const u32 *seamFlags) {
  unknown703 *dispCall = matRes->unknown130;
  if (dispCall != nullptr && dispCall->unknown00 > 0) {
    _MdoWrkDispCallTemp *temp = dispCall->m_mdoWrkDispCallTemp;
    const MdsMatDispCCData *data = dispCall->m_mdsMatDispCCData;
    for (s32 i = 0; i < dispCall->unknown00; i++, data++, temp++) {
      if ((seamFlags[data->unknown04 >> 5] & (1 << (data->unknown04 & 31))) && checkCallBackParam(temp, data)) {
        flags[data->unknown04 >> 4] |= 1 << ((data->unknown04 & 0xf) << 1);
        flags[data->unknown04 >> 4] |= 1 << (((data->unknown04 & 0xf) << 1) | 1);
      }
    }
  }
}

int DrMdoMat::getFurShaderRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes) {
  const unknown008 *table = reinterpret_cast<const unknown008 *>(data + offset);
  if (work != nullptr) {
    unknown007 *furShader = reinterpret_cast<unknown007 *>(work);
    furShader->unknown08 = reinterpret_cast<const unknown005 *>(data + table->unknown04);
    const u16 *first = reinterpret_cast<const u16 *>(data + table->unknown00);
    furShader->unknown10 = reinterpret_cast<unknown006 *>(work + sizeof(unknown007));
    furShader->unknown00 = first;
    for (int i = 0; i < table->unknown08; i++) {
      furShader->unknown10[i].unknown00 = furShader->unknown08[i].unknown00;
      furShader->unknown10[i].unknown04 = furShader->unknown08[i].unknown00;
      furShader->unknown10[i].unknown08 = furShader->unknown08[i].unknown04;
      furShader->unknown10[i].unknown0c = furShader->unknown08[i].unknown08;
      furShader->unknown10[i].unknown10 = furShader->unknown08[i].unknown0c;
      furShader->unknown10[i].unknown14 = furShader->unknown08[i].unknown10;
    }
    matRes->unknown138 = furShader;
  }
  return table->unknown08 * sizeof(unknown006) + 0x18;
}

void DrMdoMat::resetFurShaderRes(const u8 *data, u32 offset, MdoWrkMatRes *matRes) {
  const unknown008 *table = reinterpret_cast<const unknown008 *>(data + offset);
  matRes->unknown138->unknown08 = reinterpret_cast<const unknown005 *>(data + table->unknown04);
  matRes->unknown138->unknown00 = reinterpret_cast<const u16 *>(data + table->unknown00);
}

void DrMdoMat::releaseBaseMapSeamMat(MdoWrkMatRes *matRes) {
  if (matRes->m_drResMdoVertex != nullptr) {
    delete matRes->m_drResMdoVertex;
    matRes->m_drResMdoVertex = nullptr;
  }
  if (matRes->m_drResMdoTexList != nullptr) {
    delete matRes->m_drResMdoTexList;
    matRes->m_drResMdoTexList = nullptr;
  }
  matRes->unknowne8 = nullptr;
  if (matRes->m_drResMdoSampler != nullptr) {
    m_drMan->m_drMdlMan->m_drMdoSamplerMan->releaseSamplerSeamObj(matRes->m_drResMdoSampler);
    matRes->m_drResMdoSampler = nullptr;
  }
  if (matRes->m_drShdMdoDecShdObj != nullptr) {
    delete matRes->m_drShdMdoDecShdObj;
    matRes->m_drShdMdoDecShdObj = nullptr;
  }
  matRes->m_drShdMdoExtTblObj = nullptr;
  if (matRes->unknown90 != nullptr) {
    matRes->unknown90->unknown001();
    matRes->unknown90 = nullptr;
  }
  if (matRes->unknownb0 != nullptr) {
    matRes->unknownb0->unknown001();
    matRes->unknownb0 = nullptr;
  }
  if (matRes->unknownb8 != nullptr) {
    matRes->unknownb8->unknown001();
    matRes->unknownb8 = nullptr;
  }
  if (matRes->unknown120 != nullptr && matRes->unknown120->unknown08 != nullptr) {
    matRes->unknown120->unknown08->unknown001();
    matRes->unknown120->unknown08 = nullptr;
  }
}

void DrMdoMat::releaseInstMapSeamMat(MdoWrkMatRes *matRes) {
  if (matRes->m_drResMdoTexList != nullptr) {
    delete matRes->m_drResMdoTexList;
    matRes->m_drResMdoTexList = nullptr;
  }
  matRes->unknowne8 = nullptr;
  if (matRes->m_drResMdoSampler != nullptr) {
    m_drMan->m_drMdlMan->m_drMdoSamplerMan->releaseSamplerSeamObj(matRes->m_drResMdoSampler);
    matRes->m_drResMdoSampler = nullptr;
  }
  if (matRes->m_drShdMdoDecShdObj != nullptr) {
    delete matRes->m_drShdMdoDecShdObj;
    matRes->m_drShdMdoDecShdObj = nullptr;
  }
  matRes->m_drShdMdoExtTblObj = nullptr;
  if (matRes->unknown90 != nullptr) {
    matRes->unknown90->unknown001();
    matRes->unknown90 = nullptr;
  }
  if (matRes->unknownb0 != nullptr) {
    matRes->unknownb0->unknown001();
    matRes->unknownb0 = nullptr;
  }
  if (matRes->unknownb8 != nullptr) {
    matRes->unknownb8->unknown001();
    matRes->unknownb8 = nullptr;
  }
  if (matRes->unknown120_1 != nullptr && matRes->unknown120_1->unknown08 != nullptr) {
    matRes->unknown120_1->unknown08->unknown001();
    matRes->unknown120_1->unknown08 = nullptr;
  }
}

void DrMdoMat::releaseMpfMapSeamMat(MdoWrkMatRes *matRes) {
  if (matRes->m_drResMdoVertex != nullptr) {
    delete matRes->m_drResMdoVertex;
    matRes->m_drResMdoVertex = nullptr;
  }
  if (matRes->m_drResMpfSampler != nullptr) {
    for (u32 i = 0; i < matRes->unknown30; i++) {
      matRes->m_drResMpfSampler[i].~DrResMpfSampler();
    }
    matRes->m_drResMpfSampler = nullptr;
  }
  if (matRes->m_drResMdoSampler != nullptr) {
    m_drMan->m_drMdlMan->m_drMdoSamplerMan->releaseSamplerSeamObj(matRes->m_drResMdoSampler);
    matRes->m_drResMdoSampler = nullptr;
  }
  if (matRes->m_drResMdoTexList != nullptr) {
    delete matRes->m_drResMdoTexList;
    matRes->m_drResMdoTexList = nullptr;
  }
  if (matRes->unknown90 != nullptr) {
    matRes->unknown90->unknown001();
    matRes->unknown90 = nullptr;
  }
  matRes->unknowne8 = nullptr;
}

void DrMdoMat::matCall_BaseColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  DrResMdoMat *mat = &unknown30->m_materialRes[matIndex];
  mat->unknown08.r = unknown30->unknown118->unknown00[valueIndex].r;
  mat->unknown08.g = unknown30->unknown118->unknown00[valueIndex].g;
  mat->unknown08.b = unknown30->unknown118->unknown00[valueIndex].b;
}

void DrMdoMat::matCall_BaseVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  DrResMdoMat *mat = &unknown30->m_materialRes[matIndex];
  mat->unknown08.r = unknown30->unknown118->unknown30[valueIndex];
  mat->unknown08.g = unknown30->unknown118->unknown30[valueIndex];
  mat->unknown08.b = unknown30->unknown118->unknown30[valueIndex];
}

void DrMdoMat::matCall_TransVal(const MdsMatInfoHeader *, int valueIndex, int matIndex) { unknown30->m_materialRes[matIndex].setAlpha(unknown30->unknown118->unknown30[valueIndex]); }

void DrMdoMat::matCall_CalcColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  unknown30->m_materialRes[matIndex].setColor(header->unknown0c * m_bloom, m_bloom * header->unknown10, m_bloom * header->unknown14, header->unknown18);
}

void DrMdoMat::matCall_OutLineVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40 + valueIndex;
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  f32 rangeEnd = postParm->unknown2cc;
  f32 rangeStart = postParm->unknown2d0;
  f32 rangeMax = rangeEnd > rangeStart ? rangeEnd : rangeStart;
  f32 range = fmaxf(rangeMax - rangeStart, 0.01f);
  f32 ratio = (unknowne4 - rangeStart) / range;
  ratio = mm::clamp(ratio, 0.0f, 1.0f);
  values[offset] = postParm->unknown2c4 * ratio;
}

void DrMdoMat::setDrMan(DrMan *drMan) { m_drMan = drMan; }

void DrMdoMat::updateAlphaCall() {
  if (unknown100 & unknown029_18) {
    unknown100 &= ~(unknown029_16 | unknown029_16 << 1);
    return;
  }
  int index = DrMan::s_nDblIdx;
  u32 flag = unknown029_16 << index;
  if (unknown100 & flag) {
    unknown100 &= ~flag;
    unknowne0 = unknownd0[index];
  }
}

bool DrMdoMat::isBloomMdl() const { return (unknownf8 & unknown028_15) != 0; }

bool DrMdoMat::isAlphaBloomMdl() const { return (unknownf8 & unknown028_16) != 0; }

u32 DrMdoMat::getVanishEffectMax() const {
  if (unknown30 == nullptr) {
    return 0;
  }
  const unknown022 *header = unknown30->unknown20;
  if (header == nullptr) {
    return 0;
  }
  if (!(header->unknown00 & unknown022::FLAG_UNKNOWN_13)) {
    return 0;
  }
  return header->unknown94 > 1 ? header->unknown94 : 1;
}

bool DrMdoMat::isFullScreenShadowMdl() const { return (unknownf8 & unknown028_18) != 0; }

MdoWrkVanishEffect *DrMdoMat::getVanishEffectWrk(u32 index, u32 bufferIndex) {
  if (unknown30 == nullptr) {
    return nullptr;
  }
  if (unknown30->unknown20 == nullptr) {
    return nullptr;
  }
  if (unknown30->m_mdoWrkVanishEffect == nullptr) {
    return nullptr;
  }
  return &unknown30->m_mdoWrkVanishEffect[index * 3 + bufferIndex];
}

bool DrMdoMat::isVolumeMdl() const { return (unknownf8 & unknown028_17) != 0; }

void DrMdoMat::setFlagWaveOn(bool isOn) {
  if (isOn) {
    unknownfc |= unknown027_6;
  } else {
    unknownfc &= ~unknown027_6;
  }
}

void DrMdoMat::setExtraShaderSetup(const void *shader) {}

void DrMdoMat::releaseExtraShader() {}

void DrMdoMat::matCall_EmissiveTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  const f32 *time = &values[header->unknown64 + offset];
  *value = *baseValue * *time;
}

void DrMdoMat::matCall_RgbTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  const f32 *time = &values[header->unknown64 + offset];
  value[0] = baseValue[0] * *time;
  value[1] = baseValue[1] * *time;
  value[2] = baseValue[2] * *time;
}

void DrMdoMat::matCall_RTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  const f32 *time = &values[header->unknown64 + offset];
  *value = *baseValue * *time;
}

void DrMdoMat::matCall_AccRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[0].r;
  value[1] = unknown30->unknown118->unknown00[0].g;
  value[2] = unknown30->unknown118->unknown00[0].b;
}

void DrMdoMat::matCall_AccRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[1].r;
  value[1] = unknown30->unknown118->unknown00[1].g;
  value[2] = unknown30->unknown118->unknown00[1].b;
}

void DrMdoMat::matCall_AccRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[2].r;
  value[1] = unknown30->unknown118->unknown00[2].g;
  value[2] = unknown30->unknown118->unknown00[2].b;
}

void DrMdoMat::matCall_AccRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[3].r;
  value[1] = unknown30->unknown118->unknown00[3].g;
  value[2] = unknown30->unknown118->unknown00[3].b;
}

void DrMdoMat::matCall_AccMulRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[0].r * value[0];
  value[1] = unknown30->unknown118->unknown00[0].g * value[1];
  value[2] = unknown30->unknown118->unknown00[0].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[1].r * value[0];
  value[1] = unknown30->unknown118->unknown00[1].g * value[1];
  value[2] = unknown30->unknown118->unknown00[1].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[2].r * value[0];
  value[1] = unknown30->unknown118->unknown00[2].g * value[1];
  value[2] = unknown30->unknown118->unknown00[2].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[3].r * value[0];
  value[1] = unknown30->unknown118->unknown00[3].g * value[1];
  value[2] = unknown30->unknown118->unknown00[3].b * value[2];
}

void DrMdoMat::matCall_AccVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[0];
}

void DrMdoMat::matCall_AccVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[1];
}

void DrMdoMat::matCall_AccVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[2];
}

void DrMdoMat::matCall_AccVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[3];
}

void DrMdoMat::matCall_AccMulVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[0] * value[0];
  value[1] = unknown30->unknown118->unknown30[0] * value[1];
  value[2] = unknown30->unknown118->unknown30[0] * value[2];
}

void DrMdoMat::matCall_AccMulVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[1] * value[0];
  value[1] = unknown30->unknown118->unknown30[1] * value[1];
  value[2] = unknown30->unknown118->unknown30[1] * value[2];
}

void DrMdoMat::matCall_AccMulVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[2] * value[0];
  value[1] = unknown30->unknown118->unknown30[2] * value[1];
  value[2] = unknown30->unknown118->unknown30[2] * value[2];
}

void DrMdoMat::matCall_AccMulVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[3] * value[0];
  value[1] = unknown30->unknown118->unknown30[3] * value[1];
  value[2] = unknown30->unknown118->unknown30[3] * value[2];
}

void DrMdoMat::matCall_WaterFog(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  const f32 *baseValue = unknown30->unknown38 + (header->unknown40 + valueIndex);
  value[0] = baseValue[0];
  value[1] = baseValue[1];
  value[2] = baseValue[2];
  value[4] = baseValue[4];
  value[5] = baseValue[5];
  value[6] = baseValue[6];
  f32 fog = m_drMan->m_drPixlMan->unknown7f0->m_drPixlPostMan->unknown108 + -0.05f;
  fog = fog > 0.0f ? fog : 0.0f;
  fog = fog / 0.95f;
  value[9] = mm::clamp(fog, 0.0f, 1.0f);
}

void DrMdoMat::matCall_CalcBloom(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  *value = *baseValue * m_bloom;
}

void DrMdoMat::matCall_ToonId(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = value[1] / 255.0f;
}

void DrMdoMat::matCall_VolumeTest(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {}

// Measured forms (1.0.0: 0x71007f937c, 397 instructions): the game inlines the release functions of the sampler, texture, vertex and shader managers and the uniform array release
// (unknown001). The billboard uniforms (unknown120) are read once into a local and, in the instance map branch, into a second local for the other view of the union (unknown120_1),
// because the game keeps the pointer in a register and clears the array pointer through it once, after the tail shared by the two loops (stride 0x38 and 0x28): reading
// `unknown30->unknown120` again after the calls reloads it and gives no shared store. The occlusion view (unknown160_2) is read before the matrices (unknown160) and read again after
// the store that clears their array (a null array reuses the first load). The pointer of the shader extension tables is cleared twice and the texture array pointer (unknowne8) is
// cleared in place of the texture list pointer (m_drResMdoTexList) in the game.
void DrMdoMat::releaseMat() {
  if (unknown30 == nullptr) {
    return;
  }
  if (unknown30->m_drResMpfSampler != nullptr) {
    for (u32 i = 0; i < unknown30->unknown30; i++) {
      unknown30->m_drResMpfSampler[i].~DrResMpfSampler();
    }
    unknown30->m_drResMpfSampler = nullptr;
  }
  if (unknown30->m_drResMdoSampler != nullptr) {
    m_drMan->m_drMdlMan->m_drMdoSamplerMan->releaseSamplerObj(unknown30->m_drResMdoSampler);
    unknown30->m_drResMdoSampler = nullptr;
  }
  if (unknown30->unknown98 != nullptr) {
    unknown30->unknown98->release();
    unknown30->unknown98 = nullptr;
  }
  if (unknown30->unknown90 != nullptr) {
    unknown30->unknown90->unknown001();
    unknown30->unknown90 = nullptr;
  }
  if (unknown30->unknowna0 != nullptr) {
    unknown30->unknowna0->unknown001();
    unknown30->unknowna0 = nullptr;
  }
  if (unknown30->unknowna8 != nullptr) {
    unknown30->unknowna8->unknown001();
    unknown30->unknowna8 = nullptr;
  }
  if (unknown30->unknownb0 != nullptr) {
    unknown30->unknownb0->unknown001();
    unknown30->unknownb0 = nullptr;
  }
  if (unknown30->unknownb8 != nullptr) {
    unknown30->unknownb8->unknown001();
    unknown30->unknownb8 = nullptr;
  }
  unknown712 *billboard = unknown30->unknown120;
  if (billboard != nullptr) {
    if (billboard->unknown00 == 0) {
      if (billboard->unknown08 != nullptr) {
        billboard->unknown08->unknown001();
        billboard->unknown08 = nullptr;
      }
    } else {
      unknown713 *instBillboard = unknown30->unknown120_1;
      if (instBillboard->unknown08 != nullptr) {
        instBillboard->unknown08->unknown001();
        instBillboard->unknown08 = nullptr;
      }
    }
  }
  if (unknown30->unknown140 != nullptr && unknown30->unknown140->unknown18 != nullptr) {
    unknown30->unknown140->unknown18->unknown001();
    unknown30->unknown140->unknown18 = nullptr;
  }
  unknown724 *occlusion = unknown30->unknown160_2;
  if (unknown30->unknown160 != nullptr && unknown30->unknown160->unknown08 == 0) {
    if (unknown30->unknown160->unknown00 != nullptr) {
      unknown30->unknown160->unknown00->unknown001();
      unknown30->unknown160->unknown00 = nullptr;
      occlusion = unknown30->unknown160_2;
    }
    occlusion->m_drResQueryAcc->releaseQuery();
  }
  if (unknown30->m_drShdMdoExtTblObj != nullptr) {
    mtl::MemManager::deallocate(unknown30->m_drShdMdoExtTblObj, 0, false);
    unknown30->m_drShdMdoExtTblObj = nullptr;
    unknown30->m_drShdMdoExtTblObj = nullptr;
  }
  if (unknown30->m_drResMdoTexList != nullptr) {
    m_drMan->m_drMdlMan->m_drMdoTextureMan->releaseTextureObj(unknown30->m_drResMdoTexList);
    unknown30->unknowne8 = nullptr;
  }
  if (unknown30->m_drResMdoVertex != nullptr) {
    m_drMan->m_drMdlMan->m_drMdoVertexMan->releaseVertexObj(unknown30->m_drResMdoVertex);
    unknown30->m_drResMdoVertex = nullptr;
  }
  if (unknown30->m_drShdMdoDecShdObj != nullptr) {
    m_drMan->m_drShdMan->m_drShdMdoMan->releaseShaderObj(unknown30->m_drShdMdoDecShdObj);
    unknown30->m_drShdMdoDecShdObj = nullptr;
  }
  if (unknown30 != nullptr) {
    mtl::MemManager::deallocate(unknown30, 0, false);
    unknown30 = nullptr;
  }
}
} // namespace ml

// The game instantiates these in this file, where the uniform block constructors and release() are out of line.
template void grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock>::setupArray(u32 count);
template void grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>::setupArray(u32 count);
template void grlib::CGLibUniformArray<grlib::CGLibTriUniformBlock>::setupArray(u32 count);
