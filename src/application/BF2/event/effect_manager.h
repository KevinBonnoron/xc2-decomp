#pragma once
#include "event/effect_util.h"
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class EffectPack;
} // namespace fw

namespace event {
class EffectRes;

class EffectManager : public IManager, public mm::mtl::Singleton<EffectManager> {
public:
  static constexpr u32 RES_COUNT = 16;

  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_OFFSCR_MODE = 1 << 1,
    FLAG_REPLACE_MODE = 1 << 2,
  };

  enum {
    DISP_FLAG_EFFECT = 1 << 0,
    DISP_FLAG_DISABLE = 1 << 1,
  };

  fw::EffectPack *getResPack() const;
  EffectManager();
  virtual ~EffectManager() {}
  void clear();
  void load(const char *name);
  EffectRes *searchRes(const char *name);
  bool isLoading() const;
  void setEvent(const char *name);
  bool isStreamMode() const;
  bool isOffscrMode() const;
  u32 getOffscrID() const;
  bool isReplaceMode() const;
  void replaceFile(mm::mtl::FixStr<128> &file) const;
  void setStreamMode(bool isStreamMode);
  void loadResource(const char *name);
  void setOffscrMode(bool isOffscrMode, u32 offscrID);
  void setReplaceMode(bool isReplaceMode, u32 replaceID);
  void setEffectDisp(bool isDisp);
  bool isEffectDisp() const;
  void setEffectDisable(bool isDisable);
  bool isEffectDisable() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown14 |= flag;
    } else {
      unknown14 &= ~flag;
    }
  }

  u32 unknown10;                                          // Inferred role: flags; original member name unknown.
  u32 unknown14;                                          // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixedVector<EffectRes *, RES_COUNT> unknown18; // Inferred role: res list; original member name unknown.
  EffectRes *unknowna0;                                   // Inferred role: current res; original member name unknown.
  u32 m_offscrID;
  u32 unknownac; // Inferred role: replace id; original member name unknown.
};

static_assert(sizeof(EffectManager) == 0xb0, "");

inline void EffectManager::replaceFile(mm::mtl::FixStr<128> &file) const {
  if (!isReplaceMode() || unknownac == 0) {
    return;
  }
  char buffer[256];
  __builtin_memset(buffer, 0, sizeof(buffer));
  __builtin_strcpy(buffer, file.c_str());
  char *found = __builtin_strstr(buffer, "dark");
  if (found != nullptr) {
    __builtin_strcpy(found, EffectUtil::getAttrName(unknownac));
    file = buffer;
  }
}

} // namespace event
