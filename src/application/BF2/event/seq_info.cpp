#include "event/seq_info.h"

#include "bdat.h"
#include "event/manager.h"
#include "gf/data/gf_bdat_wrapper.h"

namespace event {

constexpr f32 DEGREE_TO_RADIAN = 3.14159265f / 180.0f;

SeqInfo::SeqInfo() { clear(); }

void SeqInfo::clear() {
  mExist = false;
  mName.clear();
  mID = 0;
  mChgStID = 0;
  mChgEdID = 0;
  mCategory = 0;
  mMstxt = "";
  mText = false;
  mWeather = 0;
  mClock = "";
  mClockStop = false;
  mCloud = 0;
  mOpFadeOutEnable = false;
  mOpFadeOut = 0;
  mOpFadeWait = 0;
  mOpFadeInEnable = false;
  mOpFadeIn = 0;
  mOpFadeColR = 0;
  mOpFadeColG = 0;
  mOpFadeColB = 0;
  mEdFadeOutEnable = false;
  mEdFadeOut = 0;
  mEdFadeWait = 0;
  mEdFadeInEnable = false;
  mEdFadeIn = 0;
  mEdFadeColR = 0;
  mEdFadeColG = 0;
  mEdFadeColB = 0;
  mStFormID = 0;
  mEdFormID = 0;
  mOpBgm = true;
  mEdBgm = false;
  mHideNpc = false;
  mHideEne = false;
  mHideMob = false;
  mHideMap = false;
  mOutsiderEnable = false;
  mOutsiderType = 0;
  mOutsiderX = 0.0f;
  mOutsiderY = 0.0f;
  mOutsiderZ = 0.0f;
  mOutsiderR = 0.0f;
  mNextID = 0;
  mLinkID = 0;
  mNextIDtheater = 0;
  mJijiDisp = false;
  mWpnDisp = 0;
  mColFilterNear = 0;
  mColFilterFar = 0;
  mEnvSeam = 0;
  mEvtLight = "";
  mCenterID = 0;
  mCenterX = 0.0f;
  mCenterY = 0.0f;
  mCenterZ = 0.0f;
  mCenterR = 0.0f;
  mCenterForm = 0;
}

SeqInfo::SeqInfo(const char *name) { setup(name); }

void SeqInfo::setup(const char *name) {
  u8 *list = Bdat::getFP("EVT_listList");
  int listTop = Bdat::getIdTop(list);
  u32 listCount = Bdat::getIdCount(list);
  for (u32 i = 0; i < listCount; i++) {
    CBdatWrapper bdat;
    bdat.unknown00 = Bdat::getFP(Bdat::getVal(list, "listSeat", listTop + i).valueString);
    int top = Bdat::getIdTop(bdat.unknown00);
    int count = Bdat::getIdCount(bdat.unknown00);
    for (int j = 0; j < count; j++) {
      int id = top + j;
      const char *evtName = Bdat::getVal(bdat.unknown00, "evtName", id).valueString;
      if (__builtin_strcmp(evtName, name) == 0) {
        setup(bdat, evtName, id);
        return;
      }
    }
  }
  clear();
}

SeqInfo::SeqInfo(int id) { setup(id); }

void SeqInfo::setup(int id) {
  u8 *list = Bdat::getFP("EVT_listList");
  int listTop = Bdat::getIdTop(list);
  u32 listCount = Bdat::getIdCount(list);
  for (u32 i = 0; i < listCount; i++) {
    CBdatWrapper bdat;
    bdat.unknown00 = Bdat::getFP(Bdat::getVal(list, "listSeat", listTop + i).valueString);
    int top = Bdat::getIdTop(bdat.unknown00);
    int count = Bdat::getIdCount(bdat.unknown00);
    if (top <= id && id < top + count) {
      setup(bdat, Bdat::getVal(bdat.unknown00, "evtName", id).valueString, id);
      return;
    }
  }
  clear();
}

void SeqInfo::setup(const CBdatWrapper &bdat, const char *name, int id) {
  mExist = true;
  mName = name;
  mID = id;
  mChgStID = Bdat::getVal(bdat.unknown00, "chgStID", id).valueU16;
  mChgEdID = Bdat::getVal(bdat.unknown00, "chgEdID", id).valueU16;
  mCategory = Bdat::getVal(bdat.unknown00, "category", id).valueU8;
  mMstxt = Bdat::getVal(bdat.unknown00, "mstxt", id).valueString;
  mText = Bdat::getVal(bdat.unknown00, "text", id).valueU8 != 0;
  mWeather = Bdat::getVal(bdat.unknown00, "weather", id).valueU8;
  mClock = Bdat::getVal(bdat.unknown00, "clock", id).valueString;
  mClockStop = Bdat::getVal(bdat.unknown00, "clockStop", id).valueU8;
  mCloud = Bdat::getVal(bdat.unknown00, "cloud", id).valueU8;
  mOpFadeOutEnable = Bdat::getVal(bdat.unknown00, "opFadeOutEnable", id).valueU8 != 0;
  mOpFadeOut = Bdat::getVal(bdat.unknown00, "opFadeOut", id).valueU16;
  mOpFadeWait = Bdat::getVal(bdat.unknown00, "opFadeWait", id).valueU16;
  mOpFadeInEnable = Bdat::getVal(bdat.unknown00, "opFadeInEnable", id).valueU8 != 0;
  mOpFadeIn = Bdat::getVal(bdat.unknown00, "opFadeIn", id).valueU16;
  mOpFadeColR = Bdat::getVal(bdat.unknown00, "opFadeColR", id).valueU8;
  mOpFadeColG = Bdat::getVal(bdat.unknown00, "opFadeColG", id).valueU8;
  mOpFadeColB = Bdat::getVal(bdat.unknown00, "opFadeColB", id).valueU8;
  mEdFadeOutEnable = Bdat::getVal(bdat.unknown00, "edFadeOutEnable", id).valueU8 != 0;
  mEdFadeOut = Bdat::getVal(bdat.unknown00, "edFadeOut", id).valueU16;
  mEdFadeWait = Bdat::getVal(bdat.unknown00, "edFadeWait", id).valueU16;
  mEdFadeInEnable = Bdat::getVal(bdat.unknown00, "edFadeInEnable", id).valueU8 != 0;
  mEdFadeIn = Bdat::getVal(bdat.unknown00, "edFadeIn", id).valueU16;
  mEdFadeColR = Bdat::getVal(bdat.unknown00, "edFadeColR", id).valueU8;
  mEdFadeColG = Bdat::getVal(bdat.unknown00, "edFadeColG", id).valueU8;
  mEdFadeColB = Bdat::getVal(bdat.unknown00, "edFadeColB", id).valueU8;
  if (Manager::get()->isEndFadeOut() && !mEdFadeOutEnable) {
    mEdFadeOutEnable = true;
    mEdFadeOut = 20;
    mEdFadeWait = 0;
    mEdFadeColR = 0;
    mEdFadeColG = 0;
    mEdFadeColB = 0;
  }
  mStFormID = Bdat::getVal(bdat.unknown00, "stFormID", id).valueU16;
  mEdFormID = Bdat::getVal(bdat.unknown00, "edFormID", id).valueU16;
  mOpBgm = Bdat::getVal(bdat.unknown00, "opBgm", id).valueU8;
  mEdBgm = Bdat::getVal(bdat.unknown00, "edBgm", id).valueU8;
  mHideNpc = Bdat::getVal(bdat.unknown00, "hideNpc", id).valueU8 != 0;
  mHideEne = Bdat::getVal(bdat.unknown00, "hideEne", id).valueU8 != 0;
  mHideMob = Bdat::getVal(bdat.unknown00, "hideMob", id).valueU8 != 0;
  mHideMap = Bdat::getVal(bdat.unknown00, "hideMap", id).valueU8 != 0;
  mOutsiderOpt = Bdat::getVal(bdat.unknown00, "outsiderOpt", id).valueU16;
  mOutsiderEnable = Bdat::getVal(bdat.unknown00, "outsiderEnable", id).valueU8 != 0;
  mOutsiderType = Bdat::getVal(bdat.unknown00, "outsiderType", id).valueU8;
  mOutsiderX = Bdat::getVal(bdat.unknown00, "outsiderX", id).valueF32;
  mOutsiderY = Bdat::getVal(bdat.unknown00, "outsiderY", id).valueF32;
  mOutsiderZ = Bdat::getVal(bdat.unknown00, "outsiderZ", id).valueF32;
  mOutsiderR = Bdat::getVal(bdat.unknown00, "outsiderR", id).valueF32;
  mNextID = Bdat::getVal(bdat.unknown00, "nextID", id).valueU16;
  mLinkID = Bdat::getVal(bdat.unknown00, "linkID", id).valueU16;
  mNextIDtheater = Bdat::getMember(bdat.unknown00, "nextIDtheater") ? Bdat::getVal(bdat.unknown00, "nextIDtheater", id).valueU16 : 0;
  mJijiDisp = Bdat::getVal(bdat.unknown00, "jijiDisp", id).valueU8 != 0;
  mWpnDisp = Bdat::getVal(bdat.unknown00, "wpnDisp", id).valueU16;
  mColFilterNear = Bdat::getVal(bdat.unknown00, "colFilterNear", id).valueU16;
  mColFilterFar = Bdat::getVal(bdat.unknown00, "colFilterFar", id).valueU16;
  mEnvSeam = Bdat::getMember(bdat.unknown00, "envSeam") ? Bdat::getVal(bdat.unknown00, "envSeam", id).valueU16 : 0;
  mEvtLight = Bdat::getMember(bdat.unknown00, "evtLight") ? Bdat::getVal(bdat.unknown00, "evtLight", id).valueString : "";
  mHood = Bdat::getMember(bdat.unknown00, "hood") ? Bdat::getVal(bdat.unknown00, "hood", id).valueU8 : 1;
  mVoice = Bdat::getVal(bdat.unknown00, "voice", id).valueU8;
  mCssnd = Bdat::getMember(bdat.unknown00, "cssnd") ? Bdat::getVal(bdat.unknown00, "cssnd", id).valueU8 : false;
  mCenterForm = Bdat::getMember(bdat.unknown00, "centerForm") ? Bdat::getVal(bdat.unknown00, "centerForm", id).valueU16 : 0;
  mCenterID = Bdat::getMember(bdat.unknown00, "centerID") ? Bdat::getVal(bdat.unknown00, "centerID", id).valueU16 : 0;
  mCenterX = Bdat::getMember(bdat.unknown00, "centerX") ? Bdat::getVal(bdat.unknown00, "centerX", id).valueF32 : 0.0f;
  mCenterY = Bdat::getMember(bdat.unknown00, "centerY") ? Bdat::getVal(bdat.unknown00, "centerY", id).valueF32 : 0.0f;
  mCenterZ = Bdat::getMember(bdat.unknown00, "centerZ") ? Bdat::getVal(bdat.unknown00, "centerZ", id).valueF32 : 0.0f;
  mCenterR = Bdat::getMember(bdat.unknown00, "centerR") ? Bdat::getVal(bdat.unknown00, "centerR", id).valueF32 * DEGREE_TO_RADIAN : 0.0f;
}

bool SeqInfo::exist() const { return mExist; }

} // namespace event
