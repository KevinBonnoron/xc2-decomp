#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

struct GfSetupPfTalk {
  int unknown00;            // Inferred role: event; original member name unknown.
  GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  u32 unknown10;            // Inferred role: param 0; original member name unknown.
  u32 unknown14;            // Inferred role: param 1; original member name unknown.
};

static_assert(sizeof(GfSetupPfTalk) == 0x18, "");

class GfGameTalk : public mm::mtl::PtrSingleton<GfGameTalk> {
public:
  GfGameTalk(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameTalk();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  static bool isPlaying();
  static bool isError();
  static void play(const GfSetupPfTalk &talk);
  static void end();

private:
  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(GfGameTalk) == 0x10, "");

} // namespace gf
