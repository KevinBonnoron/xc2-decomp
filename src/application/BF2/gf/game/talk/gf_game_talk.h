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
  int event;
  GF_OBJ_HANDLE *handle;
  u32 param0;
  u32 param1;
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
  static void play(const GfSetupPfTalk &talk);
  static void end();

private:
  bool initialized;
};

static_assert(sizeof(GfGameTalk) == 0x10, "");

} // namespace gf
