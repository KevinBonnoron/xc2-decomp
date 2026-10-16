#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

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

  EffectManager();
  virtual ~EffectManager() {}
  bool isStreamMode() const { return (flags & FLAG_STREAM_MODE) != 0; }
  bool isOffscrMode() const { return (flags & FLAG_OFFSCR_MODE) != 0; }
  u32 getOffscrID() const { return mOffscrID; }
  bool isReplaceMode() const { return (flags & FLAG_REPLACE_MODE) != 0; }
  void setStreamMode(bool isStreamMode);
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

} // namespace event
