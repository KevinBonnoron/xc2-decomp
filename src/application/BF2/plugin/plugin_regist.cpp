#include "plugin/plugin_regist.h"

void pluginRegist() {
  ocBuiltinRegist();
  ocThreadRegist();
  ocBdatRegist();
  ocMenuRegist();
  ocAiDataRegist();
  pluginWaitRegist();
  pluginDebRegist();
  pluginSysRegist();
  pluginFldRegist();
  pluginPartyRegist();
  pluginUiRegist();
  pluginEvtRegist();
  pluginEvtObjRegist();
  pluginEvtSetupRegist();
  pluginEvtCharaRegist();
  pluginEvtCamRegist();
  pluginEvtEffRegist();
  pluginEvtLgtRegist();
  pluginEvtPostRegist();
  pluginEvtTextRegist();
  pluginEvtSelRegist();
  pluginEvtStatusRegist();
  pluginEvtBgmRegist();
  pluginEvtSeRegist();
  pluginEvtVolRegist();
  pluginEvtRandRegist();
  pluginEvtPayRegist();
  pluginEvtEnvRegist();
  pluginEvtMovRegist();
  pluginEvtMapRegist();
  pluginEvtUiRegist();
  pluginEvtVoiceRegist();
  pluginBtlAiRegist();
  pluginGmkRegist();
}
