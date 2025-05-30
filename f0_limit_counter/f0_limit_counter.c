//      ----------------------------------------------------------
//      -- fredrik olofsson 040226                              --
//      -- ported to pd 060511                                  --
//      -- converted from abstraction with the same name        --
//      -- replaced 2nd dec-bang inlet with dec method          --
//      -- bugfix 240318 set minimum                            --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#define LONG_MIN -2147483647
#define LONG_MAX 2147483647

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_int valCount;
    t_float valMin;
    t_float valMax;
    t_outlet *out;
    t_outlet *out2;
    t_outlet *out3;
} t_f0ext;

void *f0ext_new(t_symbol *s, int argc, t_atom *argv) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valMin);
    floatinlet_new(&x->ob, &x->valMax);
    x->valCount = 0;
    x->valMin = LONG_MIN;
    x->valMax = LONG_MAX;
    switch (argc) {
        case 2:
            x->valMax = atom_getfloat(argv + 1);
        case 1:
            x->valMin = atom_getfloat(argv);
    }
    x->out = outlet_new(&x->ob, gensym("float"));
    x->out2 = outlet_new(&x->ob, gensym("bang"));
    x->out3 = outlet_new(&x->ob, gensym("bang"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    x->valCount = fmin(fmax(x->valCount, x->valMin), x->valMax);
    if (x->valCount < x->valMax) {
        x->valCount++;
    }
    if (x->valCount == x->valMax) {
        outlet_bang(x->out3);
    }
    outlet_float(x->out, x->valCount);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    f0ext_bang(x);
}
void f0ext_inc(t_f0ext *x) {
    f0ext_bang(x);
}
void f0ext_dec(t_f0ext *x) {
    x->valCount = fmin(fmax(x->valCount, x->valMin), x->valMax);
    if (x->valCount > x->valMin) {
        x->valCount--;
    }
    if (x->valCount == x->valMin) {
        outlet_bang(x->out2);
    }
    outlet_float(x->out, x->valCount);
}
void f0ext_set(t_f0ext *x, t_floatarg val) {
    if (val < x->valMin) {
        val = x->valMin;
    } else if (val > x->valMax) {
        val = x->valMax;
    }
    x->valCount = val;
}
void f0_limit_counter_setup(void) {
    f0ext_class = class_new(gensym("f0_limit_counter"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_GIMME, 0);
    class_addfloat(f0ext_class, f0ext_float);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addmethod(f0ext_class, (t_method)f0ext_inc, gensym("inc"), 0);
    class_addmethod(f0ext_class, (t_method)f0ext_dec, gensym("dec"), 0);
    class_addmethod(f0ext_class, (t_method)f0ext_set, gensym("set"), A_DEFFLOAT, 0);
    post("f0_limit_counter v3.0.2; distributed under GNU GPL license");
}
