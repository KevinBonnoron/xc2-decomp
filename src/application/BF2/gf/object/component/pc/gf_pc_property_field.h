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
  void resetStatus(const GfComPropertyPc &property);

  mm::mtl::IntrusivePtr<fw::ParamList> unknown08; // Inferred role: param list; original member name unknown.
  u32 unknown10_0 : 1;                            // Inferred role: walk mode; original member name unknown.
  u32 : 1;
  u32 unknown10_2 : 1; // Inferred role: idle; original member name unknown.
  u32 unknown10_3 : 1; // Inferred role: pad control; original member name unknown.
  u32 : 4;
  u32 unknown11_0 : 1; // Inferred role: auto run; original member name unknown.
  u32 : 2;
  u32 unknown11_3 : 1; // Inferred role: slide; original member name unknown.
  u32 : 5;
  u32 unknown12_1 : 1; // Inferred role: field status reset; original member name unknown.
  u32 : 14;
  WALL_MOVE_MODE unknown14; // Inferred role: wall move mode; original member name unknown.
  u8 _18[0x130 - 0x18];
};

static_assert(offsetof(GfPropertyField, unknown08) == 0x08, "");
static_assert(offsetof(GfPropertyField, unknown14) == 0x14, "");
static_assert(sizeof(GfPropertyField) == 0x130, "");

} // namespace pc
} // namespace gf
