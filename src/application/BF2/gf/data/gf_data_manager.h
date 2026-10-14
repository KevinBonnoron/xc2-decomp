#pragma once
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"
#include "mm_mtl/singleton.h"

namespace gf {

struct GfSetupParam;

class GfDataManager : public mm::mtl::PtrSingleton<GfDataManager> {
public:
  GfDataManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfDataManager();

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();

  static void clear();
  static void setupGame(const SDataSystem *dataSystem, const SDataGame *dataGame, const SDataOption *dataOption);
  static void setupOptionData(const SDataOption &dataOption);

  static SDataSystem *getDataSystem();
  static SDataGame *getDataGame();
  static SDataOption *getDataOption();

private:
  bool mInitialized;
};

} // namespace gf
