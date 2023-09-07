#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _5ht_reg(void);
extern void _AXNODE_reg(void);
extern void _cac1_reg(void);
extern void _caconc_reg(void);
extern void _cal_reg(void);
extern void _diffusion_reg(void);
extern void _FC_reg(void);
extern void _hill_eq_reg(void);
extern void _iagen_reg(void);
extern void _kir_reg(void);
extern void _kno_reg(void);
extern void _MOTONEURON_5HT_reg(void);
extern void _MOTONEURON_reg(void);
extern void _muscle_reg(void);
extern void _nav14_reg(void);
extern void _pregen_reg(void);
extern void _slow5HT_reg(void);
extern void _stdwa_soft_reg(void);
extern void _xm_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"./mod_files/5ht.mod\"");
    fprintf(stderr, " \"./mod_files/AXNODE.mod\"");
    fprintf(stderr, " \"./mod_files/cac1.mod\"");
    fprintf(stderr, " \"./mod_files/caconc.mod\"");
    fprintf(stderr, " \"./mod_files/cal.mod\"");
    fprintf(stderr, " \"./mod_files/diffusion.mod\"");
    fprintf(stderr, " \"./mod_files/FC.mod\"");
    fprintf(stderr, " \"./mod_files/hill_eq.mod\"");
    fprintf(stderr, " \"./mod_files/iagen.mod\"");
    fprintf(stderr, " \"./mod_files/kir.mod\"");
    fprintf(stderr, " \"./mod_files/kno.mod\"");
    fprintf(stderr, " \"./mod_files/MOTONEURON_5HT.mod\"");
    fprintf(stderr, " \"./mod_files/MOTONEURON.mod\"");
    fprintf(stderr, " \"./mod_files/muscle.mod\"");
    fprintf(stderr, " \"./mod_files/nav14.mod\"");
    fprintf(stderr, " \"./mod_files/pregen.mod\"");
    fprintf(stderr, " \"./mod_files/slow5HT.mod\"");
    fprintf(stderr, " \"./mod_files/stdwa_soft.mod\"");
    fprintf(stderr, " \"./mod_files/xm.mod\"");
    fprintf(stderr, "\n");
  }
  _5ht_reg();
  _AXNODE_reg();
  _cac1_reg();
  _caconc_reg();
  _cal_reg();
  _diffusion_reg();
  _FC_reg();
  _hill_eq_reg();
  _iagen_reg();
  _kir_reg();
  _kno_reg();
  _MOTONEURON_5HT_reg();
  _MOTONEURON_reg();
  _muscle_reg();
  _nav14_reg();
  _pregen_reg();
  _slow5HT_reg();
  _stdwa_soft_reg();
  _xm_reg();
}

#if defined(__cplusplus)
}
#endif
