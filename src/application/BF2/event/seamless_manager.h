#pragma once
#include "event/i_manager.h"
#include "event/pos_axis.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class SeamlessManager : public IManager, public mm::mtl::Singleton<SeamlessManager> {
public:
  static constexpr u32 FIRST_KEY_COUNT = 16;
  static constexpr u32 SEAM_POINT_COUNT = 256;

  enum {
    FLAG_FIRST = 1 << 0,
    FLAG_SEAM = 1 << 1,
    FLAG_READ_ENABLE = 1 << 2,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  struct FirstKey {
    FirstKey(const char *name, const PosAxis &axis, const mm::Vec3 &pos) {
      this->name = name;
      this->axis = axis;
      this->pos = pos;
    }

    mm::mtl::FixStr<16> name;
    PosAxis axis;
    mm::Vec3 pos;
  };

  struct SeamPoint {
    SeamPoint(f32 frame, const mm::Vec3 &pos) : frame(frame), pos(pos) {}

    f32 frame;
    mm::Vec3 pos;
  };

  SeamlessManager();
  void clear();
  void setReadEnable(bool isEnable, const mm::Vec3 *pos);
  void update();
  void render();
  void addFirstSeamPoint(const char *name, const PosAxis &axis);
  void readFirstSeamPoint(const char *name);
  void readNextSeamPoint(const char *name);
  void addSeamPoint(f32 frame, const PosAxis &axis);
  bool isActiveSeamPoint() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  u32 dispFlags;
  mm::mtl::FixedVector<FirstKey, FIRST_KEY_COUNT> firstKeys;
  mm::Vec3 readPos;
  mm::mtl::FixedVector<SeamPoint, SEAM_POINT_COUNT> seamPoints;
  mm::Vec3 currentPos;
};

static_assert(sizeof(SeamlessManager::FirstKey) == 0x50, "");
static_assert(sizeof(SeamlessManager::SeamPoint) == 0x20, "");
static_assert(sizeof(SeamlessManager) == 0x2560, "");

} // namespace event
