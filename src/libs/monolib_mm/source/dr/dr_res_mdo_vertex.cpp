#include "dr/dr_res_mdo_vertex.h"

#include <new>

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_man.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

static const GrlPrimitiveType s_primitiveTbl[] = {GRL_PRIMITIVE_TRIANGLES, GRL_PRIMITIVE_QUADS, GRL_PRIMITIVE_TRIANGLE_STRIP};
static const GrlIndexFormat s_indexFormatTbl[] = {GRL_INDEX_FORMAT_U16, GRL_INDEX_FORMAT_U32};

void DrResMdoVertex::beginVertexSetup() { unknown4e = -1; }

DrResMdoVertex::DrResMdoVertex(const u8 *resource) : unknown00(nullptr), unknown08(nullptr), unknown10(resource), unknown18(1), m_buffer(nullptr), unknown78(nullptr) { setupVertex(resource); }

void DrResMdoVertex::setupVertex(const u8 *resource) {
  vertexRelease();
  const MdsVertexHeader *header = reinterpret_cast<const MdsVertexHeader *>(resource);
  unknown28 = header;
  u32 vertexOffset = header->unknown00;
  unknown48 = header->unknown04;
  u32 indexOffset = header->unknown08;
  unknown4a = header->unknown0c;
  u32 etcVertexOffset = header->unknown20;
  unknown4c = header->unknown24;
  if (header->unknown1c != 0) {
    unknown30 = reinterpret_cast<const MdsEtcVertexInfo *>(resource + header->unknown1c);
  } else {
    unknown30 = nullptr;
  }
  if (header->unknown28 != 0) {
    const MdsMofBlendHeader *mofBlendHeader = reinterpret_cast<const MdsMofBlendHeader *>(resource + header->unknown28);
    unknown38 = reinterpret_cast<const MdsMofBlendInfo *>(resource + mofBlendHeader->infoOffset);
  } else {
    unknown38 = nullptr;
  }

  u32 uniformVertexOffset = header->unknown34;
  m_buffer = static_cast<u8 *>(
      mtl::MemManager::allocate(DrMan::getIns()->unknown10,
                                (unknown48 + unknown4c + unknown4a) * sizeof(grlib::CGLibVtxVertex) +
                                    (uniformVertexOffset != 0 ? sizeof(grlib::CGLibVtlMemPool) + sizeof(DrResUniformVertex) + sizeof(grlib::CGLibVtxVertex) + sizeof(grlib::CGLibOneUniformBlock)
                                                              : sizeof(grlib::CGLibVtlMemPool)),
                                0x10,
                                false,
                                "no name",
                                0));
  unknown50 = reinterpret_cast<grlib::CGLibVtxVertex *>(m_buffer);
  for (int i = 0; i < unknown48; i++) {
    new (&unknown50[i]) grlib::CGLibVtxVertex;
  }
  int offset = unknown48 * sizeof(grlib::CGLibVtxVertex);
  if (unknown4c != 0) {
    unknown60 = reinterpret_cast<grlib::CGLibVtxVertex *>(m_buffer + offset);
    for (int i = 0; i < unknown4c; i++) {
      new (&unknown60[i]) grlib::CGLibVtxVertex;
    }
    offset += unknown4c * sizeof(grlib::CGLibVtxVertex);
  }
  if (header->unknown34 != 0) {
    unknown70 = reinterpret_cast<DrResUniformVertex *>(m_buffer + offset);
    unknown70->unknown00 = reinterpret_cast<grlib::CGLibVtxVertex *>(m_buffer + offset + sizeof(DrResUniformVertex));
    new (unknown70->unknown00) grlib::CGLibVtxVertex;
    unknown70->unknown08 = reinterpret_cast<grlib::CGLibOneUniformBlock *>(m_buffer + offset + sizeof(DrResUniformVertex) + sizeof(grlib::CGLibVtxVertex));
    new (unknown70->unknown08) grlib::CGLibOneUniformBlock;
    offset += sizeof(DrResUniformVertex) + sizeof(grlib::CGLibVtxVertex) + sizeof(grlib::CGLibOneUniformBlock);
  } else {
    unknown70 = nullptr;
  }
  unknown58 = reinterpret_cast<grlib::CGLibVtxIndex *>(m_buffer + offset);
  for (int i = 0; i < unknown4a; i++) {
    new (&unknown58[i]) grlib::CGLibVtxIndex;
  }
  offset += unknown4a * sizeof(grlib::CGLibVtxIndex);
  unknown68 = reinterpret_cast<grlib::CGLibVtlMemPool *>(m_buffer + offset);
  new (unknown68) grlib::CGLibVtlMemPool;
  unknown68->setupBuffer(const_cast<u8 *>(reinterpret_cast<const u8 *>(unknown28)) + header->unknown30, header->unknown2c);

  const MdsVertexBuffInfo *vertexInfos = reinterpret_cast<const MdsVertexBuffInfo *>(resource + vertexOffset);
  for (int i = 0; i < unknown48; i++) {
    unknown50[i].createMemVertexBuff(unknown68, vertexInfos[i].unknown00, vertexInfos[i].unknown08 * vertexInfos[i].unknown04, vertexInfos[i].unknown08);
  }
  const MdsEtcVertexBuffInfo *etcVertexInfos = reinterpret_cast<const MdsEtcVertexBuffInfo *>(resource + etcVertexOffset);
  for (int i = 0; i < unknown4c; i++) {
    unknown60[i].createMemVertexBuff(unknown68, etcVertexInfos[i].unknown00, etcVertexInfos[i].unknown08 * etcVertexInfos[i].unknown04, etcVertexInfos[i].unknown08);
  }
  const MdsIndexBuffInfo *indexInfos = reinterpret_cast<const MdsIndexBuffInfo *>(resource + indexOffset);
  for (int i = 0; i < unknown4a; i++) {
    unknown58[i].createMemIndexBuff(unknown68, indexInfos[i].unknown00, indexInfos[i].unknown04, s_primitiveTbl[indexInfos[i].unknown08], s_indexFormatTbl[indexInfos[i].unknown0a]);
  }
  if (header->unknown38 != 0) {
    unknown40 = reinterpret_cast<const MdsWeightInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown38);
  } else {
    unknown40 = nullptr;
  }
  if (header->unknown34 != 0) {
    const MdsUniformVertexInfo *uniformInfo = reinterpret_cast<const MdsUniformVertexInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown34);
    unknown70->unknown00->createMemVertexBuff(unknown68, uniformInfo->vertexOffset, uniformInfo->vertexSize, uniformInfo->vertexStride);
    unknown70->unknown08->setup(unknown68, uniformInfo->uniformSize, uniformInfo->uniformOffset);
    unknown70->unknown08->updateData();
  }
}

DrResMdoVertex::~DrResMdoVertex() { vertexRelease(); }

void DrResMdoVertex::vertexRelease() {
  if (m_buffer == nullptr) {
    return;
  }
  for (int i = 0; i < unknown48; i++) {
    unknown50[i].~CGLibVtxVertex();
  }
  for (int i = 0; i < unknown4c; i++) {
    unknown60[i].~CGLibVtxVertex();
  }
  for (int i = 0; i < unknown4a; i++) {
    unknown58[i].~CGLibVtxIndex();
  }
  if (unknown70 != nullptr) {
    unknown70->unknown00->~CGLibVtxVertex();
    unknown70->unknown08->~CGLibOneUniformBlock();
    unknown70 = nullptr;
  }
  unknown68->~CGLibVtlMemPool();
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
}

void DrResMdoVertex::update() {
  if (unknown78 != nullptr) {
    DrCalcStmRes *res = unknown78->getResVertexObj();
    if (res->unknown10 & 1) {
      changeMemVertex(res->unknown00);
    }
  }
}

bool DrResMdoVertex::isEtcVertex(int index) {
  if (unknown30 != nullptr && (unknown30[index].unknown00 & 1)) {
    return true;
  }
  return false;
}

const u8 *DrResMdoVertex::getVertexTbl(int index) const {
  const u8 *resource = reinterpret_cast<const u8 *>(unknown28);
  return resource + reinterpret_cast<const MdsVertexBuffInfo *>(resource + unknown28->unknown00)[index].unknown00;
}

u32 DrResMdoVertex::getVertexMax(int index) const { return unknown50[index].unknown08; }

void DrResMdoVertex::setVertexBind(int index) {
  if (unknown4e != index) {
    grlib::CGLibCtlVertex::setVertex(unknown50[index]);
    unknown4e = index;
  }
}

u32 DrResMdoVertex::setWeightVertexBind(int index) {
  const u16 &vertexIdx = unknown28->unknown10[index];
  if (vertexIdx == 0) {
    return 0;
  }
  grlib::CGLibCtlVertex::setVertex(unknown50[vertexIdx]);
  unknown4e = vertexIdx;
  return unknown50[vertexIdx].unknown08;
}

const MdsWeightVertexInfo *DrResMdoVertex::getWeightVertexInfo(int index, int pass) {
  const u8 *resource = reinterpret_cast<const u8 *>(unknown28);
  const u16 *infoIdxTbl = reinterpret_cast<const u16 *>(resource + unknown40->unknown0c);
  u32 infoIdx = infoIdxTbl[pass * 9 + index];
  if (infoIdx != 0) {
    const MdsWeightVertexInfo *infos = reinterpret_cast<const MdsWeightVertexInfo *>(resource + unknown40->unknown04);
    return &infos[infoIdx - 1];
  }
  return nullptr;
}

grlib::CGLibVtxVertex *DrResMdoVertex::getWeightVertex() { return &unknown50[unknown40->unknown08]; }

void DrResMdoVertex::setEtcVertexBind(int index, int stream) {
  unknown4e = -1;
  grlib::CGLibCtlVertex::setAddVertex(unknown60[unknown30[index].unknown02], 0, stream, 0);
}

void DrResMdoVertex::setMofBlendVertexBind(grlib::CGLibOneUniformArray *uniforms, int index, int stream) {
  unknown4e = -1;
  u16 mofBlendIdx = unknown30[index].unknown04;
  grlib::CGLibCtlVertex::setUniformVertex((*uniforms)[mofBlendIdx], unknown38[mofBlendIdx].unknown08, 0, stream, 0);
}

grlib::CGLibVtxVertex *DrResMdoVertex::getResVertexObj(int index) { return &unknown50[index]; }

grlib::CGLibVtxIndex *DrResMdoVertex::getResIndexObj(int index) { return &unknown58[index]; }

grlib::CGLibVtxVertex *DrResMdoVertex::getResEtcVertexObj(int index) {
  if (unknown30 == nullptr) {
    return nullptr;
  }
  if (!(unknown30[index].unknown00 & 1)) {
    return nullptr;
  }
  return &unknown60[unknown30[index].unknown02];
}

bool DrResMdoVertex::getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count) {
  if (index < unknown48) {
    const u8 *resource = reinterpret_cast<const u8 *>(unknown28);
    const MdsVertexBuffInfo *infos = reinterpret_cast<const MdsVertexBuffInfo *>(resource + unknown28->unknown00);
    *format = reinterpret_cast<const MdsMdlVertexFmt *>(resource + infos[index].unknown0c);
    *count = infos[index].unknown10;
    return true;
  }
  return false;
}

void DrResMdoVertex::render(int index) { unknown58[index].drawIndex(); }

void DrResMdoVertex::renderIns(int index, int instanceCount) { unknown58[index].drawInsIndex(instanceCount); }

} // namespace ml
