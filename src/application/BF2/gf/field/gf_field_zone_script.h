#pragma once
#include "gf/field/gf_field_zone.h"
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfFieldZoneScript : public mm::mtl::PtrSingleton<GfFieldZoneScript>, public IEventZone {
public:
  GfFieldZoneScript(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFieldZoneScript();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  static bool execScript(const char *script);
  static void destroyScript();
  static bool isExecScriptBusy();
  static bool isDestroyScriptBusy();

private:
  bool unknown10; // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(GfFieldZoneScript) == 0x18, "");

} // namespace gf
