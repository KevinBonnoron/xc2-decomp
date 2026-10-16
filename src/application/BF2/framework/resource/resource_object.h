#pragma once

namespace fw {

class ResourceObject {
public:
  virtual ~ResourceObject();
  virtual void update() = 0;
  virtual bool valid() const = 0;
};

} // namespace fw
