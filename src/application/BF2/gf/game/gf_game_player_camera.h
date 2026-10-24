#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class Camera;
class CameraTarget;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

struct MsgPcResetCamera : fw::Message {};

class GfGamePlayerCamera : public mm::mtl::PtrSingleton<GfGamePlayerCamera>, public IGfEvent, public fw::MessageObject {
public:
  static void build(const GfSetupParam &param);
  void setup();
  static void destroy();
  void cleanup();
  static void resetCameraForSceneJump();
  static void resetCamera();
  static void requestResetCamera();
  static void resetCameraClimb(ResetCameraWallTiming timing);
  static void resetCameraLoad();
  static void resetCameraBattleWarp();
  static void setTargetObject(GF_OBJ_HANDLE *handle);
  static bool isManualCamera();
  static void setTargetPlayer(GF_OBJ_HANDLE *handle);
  static f32 getSaveYaw();
  static f32 getSavePitch();
  static f32 getSaveDistance();
  static f32 getSaveHeight();
  static u32 getSaveSide();
  static bool isSaveFreeMode();
  GfGamePlayerCamera();
  ~GfGamePlayerCamera();
  void gevPartyMemberOK(bool isOK) override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  static void procMsgPcResetCamera(fw::MessageObject *sender, MsgPcResetCamera &message);

  mm::mtl::IntrusivePtr<fw::Camera> unknown28;       // Inferred role: camera; original member name unknown.
  mm::mtl::IntrusivePtr<fw::CameraTarget> unknown30; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(GfGamePlayerCamera, unknown28) == 0x28, "");
static_assert(offsetof(GfGamePlayerCamera, unknown30) == 0x30, "");
static_assert(sizeof(GfGamePlayerCamera) == 0x38, "");

} // namespace gf
