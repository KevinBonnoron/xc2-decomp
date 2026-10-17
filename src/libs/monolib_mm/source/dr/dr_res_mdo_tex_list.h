#pragma once
#include <stddef.h>

#include "grlib/cglib_vtl_mem_pool.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrCalcStmListObj;

struct MdsTexInfo {
  u8 _00[0x0c - 0x00];
  u32 nameOffset;
};

static_assert(sizeof(MdsTexInfo) == 0x10, "");

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

  DrResMdoTexList *m_prev;
  DrResMdoTexList *m_next;
  const u8 *m_resourceKey;
  s32 m_refCount;
  grlib::CGLibTextureBuffer *m_textures;
  grlib::CGLibVtlMemPool m_memPool;
  DrCalcStmListObj *m_stmList;
  void *m_buffer;
  s32 m_texMax;
  u32 m_flags;
  u8 _70[0x74 - 0x70];
  u8 _74[0x78 - 0x74];
  const u16 *m_stmTexIdx;
  const u8 *m_texHeader;
  const u8 *m_texData;
  u8 _90[0x98 - 0x90];
  u8 _98[0xa0 - 0x98];
};

static_assert(offsetof(DrResMdoTexList, m_memPool) == 0x28, "");
static_assert(offsetof(DrResMdoTexList, m_stmList) == 0x58, "");
static_assert(offsetof(DrResMdoTexList, m_texMax) == 0x68, "");
static_assert(offsetof(DrResMdoTexList, m_stmTexIdx) == 0x78, "");
static_assert(sizeof(DrResMdoTexList) == 0xa0, "");

} // namespace ml
