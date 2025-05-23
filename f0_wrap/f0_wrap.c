//      ----------------------------------------------------------
//      -- fredrik olofsson 060830                              --
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

t_float theFunction(t_float in, t_float min, t_float max);

void *f0ext_new(t_symbol *s, int ac, t_atom *av) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valMin);
    floatinlet_new(&x->ob, &x->valMax);
    x->valIn = 0.0;
    x->valMin = 0.0;
    x->valMax = 100.0;
    if (ac > 2) {
        post("warning: f0.wrap %d extra argument(s)", ac - 2);
    }
    switch (ac) {
        case 2:
            x->valMax = atom_getfloat(av + 1);
        case 1:
            x->valMin = atom_getfloat(av);
    }
    x->out = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    x->valOut = theFunction(x->valIn, x->valMin, x->valMax);
    outlet_float(x->out, x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valIn = val;
    f0ext_bang(x);
}
t_float theFunction(t_float in, t_float min, t_float max) {
    t_float a, b;
    if (min > max) {
        a = min;
        min = max;
        max = a;
    }
    if (((in >= min) && (in <= max)) || (min == max)) {
        a = in;
    } else {
        b = fabs(max - min);
        if (in < min) {
            a = max - fabs(fmod(in - min, b));
        } else {
            a = min + fabs(fmod(in - max, b));
        }
    }
    return a;
}
void f0_wrap_setup(void) {
    f0ext_class = class_new(gensym("f0_wrap"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_GIMME, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    post("f0.wrap v3.0.0; distributed under GNU GPL license");
}
