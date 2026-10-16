#include "gf/game/talk/gf_game_talk.h"

#include "bdat.h"
#include "event/manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

GfGameTalk::GfGameTalk(const GfSetupParam &param) { initialize(param); }

void GfGameTalk::initialize(const GfSetupParam &) { initialized = true; }

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

void GfGameTalk::finalize() { initialized = false; }

bool GfGameTalk::isInitialized() { return get() != nullptr && get()->initialized; }

void GfGameTalk::update(const fw::UpdateInfo &) {}

void GfGameTalk::play(const GfSetupPfTalk &talk) {
  u8 *list = Bdat::getFP("EVT_listList");
  int listTop = Bdat::getIdTop(list);
  int listCount = Bdat::getIdCount(list);
  for (int i = listTop; i < listTop + listCount; i++) {
    u8 *bdat = Bdat::getFP(Bdat::getVal(list, "listSeat", i).valueString);
    int top = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    if (talk.event >= top && top + count > talk.event) {
      mm::mtl::FixStr<64> name = Bdat::getVal(bdat, "evtName", talk.event).valueString;
      if (name.c_str()[0] == '\0') {
        return;
      }
      if (!event::Manager::get()->isDebugPlayOnetime() && Bdat::getVal(bdat, "linkID", talk.event).valueU16 != 0) {
        name += "_link";
      }
      Bdat::getVal(bdat, "category", talk.event);
      event::Manager::get()->play(name.c_str(), talk.handle, talk.param0, talk.param1, 0, 0, false);
      return;
    }
  }
}

void GfGameTalk::end() { event::Manager::get()->end(); }

} // namespace gf
