#pragma once
#include "gf/request/gf_req_scom.h"

namespace gf {

struct GAME_VOICE_HANDLE;
struct GF_OBJ_HANDLE;

class GfSalvageVoice {
public:
  static GAME_VOICE_HANDLE *playVoice(GF_OBJ_HANDLE *handle, CV_SALVAGE voice);
  static GAME_VOICE_HANDLE *playResultVoice(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice);
};

} // namespace gf
