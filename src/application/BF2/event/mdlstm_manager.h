#pragma once
#include "event/i_manager.h"
#include "event/mdlstm_data.h"
#include "event/mdlstm_obj.h"
#include "event/model_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace mtl {
class ALLOC_HANDLE;
}

namespace event {

class MdlstmManager : public IManager, public mm::mtl::Singleton<MdlstmManager> {
public:
  static constexpr u32 OBJ_UNKNOWN_1024 = 1024; // Inferred role: obj count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: create flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: start flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Role and original name unknown.
  };

  enum {
    REUSE_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: enable flag; original name unknown.
  };

  MdlstmManager();
  virtual ~MdlstmManager() {}
  void clear();
  void dispose(ModelObj *model);
  void create(mtl::ALLOC_HANDLE handle);
  void update();
  void render();
  void start();
  void setReuseEnable(bool isReuseEnable);
  void setReuseFlag(int reuseFlag);
  f32 getNextCutFrame(f32 frame);
  void addReplaceInfo(const MdlstmData::Info &info);
  virtual void OnEventProc(MSG_TYPE type);

  bool isReuseEnable() const;
  bool isLoadingPrio(f32 priority) const;
  bool searchByHandle(gf::GF_OBJ_HANDLE *handle) const;
  void load(f32 frame, const char *path, u32 value, bool isActive);
  void load(f32 frame, MODEL_TYPE type, u32 id, u32 value, bool isActive);
  ModelObj *build(const char *path, u32 value);
  ModelObj *build(MODEL_TYPE type, u32 id, u32 value);

private:
  // Inferred role: inserts the object into the frame ordered list; no game symbol, original name unknown.
  void unknown001(MdlstmObj *obj) {
    for (u32 i = 0; i < unknown3c020.size(); i++) {
      if (!(unknown3c020[i]->unknown10 <= obj->unknown10)) {
        while (i < unknown3c020.size()) {
          MdlstmObj *next = unknown3c020[i];
          unknown3c020[i] = obj;
          obj = next;
          i++;
        }
      }
    }
    unknown3c020.push_back(obj);
  }

  u32 unknown10;                                                    // Inferred role: flags; original member name unknown.
  u32 unknown14;                                                    // Inferred role: reuse flags; original member name unknown.
  MdlstmObj unknown18[OBJ_UNKNOWN_1024];                            // Inferred role: objs; original member name unknown.
  u32 unknown3c018;                                                 // Inferred role: object count; original member name unknown.
  mm::mtl::FixedVector<MdlstmObj *, OBJ_UNKNOWN_1024> unknown3c020; // Inferred role: active objs; original member name unknown.
  u32 _3e028;
  u32 _3e02c;
  int unknown3e030; // Inferred role: reuse flag; original member name unknown.
};

static_assert(sizeof(MdlstmManager) == 0x3e038, "");

} // namespace event
