#include "gmk/gmk_event.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_active_list.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkEvent, GmkEvent::BdatInfo, 1414420037u, 4u, GmkEventGob>::initGmkBdatInfo(GmkEvent::BdatInfo &, int &, const AGmkBase &);

template class TGmkActiveList<GmkEvent>;

GmkEvent::GmkEvent() : IntrusiveListNode(), unknown60(nullptr), unknownF0(false), unknownF1(false), unknownF2(false) {}

void GmkEvent::debugDraw() const { isValid(); }

void GmkEvent::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0a = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("EventID", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("Icon", id, BDAT_TYPE_U16);
}

bool GmkEvent::BdatInfo::isCondMatched() const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

void GmkEvent::beginEvent() {
  if (!unknownF1 && gf::GfPlayFactory::createOneEventForGimmick(unknown20.unknown10->unknown02)) {
    unknownF1 = true;
    unknownF2 = false;
    gf::SCOM_QUEST_REACH::createArrivePlace(unknown20.unknown18);
  }
}

void GmkEvent::disposeGmkPhantom() {
  if (this != nullptr && intoNode() && TGmkActiveList<GmkEvent>::get() != nullptr) {
    TGmkActiveList<GmkEvent>::get()->unknown08.erase(this);
  }
  unknown60.dispose();
}

void GmkEvent::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkEvent::dispose() {
  unknownF2 = false;
  unknownF0 = false;
  unknownF1 = false;
  disposeGmkPhantom();
  AGmkBase::dispose();
}

GmkType GmkEvent::getGmkType() const { return GMK_TYPE; }

} // namespace gmk
