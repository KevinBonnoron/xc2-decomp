#pragma once
#include "event/i_res_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

enum MODEL_TYPE {
  MODEL_TYPE_PATH = 0,
  MODEL_TYPE_NONE = 3,
};

class ModelObj : public IResEvent {
public:
  enum {
    FLAG_PRIORITY = 1 << 0,
    FLAG_SAME = 1 << 1,
  };

  virtual ~ModelObj();
  void setReserve(u32 index, bool isReserve);
  bool isReserve(int index);
  bool isSame(const char *path, bool isPriority, u32 id);
  bool isSame();
  gf::GF_OBJ_HANDLE *getHandle() const { return handle; }
  virtual void OnResEvent(const PARAM &param);

private:
  u32 flags;
  MODEL_TYPE mType;
  u8 _10[0x18 - 0x10];
  mm::mtl::FixStr<64> path;
  u32 mId;
  u8 _60[0x120 - 0x60];
  gf::GF_OBJ_HANDLE *handle;
  u8 _128[0x134 - 0x128];
  u32 mReserve;
};

static_assert(sizeof(ModelObj) == 0x138, "");

} // namespace event
