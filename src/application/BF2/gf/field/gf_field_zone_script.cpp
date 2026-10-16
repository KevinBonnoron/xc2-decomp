#include "gf/field/gf_field_zone_script.h"

#include "gf/gf_allocator.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"

namespace gf {

GfFieldZoneScript::GfFieldZoneScript(const GfSetupParam &param) { initialize(param); }

void GfFieldZoneScript::initialize(const GfSetupParam &) {
  mInitialized = true;
  GfFieldZone::addEvent(this);
}

GfFieldZoneScript::~GfFieldZoneScript() { ; }

void GfFieldZoneScript::build(const GfSetupParam &param) {
  // __LINE__ must be 22 as in the original file: its value changes the instruction order.
#line 22
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldZoneScript(param);
}

void GfFieldZoneScript::destroy() {
  GfFieldZoneScript *script = get();
  script->finalize();
  delete script;
}

void GfFieldZoneScript::finalize() {
  GfFieldZone::addEvent(this);
  mInitialized = false;
}

bool GfFieldZoneScript::isInitialized() {
  if (get() != nullptr) {
    return get()->mInitialized;
  }

  return false;
}

void GfFieldZoneScript::update(const fw::UpdateInfo &) {}

void GfFieldZoneScript::destroyScript() { SCOM_SCRIPT::create(SCRIPT_SLOT_FIELD, nullptr, false); }

bool GfFieldZoneScript::isExecScriptBusy() {
  if (GfScriptManager::isScriptLoadError(SCRIPT_SLOT_FIELD)) {
    return false;
  }

  return !GfScriptManager::isScriptActive(SCRIPT_SLOT_FIELD);
}

bool GfFieldZoneScript::isDestroyScriptBusy() {
  if (GfScriptManager::isScriptLoadError(SCRIPT_SLOT_FIELD)) {
    return false;
  }

  return GfScriptManager::isScriptActive(SCRIPT_SLOT_FIELD);
}

} // namespace gf
