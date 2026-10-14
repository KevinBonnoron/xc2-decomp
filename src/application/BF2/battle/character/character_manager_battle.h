#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class BattleCharacter;

class CharacterManager : public mm::mtl::PtrSingleton<CharacterManager> {
public:
  int SearchCharacter(gf::GF_OBJ_HANDLE *handle) const;
  BattleCharacter *GetCharacterConst(gf::GF_OBJ_HANDLE *handle) const;
  BattleCharacter *GetCharacterConst(int id) const;
  BattleCharacter *GetControlCharacter();
  int GetCharacterIDByAiChrID(int aiId, bool isPlayer) const;
  bool IsExistHomuri() const;
};

} // namespace btl
