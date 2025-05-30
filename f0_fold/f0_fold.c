//      ----------------------------------------------------------
//      -- fredrik olofsson 010502 (rev.011004)                 --
//      -- ported to pd 060511                                  --
//      -- converted from abstraction with the same name        --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valIn;
    t_float valMin;
    t_float valMax;
    t_float valOut;
    t_outlet *out;
} t_f0ext;

t_float foldFunction(t_floatarg in, t_floatarg min, t_floatarg max);

void *f0ext_new(t_symbol *s, int argc, t_atom *argv) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valMin);
    floatinlet_new(&x->ob, &x->valMax);
    x->valIn = 0.0;
    x->valMin = 0.0;
    x->valMax = 100.0;
    x->valOut = 0.0;
    switch (argc) {
        case 2:
            x->valMax = atom_getfloat(argv + 1);
        case 1:
            x->valMin = atom_getfloat(argv);
    }
    x->out = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    x->valOut = foldFunction(x->valIn, x->valMin, x->valMax);
    outlet_float(x->out, x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valIn = val;
    f0ext_bang(x);
}
t_float foldFunction(t_floatarg in, t_floatarg min, t_floatarg max) {
    t_float a, b, c;
    if (min > max) {
        a = min;
        min = max;
        max = a;
    }
    if (((in >= min) && (in <= max)) || (min == max)) {
        b = in;
    } else {
        c = fabs(max - min) * 2.0;
        if (in < min) {
            a = min - fmod(in - min, c);
            if ((a >= min) && (a <= max)) {
                b = a;
            } else {
                b = max + (max - a);
            }
        } else {
            a = max-fmod(in - max, c);
            if ((a > (min - c / 2.0)) && (a <= min)) {
                b = min + (min - a);
            } else {
                b = a;
            }
        }
    }
    return b;
}
void f0_fold_setup(void) {
    f0ext_class = class_new(gensym("f0_fold"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_GIMME, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    post("f0_fold v3.0.0; distributed under GNU GPL license");
}
