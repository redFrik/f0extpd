//      ----------------------------------------------------------
//      -- fredrik olofsson 010608 (rev.011004)                 --
//      -- ported to pd 060512                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valRight;
    t_float valOut;
    t_outlet *out;
} t_f0ext;

void theFunction(t_f0ext *x, t_float value);

void *f0ext_new(t_floatarg value) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valRight);
    if (value > 0) {
        x->valRight = value;
    } else {
        x->valRight = 1.0;
    }
    x->out = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    outlet_float(x->out, x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg value) {
    theFunction(x, value);
}
void theFunction(t_f0ext *x, t_float value) {
    x->valOut = fmod(value, x->valRight);
    f0ext_bang(x);
}
void f0_fmod_setup(void) {
    f0ext_class = class_new(gensym("f0_fmod"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_DEFFLOAT, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    post("f0_fmod v3.0.0; distributed under GNU GPL license");
}
