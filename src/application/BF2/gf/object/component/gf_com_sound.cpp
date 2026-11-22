#include "gf/object/component/gf_com_sound.h"

#include <string.h>

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"      // IWYU pragma: keep
#include "gf/object/component/animation/gf_com_evt_anim.h" // IWYU pragma: keep
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/unique_ptr.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

// Names as the game's global symbols gf::SOUND_CALLBACK_EVENT_NAME and gf::SND_VAR_WATER_THRESOULD_NAME (the strings are at 0x7100f5284e and 0x7100f52854).
// The two pointers (0x710119fa38/0x710119fa40) sit in the game's data before the vtable of GfComSound (0x710119fa48), so they belong to this unit and not to the variable
// name unit (gf_com_sound_variable.cpp), whose tables come after the vtables of the class.
const char *SOUND_CALLBACK_EVENT_NAME = "sound";
const char *SND_VAR_WATER_THRESOULD_NAME = "water_th";

GfComSound::~GfComSound() {}

GfComSound::GfComSound() : unknown30(getAllocator(ALLOCATOR_UNKNOWN_0)), unknown128(nullptr), unknown150(false), unknown168(nullptr) { m_viewerListener.m_comSound = this; }

void GfComSound::setup() {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    GfComEvtAnim *evtAnim = unknown08->getComponent<GfComEvtAnim>();
    if (evtAnim != nullptr) {
      evtAnim->m_asm.unknown70[4].unknown00 = SOUND_CALLBACK_EVENT_NAME;
      evtAnim->m_asm.unknown70[4].unknown08.bind<GfComSound>(this, &GfComSound::callbackAnimForEvent);
    }
  } else {
    comAsm->unknown70[4].unknown00 = SOUND_CALLBACK_EVENT_NAME;
    comAsm->unknown70[4].unknown08.bind<GfComSound>(this, &GfComSound::callbackAnim);
  }
  m_soundUpdater.unknown10.bind<GfComSound>(this, &GfComSound::flush);
  m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 0);
  int attribute = GfGameUtil::getObjAttribute(static_cast<GfObj *>(unknown08)->unknownf8);
  m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_1), attribute);
  m_soundVariableTable.setVariable(SND_VAR_WATER_THRESOULD_NAME, 10);
  m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_4), 0);
  m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_2), 0);
  m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_3), 0);
  unknown150 = true;
}

void GfComSound::callbackAnim(GfComAsm *comAsm, const CallBackCache &cache) { callbackAnimImpl(cache); }

void GfComSound::callbackAnimForEvent(GfComEvtAnim *evtAnim, const CallBackCache &cache) { callbackAnimImpl(cache); }

void GfComSound::cleanup() {
  while (unknown30.size() != 0) {
    eraseCache(unknown30.begin());
  }
  fw::SoundLayerManager *manager = fw::SoundLayerManager::get();
  if (manager != nullptr && m_soundUpdater.unknown31) {
    manager->unknown08[getLayer()].erase(&m_soundUpdater);
    m_soundUpdater.unknown31 = false;
  }
  unknown150 = false;
}

void GfComSound::changeLayer(u32 oldLayer, u32 newLayer) {
  fw::SoundLayerManager *manager = fw::SoundLayerManager::get();
  if (manager != nullptr && m_soundUpdater.unknown31) {
    manager->unknown08[oldLayer].erase(&m_soundUpdater);
    m_soundUpdater.unknown31 = false;
    manager->unknown08[newLayer].push_back(&m_soundUpdater);
    m_soundUpdater.unknown31 = true;
  }
}

void GfComSound::clearCahches() {
  while (unknown30.size() != 0) {
    eraseCache(unknown30.begin());
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a
// symbol. Its user is GfComSound::stopSe (0x710057fa0c). It takes begin() and end() by value, like the algorithms of docs/lessons.md ("for_each form"): every loop written in
// stopSe (for or while with it != end(), end() first, early return) is rotated with a guard (31 insns against the game's 30), and mm::mtl::find_if followed by a test of
// the result is unrotated like the game but keeps that test on the found path (32 insns).
static bool eraseFirstMatchingCache(GfComSound *self, mm::mtl::List<GfComSound::SoundInfo>::iterator first, mm::mtl::List<GfComSound::SoundInfo>::iterator last, const char *name) {
  for (; first != last; ++first) {
    if (strcmp((*first).unknown04.c_str(), name) == 0) {
      self->eraseCache(first);
      return true;
    }
  }
  return false;
}

bool GfComSound::stopSe(const char *name) { return eraseFirstMatchingCache(this, unknown30.begin(), unknown30.end(), name); }

mm::mtl::List<GfComSound::SoundInfo>::iterator GfComSound::eraseCache(mm::mtl::List<SoundInfo>::iterator it) {
  fw::SoundManager *manager = fw::SoundManager::get();
  if (manager != nullptr && manager->isValid((*it).unknown00)) {
    fw::SoundResSourceManager::stopSe((*it).unknown00, 0.05f);
  }
  if ((*it).unknown30 == 1) {
    unknown08->getComponent<GfComModel>()->destroyBoneReferenceFrame((*it).unknown34.c_str());
  }
  return unknown30.erase(it);
}

void GfComSound::setAttributeVariable(int attribute) { m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_1), attribute); }

int GfComSound::getAttributeVariable() const {
  int attribute;
  return m_soundVariableTable.getVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_1), &attribute) ? attribute : 0;
}

void GfComSound::flushVariables() {
  GfComProperty *property = unknown08->getComponent<GfComProperty>();
  if (property == nullptr) {
    return;
  }
  GfEnvProperty *env = property->unknown28.get();
  if (env == nullptr) {
    return;
  }
  if ((env->unknown2d0 & 1) != 0) {
    int threshold = 0;
    m_soundVariableTable.getVariable(SND_VAR_WATER_THRESOULD_NAME, &threshold);
    f32 depth = static_cast<f32>(threshold) * 0.01f;
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_3), !(env->unknown280.unknown30 < depth));
    int ground = env->unknown280.unknown38;
    const char *name = getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0);
    if (ground == 11) {
      m_soundVariableTable.setVariable(name, 11);
    } else {
      m_soundVariableTable.setVariable(name, 10);
    }
    return;
  }
  const GfEnvProperty::unknown002 *ground = env->unknown004(GfEnvProperty::GROUND_INDEX_UNKNOWN_0);
  if (ground == nullptr) {
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 0);
    return;
  }
  switch (ground->unknown34) {
  case 2:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 6);
    break;
  case 3:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 3);
    break;
  case 4:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 2);
    break;
  case 5:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 1);
    break;
  case 6:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 4);
    break;
  case 7:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 7);
    break;
  case 8:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 5);
    break;
  case 9:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 9);
    break;
  case 10:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 8);
    break;
  case 12:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 12);
    break;
  default:
    m_soundVariableTable.setVariable(getSoundVariableName(SOUND_VARIABLE_UNKNOWN_0), 0);
    break;
  }
}

u32 GfComSound::flush() {
  flushVariables();
  fw::SoundManager *manager = fw::SoundManager::get();
  if (manager != nullptr) {
    // The end of the list is read once and kept: the game compares both loops against one register (x26: 0x710057ee00, 0x710057eecc; 1.0.0 function at 0x710057edc0, 194
    // instructions). With `unknown30.end()` in the conditions the function has 193 instructions and 59 differing lines.
    mm::mtl::List<SoundInfo>::iterator it = unknown30.begin();
    mm::mtl::List<SoundInfo>::iterator end = unknown30.end();
    while (it != end) {
      if (manager->isValid((*it).unknown00)) {
        ++it;
      } else {
        it = unknown30.erase(it);
      }
    }
    it = unknown30.begin();
    end = unknown30.end();
    for (; it != end; ++it) {
      SoundInfo &info = *it;
      if (info.unknown28.get() != nullptr && info.unknown70) {
        // The rotation of the offset is written out (1.0.0: 0x710057ef64-0x710057f01c: the loads of the quaternion and the offset, the four temporaries, the three stored components), the
        // same statements as mm::unknown010. Measured against the game: `position = q.rotate(offset)` has the 194 instructions and 51 differing lines; `position = offset;
        // mm::unknown010(q, position)` 194 instructions and 22 differing lines (a helper is simplified before it is inlined, which changes the order of the operands of the products),
        // and `mm::Vec3 position = offset` before the call 200 instructions. The result is declared before the four temporaries: declared after them (just before the three stores) 4
        // lines differ in operand order; before or after the quaternion and the offset it matches.
        mm::Vec3 position;
        const mm::Quat &q = unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown10;
        const mm::Vec3 &v = info.unknown60;
        f32 tx = q.y * v.z - q.z * v.y + q.w * v.x;
        f32 ty = q.z * v.x - v.z * q.x + v.y * q.w;
        f32 tz = v.y * q.x - q.y * v.x + v.z * q.w;
        f32 tw = -v.x * q.x - q.y * v.y - v.z * q.z;
        position.x = -(q.z * ty) + q.y * tz - q.x * tw + q.w * tx;
        position.y = -(q.x * tz) + q.z * tx - q.y * tw + q.w * ty;
        position.z = -(q.y * tx) + q.x * ty - q.z * tw + q.w * tz;
        position += info.unknown28->getSyncedWorldTransform().unknown00;
        manager->setPos(info.unknown00, position);
        if (!manager->isLoop(info.unknown00)) {
          info.unknown70 = false;
        }
      }
    }
  }
  return unknown30.size();
}

namespace {

// Inferred helper: starts the sound of the given name in the category of the object; original name unknown. The game inlines it in playSe, playSeBone and playSe2D.
u32 unknown003(GfComSound *sound, const char *name, f32 volume, bool isWithoutSlow) {
  GF_OBJ_HANDLE *handle = static_cast<GfObj *>(sound->unknown08)->unknownf8;
  fw::SoundCategory category = isWithoutSlow ? GfObjUtil::getSoundCategoryWithoutSlow(handle) : GfObjUtil::getSoundCategoryNormal(handle);
  return fw::SoundResSourceManager::playSe(name, volume, sound->m_soundVariableTable, category, sound->unknown130);
}

} // namespace

bool GfComSound::playSe(const char *name, f32 volume, const mm::Vec3 &offset, bool isWithoutSlow) {
  if (!unknown150) {
    return false;
  }
  u32 id = unknown003(this, name, volume, isWithoutSlow);
  if (id == 0) {
    return false;
  }
  SoundInfo info;
  info.unknown00 = id;
  info.unknown04 = name;
  info.unknown28 = unknown08->getComponent<GfComTransform>()->unknown001();
  info.unknown30 = 0;
  info.unknown60 = offset;
  unknown30.push_back(info);
  unknown002();
  return true;
}

bool GfComSound::playSeBone(const char *name, const char *bone, f32 volume, const mm::Vec3 &offset, bool isWithoutSlow) {
  if (!unknown150) {
    return false;
  }
  u32 id = unknown003(this, name, volume, isWithoutSlow);
  if (id == 0) {
    return false;
  }
  SoundInfo info;
  info.unknown00 = id;
  info.unknown04 = name;
  info.unknown28 = unknown08->getComponent<GfComModel>()->createBoneReferenceFrame(bone);
  info.unknown30 = 1;
  info.unknown34 = bone;
  info.unknown60 = offset;
  unknown30.push_back(info);
  unknown002();
  return true;
}

bool GfComSound::playSe2D(const char *name, f32 volume, bool isWithoutSlow, bool isCache) {
  if (!unknown150) {
    return false;
  }
  u32 id = unknown003(this, name, volume, isWithoutSlow);
  if (id == 0) {
    return false;
  }
  if (!isCache) {
    return true;
  }
  SoundInfo info;
  info.unknown00 = id;
  info.unknown04 = name;
  info.unknown30 = 2;
  info.unknown70 = false;
  unknown30.push_back(info);
  return true;
}

bool GfComSound::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_UNKNOWN_16777219) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComSound::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

const mm::mtl::RTTI *GfComSound::getRTTI() const { return &m_rtti; }

} // namespace gf

template void mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComSound>(const mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)> *,
                                                                                                                    gf::GfComAsm *, const gf::CallBackCache &);
template void mm::mtl::Delegate<void(gf::GfComEvtAnim *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComSound>(const mm::mtl::Delegate<void(gf::GfComEvtAnim *, const gf::CallBackCache &)> *,
                                                                                                                        gf::GfComEvtAnim *, const gf::CallBackCache &);
template unsigned int mm::mtl::Delegate<unsigned int()>::memberFuncInvoker<gf::GfComSound>(const mm::mtl::Delegate<unsigned int()> *);
