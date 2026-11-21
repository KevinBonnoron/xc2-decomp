#pragma once

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam_light.h"
#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;
struct _wkSeamReadCall;
struct _wkSeamReadWait;

class DrMdoCtlSeamRead : public DrMdoCtlSeamLight {
public:
  DrMdoCtlSeamRead(int viewNum);
  _wkSeamReadCall *getSeamReadCall();
  void releaseSeamReadCall(int index);
  void updateReadList();
  void updateReadCall();
  void callBaseMapStream(_wkSeamReadWait *wait);
  void callLowMdlStream(_wkSeamReadWait *wait);
  void callInstMapStream(_wkSeamReadWait *wait);
  void callMpfMdlStream(_wkSeamReadWait *wait);
  void callEnvMdlStream(_wkSeamReadWait *wait);
  void callBaseVertexStream(_wkSeamReadWait *wait);
  void callVertexStream(_wkSeamReadWait *wait);
  void callTexutreStream(_wkSeamReadWait *wait);
  void callHeightTexutreStream(_wkSeamReadWait *wait);
  void callTexListStream(_wkSeamReadWait *wait);
  void callInstPosStream(_wkSeamReadWait *wait);
  void callMpfEtclStream(_wkSeamReadWait *wait);
  void callMpfPolilStream(_wkSeamReadWait *wait);
  void callLightStream(_wkSeamReadWait *wait);
  void waitBaseMapStream(_wkSeamReadCall *call, bool isRead);
  void waitLowMdlStream(_wkSeamReadCall *call, bool isRead);
  void waitInstMapStream(_wkSeamReadCall *call, bool isRead);
  void waitMpfMdlStream(_wkSeamReadCall *call, bool isRead);
  void waitEnvMdlStream(_wkSeamReadCall *call, bool isRead);
  void waitBaseVertexStream(_wkSeamReadCall *call, bool isRead);
  void waitVertexStream(_wkSeamReadCall *call, bool isRead);
  void waitTexutreStream(_wkSeamReadCall *call, bool isRead);
  void waitHeightTexutreStream(_wkSeamReadCall *call, bool isRead);
  void waitTexListStream(_wkSeamReadCall *call, bool isRead);
  void waitInstPosStream(_wkSeamReadCall *call, bool isRead);
  void waitMpfEtcStream(_wkSeamReadCall *call, bool isRead);
  void waitMpfPoliStream(_wkSeamReadCall *call, bool isRead);
  void waitLightStream(_wkSeamReadCall *call, bool isRead);

  // Inferred helper: the code of a read that is not complete yet: sets flag 0x10000 and, when the DrMan level is above `level`, flag 0x400;
  // the statements the game repeats in the wait*Stream functions that have no other statement in between; original name unknown.
  void unknown006(int level) {
    unknownc7c |= 0x10000;
    if (m_drMan->unknown1cfc > level) {
      unknownc7c |= 0x400;
    }
  }

  template <typename T> void unknown007(DrResMdoSeamMemObj *mem, void *work, const T &size, s16 kind, const int &handle, const _wkSeamReadWait *wait);
};

} // namespace ml
