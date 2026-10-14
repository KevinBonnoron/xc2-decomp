#pragma once
#include "framework/message/message_object.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
class GfComTransform;

struct MsgPcResetState : fw::Message {
  MsgPcResetState() : fw::Message(0x1000007, 0x40) {}
};

class GfGamePlayerPicker : public mm::mtl::PtrSingleton<GfGamePlayerPicker>, public fw::MessageObject {
public:
  static void build(const GfSetupParam &param);
  void setup(const GfSetupParam &param);
  static void destroy();
  void cleanup();
  void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  static bool isPick();
  GfGamePlayerPicker();
  ~GfGamePlayerPicker();
  bool isEnableChange() const;
  void onActive();
  void onDeactive();
  GF_OBJ_HANDLE *getPlayerHandle() const;
  void calcWorldDir(GfComTransform *transform);
  void movePlayer(GfComTransform *transform);
  void dispStatus(GfComTransform *transform);

private:
  u32 mSpeedLevel;
  bool mIsPick;
  bool mIsModifierReleased;
  mm::Vec3 mUpDir;
  mm::Vec3 mFrontDir;
  mm::Vec3 mRightDir;
};

static_assert(sizeof(GfGamePlayerPicker) == 0x60, "");

} // namespace gf
