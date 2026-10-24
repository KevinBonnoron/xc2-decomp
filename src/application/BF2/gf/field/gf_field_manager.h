#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class EffectPack;
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GfSetupParam;

class GfFieldManager : public mm::mtl::PtrSingleton<GfFieldManager>, public IGfObjListener, public IGfEvent {
public:
  GfFieldManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFieldManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void clear();
  static void setupGame();
  void setSuspendGame(bool isSuspend);
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info) override;
  void gevReloadBdat(RELOAD_BDAT reload, u32 value) override;
  void gevBattleStart() override;
  void gevBattleEnd() override;
  void gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter) override;
  void gevPause(u32 resumeBits, u32 pauseBits) override;
  void gevPlayEvent(GEV event, u32 value) override;
  static bool isExistObj();
  static void destroyObj();
  static fw::EffectPack *getEffectPack();
  void getFieldParam(u32 mapJump);
  static bool execMapScript(const char *script);
  static void destroyMapScript();
  static bool isExecMapScriptBusy();
  static bool isDestroyMapScriptBusy();
  static void updateGlobalWind();
  static f32 getEnemyBaloonRadius();
  static const char *getMapName();
  static bool getLandmarkNameId(u8 *&bdat, int &textId);
  static void setLandmarkPoint(u32 landmark, const mm::Vec3 &position, f32 rotationY);
  static u32 getLandmarkPoint();
  static const mm::Vec3 &getLandmarkPos();
  static f32 getLandmarkRotY();
  void postUpdate(const fw::UpdateInfo &info);
  void update(const fw::UpdateInfo &info);

  bool unknown18; // Inferred role: initialized; original member name unknown.
  f32 unknown1c;  // Inferred role: enemy baloon radius; original member name unknown.
};

static_assert(offsetof(GfFieldManager, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldManager, unknown1c) == 0x1c, "");
static_assert(sizeof(GfFieldManager) == 0x20, "");

} // namespace gf
