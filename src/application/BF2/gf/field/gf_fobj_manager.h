#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/field/gf_fobj_gotten_effect_manager.h"
#include "gf/field/gf_fobj_se_manager.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
class GfDropitemParams;
class GfFobjDropitem;

// The IGfObjListener base sits at 0x08 and the IGfEvent base at 0x10: the game's non-virtual thunks adjust this by -8 and -16.
class GfFobjManager : public mm::mtl::PtrSingleton<GfFobjManager>, public IGfObjListener, public IGfEvent {
public:
  GfFobjManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFobjManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static void update(const fw::UpdateInfo &info);
  static bool isInitialized();
  static bool isExistObj();
  static void destroyObj();
  void leaveGameField(GF_OBJ_HANDLE *handle);
  static void registFiledObj(GfFobjDropitem *dropitem);
  static void debugRecreateBdat_dropitem();
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;
  void gevPlayEvent(GEV event, u32 value) override;
  void gevGameObjLeave(GF_OBJ_HANDLE *handle) override;
  static GfDropitemParams *getDropitemParams();

  mm::mtl::FixedList<GfFobjDropitem *, 1024> unknown18;   // Inferred role: dropitems waiting for their object; original member name unknown.
  mm::mtl::FixedList<GfFobjDropitem *, 1024> unknown4838; // Inferred role: dropitems of the loaded objects; original member name unknown.
  bool unknown9058;                                       // Inferred role: initialized; original member name unknown.
  u8 _9059[0x9060 - 0x9059];
  GfDropitemParams *unknown9060; // Inferred role: dropitem params; original member name unknown.
  u8 *unknown9068;               // Inferred role: dropitem bdat; original member name unknown.
  u8 *unknown9070;               // Inferred role: dropitem param bdat; original member name unknown.
  bool unknown9078;              // Inferred role: dropitems are displayed (cleared while an event plays); original member name unknown.
  f32 unknown907c;               // Inferred role: dropitem collect range, read by GfFobjDropitem and ramped by GfReqCommand::execWaitEvent; original member name unknown.
  bool unknown9080;              // Inferred role: set while the collect range is ramped; original member name unknown.
  u8 _9081[0x9088 - 0x9081];
  GfFobjGottenEffectManager unknown9088; // Inferred role: effects of the gotten dropitems; original member name unknown.
  GfFobjSeManager unknown90d0;           // Inferred role: sounds of the dropitems; original member name unknown.
};

static_assert(offsetof(GfFobjManager, unknown18) == 0x18, "");
static_assert(offsetof(GfFobjManager, unknown4838) == 0x4838, "");
static_assert(offsetof(GfFobjManager, unknown9058) == 0x9058, "");
static_assert(offsetof(GfFobjManager, unknown9060) == 0x9060, "");
static_assert(offsetof(GfFobjManager, unknown9068) == 0x9068, "");
static_assert(offsetof(GfFobjManager, unknown9070) == 0x9070, "");
static_assert(offsetof(GfFobjManager, unknown9078) == 0x9078, "");
static_assert(offsetof(GfFobjManager, unknown907c) == 0x907c, "");
static_assert(offsetof(GfFobjManager, unknown9080) == 0x9080, "");
static_assert(offsetof(GfFobjManager, unknown9088) == 0x9088, "");
static_assert(offsetof(GfFobjManager, unknown90d0) == 0x90d0, "");
static_assert(sizeof(GfFobjManager) == 0x9120, "");

} // namespace gf
