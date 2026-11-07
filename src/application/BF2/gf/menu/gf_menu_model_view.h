#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_simple.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
class EffectPack;
struct Transform;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuModelView {
public:
  struct CtrlParam {
    void setMovePosX(f32 value);
    void setMovePosY(f32 value);
    void setMovePosZ(f32 value);
    void setMoveSclX(f32 value);
    void setMoveSclY(f32 value);
    void setMoveSclZ(f32 value);
    void setMoveRotY(f32 value);
    void setMoveAlpha(f32 value);
    void setMoveVanish(f32 value);

    GF_OBJ_HANDLE *unknown00; // Inferred role: object handle; original member name unknown.
    u16 unknown08;            // Inferred role: set value flags; original member name unknown.
    u16 unknown0a;            // Inferred role: curve type; original member name unknown.
    f32 unknown0c;            // Inferred role: duration; original member name unknown.
    bool unknown10;           // Inferred role: set by the CtrlParam constructor; original member name unknown.
    u8 _11[0x14 - 0x11];
    f32 m_movePosX;
    f32 m_movePosY;
    f32 m_movePosZ;
    f32 m_moveSclX;
    f32 m_moveSclY;
    f32 m_moveSclZ;
    f32 m_moveAlpha;
    f32 m_moveRotY;
    f32 m_moveVanish;
  };

  // Inferred role: running object control (startObjectCtrl copies the start values and the CtrlParam targets here).
  struct unknown001 {
    unknown001(GF_OBJ_HANDLE *handle) : unknown00(handle), unknown08() {}

    GF_OBJ_HANDLE *unknown00;      // Inferred role: object handle; original member name unknown.
    ui::UICtrlSimple<9> unknown08; // Inferred role: interpolation of the position, scale, alpha, rotation y and vanish ratio; original member name unknown.
  };

  // Inferred role: effect slot, handle 0 when unused.
  struct unknown002 {
    u32 unknown00; // Inferred role: effect handle; original member name unknown.
    u8 _04[0x08 - 0x04];
    GF_OBJ_HANDLE *unknown08; // Inferred role: effect owner, invalid handle when unused; original member name unknown.
  };

  void update();
  static void setVanishRatio(GF_OBJ_HANDLE *handle, f32 ratio);
  void addWeaponFromBlade(u32 blade, u32 id);
  void delWeaponFromBlade(u32 id);
  u32 getMapObjID(u32 index);
  void sendObjectCommand(GF_OBJ_HANDLE *handle, const char *command);
  void setObjectCommandValue(GF_OBJ_HANDLE *handle, const char *name, int value);
  void attachObject(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone);
  void detachObject(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone);
  static const fw::Transform &getObjectTransform(GF_OBJ_HANDLE *handle);
  static const fw::Transform &getObjectTransformLocal(GF_OBJ_HANDLE *handle);
  static bool getObjectEffectPoint(GF_OBJ_HANDLE *handle, const char *name, mm::Vec3 &position);
  static void setObjectScale(GF_OBJ_HANDLE *handle, const mm::Vec3 &scale);
  static void setObjectDisp(GF_OBJ_HANDLE *handle, bool isDisp);
  static f32 getVanishRatio(GF_OBJ_HANDLE *handle);
  void stopObjectCtrl(GF_OBJ_HANDLE *handle);
  bool isObjectCtrlBusy(GF_OBJ_HANDLE *handle);
  bool isObjectAnimationBusy(GF_OBJ_HANDLE *handle);
  const char *getObjectAnimationState(GF_OBJ_HANDLE *handle);
  void setObjectVanishParam(GF_OBJ_HANDLE *handle, u32 param);
  void setObjectVanishRatio(GF_OBJ_HANDLE *handle, f32 ratio);
  u32 addCamera(mm::mtl::IntrusivePtr<fw::Camera> camera);
  void pushCamera(u32 index, f32 time);
  void popCamera(f32 time);
  void changeCamera(u32 index, f32 time);
  int getCurrentCameraIndex();
  void stopCameraMotion();
  void playEffect(u32 type, const char *name, const mm::Vec3 &position, GF_OBJ_HANDLE *handle);
  u32 createEffect(u32 type, const char *name);
  void playEffectFromCAS(u32 type, const char *name, GF_OBJ_HANDLE *handle);
  bool isPlayEffect(u32 index);
  void stopEffect(u32 index);
  void removeEffect(u32 index);
  bool isLoading() const;
  void delGfObj(u32 type, u32 id);
  GF_OBJ_HANDLE *findGfObj(u32 type, u32 id);
  bool checkGfObj(u32 type, u32 id);

  u8 _00[0x08];
  int unknown08; // Inferred role: row of the model view bdat; original member name unknown.
  u32 unknown0c; // Inferred role: ui object handle; original member name unknown.
  u32 unknown10; // Inferred role: render index; original member name unknown.
  u8 _14[0x28 - 0x14];
  mm::mtl::FixedVector<unknown001, 16> unknown28;                // Inferred role: running object controls; original member name unknown.
  mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::Camera>> unknown930; // Inferred role: cameras; original member name unknown.
  mm::mtl::FixedVector<u32, 16> unknown958;                      // Inferred role: pushed camera indices; original member name unknown.
  fw::EffectPack *unknown9a0;                                    // Inferred role: effect pack; original member name unknown.
  unknown002 unknown9a8[16];                                     // Inferred role: effect slots; original member name unknown.
  bool unknownaa8;                                               // Inferred role: resources loaded; original member name unknown.
  u8 _aa9[0xab8 - 0xaa9];
};

static_assert(sizeof(GfMenuModelView::unknown001) == 0x90, "");
static_assert(sizeof(GfMenuModelView::unknown002) == 0x10, "");
static_assert(offsetof(GfMenuModelView, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuModelView, unknown930) == 0x930, "");
static_assert(offsetof(GfMenuModelView, unknown958) == 0x958, "");
static_assert(offsetof(GfMenuModelView, unknown9a8) == 0x9a8, "");
static_assert(offsetof(GfMenuModelView, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuModelView, unknown9a0) == 0x9a0, "");
static_assert(offsetof(GfMenuModelView, unknownaa8) == 0xaa8, "");
static_assert(sizeof(GfMenuModelView) == 0xab8, "");

} // namespace gf
