#pragma once
#include "framework/message/message_object.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

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
  u32 unknown20;      // Inferred role: speed level; original member name unknown.
  bool unknown24;     // Inferred role: pick; original member name unknown.
  bool unknown25;     // Inferred role: modifier released; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: up direction; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: front direction; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: right direction; original member name unknown.
};

static_assert(sizeof(GfGamePlayerPicker) == 0x60, "");

} // namespace gf
