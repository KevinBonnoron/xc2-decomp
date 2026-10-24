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
  u32 unknown00; // Inferred role: offset; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u32 unknown08; // Inferred role: stride; original member name unknown.
  u32 unknown0c; // Inferred role: fmt offset; original member name unknown.
  u32 unknown10; // Inferred role: fmt num; original member name unknown.
  u8 _14[0x20 - 0x14];
};

static_assert(sizeof(MdsVertexBuffInfo) == 0x20, "");

struct MdsIndexBuffInfo {
  u32 unknown00; // Inferred role: offset; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u16 unknown08; // Inferred role: primitive; original member name unknown.
  u8 unknown0a;  // Inferred role: format; original member name unknown.
  u8 _0b[0x14 - 0x0b];
};

static_assert(sizeof(MdsIndexBuffInfo) == 0x14, "");

struct MdsEtcVertexBuffInfo {
  u32 unknown00; // Inferred role: offset; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u32 unknown08; // Inferred role: stride; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(sizeof(MdsEtcVertexBuffInfo) == 0x10, "");

struct MdsEtcVertexInfo {
  u8 unknown00;  // Inferred role: flags; original member name unknown.
  u16 unknown02; // Inferred role: etc vertex idx; original member name unknown.
  u16 unknown04; // Inferred role: mof blend idx; original member name unknown.
  u8 _06[0xc - 0x6];
};

static_assert(sizeof(MdsEtcVertexInfo) == 0xc, "");

struct MdsMofBlendInfo {
  u8 _00[0x8 - 0x0];
  s32 unknown08; // Inferred role: stride; original member name unknown.
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
  u32 unknown04; // Inferred role: vertex info offset; original member name unknown.
  u16 unknown08; // Inferred role: vertex idx; original member name unknown.
  u32 unknown0c; // Inferred role: vertex info idx offset; original member name unknown.
};

static_assert(offsetof(MdsWeightInfo, unknown08) == 0x8, "");
static_assert(offsetof(MdsWeightInfo, unknown0c) == 0xc, "");

struct MdsWeightVertexInfo {
  u8 _00[0x28 - 0x00];
};

struct MdsVertexHeader {
  u32 unknown00;    // Inferred role: vertex offset; original member name unknown.
  u32 unknown04;    // Inferred role: vertex num; original member name unknown.
  u32 unknown08;    // Inferred role: index offset; original member name unknown.
  u32 unknown0c;    // Inferred role: index num; original member name unknown.
  u16 unknown10[6]; // Inferred role: weight vertex idx; original member name unknown.
  u32 unknown1c;    // Inferred role: etc info offset; original member name unknown.
  u32 unknown20;    // Inferred role: etc vertex offset; original member name unknown.
  u32 unknown24;    // Inferred role: etc vertex num; original member name unknown.
  u32 unknown28;    // Inferred role: mof blend offset; original member name unknown.
  u32 unknown2c;    // Inferred role: buffer size; original member name unknown.
  u32 unknown30;    // Inferred role: buffer offset; original member name unknown.
  u32 unknown34;    // Inferred role: uniform vertex offset; original member name unknown.
  u32 unknown38;    // Inferred role: weight offset; original member name unknown.
};

static_assert(offsetof(MdsVertexHeader, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsVertexHeader, unknown38) == 0x38, "");

struct DrResUniformVertex {
  grlib::CGLibVtxVertex *unknown00;       // Inferred role: vertex; original member name unknown.
  grlib::CGLibOneUniformBlock *unknown08; // Inferred role: uniform block; original member name unknown.
};

class DrResMdoVertex {
public:
  void changeMemVertex(const u8 *resource);
  void beginVertexSetup() { unknown4e = -1; }
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

  DrResMdoVertex *unknown00; // Inferred role: prev; original member name unknown.
  DrResMdoVertex *unknown08; // Inferred role: next; original member name unknown.
  const u8 *unknown10;       // Inferred role: resource key; original member name unknown.
  s32 unknown18;             // Inferred role: ref count; original member name unknown.
  u8 *m_buffer;
  const MdsVertexHeader *unknown28;  // Inferred role: header; original member name unknown.
  const MdsEtcVertexInfo *unknown30; // Inferred role: etc infos; original member name unknown.
  const MdsMofBlendInfo *unknown38;  // Inferred role: mof blend infos; original member name unknown.
  const MdsWeightInfo *unknown40;    // Inferred role: weight info; original member name unknown.
  u16 unknown48;                     // Inferred role: vertex num; original member name unknown.
  u16 unknown4a;                     // Inferred role: index num; original member name unknown.
  u16 unknown4c;                     // Inferred role: etc vertex num; original member name unknown.
  s16 unknown4e;                     // Inferred role: bind vertex; original member name unknown.
  grlib::CGLibVtxVertex *unknown50;  // Inferred role: vertices; original member name unknown.
  grlib::CGLibVtxIndex *unknown58;   // Inferred role: indices; original member name unknown.
  grlib::CGLibVtxVertex *unknown60;  // Inferred role: etc vertices; original member name unknown.
  grlib::CGLibVtlMemPool *unknown68; // Inferred role: mem pool; original member name unknown.
  DrResUniformVertex *unknown70;     // Inferred role: uniform vertex; original member name unknown.
  DrCalcStmListObj *unknown78;       // Inferred role: stm list; original member name unknown.
};

static_assert(offsetof(DrResMdoVertex, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoVertex, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoVertex, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoVertex, unknown4e) == 0x4e, "");
static_assert(offsetof(DrResMdoVertex, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoVertex, unknown78) == 0x78, "");
static_assert(sizeof(DrResMdoVertex) == 0x80, "");

inline void DrResMdoVertex::changeMemVertex(const u8 *resource) {
  const MdsVertexHeader *header = reinterpret_cast<const MdsVertexHeader *>(resource);
  unknown28 = header;
  unknown68->delayRelease();
  unknown68->setupBuffer(const_cast<u8 *>(reinterpret_cast<const u8 *>(unknown28)) + header->unknown30, header->unknown2c);
  const MdsVertexBuffInfo *vertexInfos = reinterpret_cast<const MdsVertexBuffInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown00);
  for (int i = 0; i < unknown48; i++) {
    unknown50[i].resetVertexBuff(unknown68, vertexInfos[i].unknown00);
  }
  const MdsEtcVertexBuffInfo *etcVertexInfos = reinterpret_cast<const MdsEtcVertexBuffInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown20);
  for (int i = 0; i < unknown4c; i++) {
    unknown60[i].resetVertexBuff(unknown68, etcVertexInfos[i].unknown00);
  }
  const MdsIndexBuffInfo *indexInfos = reinterpret_cast<const MdsIndexBuffInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown08);
  for (int i = 0; i < unknown4a; i++) {
    unknown58[i].resetIndexBuff(unknown68, indexInfos[i].unknown00);
  }
  if (header->unknown34 != 0) {
    const MdsUniformVertexInfo *uniformInfo = reinterpret_cast<const MdsUniformVertexInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown34);
    unknown70->unknown00->resetVertexBuff(unknown68, uniformInfo->vertexOffset);
    unknown70->unknown08->setup(unknown68, uniformInfo->uniformSize, uniformInfo->uniformOffset);
    unknown70->unknown08->updateData();
  }
  if (header->unknown1c != 0) {
    unknown30 = reinterpret_cast<const MdsEtcVertexInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown1c);
  } else {
    unknown30 = nullptr;
  }
  if (header->unknown28 != 0) {
    const u8 *base = reinterpret_cast<const u8 *>(unknown28);
    unknown38 = reinterpret_cast<const MdsMofBlendInfo *>(base + reinterpret_cast<const MdsMofBlendHeader *>(base + header->unknown28)->infoOffset);
  } else {
    unknown38 = nullptr;
  }
  if (header->unknown38 != 0) {
    unknown40 = reinterpret_cast<const MdsWeightInfo *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown38);
  } else {
    unknown40 = nullptr;
  }
}

} // namespace ml
