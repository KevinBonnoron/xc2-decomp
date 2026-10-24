#include "gf/field/gf_field_zone.h"
#include "gf/field/gf_field_zone_script.h"
#include "gf/field/gf_field_zone_se.h"
#include "gf/gf_allocator.h"

namespace gf {

GfFieldZone::GfFieldZone(const GfSetupParam &param) : unknown98(false) { initialize(param); }

void GfFieldZone::initialize(const GfSetupParam &param) {
  GfFieldZoneSe::build(param);
  GfFieldZoneScript::build(param);
  unknown98 = true;
}

GfFieldZone::~GfFieldZone() {}

void GfFieldZone::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldZone(param); }

void GfFieldZone::destroy() {
  GfFieldZone *zone = get();
  zone->finalize();
  delete zone;
}

void GfFieldZone::finalize() {
  GfFieldZoneScript::destroy();
  GfFieldZoneSe::destroy();
  unknown98 = false;
}

bool GfFieldZone::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown98;
  }

  return false;
}

void GfFieldZone::update(const fw::UpdateInfo &) {}

void GfFieldZone::gevMapjump(GEV gev, const MapjumpCallbackInfo &) {
  if (gev == GEV_MAPJUMP_DESTROY_FIELD) {
    GfFieldZoneScript::destroyScript();
  }
}

} // namespace gf
