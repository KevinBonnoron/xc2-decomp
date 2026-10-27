#pragma once

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class ASMControl;
class Binding;
class Blender;
class Control;
class ExtraTruckBuffer;
class Pose;
class ResASM;
class Skeleton;

class Factory {
public:
  static Pose *createPose(const Skeleton *skeleton, mm::mtl::IAllocator *allocator);
  static Binding *createReferencePoseAnimation(const Skeleton *skeleton, mm::mtl::IAllocator *allocator);
  static ExtraTruckBuffer *createExtraTruckBuffer(const Skeleton *skeleton, const char *name, mm::mtl::IAllocator *allocator);
  static Blender *createBlender(const Skeleton *skeleton, mm::mtl::IAllocator *allocator);
  static Control *createControl(const Binding *binding, mm::mtl::IAllocator *allocator);
  static ASMControl *createASMControl(const ResASM &resAsm, mm::mtl::IAllocator &allocator);
};

} // namespace anm
