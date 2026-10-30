#include "grlib/cglib_device_obj.h"

#include <stdlib.h>

#include "grlib/cglib_display.h"
#include "grlib/cglib_system_context.h"
#include "nn/diag.h"
#include "nn/result.h"
#include "nn/vi.h"
#include "nv.h"

namespace {

// Inferred role: graphics allocator callback; original name unknown.
void *unknown001(size_t size, size_t alignment, void *userPtr) { return aligned_alloc(alignment, size); }

// Inferred role: graphics free callback; original name unknown.
void unknown002(void *address, void *userPtr) { free(address); }

// Inferred role: graphics reallocator callback; original name unknown.
void *unknown003(void *address, size_t newSize, void *userPtr) { return realloc(address, newSize); }

// Inferred role: graphics devtools allocator callback; original name unknown.
void *unknown004(size_t size, size_t alignment, void *userPtr) { return aligned_alloc(alignment, size); }

// Inferred role: graphics devtools free callback; original name unknown.
void unknown005(void *address, void *userPtr) { free(address); }

// Inferred role: graphics devtools reallocator callback; original name unknown.
void *unknown006(void *address, size_t newSize, void *userPtr) { return realloc(address, newSize); }

} // namespace

namespace grlib {

CGLibDeviceObj_plf::CGLibDeviceObj_plf() {}

CGLibDeviceObj::CGLibDeviceObj() {}

bool CGLibDeviceObj::init() {
  nv::SetGraphicsAllocator(::unknown001, ::unknown002, ::unknown003, nullptr);
  nv::SetGraphicsDevtoolsAllocator(::unknown004, ::unknown005, ::unknown006, nullptr);
  nv::InitializeGraphics(malloc(0x800000), 0x800000);
  unknown5000.init();
  PFNNVNDEVICEGETPROCADDRESSPROC getProcAddress = reinterpret_cast<PFNNVNDEVICEGETPROCADDRESSPROC>(nvnBootstrapLoader("nvnDeviceGetProcAddress"));
  nvnLoadCProcs(nullptr, getProcAddress);
  {
    NVNdeviceBuilder deviceBuilder;
    nvnDeviceBuilderSetDefaults(&deviceBuilder);
    nvnDeviceBuilderSetFlags(&deviceBuilder, 0);
    nvnDeviceInitialize(&unknown00, &deviceBuilder);
  }
  nvnLoadCProcs(&unknown00, getProcAddress);
  int deviceInfo;
  int minorVersion;
  nvnDeviceGetInteger(&unknown00, NVN_DEVICE_INFO_API_MAJOR_VERSION, &deviceInfo);
  nvnDeviceGetInteger(&unknown00, NVN_DEVICE_INFO_API_MINOR_VERSION, &minorVersion);
  NVNqueueBuilder queueBuilder;
  nvnQueueBuilderSetDevice(&queueBuilder, &unknown00);
  nvnQueueBuilderSetDefaults(&queueBuilder);
  deviceInfo = 0;
  nvnDeviceGetInteger(&unknown00, NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_MIN_SIZE, &deviceInfo);
  deviceInfo *= 2;
  nvnQueueBuilderSetCommandMemorySize(&queueBuilder, deviceInfo);
  nvnQueueBuilderSetCommandFlushThreshold(&queueBuilder, deviceInfo);
  if (!nvnQueueInitialize(&unknown3000, &queueBuilder)) {
    return false;
  }
  nvnDeviceSetDepthMode(&unknown00, NVN_DEPTH_MODE_NEAR_IS_MINUS_W);
  nvnDeviceSetWindowOriginMode(&unknown00, NVN_WINDOW_ORIGIN_MODE_UPPER_LEFT);
  return true;
}

void CGLibDeviceVI::init() {
  unknown18 = 1280;
  unknown1c = 720;
  nn::vi::Initialize();
  nn::vi::OpenDefaultDisplay(&unknown08);
  nn::Result result = nn::vi::CreateLayer(&unknown10, unknown08);
  NN_ASSERT(result.IsSuccess());
  nn::vi::SetLayerScalingMode(unknown10, nn::vi::FitLayer);
  result = nn::vi::GetNativeWindow(&unknown00, unknown10);
  NN_ASSERT(result.IsSuccess());
}

void CGLibDeviceObj::release() {
  nvnQueueFinalize(&unknown3000);
  nvnDeviceFinalize(&unknown00);
  unknown5000.release();
}

void CGLibDeviceVI::release() {
  nn::vi::DestroyLayer(unknown10);
  nn::vi::CloseDisplay(unknown08);
  nn::vi::Finalize();
}

void CGLibDeviceObj::swapChain() { context::CGLibSystemContext::get()->unknown1110.swapChain(&unknown3000); }

void CGLibDeviceVI::update() {}

CGLibDeviceVI::CGLibDeviceVI() {}

CGLibDeviceVI::~CGLibDeviceVI() {}

} // namespace grlib
