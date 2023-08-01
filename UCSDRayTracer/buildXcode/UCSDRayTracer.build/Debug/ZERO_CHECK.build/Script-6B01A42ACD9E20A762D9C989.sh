#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/brendanmulcahey/Library/Mobile Documents/com~apple~CloudDocs/Self Learning/RayTracerClean/UCSDRayTracer/buildXcode"
  make -f /Users/brendanmulcahey/Library/Mobile\ Documents/com~apple~CloudDocs/Self\ Learning/RayTracerClean/UCSDRayTracer/buildXcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/brendanmulcahey/Library/Mobile Documents/com~apple~CloudDocs/Self Learning/RayTracerClean/UCSDRayTracer/buildXcode"
  make -f /Users/brendanmulcahey/Library/Mobile\ Documents/com~apple~CloudDocs/Self\ Learning/RayTracerClean/UCSDRayTracer/buildXcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/brendanmulcahey/Library/Mobile Documents/com~apple~CloudDocs/Self Learning/RayTracerClean/UCSDRayTracer/buildXcode"
  make -f /Users/brendanmulcahey/Library/Mobile\ Documents/com~apple~CloudDocs/Self\ Learning/RayTracerClean/UCSDRayTracer/buildXcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/brendanmulcahey/Library/Mobile Documents/com~apple~CloudDocs/Self Learning/RayTracerClean/UCSDRayTracer/buildXcode"
  make -f /Users/brendanmulcahey/Library/Mobile\ Documents/com~apple~CloudDocs/Self\ Learning/RayTracerClean/UCSDRayTracer/buildXcode/CMakeScripts/ReRunCMake.make
fi

