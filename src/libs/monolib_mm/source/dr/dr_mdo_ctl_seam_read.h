#pragma once

#include "dr/dr_mdo_ctl_seam_light.h"

namespace ml {
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
};

} // namespace ml
