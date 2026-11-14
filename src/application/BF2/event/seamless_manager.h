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
  static constexpr u32 FIRST_KEY_UNKNOWN_16 = 16;    // Inferred role: first key count; original name unknown.
  static constexpr u32 SEAM_POINT_UNKNOWN_256 = 256; // Inferred role: seam point count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: first flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: seam flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: read enable flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
  };

  struct FirstKey {
    FirstKey(const char *name, const PosAxis &axis, const mm::Vec3 &pos) {
      this->unknown00 = name;
      this->unknown20 = axis;
      this->unknown40 = pos;
    }

    mm::mtl::FixStr<16> unknown00; // Inferred role: name; original member name unknown.
    PosAxis unknown20;             // Inferred role: axis; original member name unknown.
    mm::Vec3 unknown40;            // Inferred role: pos; original member name unknown.
  };

  // Inferred role: seam point; original type name unknown.
  struct unknown001 {
    unknown001(f32 frame, const mm::Vec3 &pos) : unknown00(frame), unknown10(pos) {}

    f32 unknown00;      // Inferred role: frame; original member name unknown.
    mm::Vec3 unknown10; // Inferred role: pos; original member name unknown.
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
  u32 unknown10;                                                       // Inferred role: flags; original member name unknown.
  u32 unknown14;                                                       // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixedVector<FirstKey, FIRST_KEY_UNKNOWN_16> unknown20;      // Inferred role: first keys; original member name unknown.
  mm::Vec3 unknown530;                                                 // Inferred role: read pos; original member name unknown.
  mm::mtl::FixedVector<unknown001, SEAM_POINT_UNKNOWN_256> unknown540; // Inferred role: seam points; original member name unknown.
  mm::Vec3 unknown2550;                                                // Inferred role: current pos; original member name unknown.
};

static_assert(sizeof(SeamlessManager::FirstKey) == 0x50, "");
static_assert(sizeof(SeamlessManager::unknown001) == 0x20, "");
static_assert(sizeof(SeamlessManager) == 0x2560, "");

} // namespace event
