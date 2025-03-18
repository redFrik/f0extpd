//      ----------------------------------------------------------
//      -- fredrik olofsson 040226                              --
//      -- ported to pd 060510                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valLeft;
    t_float valRight;
    t_float valOut;
    t_outlet *out;
} t_f0ext;

void f0ext_theFunction(t_f0ext *x);

void *f0ext_new(t_floatarg val) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valRight);
    x->valLeft = 0.0;
    x->valOut = 0.0;
    x->out = outlet_new(&x->ob, gensym("float"));
    if (val != 0) {
        x->valRight = val;
    } else {
        x->valRight = 1.0;
    }
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    outlet_float(x->out, x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valLeft = val;
    f0ext_theFunction(x);
}
void f0ext_theFunction(t_f0ext *x) {
    if (x->valRight == 0.0) {
        x->valOut = x->valLeft;
    } else {
        x->valOut = round(x->valLeft / x->valRight) * x->valRight;
    }
    f0ext_bang(x);
}
void f0_round_setup(void) {
    f0ext_class = class_new(gensym("f0_round"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_DEFFLOAT, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    post("f0_round v3.0.0; distributed under GNU GPL license");
}
