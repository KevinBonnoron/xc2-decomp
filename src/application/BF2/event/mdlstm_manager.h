#pragma once
#include "event/i_manager.h"
#include "event/mdlstm_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

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

  bool isReuseEnable() const { return (mReuseFlags & REUSE_FLAG_ENABLE) != 0; }

private:
  u32 flags;
  u32 mReuseFlags;
  MdlstmObj objs[OBJ_COUNT];
  u32 mObjCount;
  mm::mtl::FixedVector<MdlstmObj *, OBJ_COUNT> mActiveObjs;
  u32 _3e028;
  u32 _3e02c;
  int mReuseFlag;
};

static_assert(sizeof(MdlstmManager) == 0x3e038, "");

} // namespace event
