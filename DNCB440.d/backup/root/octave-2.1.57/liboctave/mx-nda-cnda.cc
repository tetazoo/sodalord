// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-nda-cnda.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "CNDArray.h"
#include "dNDArray.h"
NDND_BIN_OPS (ComplexNDArray, NDArray, ComplexNDArray)
NDND_CMP_OPS (NDArray, , ComplexNDArray, real)
NDND_BOOL_OPS (NDArray, ComplexNDArray, 0.0)
