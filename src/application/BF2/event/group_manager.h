#pragma once
#include "event/group.h"
#include "event/i_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CharaObj;

class GroupManager : public IManager, public mm::mtl::Singleton<GroupManager> {
public:
  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  GroupManager();
  virtual ~GroupManager() {}
  void push(const CharaObj *chara);
  void pop(const CharaObj *chara);
  void clear();
  void update();
  void render();
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;        // Inferred role: disp flags; original member name unknown.
  Group unknown20;      // Inferred role: group; original member name unknown.
  mm::Mat44 unknown450; // Inferred role: matrix; original member name unknown.
  f32 unknown490;       // Inferred role: radius; original member name unknown.
};

static_assert(sizeof(GroupManager) == 0x4a0, "");

} // namespace event
