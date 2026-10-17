#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
struct Message;
class MessageObject;
} // namespace fw

namespace gf {

class GfComPropertyPc;

namespace pc {

class GfPropertyField {
public:
  enum WALL_MOVE_MODE {
    WALL_MOVE_MODE_INVALID = -1,
    WALL_MOVE_MODE_UP = 0,
    WALL_MOVE_MODE_UP_RIGHT = 1,
    WALL_MOVE_MODE_RIGHT = 2,
    WALL_MOVE_MODE_DOWN_RIGHT = 3,
    WALL_MOVE_MODE_DOWN = 4,
    WALL_MOVE_MODE_DOWN_LEFT = 5,
    WALL_MOVE_MODE_LEFT = 6,
    WALL_MOVE_MODE_UP_LEFT = 7,
  };

  virtual void setup(const GfComPropertyPc &property);
  virtual void cleanup(const GfComPropertyPc &property);
  virtual void flush(const GfComPropertyPc &property);
  virtual void flushOwner(GfComPropertyPc &property);
  virtual bool recieveMessage(const GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message);

  mm::mtl::IntrusivePtr<fw::ParamList> paramList;
  u32 isWalkMode : 1;
  u32 : 1;
  u32 isIdle : 1;
  u32 : 5;
  u32 isAutoRun : 1;
  u32 : 2;
  u32 isSlide : 1;
  u32 : 20;
  WALL_MOVE_MODE wallMoveMode;
  u8 _18[0x130 - 0x18];
};

static_assert(offsetof(GfPropertyField, paramList) == 0x08, "");
static_assert(offsetof(GfPropertyField, wallMoveMode) == 0x14, "");
static_assert(sizeof(GfPropertyField) == 0x130, "");

} // namespace pc
} // namespace gf
