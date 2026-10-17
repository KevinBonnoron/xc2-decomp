#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibOneUniformArray;
class CGLibOneUniformBlock;
class CGLibVtlMemPool;
class CGLibVtxIndex;
class CGLibVtxVertex;
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

} // namespace ml
