#pragma once
#include <stddef.h>

#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "types.h"

namespace grlib {
class CGLibOneUniformArray;
} // namespace grlib

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {
class DrCalcStmListObj;
struct MdsMdlVertexFmt;

struct MdsVertexBuffInfo {
  u32 offset;
  u32 count;
  u32 stride;
  u32 fmtOffset;
  u32 fmtNum;
  u8 _14[0x20 - 0x14];
};

static_assert(sizeof(MdsVertexBuffInfo) == 0x20, "");

struct MdsIndexBuffInfo {
  u32 offset;
  u32 count;
  u16 primitive;
  u8 format;
  u8 _0b[0x14 - 0x0b];
};

static_assert(sizeof(MdsIndexBuffInfo) == 0x14, "");

struct MdsEtcVertexBuffInfo {
  u32 offset;
  u32 count;
  u32 stride;
  u8 _0c[0x10 - 0x0c];
};

static_assert(sizeof(MdsEtcVertexBuffInfo) == 0x10, "");

struct MdsEtcVertexInfo {
  u8 flags;
  u16 etcVertexIdx;
  u16 mofBlendIdx;
  u8 _06[0xc - 0x6];
};

static_assert(sizeof(MdsEtcVertexInfo) == 0xc, "");

struct MdsMofBlendInfo {
  u8 _00[0x8 - 0x0];
  s32 stride;
  u8 _0c[0x10 - 0xc];
};

static_assert(sizeof(MdsMofBlendInfo) == 0x10, "");

struct MdsMofBlendHeader {
  u8 _00[0xc - 0x0];
  u32 infoOffset;
};

struct MdsUniformVertexInfo {
  u8 _00[0x4 - 0x0];
  u32 vertexOffset;
  u32 vertexSize;
  u32 uniformOffset;
  u32 uniformSize;
  u8 _14[0x18 - 0x14];
  u32 vertexStride;
};

struct MdsWeightInfo {
  u8 _00[0x4 - 0x0];
  u32 vertexInfoOffset;
  u16 vertexIdx;
  u32 vertexInfoIdxOffset;
};

static_assert(offsetof(MdsWeightInfo, vertexIdx) == 0x8, "");
static_assert(offsetof(MdsWeightInfo, vertexInfoIdxOffset) == 0xc, "");

struct MdsWeightVertexInfo {
  u8 _00[0x28 - 0x00];
};

struct MdsVertexHeader {
  u32 vertexOffset;
  u32 vertexNum;
  u32 indexOffset;
  u32 indexNum;
  u16 weightVertexIdx[6];
  u32 etcInfoOffset;
  u32 etcVertexOffset;
  u32 etcVertexNum;
  u32 mofBlendOffset;
  u32 bufferSize;
  u32 bufferOffset;
  u32 uniformVertexOffset;
  u32 weightOffset;
};

static_assert(offsetof(MdsVertexHeader, etcInfoOffset) == 0x1c, "");
static_assert(offsetof(MdsVertexHeader, weightOffset) == 0x38, "");

struct DrResUniformVertex {
  grlib::CGLibVtxVertex *vertex;
  grlib::CGLibOneUniformBlock *uniformBlock;
};

class DrResMdoVertex {
public:
  void changeMemVertex(const u8 *resource);
  void beginVertexSetup() { m_bindVertex = -1; }
  DrResMdoVertex(const u8 *resource);
  void setupVertex(const u8 *resource);
  ~DrResMdoVertex();
  void vertexRelease();
  void update();
  bool isEtcVertex(int index);
  void mulVertex(const mm::Mat44 &matrix, int index);
  const u8 *getVertexTbl(int index) const;
  u32 getVertexMax(int index) const;
  void setVertexBind(int index);
  u32 setWeightVertexBind(int index);
  const MdsWeightVertexInfo *getWeightVertexInfo(int index, int pass);
  grlib::CGLibVtxVertex *getWeightVertex();
  void setEtcVertexBind(int index, int stream);
  void setMofBlendVertexBind(grlib::CGLibOneUniformArray *uniforms, int index, int stream);
  grlib::CGLibVtxVertex *getResVertexObj(int index);
  grlib::CGLibVtxIndex *getResIndexObj(int index);
  grlib::CGLibVtxVertex *getResEtcVertexObj(int index);
  bool getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count);
  void render(int index);
  void renderIns(int index, int instanceCount);

  DrResMdoVertex *m_prev;
  DrResMdoVertex *m_next;
  const u8 *m_resourceKey;
  s32 m_refCount;
  u8 *m_buffer;
  const MdsVertexHeader *m_header;
  const MdsEtcVertexInfo *m_etcInfos;
  const MdsMofBlendInfo *m_mofBlendInfos;
  const MdsWeightInfo *m_weightInfo;
  u16 m_vertexNum;
  u16 m_indexNum;
  u16 m_etcVertexNum;
  s16 m_bindVertex;
  grlib::CGLibVtxVertex *m_vertices;
  grlib::CGLibVtxIndex *m_indices;
  grlib::CGLibVtxVertex *m_etcVertices;
  grlib::CGLibVtlMemPool *m_memPool;
  DrResUniformVertex *m_uniformVertex;
  DrCalcStmListObj *m_stmList;
};

static_assert(offsetof(DrResMdoVertex, m_refCount) == 0x18, "");
static_assert(offsetof(DrResMdoVertex, m_header) == 0x28, "");
static_assert(offsetof(DrResMdoVertex, m_vertexNum) == 0x48, "");
static_assert(offsetof(DrResMdoVertex, m_bindVertex) == 0x4e, "");
static_assert(offsetof(DrResMdoVertex, m_vertices) == 0x50, "");
static_assert(offsetof(DrResMdoVertex, m_stmList) == 0x78, "");
static_assert(sizeof(DrResMdoVertex) == 0x80, "");

inline void DrResMdoVertex::changeMemVertex(const u8 *resource) {
  const MdsVertexHeader *header = reinterpret_cast<const MdsVertexHeader *>(resource);
  m_header = header;
  m_memPool->delayRelease();
  m_memPool->setupBuffer(const_cast<u8 *>(reinterpret_cast<const u8 *>(m_header)) + header->bufferOffset, header->bufferSize);
  const MdsVertexBuffInfo *vertexInfos = reinterpret_cast<const MdsVertexBuffInfo *>(reinterpret_cast<const u8 *>(m_header) + header->vertexOffset);
  for (int i = 0; i < m_vertexNum; i++) {
    m_vertices[i].resetVertexBuff(m_memPool, vertexInfos[i].offset);
  }
  const MdsEtcVertexBuffInfo *etcVertexInfos =
      reinterpret_cast<const MdsEtcVertexBuffInfo *>(reinterpret_cast<const u8 *>(m_header) + header->etcVertexOffset);
  for (int i = 0; i < m_etcVertexNum; i++) {
    m_etcVertices[i].resetVertexBuff(m_memPool, etcVertexInfos[i].offset);
  }
  const MdsIndexBuffInfo *indexInfos = reinterpret_cast<const MdsIndexBuffInfo *>(reinterpret_cast<const u8 *>(m_header) + header->indexOffset);
  for (int i = 0; i < m_indexNum; i++) {
    m_indices[i].resetIndexBuff(m_memPool, indexInfos[i].offset);
  }
  if (header->uniformVertexOffset != 0) {
    const MdsUniformVertexInfo *uniformInfo =
        reinterpret_cast<const MdsUniformVertexInfo *>(reinterpret_cast<const u8 *>(m_header) + header->uniformVertexOffset);
    m_uniformVertex->vertex->resetVertexBuff(m_memPool, uniformInfo->vertexOffset);
    m_uniformVertex->uniformBlock->setup(m_memPool, uniformInfo->uniformSize, uniformInfo->uniformOffset);
    m_uniformVertex->uniformBlock->updateData();
  }
  if (header->etcInfoOffset != 0) {
    m_etcInfos = reinterpret_cast<const MdsEtcVertexInfo *>(reinterpret_cast<const u8 *>(m_header) + header->etcInfoOffset);
  } else {
    m_etcInfos = nullptr;
  }
  if (header->mofBlendOffset != 0) {
    const u8 *base = reinterpret_cast<const u8 *>(m_header);
    m_mofBlendInfos =
        reinterpret_cast<const MdsMofBlendInfo *>(base + reinterpret_cast<const MdsMofBlendHeader *>(base + header->mofBlendOffset)->infoOffset);
  } else {
    m_mofBlendInfos = nullptr;
  }
  if (header->weightOffset != 0) {
    m_weightInfo = reinterpret_cast<const MdsWeightInfo *>(reinterpret_cast<const u8 *>(m_header) + header->weightOffset);
  } else {
    m_weightInfo = nullptr;
  }
}

} // namespace ml
