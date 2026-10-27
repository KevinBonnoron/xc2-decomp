#pragma once

namespace effect {

// Interface inferred from the base of fw::EffectCasterSend (1.0.0: _ZTVN2fw16EffectCasterSendE) and from the
// SystemManager::es_create and es_set_param overloads that take it. Only the virtual destructor is known to be
// declared first; the other virtual functions are those of fw::EffectCasterSend.
class IEffectCallBack {
public:
  virtual ~IEffectCallBack() {}
};

} // namespace effect
