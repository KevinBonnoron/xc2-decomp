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
    TYPE_SS,
    TYPE_S,
    TYPE_M,
    TYPE_L,
    TYPE_COUNT,
  };

  enum {
    FLAG_IDLE_SHAKE = 1 << 0,
    FLAG_SHAKE = 1 << 1,
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
