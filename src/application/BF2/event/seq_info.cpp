#include "event/seq_info.h"

#include "bdat.h"
#include "event/manager.h"
#include "gf/data/gf_bdat_wrapper.h"

namespace event {

constexpr f32 DEGREE_TO_RADIAN = 3.14159265f / 180.0f;

SeqInfo::SeqInfo() { clear(); }

void SeqInfo::clear() {
  unknown00 = false;
  unknown04.clear();
  unknown48 = 0;
  unknown4c = 0;
  unknown50 = 0;
  unknown54 = 0;
  unknown58 = "";
  unknown60 = false;
  unknown64 = 0;
  unknown68 = "";
  unknown70 = false;
  unknown74 = 0;
  unknown78 = false;
  unknown7c = 0;
  unknown80 = 0;
  unknown84 = false;
  unknown88 = 0;
  unknown8c = 0;
  unknown90 = 0;
  unknown94 = 0;
  unknown98 = false;
  unknown9c = 0;
  unknowna0 = 0;
  unknowna4 = false;
  unknowna8 = 0;
  unknownac = 0;
  unknownb0 = 0;
  unknownb4 = 0;
  unknownb8 = 0;
  unknownbc = 0;
  unknownc0 = true;
  unknownc1 = false;
  unknownc2 = false;
  unknownc3 = false;
  unknownc4 = false;
  unknownc5 = false;
  unknowncc = false;
  unknownd0 = 0;
  unknownd4 = 0.0f;
  unknownd8 = 0.0f;
  unknowndc = 0.0f;
  unknowne0 = 0.0f;
  unknowne4 = 0;
  unknowne8 = 0;
  unknownec = 0;
  unknownf0 = false;
  unknownf4 = 0;
  unknownf8 = 0;
  unknownfc = 0;
  unknown100 = 0;
  unknown108 = "";
  unknown118 = 0;
  unknown11c = 0.0f;
  unknown120 = 0.0f;
  unknown124 = 0.0f;
  unknown128 = 0.0f;
  unknown12c = 0;
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
  unknown00 = true;
  unknown04 = name;
  unknown48 = id;
  unknown4c = Bdat::getVal(bdat.unknown00, "chgStID", id).valueU16;
  unknown50 = Bdat::getVal(bdat.unknown00, "chgEdID", id).valueU16;
  unknown54 = Bdat::getVal(bdat.unknown00, "category", id).valueU8;
  unknown58 = Bdat::getVal(bdat.unknown00, "mstxt", id).valueString;
  unknown60 = Bdat::getVal(bdat.unknown00, "text", id).valueU8 != 0;
  unknown64 = Bdat::getVal(bdat.unknown00, "weather", id).valueU8;
  unknown68 = Bdat::getVal(bdat.unknown00, "clock", id).valueString;
  unknown70 = Bdat::getVal(bdat.unknown00, "clockStop", id).valueU8;
  unknown74 = Bdat::getVal(bdat.unknown00, "cloud", id).valueU8;
  unknown78 = Bdat::getVal(bdat.unknown00, "opFadeOutEnable", id).valueU8 != 0;
  unknown7c = Bdat::getVal(bdat.unknown00, "opFadeOut", id).valueU16;
  unknown80 = Bdat::getVal(bdat.unknown00, "opFadeWait", id).valueU16;
  unknown84 = Bdat::getVal(bdat.unknown00, "opFadeInEnable", id).valueU8 != 0;
  unknown88 = Bdat::getVal(bdat.unknown00, "opFadeIn", id).valueU16;
  unknown8c = Bdat::getVal(bdat.unknown00, "opFadeColR", id).valueU8;
  unknown90 = Bdat::getVal(bdat.unknown00, "opFadeColG", id).valueU8;
  unknown94 = Bdat::getVal(bdat.unknown00, "opFadeColB", id).valueU8;
  unknown98 = Bdat::getVal(bdat.unknown00, "edFadeOutEnable", id).valueU8 != 0;
  unknown9c = Bdat::getVal(bdat.unknown00, "edFadeOut", id).valueU16;
  unknowna0 = Bdat::getVal(bdat.unknown00, "edFadeWait", id).valueU16;
  unknowna4 = Bdat::getVal(bdat.unknown00, "edFadeInEnable", id).valueU8 != 0;
  unknowna8 = Bdat::getVal(bdat.unknown00, "edFadeIn", id).valueU16;
  unknownac = Bdat::getVal(bdat.unknown00, "edFadeColR", id).valueU8;
  unknownb0 = Bdat::getVal(bdat.unknown00, "edFadeColG", id).valueU8;
  unknownb4 = Bdat::getVal(bdat.unknown00, "edFadeColB", id).valueU8;
  if (Manager::get()->isEndFadeOut() && !unknown98) {
    unknown98 = true;
    unknown9c = 20;
    unknowna0 = 0;
    unknownac = 0;
    unknownb0 = 0;
    unknownb4 = 0;
  }
  unknownb8 = Bdat::getVal(bdat.unknown00, "stFormID", id).valueU16;
  unknownbc = Bdat::getVal(bdat.unknown00, "edFormID", id).valueU16;
  unknownc0 = Bdat::getVal(bdat.unknown00, "opBgm", id).valueU8;
  unknownc1 = Bdat::getVal(bdat.unknown00, "edBgm", id).valueU8;
  unknownc2 = Bdat::getVal(bdat.unknown00, "hideNpc", id).valueU8 != 0;
  unknownc3 = Bdat::getVal(bdat.unknown00, "hideEne", id).valueU8 != 0;
  unknownc4 = Bdat::getVal(bdat.unknown00, "hideMob", id).valueU8 != 0;
  unknownc5 = Bdat::getVal(bdat.unknown00, "hideMap", id).valueU8 != 0;
  unknownc8 = Bdat::getVal(bdat.unknown00, "outsiderOpt", id).valueU16;
  unknowncc = Bdat::getVal(bdat.unknown00, "outsiderEnable", id).valueU8 != 0;
  unknownd0 = Bdat::getVal(bdat.unknown00, "outsiderType", id).valueU8;
  unknownd4 = Bdat::getVal(bdat.unknown00, "outsiderX", id).valueF32;
  unknownd8 = Bdat::getVal(bdat.unknown00, "outsiderY", id).valueF32;
  unknowndc = Bdat::getVal(bdat.unknown00, "outsiderZ", id).valueF32;
  unknowne0 = Bdat::getVal(bdat.unknown00, "outsiderR", id).valueF32;
  unknowne4 = Bdat::getVal(bdat.unknown00, "nextID", id).valueU16;
  unknowne8 = Bdat::getVal(bdat.unknown00, "linkID", id).valueU16;
  unknownec = Bdat::getMember(bdat.unknown00, "nextIDtheater") ? Bdat::getVal(bdat.unknown00, "nextIDtheater", id).valueU16 : 0;
  unknownf0 = Bdat::getVal(bdat.unknown00, "jijiDisp", id).valueU8 != 0;
  unknownf4 = Bdat::getVal(bdat.unknown00, "wpnDisp", id).valueU16;
  unknownf8 = Bdat::getVal(bdat.unknown00, "colFilterNear", id).valueU16;
  unknownfc = Bdat::getVal(bdat.unknown00, "colFilterFar", id).valueU16;
  unknown100 = Bdat::getMember(bdat.unknown00, "envSeam") ? Bdat::getVal(bdat.unknown00, "envSeam", id).valueU16 : 0;
  unknown108 = Bdat::getMember(bdat.unknown00, "evtLight") ? Bdat::getVal(bdat.unknown00, "evtLight", id).valueString : "";
  unknown110 = Bdat::getMember(bdat.unknown00, "hood") ? Bdat::getVal(bdat.unknown00, "hood", id).valueU8 : 1;
  unknown114 = Bdat::getVal(bdat.unknown00, "voice", id).valueU8;
  unknown115 = Bdat::getMember(bdat.unknown00, "cssnd") ? Bdat::getVal(bdat.unknown00, "cssnd", id).valueU8 : false;
  unknown12c = Bdat::getMember(bdat.unknown00, "centerForm") ? Bdat::getVal(bdat.unknown00, "centerForm", id).valueU16 : 0;
  unknown118 = Bdat::getMember(bdat.unknown00, "centerID") ? Bdat::getVal(bdat.unknown00, "centerID", id).valueU16 : 0;
  unknown11c = Bdat::getMember(bdat.unknown00, "centerX") ? Bdat::getVal(bdat.unknown00, "centerX", id).valueF32 : 0.0f;
  unknown120 = Bdat::getMember(bdat.unknown00, "centerY") ? Bdat::getVal(bdat.unknown00, "centerY", id).valueF32 : 0.0f;
  unknown124 = Bdat::getMember(bdat.unknown00, "centerZ") ? Bdat::getVal(bdat.unknown00, "centerZ", id).valueF32 : 0.0f;
  unknown128 = Bdat::getMember(bdat.unknown00, "centerR") ? Bdat::getVal(bdat.unknown00, "centerR", id).valueF32 * DEGREE_TO_RADIAN : 0.0f;
}

bool SeqInfo::exist() const { return unknown00; }

} // namespace event
