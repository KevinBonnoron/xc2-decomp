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

// Inferred role: model data vertex buff info; original type name unknown.
struct unknown046 {
  u32 unknown00; // Inferred role: offset; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u32 unknown08; // Inferred role: stride; original member name unknown.
  u32 unknown0c; // Inferred role: fmt offset; original member name unknown.
  u32 unknown10; // Inferred role: fmt num; original member name unknown.
  u8 _14[0x20 - 0x14];
};

static_assert(sizeof(unknown046) == 0x20, "");

// Inferred role: model data index buff info; original type name unknown.
struct unknown047 {
  u32 unknown00; // Inferred role: offset; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u16 unknown08; // Inferred role: primitive; original member name unknown.
  u8 unknown0a;  // Inferred role: format; original member name unknown.
  u8 _0b[0x14 - 0x0b];
};

static_assert(sizeof(unknown047) == 0x14, "");

// Inferred role: model data etc vertex buff info; original type name unknown.
struct unknown048 {
  u32 unknown00; // Inferred role: offset; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u32 unknown08; // Inferred role: stride; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(sizeof(unknown048) == 0x10, "");

// Inferred role: model data etc vertex info; original type name unknown.
struct unknown049 {
  u8 unknown00;  // Inferred role: flags; original member name unknown.
  u16 unknown02; // Inferred role: etc vertex idx; original member name unknown.
  u16 unknown04; // Inferred role: mof blend idx; original member name unknown.
  u8 _06[0xc - 0x6];
};

static_assert(sizeof(unknown049) == 0xc, "");

// Inferred role: model data mof blend info; original type name unknown.
struct unknown050 {
  u8 _00[0x8 - 0x0];
  s32 unknown08; // Inferred role: stride; original member name unknown.
  u8 _0c[0x10 - 0xc];
};

static_assert(sizeof(unknown050) == 0x10, "");

// Inferred role: model data mof blend header; original type name unknown.
struct unknown051 {
  u8 _00[0xc - 0x0];
  u32 infoOffset;
};

// Inferred role: model data uniform vertex info; original type name unknown.
struct unknown052 {
  u8 _00[0x4 - 0x0];
  u32 vertexOffset;
  u32 vertexSize;
  u32 uniformOffset;
  u32 uniformSize;
  u8 _14[0x18 - 0x14];
  u32 vertexStride;
};

// Inferred role: model data weight info; original type name unknown.
struct unknown053 {
  u8 _00[0x4 - 0x0];
  u32 unknown04; // Inferred role: vertex info offset; original member name unknown.
  u16 unknown08; // Inferred role: vertex idx; original member name unknown.
  u32 unknown0c; // Inferred role: vertex info idx offset; original member name unknown.
};

static_assert(offsetof(unknown053, unknown08) == 0x8, "");
static_assert(offsetof(unknown053, unknown0c) == 0xc, "");

// Inferred role: model data weight vertex info; original type name unknown.
struct unknown054 {
  u8 _00[0x28 - 0x00];
};

// Inferred role: model data vertex header; original type name unknown.
struct unknown055 {
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

static_assert(offsetof(unknown055, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown055, unknown38) == 0x38, "");

// Inferred role: resource uniform vertex; original type name unknown.
struct unknown056 {
  grlib::CGLibVtxVertex *unknown00;       // Inferred role: vertex; original member name unknown.
  grlib::CGLibOneUniformBlock *unknown08; // Inferred role: uniform block; original member name unknown.
};

class DrResMdoVertex {
public:
  void changeMemVertex(const u8 *resource);
  void beginVertexSetup();
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
  const unknown054 *getWeightVertexInfo(int index, int pass);
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
  const unknown055 *unknown28;       // Inferred role: header; original member name unknown.
  const unknown049 *unknown30;       // Inferred role: etc infos; original member name unknown.
  const unknown050 *unknown38;       // Inferred role: mof blend infos; original member name unknown.
  const unknown053 *unknown40;       // Inferred role: weight info; original member name unknown.
  u16 unknown48;                     // Inferred role: vertex num; original member name unknown.
  u16 unknown4a;                     // Inferred role: index num; original member name unknown.
  u16 unknown4c;                     // Inferred role: etc vertex num; original member name unknown.
  s16 unknown4e;                     // Inferred role: bind vertex; original member name unknown.
  grlib::CGLibVtxVertex *unknown50;  // Inferred role: vertices; original member name unknown.
  grlib::CGLibVtxIndex *unknown58;   // Inferred role: indices; original member name unknown.
  grlib::CGLibVtxVertex *unknown60;  // Inferred role: etc vertices; original member name unknown.
  grlib::CGLibVtlMemPool *unknown68; // Inferred role: mem pool; original member name unknown.
  unknown056 *unknown70;             // Inferred role: uniform vertex; original member name unknown.
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
  const unknown055 *header = reinterpret_cast<const unknown055 *>(resource);
  unknown28 = header;
  unknown68->delayRelease();
  unknown68->setupBuffer(const_cast<u8 *>(reinterpret_cast<const u8 *>(unknown28)) + header->unknown30, header->unknown2c);
  const unknown046 *vertexInfos = reinterpret_cast<const unknown046 *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown00);
  for (int i = 0; i < unknown48; i++) {
    unknown50[i].resetVertexBuff(unknown68, vertexInfos[i].unknown00);
  }
  const unknown048 *etcVertexInfos = reinterpret_cast<const unknown048 *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown20);
  for (int i = 0; i < unknown4c; i++) {
    unknown60[i].resetVertexBuff(unknown68, etcVertexInfos[i].unknown00);
  }
  const unknown047 *indexInfos = reinterpret_cast<const unknown047 *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown08);
  for (int i = 0; i < unknown4a; i++) {
    unknown58[i].resetIndexBuff(unknown68, indexInfos[i].unknown00);
  }
  if (header->unknown34 != 0) {
    const unknown052 *uniformInfo = reinterpret_cast<const unknown052 *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown34);
    unknown70->unknown00->resetVertexBuff(unknown68, uniformInfo->vertexOffset);
    unknown70->unknown08->setup(unknown68, uniformInfo->uniformSize, uniformInfo->uniformOffset);
    unknown70->unknown08->updateData();
  }
  if (header->unknown1c != 0) {
    unknown30 = reinterpret_cast<const unknown049 *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown1c);
  } else {
    unknown30 = nullptr;
  }
  if (header->unknown28 != 0) {
    const u8 *base = reinterpret_cast<const u8 *>(unknown28);
    unknown38 = reinterpret_cast<const unknown050 *>(base + reinterpret_cast<const unknown051 *>(base + header->unknown28)->infoOffset);
  } else {
    unknown38 = nullptr;
  }
  if (header->unknown38 != 0) {
    unknown40 = reinterpret_cast<const unknown053 *>(reinterpret_cast<const u8 *>(unknown28) + header->unknown38);
  } else {
    unknown40 = nullptr;
  }
}

} // namespace ml
