#include "dr/dr_mdo_mat.h"

#include <math.h>
#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_sampler_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_mpf_sampler.h"
#include "dr/dr_shd_mdo_dec_shd_obj.h"
#include "grlib/cglib_dbl_uniform_block.h" // IWYU pragma: keep
#include "grlib/cglib_one_uniform_block.h" // IWYU pragma: keep
#include "grlib/cglib_tri_uniform_block.h" // IWYU pragma: keep
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_array.h"
// The game builds the sampler manager in the same unit, so its release functions are inlined here.
#include "dr_mdo_sampler_man.cpp"
#include "grlib/cglib_uniform_array.h"

namespace ml {

const f32 DrMdoMat::MDL_SCALE_PARAMS = 0.57735055f;

void DrMdoMat::initMdlInfo(const u8 *data, MdoWrkMatRes *matRes) {
  const unknown022 *header = reinterpret_cast<const unknown022 *>(data);
  matRes->unknown18 = data;
  matRes->unknown20 = header;
  matRes->unknown170 = header->unknown20;
  matRes->unknown168 = reinterpret_cast<const MdsMdlTopHeader *>(data + header->unknown1c);
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
    matRes->unknownd0->changeMemTexList(texData);
  }
  initMdlInfo(mdlData, matRes);
  if (matRes->unknown00 != nullptr && matRes->unknownc8 != nullptr) {
    matRes->unknownc8->changeMemVertex(matRes->unknown00);
  }
}

void DrMdoMat::resetBaseMapMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *mdlData, const u8 *vertexData, const u8 *shaderData, const u8 *texData, int skipTexList) {
  const MdsMatTopHeader *header = reinterpret_cast<const MdsMatTopHeader *>(matData);
  const MdsMatTechnique *techniques = reinterpret_cast<const MdsMatTechnique *>(matData + header->unknown28);
  initMdlInfo(mdlData, matRes);
  matRes->unknown10 = matData;
  matRes->unknown08 = texData;
  matRes->unknown00 = vertexData;
  matRes->unknown70 = techniques;
  matRes->unknown78 = matData;
  matRes->unknown28 = reinterpret_cast<const MdsMatInfoHeader *>(matData + header->unknown00);
  if (header->unknown20 != 0) {
    matRes->unknown40 = reinterpret_cast<const unknown010 *>(matData + header->unknown20);
  }
  DrResMdoMat *names = matRes->unknownc0;
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
    matRes->unknownd0->changeMemTexList(matRes->unknown08);
  }
  if (matRes->unknown00 != nullptr && matRes->unknownc8 != nullptr) {
    matRes->unknownc8->changeMemVertex(matRes->unknown00);
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_3) {
    matRes->unknown48 = matData + reinterpret_cast<const unknown718 *>(matData + header->unknown54)->unknown00;
  }
  matRes->unknown80->changeMemShader(shaderData, matData, techniques);
}

void DrMdoMat::resetInstMapMaterial(MdoWrkMatRes *matRes, const u8 *matData, const u8 *mdlData, const u8 *shaderData, const u8 *texData, int skipTexList) {
  const MdsMatTopHeader *header = reinterpret_cast<const MdsMatTopHeader *>(matData);
  const MdsMatTechnique *techniques = reinterpret_cast<const MdsMatTechnique *>(matData + header->unknown28);
  initMdlInfo(mdlData, matRes);
  matRes->unknown08 = texData;
  matRes->unknown10 = matData;
  matRes->unknown70 = techniques;
  matRes->unknown78 = matData;
  matRes->unknown28 = reinterpret_cast<const MdsMatInfoHeader *>(matData + header->unknown00);
  if (header->unknown20 != 0) {
    matRes->unknown40 = reinterpret_cast<const unknown010 *>(matData + header->unknown20);
  }
  DrResMdoMat *names = matRes->unknownc0;
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
    matRes->unknownd0->changeMemTexList(matRes->unknown08);
  }
  if (header->unknown44 & MdsMatTopHeader::FLAG_UNKNOWN_3) {
    matRes->unknown48 = matData + reinterpret_cast<const unknown718 *>(matData + header->unknown54)->unknown00;
  }
  if (matRes->unknown80 != nullptr) {
    matRes->unknown80->changeMemShader(shaderData, matData, techniques);
  }
}

int DrMdoMat::getDispCallRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes) {
  const unknown704 *table = reinterpret_cast<const unknown704 *>(data + offset);
  if (work != nullptr) {
    unknown703 *dispCall = reinterpret_cast<unknown703 *>(work);
    dispCall->unknown00 = table->unknown00;
    dispCall->unknown10 = reinterpret_cast<const MdsMatDispCCData *>(data + table->unknown04);
    dispCall->unknown08 = reinterpret_cast<_MdoWrkDispCallTemp *>(work + sizeof(unknown703));
    memset(dispCall->unknown08, 0, static_cast<u64>(table->unknown00) * 8);
    matRes->unknown130 = dispCall;
  }
  return table->unknown00 * 8 + sizeof(unknown703);
}

void DrMdoMat::resetDispCallRes(const u8 *data, u32 offset, MdoWrkMatRes *matRes) {
  const unknown704 *table = reinterpret_cast<const unknown704 *>(data + offset);
  matRes->unknown130->unknown10 = reinterpret_cast<const MdsMatDispCCData *>(data + table->unknown04);
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
    _MdoWrkDispCallTemp *temp = dispCall->unknown08;
    const MdsMatDispCCData *data = dispCall->unknown10;
    for (s32 i = 0; i < dispCall->unknown00; i++, data++, temp++) {
      if (checkCallBackParam(temp, data)) {
        unknown20 &= ~0x60;
      }
    }
  }
}

bool DrMdoMat::updateDispEnvCall(MdoWrkMatRes *matRes) {
  unknown703 *dispCall = matRes->unknown130;
  if (dispCall == nullptr || dispCall->unknown00 < 1) {
    return false;
  }
  _MdoWrkDispCallTemp *temp = dispCall->unknown08;
  const MdsMatDispCCData *data = dispCall->unknown10;
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
    _MdoWrkDispCallTemp *temp = dispCall->unknown08;
    const MdsMatDispCCData *data = dispCall->unknown10;
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
    const u8 *first = data + table->unknown00;
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
  matRes->unknown138->unknown00 = data + table->unknown00;
}

void DrMdoMat::releaseBaseMapSeamMat(MdoWrkMatRes *matRes) {
  if (matRes->unknownc8 != nullptr) {
    delete matRes->unknownc8;
    matRes->unknownc8 = nullptr;
  }
  if (matRes->unknownd0 != nullptr) {
    delete matRes->unknownd0;
    matRes->unknownd0 = nullptr;
  }
  matRes->unknowne8 = nullptr;
  if (matRes->unknownd8 != nullptr) {
    m_drMan->unknown88->unknown018->releaseSamplerSeamObj(matRes->unknownd8);
    matRes->unknownd8 = nullptr;
  }
  if (matRes->unknown80 != nullptr) {
    delete matRes->unknown80;
    matRes->unknown80 = nullptr;
  }
  matRes->unknown88 = nullptr;
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
  if (matRes->unknownd0 != nullptr) {
    delete matRes->unknownd0;
    matRes->unknownd0 = nullptr;
  }
  matRes->unknowne8 = nullptr;
  if (matRes->unknownd8 != nullptr) {
    m_drMan->unknown88->unknown018->releaseSamplerSeamObj(matRes->unknownd8);
    matRes->unknownd8 = nullptr;
  }
  if (matRes->unknown80 != nullptr) {
    delete matRes->unknown80;
    matRes->unknown80 = nullptr;
  }
  matRes->unknown88 = nullptr;
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
  if (matRes->unknownc8 != nullptr) {
    delete matRes->unknownc8;
    matRes->unknownc8 = nullptr;
  }
  if (matRes->unknowne0 != nullptr) {
    for (u32 i = 0; i < matRes->unknown30; i++) {
      matRes->unknowne0[i].~DrResMpfSampler();
    }
    matRes->unknowne0 = nullptr;
  }
  if (matRes->unknownd8 != nullptr) {
    m_drMan->unknown88->unknown018->releaseSamplerSeamObj(matRes->unknownd8);
    matRes->unknownd8 = nullptr;
  }
  if (matRes->unknownd0 != nullptr) {
    delete matRes->unknownd0;
    matRes->unknownd0 = nullptr;
  }
  if (matRes->unknown90 != nullptr) {
    matRes->unknown90->unknown001();
    matRes->unknown90 = nullptr;
  }
  matRes->unknowne8 = nullptr;
}

void DrMdoMat::matCall_BaseColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  DrResMdoMat *mat = &unknown30->unknownc0[matIndex];
  mat->unknown08.r = unknown30->unknown118->unknown00[valueIndex].r;
  mat->unknown08.g = unknown30->unknown118->unknown00[valueIndex].g;
  mat->unknown08.b = unknown30->unknown118->unknown00[valueIndex].b;
}

void DrMdoMat::matCall_BaseVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  DrResMdoMat *mat = &unknown30->unknownc0[matIndex];
  mat->unknown08.r = unknown30->unknown118->unknown30[valueIndex];
  mat->unknown08.g = unknown30->unknown118->unknown30[valueIndex];
  mat->unknown08.b = unknown30->unknown118->unknown30[valueIndex];
}

void DrMdoMat::matCall_TransVal(const MdsMatInfoHeader *, int valueIndex, int matIndex) { unknown30->unknownc0[matIndex].setAlpha(unknown30->unknown118->unknown30[valueIndex]); }

void DrMdoMat::matCall_CalcColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  unknown30->unknownc0[matIndex].setColor(header->unknown0c * unknownd8, unknownd8 * header->unknown10, unknownd8 * header->unknown14, header->unknown18);
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
  if (unknown30->unknown150 == nullptr) {
    return nullptr;
  }
  return &unknown30->unknown150[index * 3 + bufferIndex];
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
  f32 fog = m_drMan->unknown78->unknown7f0->unknown180->unknown108 + -0.05f;
  fog = fog > 0.0f ? fog : 0.0f;
  fog = fog / 0.95f;
  value[9] = mm::clamp(fog, 0.0f, 1.0f);
}

void DrMdoMat::matCall_CalcBloom(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  *value = *baseValue * unknownd8;
}

void DrMdoMat::matCall_ToonId(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = value[1] / 255.0f;
}

void DrMdoMat::matCall_VolumeTest(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {}

} // namespace ml

// The game instantiates these in this file, where the uniform block constructors and release() are out of line.
template void grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock>::setupArray(u32 count);
template void grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>::setupArray(u32 count);
template void grlib::CGLibUniformArray<grlib::CGLibTriUniformBlock>::setupArray(u32 count);
