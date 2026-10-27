#include "dr/dr_res_mdo_seam_wrk_pos_inst.h"

#include <string.h>

#include "dr/dr_res_mdo_seam_res.h"

namespace ml {

namespace {

// Inferred role: header of the base position data; original type name unknown.
struct unknown004 {
  u8 _00[0x18];
  u32 unknown18; // Inferred role: position model table offset; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  u32 unknown20; // Inferred role: first position table offset; original member name unknown.
  u8 _24[0x28 - 0x24];
  s32 unknown28; // Inferred role: second position table offset; original member name unknown.
  u8 _2c[0x4c - 0x2c];
  u32 unknown4c; // Inferred role: model table offsets offset; original member name unknown.
  u8 _50[0x54 - 0x50];
  u32 unknown54; // Inferred role: tree work offset; original member name unknown.
};

// Inferred role: header of the etc position data; original type name unknown.
struct unknown005 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: position model table offset; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: first position table offset; original member name unknown.
  u8 _10[0x14 - 0x10];
  s32 unknown14; // Inferred role: second position table offset; original member name unknown.
  u8 _18[0x2c - 0x18];
  u32 unknown2c; // Inferred role: model table offsets offset; original member name unknown.
  u8 _30[0x34 - 0x30];
  u32 unknown34; // Inferred role: tree work offset; original member name unknown.
};

// Inferred role: header of the position tree work; original type name unknown.
struct unknown006 {
  u32 unknown00; // Inferred role: tree offset; original member name unknown.
};

} // namespace

u16 *DrResMdoSeamWrkPosInst::s_pVertexTbl;
u16 *DrResMdoSeamWrkPosInst::s_pTextureTbl;
DrResMdoSeamVertex *DrResMdoSeamWrkPosInst::s_pSeamVertex;
DrResMdoSeamTexture *DrResMdoSeamWrkPosInst::s_pSeamTexture;
DrResMdoSeamParmRead *DrResMdoSeamWrkPosInst::s_pParmRead;

DrResMdoSeamWrkPosInst::DrResMdoSeamWrkPosInst() : unknown20(nullptr), unknown40(nullptr), unknown50(nullptr), unknown60(0), unknown6c(0), unknown74(0), unknown78(nullptr) {}

void DrResMdoSeamWrkPosInst::delCall() { unknown74 |= 2; }

u32 DrResMdoSeamWrkPosInst::getDataSize() const {
  if (unknown50 != nullptr) {
    return unknown50->m_size;
  }
  return 0;
}

u32 DrResMdoSeamWrkPosInst::clipCheck(u32 index) {
  const u32 *bits = unknown40->unknown18;
  return bits[static_cast<s32>(index) >> 5] & (1 << (index & 0x1f));
}

u32 *DrResMdoSeamWrkPosInst::getShwBitTbl(u32 index) {
  if (unknown60 != 0) {
    return unknown58[index];
  }
  return nullptr;
}

void DrResMdoSeamWrkPosInst::clearShwBitTbl(u32 index) {
  if (unknown60 != 0) {
    memset(unknown58[index], 0, unknown60);
  }
}

void DrResMdoSeamWrkPosInst::clearAllShwBitTbl() {
  if (unknown60 != 0) {
    memset(unknown58[0], 0, unknown60 * 0x24);
  }
}

void DrResMdoSeamWrkPosInst::changeMemBaseInstPos(const u8 *data) {
  const unknown004 *header = reinterpret_cast<const unknown004 *>(data);
  unknown00 = data;
  unknown08 = data + header->unknown18;
  unknown18 = data + header->unknown28;
  unknown10 = data + header->unknown20;
  if (header->unknown4c != 0) {
    unknown20 = reinterpret_cast<const unknown003 *>(data + header->unknown4c);
    unknown28 = data + unknown20->unknown10;
    unknown30 = data + unknown20->unknown00;
    unknown38 = data + unknown20->unknown08;
  }
  for (int i = 0; i < unknown6c; i++) {
    unknown48[i].unknown08 = unknown08 + i * 0x70;
  }
  u32 treeOffset = header->unknown54;
  if (treeOffset != 0) {
    unknown001 *work = unknown40;
    const u8 *base = unknown00;
    work->unknown00 = base;
    work->unknown08 = base + reinterpret_cast<const unknown006 *>(base + treeOffset)->unknown00;
  }
}

void DrResMdoSeamWrkPosInst::changeMemEtcInstPos() {
  const u8 *data = unknown50->m_buffer;
  const unknown005 *header = reinterpret_cast<const unknown005 *>(data);
  unknown00 = data;
  unknown08 = data + header->unknown04;
  unknown18 = data + header->unknown14;
  unknown10 = data + header->unknown0c;
  if (header->unknown2c != 0) {
    unknown20 = reinterpret_cast<const unknown003 *>(data + header->unknown2c);
    unknown28 = data + unknown20->unknown10;
    unknown30 = data + unknown20->unknown00;
    unknown38 = data + unknown20->unknown08;
  }
  for (int i = 0; i < unknown6c; i++) {
    unknown48[i].unknown08 = unknown08 + i * 0x70;
  }
  u32 treeOffset = header->unknown34;
  if (treeOffset != 0) {
    unknown001 *work = unknown40;
    const u8 *base = unknown00;
    work->unknown00 = base;
    work->unknown08 = base + reinterpret_cast<const unknown006 *>(base + treeOffset)->unknown00;
  }
}

void DrResMdoSeamWrkPosInst::seachCalcTbl(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrResMdoSeamParmRead *parmRead) {
  s_pVertexTbl = vertexTbl;
  s_pTextureTbl = textureTbl;
  s_pSeamVertex = seamVertex;
  s_pSeamTexture = seamTexture;
  s_pParmRead = parmRead;
}

} // namespace ml
