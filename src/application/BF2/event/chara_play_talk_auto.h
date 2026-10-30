#pragma once
#include "event/i_cmd.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf

namespace event {

class CharaPlayAction;

class CharaPlayTalkAuto : public ICmd {
public:
  enum {
    FLAG_MESSAGE = 0,
    FLAG_STANBY = 1,
    FLAG_PLAY = 2,
    FLAG_MAX = 32,
  };

  virtual ~CharaPlayTalkAuto();
  void stanby(f32 life);
  void play(gf::GfObj *obj);
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  mm::mtl::unknown027<FLAG_MAX> unknown08; // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;            // Inferred role: handle; original member name unknown.
  CharaPlayAction *unknown18;              // Inferred role: action; original member name unknown.
  f32 unknown20;                           // Inferred role: life; original member name unknown.
};

static_assert(sizeof(CharaPlayTalkAuto) == 0x28, "");

} // namespace event
