#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "types.h"

namespace ml {

class DrCalcStmListObj;

// Inferred role: model data tex info; original type name unknown.
struct unknown092 {
  u8 _00[0x04 - 0x00];
  u32 unknown04; // Inferred role: image size; original member name unknown.
  u32 unknown08; // Inferred role: image offset; original member name unknown.
  u32 unknown0c; // Inferred role: name offset; original member name unknown.
};

static_assert(sizeof(unknown092) == 0x10, "");

struct MdsTexHeader {
  s32 texNum;
  u32 infoOffset;
};

class DrResMdoTexList {
public:
  DrResMdoTexList(const u8 *texData);
  void createTexInfoList();
  void createTexList(const u8 *texHeader, const u8 *texData);
  DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const MdsTexHeader *stmHeader);
  void createStmTexInfoList(DrCalcStmListObj *stmList, const u8 *stmHeader, bool isCreate);
  DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const u16 *stmTexIdx);
  DrResMdoTexList(const u8 *texHeader, const u8 *texData);
  ~DrResMdoTexList();
  void release();
  void update();
  void texStmUpdate();
  void callStmRead(int index);
  void changeCallTexMemTexList(const u8 *texHeader, const u8 *texData);
  void resetTexutre();
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  grlib::CGLibTextureBuffer *getStmTexObj(u32 index);
  const char *getTexName(u32 index);
  bool isTexMiddelStmCheck() const;
  void changeMemTexList(const u8 *texData);
  static int calcTextureMax(const u8 *texHeader);

  DrResMdoTexList *unknown00;               // Inferred role: prev; original member name unknown.
  DrResMdoTexList *unknown08;               // Inferred role: next; original member name unknown.
  const void *unknown10;                    // Inferred role: resource key; original member name unknown.
  s32 unknown18;                            // Inferred role: ref count; original member name unknown.
  grlib::CGLibTextureBuffer *m_texObj;      // Inferred role: textures; named after the game accessor ml::DrResMdoTexList::getTexObj.
  grlib::CGLibVtlMemPool m_cGLibVtlMemPool; // Inferred role: mem pool; original member name unknown.
  DrCalcStmListObj *m_drCalcStmListObj;     // Inferred role: stm list; original member name unknown.
  void *m_buffer;
  s32 unknown68; // Inferred role: tex max; original member name unknown.
  u32 unknown6c; // Inferred role: flags; original member name unknown.
  u32 unknown70; // Inferred role: stream state; original member name unknown.
  u8 _74[0x78 - 0x74];
  u16 *unknown78;      // Inferred role: stm tex idx; original member name unknown.
  const u8 *unknown80; // Inferred role: tex header; original member name unknown.
  const u8 *unknown88; // Inferred role: tex data; original member name unknown.
  u64 _90;
  u8 _98[0xa0 - 0x98];
};

static_assert(offsetof(DrResMdoTexList, m_cGLibVtlMemPool) == 0x28, "");
static_assert(offsetof(DrResMdoTexList, m_drCalcStmListObj) == 0x58, "");
static_assert(offsetof(DrResMdoTexList, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoTexList, unknown78) == 0x78, "");
static_assert(sizeof(DrResMdoTexList) == 0xa0, "");

class DrResMdoTexSimple {
public:
  DrResMdoTexSimple(const void *texData, int size, bool isMiddle);
  ~DrResMdoTexSimple();
  void releaseTex();
  void release();
  void createTex();

  DrResMdoTexSimple *unknown00;                   // Inferred role: prev; original member name unknown.
  DrResMdoTexSimple *unknown08;                   // Inferred role: next; original member name unknown.
  grlib::CGLibTextureBuffer m_cGLibTextureBuffer; // Inferred role: texture; original member name unknown.
  const void *unknown80;                          // Inferred role: tex data; original member name unknown.
  int m_size;
  u32 unknown8c; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResMdoTexSimple, unknown80) == 0x80, "");
static_assert(sizeof(DrResMdoTexSimple) == 0x90, "");

} // namespace ml
