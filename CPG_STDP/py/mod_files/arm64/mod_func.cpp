#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern "C" void _5ht_reg(void);
extern "C" void _AXNODE_reg(void);
extern "C" void _FC_reg(void);
extern "C" void _MOTONEURON_reg(void);
extern "C" void _MOTONEURON_5HT_reg(void);
extern "C" void _NaP_reg(void);
extern "C" void _cac1_reg(void);
extern "C" void _caconc_reg(void);
extern "C" void _cal_reg(void);
extern "C" void _diffusion_reg(void);
extern "C" void _hill_eq_reg(void);
extern "C" void _kir_reg(void);
extern "C" void _kno_reg(void);
extern "C" void _nav14_reg(void);
extern "C" void _pregen_reg(void);
extern "C" void _slow5HT_reg(void);
extern "C" void _stdp_reg(void);
extern "C" void _stdp_mini_reg(void);
extern "C" void _stdwa_soft_reg(void);
extern "C" void _xm_reg(void);

extern "C" void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"5ht.mod\"");
    fprintf(stderr, " \"AXNODE.mod\"");
    fprintf(stderr, " \"FC.mod\"");
    fprintf(stderr, " \"MOTONEURON.mod\"");
    fprintf(stderr, " \"MOTONEURON_5HT.mod\"");
    fprintf(stderr, " \"NaP.mod\"");
    fprintf(stderr, " \"cac1.mod\"");
    fprintf(stderr, " \"caconc.mod\"");
    fprintf(stderr, " \"cal.mod\"");
    fprintf(stderr, " \"diffusion.mod\"");
    fprintf(stderr, " \"hill_eq.mod\"");
    fprintf(stderr, " \"kir.mod\"");
    fprintf(stderr, " \"kno.mod\"");
    fprintf(stderr, " \"nav14.mod\"");
    fprintf(stderr, " \"pregen.mod\"");
    fprintf(stderr, " \"slow5HT.mod\"");
    fprintf(stderr, " \"stdp.mod\"");
    fprintf(stderr, " \"stdp_mini.mod\"");
    fprintf(stderr, " \"stdwa_soft.mod\"");
    fprintf(stderr, " \"xm.mod\"");
    fprintf(stderr, "\n");
  }
  _5ht_reg();
  _AXNODE_reg();
  _FC_reg();
  _MOTONEURON_reg();
  _MOTONEURON_5HT_reg();
  _NaP_reg();
  _cac1_reg();
  _caconc_reg();
  _cal_reg();
  _diffusion_reg();
  _hill_eq_reg();
  _kir_reg();
  _kno_reg();
  _nav14_reg();
  _pregen_reg();
  _slow5HT_reg();
  _stdp_reg();
  _stdp_mini_reg();
  _stdwa_soft_reg();
  _xm_reg();
}
