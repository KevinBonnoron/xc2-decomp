#include "gf/game/talk/gf_game_talk.h"

#include "bdat.h"
#include "event/manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

GfGameTalk::GfGameTalk(const GfSetupParam &param) { initialize(param); }

void GfGameTalk::initialize(const GfSetupParam &) { unknown08 = true; }

GfGameTalk::~GfGameTalk() {}

void GfGameTalk::build(const GfSetupParam &param) {
  // __LINE__ must be 48 as in the original file: its value changes the instruction order.
#line 48
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameTalk(param);
}

void GfGameTalk::destroy() {
  GfGameTalk *gameTalk = get();
  gameTalk->finalize();
  delete gameTalk;
}

void GfGameTalk::finalize() { unknown08 = false; }

bool GfGameTalk::isInitialized() { return get() != nullptr && get()->unknown08; }

void GfGameTalk::update(const fw::UpdateInfo &) {}

bool GfGameTalk::isPlaying() { return event::Manager::get()->isPlay(); }

bool GfGameTalk::isError() { return (event::Manager::get()->unknown18 & event::Manager::FLAG_PLAY_END) != 0; }

void GfGameTalk::play(const GfSetupPfTalk &talk) {
  u8 *list = Bdat::getFP("EVT_listList");
  int listTop = Bdat::getIdTop(list);
  int listCount = Bdat::getIdCount(list);
  for (int i = listTop; i < listTop + listCount; i++) {
    u8 *bdat = Bdat::getFP(Bdat::getVal(list, "listSeat", i).valueString);
    int top = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    if (talk.unknown00 >= top && top + count > talk.unknown00) {
      mm::mtl::FixStr<64> name = Bdat::getVal(bdat, "evtName", talk.unknown00).valueString;
      if (name.c_str()[0] == '\0') {
        return;
      }
      if (!event::Manager::get()->isDebugPlayOnetime() && Bdat::getVal(bdat, "linkID", talk.unknown00).valueU16 != 0) {
        name += "_link";
      }
      Bdat::getVal(bdat, "category", talk.unknown00);
      event::Manager::get()->play(name.c_str(), talk.unknown08, talk.unknown10, talk.unknown14, 0, 0, false);
      return;
    }
  }
}

void GfGameTalk::end() { event::Manager::get()->end(); }

} // namespace gf
