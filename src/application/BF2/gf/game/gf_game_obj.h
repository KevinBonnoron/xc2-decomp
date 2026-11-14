#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Vec3;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
class GfObj;
enum OPTMNT : u32;
struct GF_MOUNT_HANDLE;
struct MsgObjectNotifyDead;

enum {
  GAME_UNKNOWN_1024 = 1024, // Inferred role: game obj list capacity; original name unknown.
};

class GfObjAcc;
class GfGameObjEnemy;

// Name from the game symbol mm::mtl::FixedList<gf::ObjMsg, 256>::erase, called by GfGameObj::update and GfGameObj::removeGameObj.
struct ObjMsg {
  GF_OBJ_HANDLE *unknown00; // Inferred role: object handle; original member name unknown.
  u32 unknown08;            // Inferred role: attribute; original member name unknown.
};

class GfGameObj : public mm::mtl::PtrSingleton<GfGameObj>, public IGfObjListener {
public:
  struct INOUT {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object handle; original member name unknown.
    f32 unknown08;            // Inferred role: fade time elapsed; original member name unknown.
    f32 unknown0c;            // Inferred role: fade time; original member name unknown.
    f32 unknown10;            // Inferred role: alpha of the object when the fade started; original member name unknown.
    bool unknown14;           // Role and original member name unknown.
    bool unknown15;           // Inferred role: entering the game; original member name unknown.
    bool unknown16;           // Inferred role: effect fade enabled; original member name unknown.
    u8 _17[0x18 - 0x17];
  };

  explicit GfGameObj(const GfSetupParam &param);
  ~GfGameObj() override;
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;
  void finalize();
  void initialize(const GfSetupParam &param);
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void postUpdate(const fw::UpdateInfo &info);
  static const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *getList(u32 objectType);
  static void getList(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list, u32 objectType);
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *getListType(u32 objectType, GF_OBJ_HANDLE *handle);
  static const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *getListEnemyBlade();
  static void getListEnemyBlade(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list);
  static bool isEmpty();
  static bool isExistEnemy();
  static void bdatReload();
  static void refreshBdat(GF_OBJ_HANDLE *handle);
  static void refreshBdatInOut(INOUT &inout);
  static bool isValidGameObj(GF_OBJ_HANDLE *handle, bool isCheckState, mm::mtl::FixStr<128> *reason);
  static bool isEnterGameObj(GF_OBJ_HANDLE *handle);
  static bool isDestroyGameObj(GF_OBJ_HANDLE *handle);
  static void setupEnterGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static GfObj *getObj(GF_OBJ_HANDLE *handle);
  bool isEffectFadeEnd(const INOUT &inout, const GfObjAcc &acc) const;
  bool fadeinGameObj(INOUT &inout, GfObjAcc &acc, const fw::UpdateInfo &info);
  void removeGameObjCommon(GfObjAcc &acc);
  void addGameObj(GF_OBJ_HANDLE *handle);
  bool isBattle(const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list) const;
  void calcCameraFade(const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list, const mm::Vec3 &cameraPosition);
  void enableGameObj(GfObjAcc &acc, bool isEnable);
  bool fadeoutGameObj(INOUT &inout, GfObjAcc &acc, const fw::UpdateInfo &info);
  void setupEffectFadeout(INOUT &inout, GfObjAcc &acc, const fw::UpdateInfo &info);
  static void destroyGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static void addCharDeadMessage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDead &message);
  bool addOutObj(GF_OBJ_HANDLE *handle, f32 fadeTime, bool isEffect);
  static bool isBattle();
  void flushEvent();
  static void setupEnterGameObjMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 fadeTime);
  static void destroyGameObjWithAttribute(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute);
  static void changeStopLayer(u32 objectType, bool isStop);
  static void changeStopLayerIgnoreEventObj(u32 layer, bool isIgnore);
  u32 getObjNumberByEnArrangeId(u32 arrange);
  void updateObjectProperty();
  void updateObjectProperty(u32 objectType);
  static bool isInitialized();
  static bool isGameObjWaiting(GF_OBJ_HANDLE *handle);
  static void enterStayObject(GF_OBJ_HANDLE *handle);
  static void enterStayObject(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void enterStayObject(GF_MOUNT_HANDLE *mountHandle);
  static void enterStayObjectMount(GF_OBJ_HANDLE *handle, GFATTACH attach);
  void addInObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static void setupLeaveGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime);
  static void setupLeaveGameObjMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 fadeTime);
  static void enterStayObjectWithVolumeFade(GF_OBJ_HANDLE *handle);
  static void enterStayObjectWithVolumeFade(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void enterStayObjectWithVolumeFade(GF_MOUNT_HANDLE *mountHandle);
  static void enterStayObjectMountWithVolumeFade(GF_OBJ_HANDLE *handle, GFATTACH attach);

  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown10;      // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown4830;    // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown9050;    // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknownd870;    // Inferred role: enemy blades; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown12090;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown168b0;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown1b0d0;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown1f8f0;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown24110;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown28930;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown2d150;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown31970;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown36190;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown3a9b0;   // Inferred role: object list; original member name unknown.
  mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024> unknown3f1d0;             // Inferred role: objects entering the game; original member name unknown.
  mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024> unknown47a00;             // Inferred role: objects leaving the game; original member name unknown.
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown50230; // Inferred role: entered objects of the frame; original member name unknown.
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> unknown52238; // Inferred role: left objects of the frame; original member name unknown.
  mm::mtl::FixedList<ObjMsg, 256> unknown54240;                          // Inferred role: objects destroyed with an attribute; original member name unknown.
  GfGameObjEnemy *unknown55c68;                                          // Inferred role: enemy manager; original member name unknown.
  bool unknown55c70;                                                     // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>) == 0x4820, "");
static_assert(sizeof(mm::mtl::FixedList<GfGameObj::INOUT, GAME_UNKNOWN_1024>) == 0x8830, "");
static_assert(offsetof(GfGameObj, unknown10) == 0x10, "");
static_assert(offsetof(GfGameObj, unknown4830) == 0x4830, "");
static_assert(offsetof(GfGameObj, unknown9050) == 0x9050, "");
static_assert(offsetof(GfGameObj, unknown12090) == 0x12090, "");
static_assert(offsetof(GfGameObj, unknown168b0) == 0x168b0, "");
static_assert(offsetof(GfGameObj, unknown1b0d0) == 0x1b0d0, "");
static_assert(offsetof(GfGameObj, unknown1f8f0) == 0x1f8f0, "");
static_assert(offsetof(GfGameObj, unknown24110) == 0x24110, "");
static_assert(offsetof(GfGameObj, unknown28930) == 0x28930, "");
static_assert(offsetof(GfGameObj, unknown2d150) == 0x2d150, "");
static_assert(offsetof(GfGameObj, unknown31970) == 0x31970, "");
static_assert(offsetof(GfGameObj, unknown36190) == 0x36190, "");
static_assert(offsetof(GfGameObj, unknown3a9b0) == 0x3a9b0, "");
static_assert(offsetof(GfGameObj, unknown47a00) == 0x47a00, "");
static_assert(offsetof(GfGameObj, unknownd870) == 0xd870, "");
static_assert(sizeof(GfGameObj::INOUT) == 0x18, "");
static_assert(offsetof(GfGameObj, unknown3f1d0) == 0x3f1d0, "");
static_assert(offsetof(GfGameObj, unknown50230) == 0x50230, "");
static_assert(offsetof(GfGameObj, unknown52238) == 0x52238, "");
static_assert(offsetof(GfGameObj, unknown54240) == 0x54240, "");
static_assert(offsetof(GfGameObj, unknown55c68) == 0x55c68, "");
static_assert(offsetof(GfGameObj, unknown55c70) == 0x55c70, "");

} // namespace gf
