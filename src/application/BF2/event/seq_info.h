#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

struct CBdatWrapper;

namespace event {

class SeqInfo {
public:
  SeqInfo();
  void clear();
  SeqInfo(const char *name);
  void setup(const char *name);
  SeqInfo(int id);
  void setup(int id);
  void setup(const CBdatWrapper &bdat, const char *name, int id);
  bool exist() const;

  bool mExist;
  mm::mtl::FixStr<64> mName;
  int mID;
  u32 mChgStID;
  u32 mChgEdID;
  u32 mCategory;
  const char *mMstxt;
  bool mText;
  u32 mWeather;
  const char *mClock;
  bool mClockStop;
  u32 mCloud;
  bool mOpFadeOutEnable;
  u32 mOpFadeOut;
  u32 mOpFadeWait;
  bool mOpFadeInEnable;
  u32 mOpFadeIn;
  u32 mOpFadeColR;
  u32 mOpFadeColG;
  u32 mOpFadeColB;
  bool mEdFadeOutEnable;
  u32 mEdFadeOut;
  u32 mEdFadeWait;
  bool mEdFadeInEnable;
  u32 mEdFadeIn;
  u32 mEdFadeColR;
  u32 mEdFadeColG;
  u32 mEdFadeColB;
  u32 mStFormID;
  u32 mEdFormID;
  bool mOpBgm;
  bool mEdBgm;
  bool mHideNpc;
  bool mHideEne;
  bool mHideMob;
  bool mHideMap;
  u32 mOutsiderOpt;
  bool mOutsiderEnable;
  u32 mOutsiderType;
  f32 mOutsiderX;
  f32 mOutsiderY;
  f32 mOutsiderZ;
  f32 mOutsiderR;
  u32 mNextID;
  int mLinkID;
  u32 mNextIDtheater;
  bool mJijiDisp;
  u32 mWpnDisp;
  u32 mColFilterNear;
  u32 mColFilterFar;
  u32 mEnvSeam;
  const char *mEvtLight;
  u32 mHood;
  bool mVoice;
  bool mCssnd;
  u32 mCenterID;
  f32 mCenterX;
  f32 mCenterY;
  f32 mCenterZ;
  f32 mCenterR;
  u32 mCenterForm;
};

static_assert(sizeof(SeqInfo) == 0x130, "");

} // namespace event
