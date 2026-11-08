#pragma once
#include <stddef.h>

#include "fw/fw_update_info.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
class MLTHG;
} // namespace ml

namespace nn {
namespace os {
struct FiberType;
} // namespace os
} // namespace nn

namespace gf {

// Inferred role: base of the parameters of the requests, each command reads its own layout; original definition unknown.
struct GfReqParam {};
struct GfSetupParam;
class GfReqSmallCom;

class GfReqManager : public mm::mtl::PtrSingleton<GfReqManager> {
public:
  // Inferred role: queued request; original type name unknown.
  struct unknown001 {
    GfReqParam *unknown00;                      // Inferred role: parameter; original member name unknown.
    void (*unknown08)(const GfReqParam *param); // Inferred role: command; original member name unknown.
    int unknown10;                              // Inferred role: handle; original member name unknown.
  };

  GfReqManager(const GfSetupParam &param);
  ~GfReqManager() override;
  static void build(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void update(const fw::UpdateInfo &info);
  void reqUpdate();
  static nn::os::FiberType *fnReqUpdate(void *param);
  static bool isValid(u32 request);
  static bool isInitialized();
  int getHandle();
  static int addCommand(GfReqParam *param, void (*command)(const GfReqParam *param));
  static void terminateCommand();
  static fw::UpdateInfo *getUpdateInfo();
  static bool isExistCommand(void (*command)(const GfReqParam *param));

  fw::UpdateInfo unknown08;                       // Inferred role: update info; original member name unknown.
  ml::MLTHG *unknown18;                           // Inferred role: micro thread group; original member name unknown.
  u64 unknown20;                                  // Inferred role: micro thread of reqUpdate; original member name unknown.
  mm::mtl::FixedQueue<unknown001, 256> unknown28; // Inferred role: requests; original member name unknown.
  GfReqSmallCom *unknown1838;                     // Inferred role: small commands; original member name unknown.
  bool unknown1840;                               // Inferred role: command terminated; original member name unknown.
  int unknown1844;                                // Inferred role: last handle; original member name unknown.
  bool unknown1848;                               // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfReqManager, unknown08) == 0x08, "");
static_assert(offsetof(GfReqManager, unknown18) == 0x18, "");
static_assert(offsetof(GfReqManager, unknown20) == 0x20, "");
static_assert(offsetof(GfReqManager, unknown28) == 0x28, "");
static_assert(offsetof(GfReqManager, unknown1838) == 0x1838, "");
static_assert(offsetof(GfReqManager, unknown1840) == 0x1840, "");
static_assert(offsetof(GfReqManager, unknown1844) == 0x1844, "");
static_assert(offsetof(GfReqManager, unknown1848) == 0x1848, "");
static_assert(sizeof(GfReqManager) == 0x1850, "");

} // namespace gf
