#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CaptureManager : public IManager, public mm::mtl::Singleton<CaptureManager> {
public:
  static const char *MOV_PATH;                // Name given by the xc2 symbol _ZN5event14CaptureManager8MOV_PATHE.
  static const char *MOV_PATH_OFS;            // Name given by the xc2 symbol _ZN5event14CaptureManager12MOV_PATH_OFSE.
  static const char *JPG_PATH;                // Name given by the xc2 symbol _ZN5event14CaptureManager8JPG_PATHE.
  static const char *JPG_PATH_OFS;            // Name given by the xc2 symbol _ZN5event14CaptureManager12JPG_PATH_OFSE.
  static const char *CONV_PATH;               // Name given by the xc2 symbol _ZN5event14CaptureManager9CONV_PATHE.
  static constexpr u32 CUT_UNKNOWN_512 = 512; // Inferred role: cut count; original name unknown.

  enum MODE {
    MODE_UNKNOWN_0, // Inferred role: movie; original name unknown.
    MODE_UNKNOWN_1, // Inferred role: developer; original name unknown.
    MODE_UNKNOWN_2, // Inferred role: composer; original name unknown.
    MODE_UNKNOWN_3, // Inferred role: aftereffect; original name unknown.
    MODE_UNKNOWN_4, // Inferred role: sound; original name unknown.
    MODE_UNKNOWN_5, // Inferred role: effect; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: reserve flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: capture flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: multi flag; original name unknown.
  };

  CaptureManager();
  virtual ~CaptureManager() {}
  void clear();
  void stop();
  void update();
  void render();
  void reserve(bool isReserve, MODE mode, bool isMulti);
  void reserveFilter(int filter);
  void ready();
  void start();
  virtual void OnEventProc(MSG_TYPE type);

private:
  bool isJpegMode() const { return static_cast<u32>(unknown14 - MODE_UNKNOWN_3) < 3; }

  u32 unknown10;                                                        // Inferred role: flags; original member name unknown.
  MODE unknown14;                                                       // Inferred role: mode; original member name unknown.
  int unknown18;                                                        // Inferred role: filter; original member name unknown.
  int unknown1c;                                                        // Inferred role: captured frame count; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixStr<16>, CUT_UNKNOWN_512> unknown20; // Inferred role: cut names; original member name unknown.
  mm::mtl::FixStr<128> unknown2828;                                     // Inferred role: directory; original member name unknown.
  mm::mtl::FixStr<128> unknown28ac;                                     // Inferred role: file name; original member name unknown.
  mm::mtl::FixStr<128> unknown2930;                                     // Inferred role: raw movie path; original member name unknown.
  mm::mtl::FixStr<128> unknown29b4;                                     // Inferred role: movie path; original member name unknown.
  mm::mtl::FixStr<128> unknown2a38;                                     // Inferred role: half movie path; original member name unknown.

  friend struct CaptureManagerLayout;
};

struct CaptureManagerLayout {
  static_assert(offsetof(CaptureManager, unknown1c) == 0x1c, "");
};

static_assert(sizeof(CaptureManager) == 0x2ac0, "");

} // namespace event
