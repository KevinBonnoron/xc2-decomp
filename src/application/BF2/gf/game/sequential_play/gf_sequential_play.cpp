#include "gf/game/sequential_play/gf_sequential_play.h"

#include "gf/game/quest/gf_quest_id.h"

namespace gf {
class GfSequentialPlaySignal;

void GfSequentialPlay::addWait(f32 time) { addCommand(GfPlayComWait::create(time)); }

void GfSequentialPlay::addWaitEvent(f32 time, GF_OBJ_HANDLE *handle) { addCommand(GfPlayComWaitEvent::create(time, handle)); }

void GfSequentialPlay::addMapjump(const GfMapjumpInfo &info) { addCommand(GfPlayComMapjump::create(info)); }

void GfSequentialPlay::addWaitBattleEnd(u32 battle) { addCommand(GfPlayComWaitBattleEnd::create(battle)); }

void GfSequentialPlay::addEventPlayerStop(bool isStop) { addCommand(GfPlayComEventPlayerStop::create(isStop)); }

void GfSequentialPlay::addResetBladePlayerStop(bool isStop) { addCommand(GfPlayComResetBladePlayerStop::create(isStop)); }

void GfSequentialPlay::addAfterEventScript(u32 event) { addCommand(GfPlayComAfterEventScript::create(event)); }

void GfSequentialPlay::pushPause(u32 pauseBits) { addCommand(GfPlayComPause::create(pauseBits)); }

void GfSequentialPlay::popPause() { addCommand(GfPlayComPause::create(0)); }

void GfSequentialPlay::popState() { addCommand(GfPlayComState::create(GF_STATE(0), false)); }

void GfSequentialPlay::addEventFade() { addCommand(GfPlayComEventFade::create()); }

void GfSequentialPlay::addEvent(int event, u32 param0, u32 param1, bool isEndFadeOut) {
  addCommand(GfPlayComEvent::create(event, param0, param1, isEndFadeOut));
}

void GfSequentialPlay::addEvent(const char *name, u32 param0, u32 param1, bool isEndFadeOut) {
  addCommand(GfPlayComEvent::create(name, param0, param1, isEndFadeOut));
}

void GfSequentialPlay::addCallbackEventSequence(int sequence, bool isStart) { addCommand(GfPlayComCallbackEventSequence::create(sequence, isStart)); }

void GfSequentialPlay::addMenuKizunaring(u32 blade) { addCommand(GfPlayComMenuKizunaring::create(blade)); }

void GfSequentialPlay::addMenuPrecious(u32 item) { addCommand(GfPlayComMenuPrecious::create(item)); }

void GfSequentialPlay::addMenuChapterSave(u32 chapter) { addCommand(GfPlayComMenuChapterSave::create(chapter)); }

void GfSequentialPlay::addMenuChapter(u32 chapter) { addCommand(GfPlayComMenuChapter::create(chapter)); }

void GfSequentialPlay::addMenuChapterEnd(u32 chapter) { addCommand(GfPlayComMenuChapterEnd::create(chapter)); }

void GfSequentialPlay::addMenuZone(u32 zone) { addCommand(GfPlayComMenuZone::create(zone)); }

void GfSequentialPlay::addMenuDummyTutorial(u32 tutorial) { addCommand(GfPlayComMenuDummyTutorial::create(tutorial)); }

void GfSequentialPlay::addOpenMenu(u32 type) { addCommand(GfPlayComOpenMenu::create(type)); }

void GfSequentialPlay::addOpenMenu2(u32 type, MAINMENU menu) { addCommand(GfPlayComOpenMenu2::create(type, menu)); }

void GfSequentialPlay::addStartTutorial(u32 tutorial) { addCommand(GfPlayComStartTutorial::create(tutorial)); }

void GfSequentialPlay::addMiniGame() { addCommand(GfPlayComMiniGame::create()); }

void GfSequentialPlay::addReturnTitle(const ParamReturnTitle &param) { addCommand(GfPlayComReturnTitle::create(param)); }

void GfSequentialPlay::addBattleStart(bool isStart) { addCommand(GfPlayComBattleStart::create(isStart)); }

void GfSequentialPlay::addMenuQuestList() { addCommand(GfPlayComMenuQuestList::create()); }

void GfSequentialPlay::addSalvage(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComSalvage::create(handle)); }

void GfSequentialPlay::addCollect(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComCollect::create(handle)); }

void GfSequentialPlay::addFieldTbox(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComFieldTbox::create(handle)); }

void GfSequentialPlay::addWaitPlayerToStartGmkTuto() { addCommand(GfPlayComWaitPlayerToStartGmkTuto::create()); }

void GfSequentialPlay::addGmkTutorial(const char *name, u32 tutorial) { addCommand(GfPlayComGmkTutorialSeq::create(name, tutorial)); }

void GfSequentialPlay::addPlayerDead(GfPlayerDead dead) { addCommand(GfPlayComPlayerDead::create(dead)); }

void GfSequentialPlay::addTalk(const GfSetupPfTalk &talk) { addCommand(GfPlayComTalk::create(talk)); }

void GfSequentialPlay::addQuestUIOrder(QuestID quest, bool isForce) { addCommand(GfPlayComQuestOrderUI::create(quest, isForce)); }

void GfSequentialPlay::addQuestUIComplete(QuestID quest, QuestID child, QSTATE state) {
  addCommand(GfPlayComQuestCompleteUI::create(quest, child, state));
}

void GfSequentialPlay::addChainAttack() { addCommand(GfPlayComChainAttack::create()); }

void GfSequentialPlay::addArtsMovie(const char *name) { addCommand(GfPlayComArtsMovie::create(name)); }

void GfSequentialPlay::addResetBlade(u32 partyId, int blade) { addCommand(GfPlayComResetBlade::create(partyId, blade)); }

void GfSequentialPlay::addMoverSwitch() { addCommand(GfPlayComMoverSwitch::create()); }

void GfSequentialPlay::addHoodHomuraBattou() { addCommand(GfPlayComHoodHomuraBattou::create()); }

void GfSequentialPlay::startSignal(GfSequentialPlaySignal *signal) { addCommand(GfPlayComExecuteSignal::create(true, signal)); }

void GfSequentialPlay::endSignal(GfSequentialPlaySignal *signal) { addCommand(GfPlayComExecuteSignal::create(false, signal)); }

} // namespace gf
