#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "framework/sound/sound_layer_manager.h"
#include "framework/sound/sound_res_source_manager.h"
#include "framework/sound/sound_variable_table.h"
#include "gf/object/component/gf_component.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/list.h"
#include "types.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {
class GfComAsm;
class GfComEvtAnim;
struct CallBackCache;
} // namespace gf

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

extern const char *SOUND_CALLBACK_EVENT_NAME;
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
// Layout evidence: GfComSound::GfComSound() (0x710057ead4) builds the variable table at 0x10, the sound list at 0x30 with its terminator SoundInfo at 0x50, the updater at 0xf0, the callback
// pointer at 0x128, the delegate at 0x130 (GfComBehaviorPc::setup, 0x71005646e4, binds it), the setup flag at 0x150, the viewer listener at 0x158 and the viewer pointer at 0x168.
class GfComSound : public GfComponent {
public:
  // Layout evidence: its copy constructor (0x71005802c0) copies the members below one by one; the terminator of the sound list (GfComSound::GfComSound, 0x710057ead4) stores the defaults.
  struct SoundInfo {
    SoundInfo() : unknown00(0), unknown30(0), unknown60(mm::Vec3::zero), unknown70(true) {}

    u32 unknown00;                                       // Role and original member name unknown.
    mm::mtl::FixStr<32> unknown04;                       // Inferred role: sound name; original member name unknown.
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown28; // Inferred role: frame the sound follows; original member name unknown.
    u32 unknown30;                                       // Inferred role: kind, 1 follows a bone and 2 is a 2D sound; original member name unknown.
    mm::mtl::FixStr<32> unknown34;                       // Inferred role: bone name; original member name unknown.
    mm::Vec3 unknown60;                                  // Inferred role: offset; original member name unknown.
    bool unknown70;                                      // Role and original member name unknown; true by default.
  };

  class ViewerListener {
  public:
    virtual void onWkStandbyLogout() {
      if (m_comSound != nullptr) {
        m_comSound->unknown168 = nullptr;
      }
    }

    GfComSound *m_comSound; // Inferred role: owner; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 10;

  GfComSound();
  ~GfComSound() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setup();
  void cleanup();
  u32 flush();
  void flushVariables();
  void clearCahches();
  void callbackAnim(GfComAsm *comAsm, const CallBackCache &cache);
  void callbackAnimForEvent(GfComEvtAnim *evtAnim, const CallBackCache &cache);
  void callbackAnimImpl(const CallBackCache &cache);
  mm::mtl::List<SoundInfo>::iterator eraseCache(mm::mtl::List<SoundInfo>::iterator it);
  bool stopSe(const char *name);
  bool playSe(const char *name, f32 volume, const mm::Vec3 &offset, bool isWithoutSlow);
  bool playSeBone(const char *name, const char *bone, f32 volume, const mm::Vec3 &offset, bool isWithoutSlow);
  bool playSe2D(const char *name, f32 volume, bool isWithoutSlow, bool isCache);
  int getAttributeVariable() const;
  void setAttributeVariable(int attribute);
  // Inferred helper: sets a sound variable; original name unknown. The game inlines it into FootStepPlugin::setAnkleHeight and update.
  void unknown001(const char *name, int value) { m_soundVariableTable.setVariable(name, value); }

  // Inferred helper: adds the updater to the sound layer manager of the layer of the component when it is not there yet; original name unknown. Shared by playSe and playSeBone (the game
  // inlines it in both: 0x710057f1d0, 0x710057f4a8).
  void unknown002() {
    fw::SoundLayerManager *manager = fw::SoundLayerManager::get();
    if (manager != nullptr && !m_soundUpdater.unknown31) {
      manager->unknown08[getLayer()].push_back(&m_soundUpdater);
      m_soundUpdater.unknown31 = true;
    }
  }

  fw::SoundVariableTable m_soundVariableTable;                   // Inferred role: sound variables; original member name unknown.
  mm::mtl::List<SoundInfo> unknown30;                            // Inferred role: playing sounds; original member name unknown.
  fw::SoundUpdater m_soundUpdater;                               // Inferred role: updater that flushes the sounds of the layer; original member name unknown.
  bool (*unknown128)(GfComSound *sound, const void *annotation); // Inferred role: filter of the sound callbacks, called by callbackAnimImpl; original member name unknown.
  mm::mtl::Delegate<void(const fw::ResSoundData &, fw::SoundResSourceManager::CustomInfo *)>
      unknown130;                  // Inferred role: callback customizing a sound resource, set by GfComBehaviorPc::setup; original member name unknown.
  bool unknown150;                 // Inferred role: set up; original member name unknown.
  ViewerListener m_viewerListener; // Inferred role: viewer listener; original member name unknown.
  void *unknown168;                // Inferred role: viewer; original member name unknown.
};

static_assert(offsetof(GfComSound::SoundInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown28) == 0x28, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown34) == 0x34, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown60) == 0x60, "");
static_assert(offsetof(GfComSound::SoundInfo, unknown70) == 0x70, "");
static_assert(sizeof(GfComSound::SoundInfo) == 0x80, "");
static_assert(offsetof(GfComSound, unknown30) == 0x30, "");
static_assert(sizeof(mm::mtl::List<GfComSound::SoundInfo>) == 0xc0, "");
static_assert(offsetof(GfComSound, m_soundUpdater) == 0xf0, "");
static_assert(offsetof(GfComSound, unknown128) == 0x128, "");
static_assert(offsetof(GfComSound, unknown130) == 0x130, "");
static_assert(offsetof(GfComSound, unknown150) == 0x150, "");
static_assert(offsetof(GfComSound, m_viewerListener) == 0x158, "");
static_assert(offsetof(GfComSound, unknown168) == 0x168, "");
static_assert(sizeof(GfComSound) == 0x170, "");

static_assert(offsetof(GfComSound, m_soundVariableTable) == 0x10, "");

} // namespace gf
