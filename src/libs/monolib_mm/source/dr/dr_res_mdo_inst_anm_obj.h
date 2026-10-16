#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

struct DrResMdoInstPartsInfo {
  u32 nameOffset;
  u8 _04[0x08 - 0x04];
  u16 id;
  u8 : 1;
  u8 isRandomStart : 1;
  u8 : 1;
  u8 isNodeAnm : 1;
  u8 isPosAnm : 1;
  u8 isPosMatrix : 1;
  u8 : 1;
  u8 isSwitch : 1;
};

static_assert(offsetof(DrResMdoInstPartsInfo, id) == 0x08, "");

class DrResMdoInstPartsObj {
public:
  virtual ~DrResMdoInstPartsObj();
  virtual void setPosFrame(f32 frame);
  virtual f32 getPosFrame() const;
  virtual f32 getPosMaxFrame() const;
  virtual f32 getPosStartFrame() const;
  virtual void setNodeFrame(f32 frame);
  virtual f32 getNodeFrame() const;
  virtual f32 getCalcNodeFrame() const;
  virtual f32 getCalcOldNodeFrame() const;
  virtual f32 getNodeMaxFrame() const;
  virtual f32 getNodeStartFrame() const;
  virtual u32 getSwitchID() const;
  virtual void setSwitchID(u8 id);
  virtual u32 getSwitchMax() const;
  virtual u32 getSwitchIndex(u32 index) const;
  virtual void update();
  virtual void getMatrix(mm::Mat44 &matrix) const;
  virtual void getAnmMatrix(mm::Mat44 &matrix) const;
  virtual void setMatrix(const mm::Mat44 &matrix);

  u8 : 2;
  u8 m_isLoop : 1;
  u8 m_isColiOff : 1;
  u8 m_isColiSkipData : 1;
  u8 : 3;
  u8 _09[0x10 - 0x09];
  const char *m_names;
  const DrResMdoInstPartsInfo *m_info;
  u8 _20[0x28 - 0x20];
  f32 m_alpha;
};

static_assert(offsetof(DrResMdoInstPartsObj, m_names) == 0x10, "");
static_assert(offsetof(DrResMdoInstPartsObj, m_info) == 0x18, "");
static_assert(offsetof(DrResMdoInstPartsObj, m_alpha) == 0x28, "");

struct DrResMdoInstAnmHeader {
  u8 _00[0x04 - 0x00];
  u32 objMax;
  u32 anmMax;
};

static_assert(offsetof(DrResMdoInstAnmHeader, objMax) == 0x04, "");
static_assert(offsetof(DrResMdoInstAnmHeader, anmMax) == 0x08, "");

class DrResMdoInstAnmObj {
public:
  int getObjIdx(const char *name);

  DrResMdoInstPartsObj *getObj(u32 index) const {
    if (m_header == nullptr) {
      return nullptr;
    }
    return m_objs[index];
  }

  const DrResMdoInstAnmHeader *m_header;
  DrResMdoInstPartsObj **m_objs;
};

static_assert(offsetof(DrResMdoInstAnmObj, m_objs) == 0x08, "");

} // namespace ml
