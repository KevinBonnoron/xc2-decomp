#pragma once

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class MessageObject;
struct Message;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComPropertyPc;

namespace pc {

class Agent {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~Agent();
  virtual void setup(GfComPropertyPc &property);
  virtual void cleanup(GfComPropertyPc &property);
  virtual void update(const fw::UpdateInfo &info, GfComPropertyPc &property) = 0;
  virtual bool testFiledAI() const;
  virtual void setFieldAI(GfComPropertyPc &property, bool isEnable);
  virtual bool testBattleAI() const;
  virtual void setBattleAI(GfComPropertyPc &property, bool isEnable);
  virtual bool recieveMessage(GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message);
};

} // namespace pc
} // namespace gf
