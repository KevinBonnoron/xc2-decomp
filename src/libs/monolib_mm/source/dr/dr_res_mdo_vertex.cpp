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

DrResMdoVertex::DrResMdoVertex(const u8 *resource)
    : m_prev(nullptr), m_next(nullptr), m_resourceKey(resource), m_refCount(1), m_buffer(nullptr), m_stmList(nullptr) {
  setupVertex(resource);
}

void DrResMdoVertex::setupVertex(const u8 *resource) {
  vertexRelease();
  const MdsVertexHeader *header = reinterpret_cast<const MdsVertexHeader *>(resource);
  m_header = header;
  u32 vertexOffset = header->vertexOffset;
  m_vertexNum = header->vertexNum;
  u32 indexOffset = header->indexOffset;
  m_indexNum = header->indexNum;
  u32 etcVertexOffset = header->etcVertexOffset;
  m_etcVertexNum = header->etcVertexNum;
  if (header->etcInfoOffset != 0) {
    m_etcInfos = reinterpret_cast<const MdsEtcVertexInfo *>(resource + header->etcInfoOffset);
  } else {
    m_etcInfos = nullptr;
  }
  if (header->mofBlendOffset != 0) {
    const MdsMofBlendHeader *mofBlendHeader = reinterpret_cast<const MdsMofBlendHeader *>(resource + header->mofBlendOffset);
    m_mofBlendInfos = reinterpret_cast<const MdsMofBlendInfo *>(resource + mofBlendHeader->infoOffset);
  } else {
    m_mofBlendInfos = nullptr;
  }

  u32 uniformVertexOffset = header->uniformVertexOffset;
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(
      DrMan::getIns()->memClass,
      (m_vertexNum + m_etcVertexNum + m_indexNum) * sizeof(grlib::CGLibVtxVertex) +
          (uniformVertexOffset != 0
               ? sizeof(grlib::CGLibVtlMemPool) + sizeof(DrResUniformVertex) + sizeof(grlib::CGLibVtxVertex) + sizeof(grlib::CGLibOneUniformBlock)
               : sizeof(grlib::CGLibVtlMemPool)),
      0x10,
      false,
      "no name",
      0));
  m_vertices = reinterpret_cast<grlib::CGLibVtxVertex *>(m_buffer);
  for (int i = 0; i < m_vertexNum; i++) {
    new (&m_vertices[i]) grlib::CGLibVtxVertex;
  }
  int offset = m_vertexNum * sizeof(grlib::CGLibVtxVertex);
  if (m_etcVertexNum != 0) {
    m_etcVertices = reinterpret_cast<grlib::CGLibVtxVertex *>(m_buffer + offset);
    for (int i = 0; i < m_etcVertexNum; i++) {
      new (&m_etcVertices[i]) grlib::CGLibVtxVertex;
    }
    offset += m_etcVertexNum * sizeof(grlib::CGLibVtxVertex);
  }
  if (header->uniformVertexOffset != 0) {
    m_uniformVertex = reinterpret_cast<DrResUniformVertex *>(m_buffer + offset);
    m_uniformVertex->vertex = reinterpret_cast<grlib::CGLibVtxVertex *>(m_buffer + offset + sizeof(DrResUniformVertex));
    new (m_uniformVertex->vertex) grlib::CGLibVtxVertex;
    m_uniformVertex->uniformBlock =
        reinterpret_cast<grlib::CGLibOneUniformBlock *>(m_buffer + offset + sizeof(DrResUniformVertex) + sizeof(grlib::CGLibVtxVertex));
    new (m_uniformVertex->uniformBlock) grlib::CGLibOneUniformBlock;
    offset += sizeof(DrResUniformVertex) + sizeof(grlib::CGLibVtxVertex) + sizeof(grlib::CGLibOneUniformBlock);
  } else {
    m_uniformVertex = nullptr;
  }
  m_indices = reinterpret_cast<grlib::CGLibVtxIndex *>(m_buffer + offset);
  for (int i = 0; i < m_indexNum; i++) {
    new (&m_indices[i]) grlib::CGLibVtxIndex;
  }
  offset += m_indexNum * sizeof(grlib::CGLibVtxIndex);
  m_memPool = reinterpret_cast<grlib::CGLibVtlMemPool *>(m_buffer + offset);
  new (m_memPool) grlib::CGLibVtlMemPool;
  m_memPool->setupBuffer(const_cast<u8 *>(reinterpret_cast<const u8 *>(m_header)) + header->bufferOffset, header->bufferSize);

  const MdsVertexBuffInfo *vertexInfos = reinterpret_cast<const MdsVertexBuffInfo *>(resource + vertexOffset);
  for (int i = 0; i < m_vertexNum; i++) {
    m_vertices[i].createMemVertexBuff(m_memPool, vertexInfos[i].offset, vertexInfos[i].stride * vertexInfos[i].count, vertexInfos[i].stride);
  }
  const MdsEtcVertexBuffInfo *etcVertexInfos = reinterpret_cast<const MdsEtcVertexBuffInfo *>(resource + etcVertexOffset);
  for (int i = 0; i < m_etcVertexNum; i++) {
    m_etcVertices[i].createMemVertexBuff(
        m_memPool, etcVertexInfos[i].offset, etcVertexInfos[i].stride * etcVertexInfos[i].count, etcVertexInfos[i].stride);
  }
  const MdsIndexBuffInfo *indexInfos = reinterpret_cast<const MdsIndexBuffInfo *>(resource + indexOffset);
  for (int i = 0; i < m_indexNum; i++) {
    m_indices[i].createMemIndexBuff(
        m_memPool, indexInfos[i].offset, indexInfos[i].count, s_primitiveTbl[indexInfos[i].primitive], s_indexFormatTbl[indexInfos[i].format]);
  }
  if (header->weightOffset != 0) {
    m_weightInfo = reinterpret_cast<const MdsWeightInfo *>(reinterpret_cast<const u8 *>(m_header) + header->weightOffset);
  } else {
    m_weightInfo = nullptr;
  }
  if (header->uniformVertexOffset != 0) {
    const MdsUniformVertexInfo *uniformInfo =
        reinterpret_cast<const MdsUniformVertexInfo *>(reinterpret_cast<const u8 *>(m_header) + header->uniformVertexOffset);
    m_uniformVertex->vertex->createMemVertexBuff(m_memPool, uniformInfo->vertexOffset, uniformInfo->vertexSize, uniformInfo->vertexStride);
    m_uniformVertex->uniformBlock->setup(m_memPool, uniformInfo->uniformSize, uniformInfo->uniformOffset);
    m_uniformVertex->uniformBlock->updateData();
  }
}

DrResMdoVertex::~DrResMdoVertex() { vertexRelease(); }

void DrResMdoVertex::vertexRelease() {
  if (m_buffer == nullptr) {
    return;
  }
  for (int i = 0; i < m_vertexNum; i++) {
    m_vertices[i].~CGLibVtxVertex();
  }
  for (int i = 0; i < m_etcVertexNum; i++) {
    m_etcVertices[i].~CGLibVtxVertex();
  }
  for (int i = 0; i < m_indexNum; i++) {
    m_indices[i].~CGLibVtxIndex();
  }
  if (m_uniformVertex != nullptr) {
    m_uniformVertex->vertex->~CGLibVtxVertex();
    m_uniformVertex->uniformBlock->~CGLibOneUniformBlock();
    m_uniformVertex = nullptr;
  }
  m_memPool->~CGLibVtlMemPool();
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
}

void DrResMdoVertex::update() {
  if (m_stmList != nullptr) {
    DrCalcStmRes *res = m_stmList->getResVertexObj();
    if (res->flags & 1) {
      changeMemVertex(res->data);
    }
  }
}

bool DrResMdoVertex::isEtcVertex(int index) {
  if (m_etcInfos != nullptr && (m_etcInfos[index].flags & 1)) {
    return true;
  }
  return false;
}

const u8 *DrResMdoVertex::getVertexTbl(int index) const {
  const u8 *resource = reinterpret_cast<const u8 *>(m_header);
  return resource + reinterpret_cast<const MdsVertexBuffInfo *>(resource + m_header->vertexOffset)[index].offset;
}

u32 DrResMdoVertex::getVertexMax(int index) const { return m_vertices[index].m_count; }

void DrResMdoVertex::setVertexBind(int index) {
  if (m_bindVertex != index) {
    grlib::CGLibCtlVertex::setVertex(m_vertices[index]);
    m_bindVertex = index;
  }
}

u32 DrResMdoVertex::setWeightVertexBind(int index) {
  const u16 &vertexIdx = m_header->weightVertexIdx[index];
  if (vertexIdx == 0) {
    return 0;
  }
  grlib::CGLibCtlVertex::setVertex(m_vertices[vertexIdx]);
  m_bindVertex = vertexIdx;
  return m_vertices[vertexIdx].m_count;
}

const MdsWeightVertexInfo *DrResMdoVertex::getWeightVertexInfo(int index, int pass) {
  const u8 *resource = reinterpret_cast<const u8 *>(m_header);
  const u16 *infoIdxTbl = reinterpret_cast<const u16 *>(resource + m_weightInfo->vertexInfoIdxOffset);
  u32 infoIdx = infoIdxTbl[pass * 9 + index];
  if (infoIdx != 0) {
    const MdsWeightVertexInfo *infos = reinterpret_cast<const MdsWeightVertexInfo *>(resource + m_weightInfo->vertexInfoOffset);
    return &infos[infoIdx - 1];
  }
  return nullptr;
}

grlib::CGLibVtxVertex *DrResMdoVertex::getWeightVertex() { return &m_vertices[m_weightInfo->vertexIdx]; }

void DrResMdoVertex::setEtcVertexBind(int index, int stream) {
  m_bindVertex = -1;
  grlib::CGLibCtlVertex::setAddVertex(m_etcVertices[m_etcInfos[index].etcVertexIdx], 0, stream, 0);
}

void DrResMdoVertex::setMofBlendVertexBind(grlib::CGLibOneUniformArray *uniforms, int index, int stream) {
  m_bindVertex = -1;
  u16 mofBlendIdx = m_etcInfos[index].mofBlendIdx;
  grlib::CGLibCtlVertex::setUniformVertex((*uniforms)[mofBlendIdx], m_mofBlendInfos[mofBlendIdx].stride, 0, stream, 0);
}

grlib::CGLibVtxVertex *DrResMdoVertex::getResVertexObj(int index) { return &m_vertices[index]; }

grlib::CGLibVtxIndex *DrResMdoVertex::getResIndexObj(int index) { return &m_indices[index]; }

grlib::CGLibVtxVertex *DrResMdoVertex::getResEtcVertexObj(int index) {
  if (m_etcInfos == nullptr) {
    return nullptr;
  }
  if (!(m_etcInfos[index].flags & 1)) {
    return nullptr;
  }
  return &m_etcVertices[m_etcInfos[index].etcVertexIdx];
}

bool DrResMdoVertex::getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count) {
  if (index < m_vertexNum) {
    const u8 *resource = reinterpret_cast<const u8 *>(m_header);
    const MdsVertexBuffInfo *infos = reinterpret_cast<const MdsVertexBuffInfo *>(resource + m_header->vertexOffset);
    *format = reinterpret_cast<const MdsMdlVertexFmt *>(resource + infos[index].fmtOffset);
    *count = infos[index].fmtNum;
    return true;
  }
  return false;
}

void DrResMdoVertex::render(int index) { m_indices[index].drawIndex(); }

void DrResMdoVertex::renderIns(int index, int instanceCount) { m_indices[index].drawInsIndex(instanceCount); }

} // namespace ml
