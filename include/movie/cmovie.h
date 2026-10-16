#pragma once
#include "mm_mtl/singleton.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

class ICMovie : public mm::mtl::PtrSingleton<ICMovie> {
public:
  virtual bool initialize(mm::mtl::IAllocator *allocator) = 0;
  virtual void finalize() = 0;
  virtual void update(unsigned char *buffer, int width, int height, int pitch) = 0;
  virtual int set_file(const char *path) = 0;
  virtual float get_length() = 0;
  virtual float pos() = 0;
  virtual void play() = 0;
  virtual void pause() = 0;
  virtual void stop() = 0;
  virtual bool isstandby() = 0;
  virtual bool ispause() = 0;
  virtual bool isplaying() = 0;
  virtual void doHomeMenu(bool isEnter) = 0;
};
