#pragma once
#include "gf/field/gf_field_zone.h"
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfFieldZoneSe : public mm::mtl::PtrSingleton<GfFieldZoneSe>, public IEventZone {
public:
  GfFieldZoneSe(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFieldZoneSe();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);

private:
  bool unknown10; // Inferred role: m initialized; original member name unknown.
};

static_assert(sizeof(GfFieldZoneSe) == 0x18, "");

} // namespace gf
