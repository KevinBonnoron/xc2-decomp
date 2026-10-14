#pragma once
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"

namespace gf {

struct GfSetupParam;

class GfDataStore {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();
  static void setGameData(const SDataSystem *dataSystem, const SDataGame *dataGame, const SDataOption *dataOption);
  static void setupOptionData(const SDataOption &dataOption);
  static SDataSystem &getDataSystem();
  static SDataGame &getDataGame();
  static SDataOption &getDataOption();
};

} // namespace gf
