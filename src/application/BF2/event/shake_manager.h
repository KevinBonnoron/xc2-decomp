#pragma once
#include "event/i_manager.h"
#include "event/shaker.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class ShakeManager : public IManager, public mm::mtl::Singleton<ShakeManager> {
public:
  enum TYPE {
    TYPE_SS, // Name given by the game string "TYPE_SS" of ShakeManager::s_names[0] (built inline by its initializer, 0x7100140fc8); row 2 of EVT_shaketype has the same text.
    TYPE_S,  // Name given by the game string "TYPE_S" of ShakeManager::s_names[1]; row 3 of EVT_shaketype has the same text.
    TYPE_M,  // Name given by the game string "TYPE_M" of ShakeManager::s_names[2]; row 4 of EVT_shaketype has the same text.
    TYPE_L,  // Name given by the game string "TYPE_L" of ShakeManager::s_names[3]; row 5 of EVT_shaketype has the same text.
    TYPE_COUNT,
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: idle shake flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: shake flag; original name unknown.
  };

  static mm::mtl::FixStr<32> s_names[TYPE_COUNT];

  ShakeManager();
  void create();
  void destroy();
  void clear();
  void update();
  void idle();
  void tail();
  void play(const char *name, f32 life, f32 fadeIn, f32 fadeOut);
  void setIdleShake(bool isIdleShake);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;              // Inferred role: flags; original member name unknown.
  Shaker unknown18;           // Inferred role: shaker; original member name unknown.
  u32 unknownca8[TYPE_COUNT]; // Inferred role: shake ids; original member name unknown.
  u32 unknowncb8;             // Inferred role: idle shake id; original member name unknown.
};

static_assert(sizeof(ShakeManager) == 0xcc0, "");

} // namespace event
