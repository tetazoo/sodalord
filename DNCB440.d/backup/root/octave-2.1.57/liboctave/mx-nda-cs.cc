// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-nda-cs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "CNDArray.h"
#include "dNDArray.h"
#include "oct-cmplx.h"
NDS_BIN_OPS (ComplexNDArray, NDArray, Complex)
NDS_CMP_OPS (NDArray, , Complex, real)
NDS_BOOL_OPS (NDArray, Complex, 0.0)
