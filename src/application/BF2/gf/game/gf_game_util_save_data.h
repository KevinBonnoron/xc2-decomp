#pragma once

namespace gf {

struct SDataGame;
struct SDataOption;
struct SDataSave;
struct SDataSystem;

class GfGameUtilSaveData {
public:
  static void setupGameSaveData(SDataSave &saveData);
  static void setupOptionSaveData(SDataOption &optionData);
  static void getSaveData(SDataGame &dataGame);
  static void getSaveData(SDataSystem &dataSystem);
  static SDataOption &getValidOptionData();
  static void flushOptionSaveData();
  static void setTitleSaveData(const SDataSave &saveData);
};

} // namespace gf
