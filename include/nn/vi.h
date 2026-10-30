#pragma once
#include "nn/result.h"

// Provenance: every name and prototype below is the public SDK API, as declared in the open-ead nnheaders project
// (https://github.com/open-ead/nnheaders, include/nn/vi.h); each function is an imported symbol of the game
// (_ZN2nn2vi... in work/syms_base.txt), called by grlib::CGLibDeviceVI (0x71007b33f0 to 0x71007b3510).

namespace nn {
namespace vi {

class Display;
class Layer;

enum ScalingMode {
  None,
  Exact,
  FitLayer,
  ScaleAndCrop,
  PreserveAspectRatio,
};

void Initialize();
void Finalize();
Result OpenDefaultDisplay(Display **outDisplay);
Result CloseDisplay(Display *display);
Result CreateLayer(Layer **outLayer, Display *display);
void DestroyLayer(Layer *layer);
Result GetNativeWindow(void **outWindow, Layer *layer);
Result SetLayerScalingMode(Layer *layer, ScalingMode scalingMode);

} // namespace vi
} // namespace nn
