#pragma once

namespace ml {

float vdC_Hammersley(int index, int base);
void hammersley(float *out, int count);
float vdC_Halton(int index, int base);

} // namespace ml
