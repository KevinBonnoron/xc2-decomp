#pragma once
#include <stddef.h>

#include "event/i_res_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfEvtModel;
} // namespace gf
namespace ml {
class DrStmReadObj;
} // namespace ml
namespace mm {
struct Mat44;
} // namespace mm

namespace event {

enum MODEL_TYPE {
  MODEL_TYPE_UNKNOWN_1 = 1, // Inferred role: driver; original name unknown.
  MODEL_TYPE_UNKNOWN_2 = 2, // Inferred role: blade; original name unknown.
  MODEL_TYPE_UNKNOWN_3 = 3, // Inferred role: npc; original name unknown.
  MODEL_TYPE_UNKNOWN_4 = 4, // Inferred role: enemy; original name unknown.
};

class ModelObj : public IResEvent {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: priority flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: same flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: loading mdo flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: loading arc flag; original name unknown.
  };

  enum {
    KIND_UNKNOWN_0 = 0, // Inferred role: path; original name unknown.
    KIND_UNKNOWN_1 = 1, // Inferred role: desc; original name unknown.
    KIND_UNKNOWN_2 = 2, // Inferred role: type; original name unknown.
    KIND_UNKNOWN_3 = 3, // Inferred role: none; original name unknown.
  };

  struct DESC {
    DESC() : unknown48(nullptr), unknown50(0), unknowna0(nullptr), unknowna8(0) {}

    mm::mtl::FixStr<64> unknown00; // Inferred role: mdo path; original member name unknown.
    void *unknown48;               // Inferred role: mdo adr; original member name unknown.
    size_t unknown50;              // Inferred role: mdo size; original member name unknown.
    mm::mtl::FixStr<64> unknown58; // Inferred role: arc path; original member name unknown.
    void *unknowna0;               // Inferred role: arc adr; original member name unknown.
    size_t unknowna8;              // Inferred role: arc size; original member name unknown.
  };

  struct OPTION {
    OPTION() : unknown00(0), unknown04(0), unknown05(0) {}

    u32 unknown00; // Inferred role: first option; original member name unknown.
    u8 unknown04;  // Inferred role: second option; original member name unknown.
    u8 unknown05;  // Inferred role: third option; original member name unknown.
  };

  ModelObj();
  ModelObj(const char *path, bool isPriority, u32 id);
  ModelObj(const char *path, const DESC &desc, bool isPriority, u32 id);
  ModelObj(MODEL_TYPE type, u32 modelId, const OPTION &option, bool isPriority, u32 id);
  virtual ~ModelObj();
  void setupModel(const DESC &desc);
  void setupModel(MODEL_TYPE type, u32 modelId, const OPTION &option);
  bool getEfpMat(mm::Mat44 &mat, const char *name) const;
  bool getBoneMat(mm::Mat44 &mat, const char *name) const;
  void setReserve(u32 index, bool isReserve);
  bool isReserve(int index);
  bool isSame(const char *path, bool isPriority, u32 id);
  bool isSame(const char *path, const DESC &desc, bool isPriority, u32 id);
  bool isSame(MODEL_TYPE type, u32 modelId, const OPTION &option, bool isPriority, u32 id);
  bool isBusy() const;
  void update();
  bool isSame();
  gf::GF_OBJ_HANDLE *getHandle() const { return unknown120; }
  virtual void OnResEvent(const PARAM &param);

private:
  u32 unknown08;                 // Inferred role: flags; original member name unknown.
  u32 unknown0c;                 // Inferred role: kind; original member name unknown.
  u32 unknown10;                 // Inferred role: model type; original member name unknown.
  u32 unknown14;                 // Inferred role: model id; original member name unknown.
  mm::mtl::FixStr<64> unknown18; // Inferred role: path; original member name unknown.
  u32 unknown5c;                 // Inferred role: id; original member name unknown.
  DESC unknown60;                // Inferred role: resources; original member name unknown.
  OPTION unknown110;             // Inferred role: option; original member name unknown.
  ml::DrStmReadObj *unknown118;  // Inferred role: stream read object; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown120; // Inferred role: handle; original member name unknown.
  gf::GfEvtModel *unknown128;    // Inferred role: evt model; original member name unknown.
  s32 unknown130;                // Inferred role: busy frame; original member name unknown.
  u32 unknown134;                // Inferred role: reserve; original member name unknown.

  friend struct ModelObjLayout;
};

struct ModelObjLayout {
  static_assert(offsetof(ModelObj, unknown08) == 0x08, "");
  static_assert(offsetof(ModelObj, unknown0c) == 0x0c, "");
  static_assert(offsetof(ModelObj, unknown10) == 0x10, "");
  static_assert(offsetof(ModelObj, unknown14) == 0x14, "");
  static_assert(offsetof(ModelObj, unknown18) == 0x18, "");
  static_assert(offsetof(ModelObj, unknown5c) == 0x5c, "");
  static_assert(offsetof(ModelObj, unknown60) == 0x60, "");
  static_assert(offsetof(ModelObj, unknown110) == 0x110, "");
  static_assert(offsetof(ModelObj, unknown118) == 0x118, "");
  static_assert(offsetof(ModelObj, unknown120) == 0x120, "");
  static_assert(offsetof(ModelObj, unknown128) == 0x128, "");
  static_assert(offsetof(ModelObj, unknown130) == 0x130, "");
  static_assert(offsetof(ModelObj, unknown134) == 0x134, "");
  static_assert(sizeof(ModelObj) == 0x138, "");
};

static_assert(sizeof(ModelObj::DESC) == 0xb0, "");
static_assert(offsetof(ModelObj::DESC, unknown48) == 0x48, "");
static_assert(offsetof(ModelObj::DESC, unknown50) == 0x50, "");
static_assert(offsetof(ModelObj::DESC, unknown58) == 0x58, "");
static_assert(offsetof(ModelObj::DESC, unknowna0) == 0xa0, "");
static_assert(offsetof(ModelObj::DESC, unknowna8) == 0xa8, "");
static_assert(offsetof(ModelObj::OPTION, unknown04) == 0x04, "");
static_assert(offsetof(ModelObj::OPTION, unknown05) == 0x05, "");

} // namespace event
