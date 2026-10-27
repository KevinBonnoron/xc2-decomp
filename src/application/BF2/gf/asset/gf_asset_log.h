#pragma once
#include <stddef.h>

#include "ml/time_count.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;
class GfAssetPack;

class GfAssetLog : public mm::mtl::PtrSingleton<GfAssetLog> {
public:
  struct AssetInfo {
    AssetInfo() : unknown24(0.0f), unknown28(0) {
      unknown30.start();
      unknown38 = 0;
    }

    mm::mtl::FixStr<32> unknown00; // Inferred role: asset name; original member name unknown.
    f32 unknown24;                 // Inferred role: load time in seconds; original member name unknown.
    u32 unknown28;                 // Inferred role: asset name hash; original member name unknown.
    u8 _2c[0x30 - 0x2c];
    ml::TimeCount unknown30; // Inferred role: load timer; original member name unknown.
    u32 unknown38;           // Inferred role: zero-initialised; original member name unknown.
  };

  GfAssetLog();
  ~GfAssetLog() override;
  u32 getHash(const char *name) const;
  AssetInfo *getAssetInfo(u32 hash);
  void createAssetPack(const GfAssetPack *pack);
  void setAssetPackForLoaded(const GfAssetPack *pack);
  static void create(const GfSetupParam &param);
  static void initialize(const GfSetupParam &param);
  static void destroy();
  static void finalize();
  void renderInfo();
  static void update();

  mm::mtl::FixedQueue<AssetInfo, 32> unknown08; // Inferred role: logged asset packs; original member name unknown.
};

static_assert(sizeof(GfAssetLog::AssetInfo) == 0x40, "");
static_assert(offsetof(GfAssetLog, unknown08) == 0x08, "");
static_assert(sizeof(GfAssetLog) == 0x818, "");

} // namespace gf
