#pragma once
#include <stddef.h>

#include "dr/dr_res_chank_list.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace ml {

class DrResMdoSeamMemMan {
public:
  DrResMdoSeamMemMan();
  ~DrResMdoSeamMemMan();
  void releaseMem();
  void cntMemUpdate();
  bool memTempCopy();
  void clearMemObj(DrResMdoSeamMemObj *obj, DrResChankList<DrResMdoSeamMemObj> &list);
  DrResMdoSeamMemObj *copyTempBuff(DrResMdoSeamMemObj *obj);
  DrResMdoSeamMemObj *copyMemObj(DrResMdoSeamMemObj *obj, DrResChankList<DrResMdoSeamMemObj> &list);
  void changeListAndCopyMemObj(DrResMdoSeamMemObj *first, DrResMdoSeamMemObj *second, DrResChankList<DrResMdoSeamMemObj> &list);
  int getUseMax() const;
  int getFreeMax() const;
  int getAllFreeSize() const;
  int getAllUseSize() const;
  u32 getFreeSize();
  u32 getFreeSize(int &freeCount, int &separatedCount);
  void renderMemInfo();
  bool calcPieceMem(bool isCheck);
  void releaseFreeObj(DrResMdoSeamMemObj *obj);
  void releaseTempFreeObj(DrResMdoSeamMemObj *obj);
  DrResMdoSeamMemObj *createFreeObj(u32 size);
  DrResMdoSeamMemObj *createFreeObj(u32 size, DrResChankList<DrResMdoSeamMemObj> &list, int index);
  DrResMdoSeamMemObj *createBackFreeObj(u32 size);
  DrResMdoSeamMemObj *createBackFreeObj(u32 size, DrResChankList<DrResMdoSeamMemObj> &list, int index);
  DrResMdoSeamMemObj *createParentFreeObj(DrResMdoSeamMemObj *parent, u32 size);
  DrResMdoSeamMemObj *createTopFreeObj(u32 size, DrResChankList<DrResMdoSeamMemObj> &list, int index);

  // Inferred helper: takes the start of a free object for a used object of the given size; original name unknown.
  DrResMdoSeamMemObj *unknown001(DrResMdoSeamMemObj *obj, u32 size, DrResChankList<DrResMdoSeamMemObj> &list) {
    u32 rest = obj->m_size - size;
    if (rest == 0) {
      obj->unknown24 = 0;
    } else {
      DrResMdoSeamMemObj *child = unknown10.unknown00;
      if (child == nullptr) {
        return nullptr;
      }
      obj->m_size = size;
      child->m_buffer = obj->m_buffer + size;
      child->m_size = rest;
      unknown10.unknown001(child);
      child->unknown24 = 0;
      list.unknown003(obj, child);
    }
    obj->unknown24 |= 1;
    return obj;
  }

  // Inferred helper: takes the end of a free object for a used object of the given size; original name unknown.
  DrResMdoSeamMemObj *unknown002(DrResMdoSeamMemObj *obj, u32 size, DrResChankList<DrResMdoSeamMemObj> &list) {
    u32 rest = obj->m_size - size;
    if (rest != 0) {
      DrResMdoSeamMemObj *child = unknown10.unknown00;
      if (child == nullptr) {
        return nullptr;
      }
      obj->m_size = rest;
      child->m_size = size;
      child->m_buffer = obj->m_buffer + rest;
      unknown10.unknown001(child);
      child->unknown24 = 0;
      list.unknown003(obj, child);
      obj = child;
    } else {
      obj->unknown24 = 0;
    }
    obj->unknown24 |= 1;
    return obj;
  }

  DrResChankList<DrResMdoSeamMemObj> unknown00; // Inferred role: object list; original member name unknown.
  DrResChankList<DrResMdoSeamMemObj> unknown10; // Inferred role: free object list; original member name unknown.
  s32 unknown20;                                // Inferred role: memory setup value; original member name unknown.
  u32 unknown24;                                // Inferred role: memory setup value, cleared by the constructor; original member name unknown.
  u32 unknown28;                                // Inferred role: memory setup value, cleared by the constructor; original member name unknown.
  u32 unknown2c;                                // Inferred role: flags; original member name unknown.
  u32 unknown30;                                // Inferred role: object count; original member name unknown.
  DrResMdoSeamMemObj *unknown38;                // Inferred role: objects; original member name unknown.
  DrResMdoSeamMemObj *unknown40[64];            // Inferred role: copied objects; original member name unknown.
  DrResMdoSeamMemObj *unknown240[64];           // Inferred role: objects to optimize; original member name unknown.
  s32 unknown440;                               // Inferred role: optimization wait count; original member name unknown.
  s32 unknown444;                               // Inferred role: listed object count; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamMemMan, unknown00) == 0x00, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown24) == 0x24, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown2c) == 0x2c, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown240) == 0x240, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown440) == 0x440, "");
static_assert(offsetof(DrResMdoSeamMemMan, unknown444) == 0x444, "");
static_assert(sizeof(DrResMdoSeamMemMan) == 0x448, "");

} // namespace ml
