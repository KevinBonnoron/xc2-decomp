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
    bdat.data = Bdat::getFP(Bdat::getVal(list, "listSeat", listTop + i).valueString);
    int top = Bdat::getIdTop(bdat.data);
    int count = Bdat::getIdCount(bdat.data);
    for (int j = 0; j < count; j++) {
      int id = top + j;
      const char *evtName = Bdat::getVal(bdat.data, "evtName", id).valueString;
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
    bdat.data = Bdat::getFP(Bdat::getVal(list, "listSeat", listTop + i).valueString);
    int top = Bdat::getIdTop(bdat.data);
    int count = Bdat::getIdCount(bdat.data);
    if (top <= id && id < top + count) {
      setup(bdat, Bdat::getVal(bdat.data, "evtName", id).valueString, id);
      return;
    }
  }
  clear();
}

void SeqInfo::setup(const CBdatWrapper &bdat, const char *name, int id) {
  mExist = true;
  mName = name;
  mID = id;
  mChgStID = Bdat::getVal(bdat.data, "chgStID", id).valueU16;
  mChgEdID = Bdat::getVal(bdat.data, "chgEdID", id).valueU16;
  mCategory = Bdat::getVal(bdat.data, "category", id).valueU8;
  mMstxt = Bdat::getVal(bdat.data, "mstxt", id).valueString;
  mText = Bdat::getVal(bdat.data, "text", id).valueU8 != 0;
  mWeather = Bdat::getVal(bdat.data, "weather", id).valueU8;
  mClock = Bdat::getVal(bdat.data, "clock", id).valueString;
  mClockStop = Bdat::getVal(bdat.data, "clockStop", id).valueU8;
  mCloud = Bdat::getVal(bdat.data, "cloud", id).valueU8;
  mOpFadeOutEnable = Bdat::getVal(bdat.data, "opFadeOutEnable", id).valueU8 != 0;
  mOpFadeOut = Bdat::getVal(bdat.data, "opFadeOut", id).valueU16;
  mOpFadeWait = Bdat::getVal(bdat.data, "opFadeWait", id).valueU16;
  mOpFadeInEnable = Bdat::getVal(bdat.data, "opFadeInEnable", id).valueU8 != 0;
  mOpFadeIn = Bdat::getVal(bdat.data, "opFadeIn", id).valueU16;
  mOpFadeColR = Bdat::getVal(bdat.data, "opFadeColR", id).valueU8;
  mOpFadeColG = Bdat::getVal(bdat.data, "opFadeColG", id).valueU8;
  mOpFadeColB = Bdat::getVal(bdat.data, "opFadeColB", id).valueU8;
  mEdFadeOutEnable = Bdat::getVal(bdat.data, "edFadeOutEnable", id).valueU8 != 0;
  mEdFadeOut = Bdat::getVal(bdat.data, "edFadeOut", id).valueU16;
  mEdFadeWait = Bdat::getVal(bdat.data, "edFadeWait", id).valueU16;
  mEdFadeInEnable = Bdat::getVal(bdat.data, "edFadeInEnable", id).valueU8 != 0;
  mEdFadeIn = Bdat::getVal(bdat.data, "edFadeIn", id).valueU16;
  mEdFadeColR = Bdat::getVal(bdat.data, "edFadeColR", id).valueU8;
  mEdFadeColG = Bdat::getVal(bdat.data, "edFadeColG", id).valueU8;
  mEdFadeColB = Bdat::getVal(bdat.data, "edFadeColB", id).valueU8;
  if (Manager::get()->isEndFadeOut() && !mEdFadeOutEnable) {
    mEdFadeOutEnable = true;
    mEdFadeOut = 20;
    mEdFadeWait = 0;
    mEdFadeColR = 0;
    mEdFadeColG = 0;
    mEdFadeColB = 0;
  }
  mStFormID = Bdat::getVal(bdat.data, "stFormID", id).valueU16;
  mEdFormID = Bdat::getVal(bdat.data, "edFormID", id).valueU16;
  mOpBgm = Bdat::getVal(bdat.data, "opBgm", id).valueU8;
  mEdBgm = Bdat::getVal(bdat.data, "edBgm", id).valueU8;
  mHideNpc = Bdat::getVal(bdat.data, "hideNpc", id).valueU8 != 0;
  mHideEne = Bdat::getVal(bdat.data, "hideEne", id).valueU8 != 0;
  mHideMob = Bdat::getVal(bdat.data, "hideMob", id).valueU8 != 0;
  mHideMap = Bdat::getVal(bdat.data, "hideMap", id).valueU8 != 0;
  mOutsiderOpt = Bdat::getVal(bdat.data, "outsiderOpt", id).valueU16;
  mOutsiderEnable = Bdat::getVal(bdat.data, "outsiderEnable", id).valueU8 != 0;
  mOutsiderType = Bdat::getVal(bdat.data, "outsiderType", id).valueU8;
  mOutsiderX = Bdat::getVal(bdat.data, "outsiderX", id).valueF32;
  mOutsiderY = Bdat::getVal(bdat.data, "outsiderY", id).valueF32;
  mOutsiderZ = Bdat::getVal(bdat.data, "outsiderZ", id).valueF32;
  mOutsiderR = Bdat::getVal(bdat.data, "outsiderR", id).valueF32;
  mNextID = Bdat::getVal(bdat.data, "nextID", id).valueU16;
  mLinkID = Bdat::getVal(bdat.data, "linkID", id).valueU16;
  mNextIDtheater = Bdat::getMember(bdat.data, "nextIDtheater") ? Bdat::getVal(bdat.data, "nextIDtheater", id).valueU16 : 0;
  mJijiDisp = Bdat::getVal(bdat.data, "jijiDisp", id).valueU8 != 0;
  mWpnDisp = Bdat::getVal(bdat.data, "wpnDisp", id).valueU16;
  mColFilterNear = Bdat::getVal(bdat.data, "colFilterNear", id).valueU16;
  mColFilterFar = Bdat::getVal(bdat.data, "colFilterFar", id).valueU16;
  mEnvSeam = Bdat::getMember(bdat.data, "envSeam") ? Bdat::getVal(bdat.data, "envSeam", id).valueU16 : 0;
  mEvtLight = Bdat::getMember(bdat.data, "evtLight") ? Bdat::getVal(bdat.data, "evtLight", id).valueString : "";
  mHood = Bdat::getMember(bdat.data, "hood") ? Bdat::getVal(bdat.data, "hood", id).valueU8 : 1;
  mVoice = Bdat::getVal(bdat.data, "voice", id).valueU8;
  mCssnd = Bdat::getMember(bdat.data, "cssnd") ? Bdat::getVal(bdat.data, "cssnd", id).valueU8 : false;
  mCenterForm = Bdat::getMember(bdat.data, "centerForm") ? Bdat::getVal(bdat.data, "centerForm", id).valueU16 : 0;
  mCenterID = Bdat::getMember(bdat.data, "centerID") ? Bdat::getVal(bdat.data, "centerID", id).valueU16 : 0;
  mCenterX = Bdat::getMember(bdat.data, "centerX") ? Bdat::getVal(bdat.data, "centerX", id).valueF32 : 0.0f;
  mCenterY = Bdat::getMember(bdat.data, "centerY") ? Bdat::getVal(bdat.data, "centerY", id).valueF32 : 0.0f;
  mCenterZ = Bdat::getMember(bdat.data, "centerZ") ? Bdat::getVal(bdat.data, "centerZ", id).valueF32 : 0.0f;
  mCenterR = Bdat::getMember(bdat.data, "centerR") ? Bdat::getVal(bdat.data, "centerR", id).valueF32 * DEGREE_TO_RADIAN : 0.0f;
}

bool SeqInfo::exist() const { return mExist; }

} // namespace event
