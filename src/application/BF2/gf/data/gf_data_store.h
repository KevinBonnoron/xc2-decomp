#pragma once
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"
#include "mm_mtl/singleton.h"

namespace gf {

struct GfSetupParam;

class GfDataStore : public mm::mtl::PtrSingleton<GfDataStore> {
public:
  GfDataStore(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfDataStore();

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void clear();
  static void initSystemData();
  static void initGameData();
  static void initOptionData();
  static SDataSystem &getDataSystem();
  static SDataGame &getDataGame();
  static SDataOption &getDataOption();
  static void setGameData(const SDataSystem *dataSystem, const SDataGame *dataGame, const SDataOption *dataOption);
  static void setupOptionData(const SDataOption &dataOption);

private:
  SDataSystem mDataSystem;
  SDataGame mDataGame;
  SDataOption mDataOption;
  bool mInitialized;
};

} // namespace gf
