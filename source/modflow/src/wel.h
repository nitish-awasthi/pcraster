#ifndef INCLUDED_WEL
#define INCLUDED_WEL

#ifndef INCLUDED_STDDEFX
#include "stddefx.h"
#define INCLUDED_STDDEFX
#endif


// Library headers.

// PCRaster library headers.
#ifndef INCLUDED_DISCR_BLOCKDATA
#include "discr_blockdata.h"
#define INCLUDED_DISCR_BLOCKDATA
#endif

// Module headers.



class PCRModflow;

namespace calc {
  class Field;
}


class WEL{
 protected:
 private:
  PCRModflow *d_mf;
  int              d_fortran_unit_number;
 public:
  WEL(PCRModflow *mf);
  ~WEL();
  void writeWEL() const;
  bool setWell(const float *values, size_t mfLayer);
  void setWell(const discr::BlockData<REAL4> &well);
  void setWell(const calc::Field *well, size_t layer);


  calc::Field*     get_well            (size_t layer);
};

#endif // INCLUDED_WEL
