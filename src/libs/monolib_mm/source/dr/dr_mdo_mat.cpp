#include "dr/dr_mdo_mat.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_mat.h"
#include "mm_math/mm_col4.h"

namespace ml {

void DrMdoMat::initMdlInfo(const u8 *data, MdoWrkMatRes *matRes) {
  const MdsMeshHeader *header = reinterpret_cast<const MdsMeshHeader *>(data);
  matRes->unknown18 = data;
  matRes->unknown20 = header;
  matRes->unknown170 = header->unknown20;
  matRes->unknown168 = reinterpret_cast<const MdsMdlEntry *>(data + header->unknown1c);
  if (header->unknown34 != 0) {
    matRes->unknown178 = data + header->unknown30;
  }
}

int DrMdoMat::getNodeAnmWrkRes(const u8 *data, u8 *work, MdoWrkMatRes *matRes) {
  const MdsMeshHeader *header = reinterpret_cast<const MdsMeshHeader *>(data);
  if (!(header->unknown00 & MdsMeshHeader::FLAG_UNKNOWN_3)) {
    return 0;
  }
  if (work != nullptr) {
    const unknown001 *table = reinterpret_cast<const unknown001 *>(data + header->unknown78);
    unknown002 *nodeAnm = reinterpret_cast<unknown002 *>(work);
    u32 dataOffset = table->unknown04;
    nodeAnm->unknown00 = table;
    nodeAnm->unknown08 = table;
    nodeAnm->unknown10 = table->unknown00;
    nodeAnm->unknown18 = reinterpret_cast<const u8 *>(table) + dataOffset;
    matRes->unknown148 = nodeAnm;
  }
  return sizeof(unknown002);
}

void DrMdoMat::resetNodeAnmWrkRes(const u8 *data, MdoWrkMatRes *matRes) {
  const MdsMeshHeader *header = reinterpret_cast<const MdsMeshHeader *>(data);
  if (header->unknown00 & MdsMeshHeader::FLAG_UNKNOWN_3) {
    const unknown001 *table = reinterpret_cast<const unknown001 *>(data + header->unknown78);
    matRes->unknown148->unknown00 = table;
    matRes->unknown148->unknown08 = table;
    matRes->unknown148->unknown18 = reinterpret_cast<const u8 *>(table) + table->unknown04;
  }
}

int DrMdoMat::getDispCallRes(const u8 *data, u32 offset, u8 *work, MdoWrkMatRes *matRes) {
  const unknown004 *table = reinterpret_cast<const unknown004 *>(data + offset);
  if (work != nullptr) {
    unknown003 *dispCall = reinterpret_cast<unknown003 *>(work);
    dispCall->unknown00 = table->unknown00;
    dispCall->unknown10 = data + table->unknown04;
    dispCall->unknown08 = work + sizeof(unknown003);
    memset(dispCall->unknown08, 0, static_cast<u64>(table->unknown00) * 8);
    matRes->unknown130 = dispCall;
  }
  return table->unknown00 * 8 + sizeof(unknown003);
}

void DrMdoMat::resetDispCallRes(const u8 *data, u32 offset, MdoWrkMatRes *matRes) {
  const unknown004 *table = reinterpret_cast<const unknown004 *>(data + offset);
  matRes->unknown130->unknown10 = data + table->unknown04;
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

void DrMdoMat::setDrMan(DrMan *drMan) { m_drMan = drMan; }

void DrMdoMat::updateAlphaCall() {
  if (unknown100 & ALPHA_FLAG_SINGLE_BUFFER) {
    unknown100 &= ~(ALPHA_FLAG_UPDATED | ALPHA_FLAG_UPDATED << 1);
    return;
  }
  int index = DrMan::s_nDblIdx;
  u32 flag = ALPHA_FLAG_UPDATED << index;
  if (unknown100 & flag) {
    unknown100 &= ~flag;
    unknowne0 = unknownd0[index];
  }
}

bool DrMdoMat::isBloomMdl() const { return (unknownf8 & MDL_FLAG_BLOOM) != 0; }

bool DrMdoMat::isAlphaBloomMdl() const { return (unknownf8 & MDL_FLAG_ALPHA_BLOOM) != 0; }

u32 DrMdoMat::getVanishEffectMax() const {
  if (unknown30 == nullptr) {
    return 0;
  }
  const MdsMeshHeader *header = unknown30->unknown20;
  if (header == nullptr) {
    return 0;
  }
  if (!(header->unknown00 & MdsMeshHeader::FLAG_VANISH_EFFECT)) {
    return 0;
  }
  return header->unknown94 > 1 ? header->unknown94 : 1;
}

bool DrMdoMat::isFullScreenShadowMdl() const { return (unknownf8 & MDL_FLAG_FULL_SCREEN_SHADOW) != 0; }

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

bool DrMdoMat::isVolumeMdl() const { return (unknownf8 & MDL_FLAG_VOLUME) != 0; }

void DrMdoMat::setFlagWaveOn(bool isOn) {
  if (isOn) {
    unknownfc |= DRAW_FLAG_FLAG_WAVE;
  } else {
    unknownfc &= ~DRAW_FLAG_FLAG_WAVE;
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
