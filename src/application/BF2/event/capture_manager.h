#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CaptureManager : public IManager, public mm::mtl::Singleton<CaptureManager> {
public:
  static const char *MOV_PATH;
  static const char *MOV_PATH_OFS;
  static const char *JPG_PATH;
  static const char *JPG_PATH_OFS;
  static const char *CONV_PATH;
  static constexpr u32 CUT_COUNT = 512;

  enum MODE {
    MODE_MOVIE,
    MODE_DEVELOPER,
    MODE_COMPOSER,
    MODE_AFTEREFFECT,
    MODE_SOUND,
    MODE_EFFECT,
  };

  enum {
    FLAG_RESERVE = 1 << 0,
    FLAG_CAPTURE = 1 << 1,
    FLAG_MULTI = 1 << 2,
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
  bool isJpegMode() const { return static_cast<u32>(unknown14 - MODE_AFTEREFFECT) < 3; }

  u32 unknown10;                                                  // Inferred role: flags; original member name unknown.
  MODE unknown14;                                                 // Inferred role: mode; original member name unknown.
  int unknown18;                                                  // Inferred role: filter; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixStr<16>, CUT_COUNT> unknown20; // Inferred role: cut names; original member name unknown.
  mm::mtl::FixStr<128> unknown2828;                               // Inferred role: directory; original member name unknown.
  mm::mtl::FixStr<128> unknown28ac;                               // Inferred role: file name; original member name unknown.
  mm::mtl::FixStr<128> unknown2930;                               // Inferred role: raw movie path; original member name unknown.
  mm::mtl::FixStr<128> unknown29b4;                               // Inferred role: movie path; original member name unknown.
  mm::mtl::FixStr<128> unknown2a38;                               // Inferred role: half movie path; original member name unknown.
};

static_assert(sizeof(CaptureManager) == 0x2ac0, "");

} // namespace event
