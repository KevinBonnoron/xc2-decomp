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
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      dispFlags |= flag;
    } else {
      dispFlags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  mm::mtl::FixedVector<EffectRes *, RES_COUNT> mResList;
  EffectRes *mCurrentRes;
  u32 mOffscrID;
  u32 mReplaceID;
};

static_assert(sizeof(EffectManager) == 0xb0, "");

inline void EffectManager::replaceFile(mm::mtl::FixStr<128> &file) const {
  if (!isReplaceMode() || mReplaceID == 0) {
    return;
  }
  char buffer[256];
  __builtin_memset(buffer, 0, sizeof(buffer));
  __builtin_strcpy(buffer, file.c_str());
  char *found = __builtin_strstr(buffer, "dark");
  if (found != nullptr) {
    __builtin_strcpy(found, EffectUtil::getAttrName(mReplaceID));
    file = buffer;
  }
}

} // namespace event
