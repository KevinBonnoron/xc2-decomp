#pragma once
#include "event/i_manager.h"
#include "event/mdlstm_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace event {

class MdlstmManager : public IManager, public mm::mtl::Singleton<MdlstmManager> {
public:
  static constexpr u32 OBJ_COUNT = 1024;

  enum {
    FLAG_CREATE = 1 << 0,
    FLAG_START = 1 << 1,
  };

  enum {
    REUSE_FLAG_ENABLE = 1 << 0,
  };

  MdlstmManager();
  virtual ~MdlstmManager() {}
  void clear();
  void update();
  void render();
  void start();
  void setReuseEnable(bool isReuseEnable);
  void setReuseFlag(int reuseFlag);
  virtual void OnEventProc(MSG_TYPE type);

  bool isReuseEnable() const;
  bool isLoadingPrio(f32 priority) const;
  bool searchByHandle(gf::GF_OBJ_HANDLE *handle) const;

private:
  u32 unknown10;                                             // Inferred role: flags; original member name unknown.
  u32 unknown14;                                             // Inferred role: reuse flags; original member name unknown.
  MdlstmObj unknown18[OBJ_COUNT];                            // Inferred role: objs; original member name unknown.
  u32 unknown3c018;                                          // Inferred role: object count; original member name unknown.
  mm::mtl::FixedVector<MdlstmObj *, OBJ_COUNT> unknown3c020; // Inferred role: active objs; original member name unknown.
  u32 _3e028;
  u32 _3e02c;
  int unknown3e030; // Inferred role: reuse flag; original member name unknown.
};

static_assert(sizeof(MdlstmManager) == 0x3e038, "");

} // namespace event
