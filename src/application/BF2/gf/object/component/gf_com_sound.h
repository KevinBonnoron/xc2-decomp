#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "framework/sound/sound_variable_table.h"
#include "gf/object/component/gf_component.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/list.h"
#include "types.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

enum SoundVariable : int {
  SOUND_VARIABLE_UNKNOWN_0,
  SOUND_VARIABLE_UNKNOWN_1,
  SOUND_VARIABLE_UNKNOWN_2,
  SOUND_VARIABLE_UNKNOWN_3,
  SOUND_VARIABLE_UNKNOWN_4,
};

enum SoundVariableWall : int {
  SOUND_VARIABLE_WALL_UNKNOWN_0,
  SOUND_VARIABLE_WALL_UNKNOWN_1,
};

enum SoundVariableWaterDepth : int {
  SOUND_VARIABLE_WATER_DEPTH_UNKNOWN_0,
  SOUND_VARIABLE_WATER_DEPTH_UNKNOWN_1,
};

enum SoundVarMoveStatus : int {
  SOUND_VAR_MOVE_STATUS_UNKNOWN_0,
  SOUND_VAR_MOVE_STATUS_UNKNOWN_1,
};

extern const char *SND_VAR_WATER_THRESOULD_NAME;

const char *getSoundVariableName(SoundVariable variable);
const char *getMaterialVariableName(int variable);
const char *getWallVariableName(SoundVariableWall variable);
const char *getWaterDepthVariableName(SoundVariableWaterDepth variable);
const char *getMoveStatusVariableName(SoundVarMoveStatus variable);
int getMaterialVariable(const char *name);
const char *getAttributeVariableName(int variable);
int getAttrbiteVariable(const char *name);
int getWallVariable(const char *name);
int getWaterDepthVariable(const char *name);
int getMoveStatusVariable(const char *name);

// Declaration rebuilt from the game's symbols (gf::GfComSound::stopSe, playSe2D); the component slot comes from the access offset 0x88.
// Layout evidence: GfComSound::GfComSound() (0x710057ead4) builds the variable table at 0x10 and the sound list at 0x30 with its terminator SoundInfo at 0x50. It also builds members from
// 0xf0 to 0x150, a viewer listener at 0x158 and a viewer pointer at 0x168, which no compiled function uses yet and which are therefore not declared.
class GfComSound : public GfComponent {
public:
  // Layout evidence: its copy constructor (0x71005802c0) copies the members below one by one.
  struct SoundInfo {
    u32 unknown00;                                       // Role and original member name unknown.
    mm::mtl::FixStr<32> unknown04;                       // Inferred role: sound name; original member name unknown.
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown28; // Inferred role: frame the sound follows; original member name unknown.
    u32 unknown30;                                       // Role and original member name unknown.
    mm::mtl::FixStr<32> unknown34;                       // Inferred role: bone name; original member name unknown.
    mm::Vec3 unknown60;                                  // Inferred role: offset; original member name unknown.
    bool unknown70;                                      // Role and original member name unknown; true by default.
  };

  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 10;

  ~GfComSound() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void stopSe(const char *name);
  bool playSe(const char *name, f32 volume, const mm::Vec3 &offset, bool isFollow);
  void playSe2D(const char *name, f32 volume, bool, bool);
  int getAttributeVariable() const;
  void setAttributeVariable(int attribute);
  // Inferred helper: sets a sound variable; original name unknown. The game inlines it into FootStepPlugin::setAnkleHeight and update.
  void unknown001(const char *name, int value) { unknown10.setVariable(name, value); }

  fw::SoundVariableTable unknown10;   // Inferred role: sound variables; original member name unknown.
  mm::mtl::List<SoundInfo> unknown30; // Inferred role: playing sounds; original member name unknown.
};

static_assert(offsetof(GfComSound::SoundInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown28) == 0x28, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown34) == 0x34, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown60) == 0x60, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown70) == 0x70, "");
static_assert(sizeof(GfComSound::SoundInfo) == 0x80, "");
static_assert(offsetof(GfComSound, unknown30) == 0x30, "");

static_assert(offsetof(GfComSound, unknown10) == 0x10, "");

} // namespace gf
