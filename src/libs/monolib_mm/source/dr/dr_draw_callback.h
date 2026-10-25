#pragma once

namespace ml {

class IDrDrawWorkInfo;

class IDrDrawCallback {
public:
  virtual ~IDrDrawCallback() {}
  virtual void begin();
  virtual void end();
  virtual void apply(const IDrDrawWorkInfo *info);
  virtual void opacityRender(const IDrDrawWorkInfo *info);
  virtual void alphaRender(const IDrDrawWorkInfo *info);
  virtual void lastRender(const IDrDrawWorkInfo *info);
  virtual void blurRender(const IDrDrawWorkInfo *info);
  virtual void finalRender(const IDrDrawWorkInfo *info);
};

} // namespace ml
