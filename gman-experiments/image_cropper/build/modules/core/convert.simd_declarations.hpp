#define CV_CPU_SIMD_FILENAME "/home/sgune/devs/see_plus_plus/gman-experiments/image_cropper/opencv-4.x/modules/core/src/convert.simd.hpp"
#define CV_CPU_DISPATCH_MODE AVX2
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODES_ALL AVX2, BASELINE

#undef CV_CPU_SIMD_FILENAME
