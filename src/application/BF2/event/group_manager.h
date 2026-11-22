#pragma once
#include "event/group.h"
#include "event/i_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CharaObj;

class GroupManager : public IManager, public mm::mtl::Singleton<GroupManager> {
public:
  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
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

  // Inferred role: translation of the group matrix; original name unknown.
  mm::Vec3 unknown001() const { return unknown450.unknown004(); }
  // Inferred role: radius of the group; original name unknown.
  f32 unknown002() const { return unknown490; }

private:
  u32 unknown10;        // Inferred role: disp flags; original member name unknown.
  Group m_group;        // Inferred role: group; original member name unknown.
  mm::Mat44 unknown450; // Inferred role: matrix; original member name unknown.
  f32 unknown490;       // Inferred role: radius; original member name unknown.
};

static_assert(sizeof(GroupManager) == 0x4a0, "");

} // namespace event
