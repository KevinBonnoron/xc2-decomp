#include "gf/field/gf_field_zone_se.h"
#include "gf/gf_allocator.h"

namespace gf {

GfFieldZoneSe::GfFieldZoneSe(const GfSetupParam &param) { initialize(param); }

void GfFieldZoneSe::initialize(const GfSetupParam &) {
  mInitialized = true;
  GfFieldZone::addEvent(this);
}

GfFieldZoneSe::~GfFieldZoneSe() {
  // A body that is not empty keeps the vtable pointer store of IEventZone that the game does.
  ;
}

void GfFieldZoneSe::build(const GfSetupParam &param) {
  // __LINE__ must be 39 as in the original file: its value changes the instruction order.
#line 39
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldZoneSe(param);
}

void GfFieldZoneSe::destroy() {
  GfFieldZoneSe *se = get();
  se->finalize();
  delete se;
}

void GfFieldZoneSe::finalize() {
  GfFieldZone::removeEvent(this);
  mInitialized = false;
}

bool GfFieldZoneSe::isInitialized() {
  if (get() != nullptr) {
    return get()->mInitialized;
  }

  return false;
}

void GfFieldZoneSe::update(const fw::UpdateInfo &) {}

} // namespace gf
