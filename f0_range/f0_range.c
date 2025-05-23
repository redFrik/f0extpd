//      ----------------------------------------------------------
//      -- fredrik olofsson 040329 (rev.060511)                 --
//      -- ported to pd 060511                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#define LONG_MIN -2147483647
#define LONG_MAX 2147483647

#include <m_pd.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valLeft;
    t_float min;
    t_float max;
    t_float setMin;
    t_float setMax;
    short setFlag;
    t_outlet *out;
    t_outlet *out2;
    t_outlet *out3;
} t_f0ext;

void f0ext_theFunction(t_f0ext *x);

void *f0ext_new(t_symbol *s, int argc, t_atom *argv) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    switch (argc) {
        case 0:
            x->setMin = LONG_MAX;
            x->setMax = LONG_MIN;
            break;
        case 1:
            x->setMin = atom_getfloat(argv);
            x->setMax = LONG_MIN;
            break;
        default:
            x->setMin = atom_getfloat(argv);
            x->setMax = atom_getfloat(argv + 1);
    }
    x->min = x->setMin;
    x->max = x->setMax;
    x->setFlag = argc;
    x->out = outlet_new(&x->ob, gensym("float"));
    x->out2 = outlet_new(&x->ob, gensym("float"));
    x->out3 = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    if (x->setFlag == 0) {
        x->min = LONG_MAX;
        x->max = LONG_MIN;
    } else if (x->setFlag == 1) {
        x->min = x->setMin;
        x->max = LONG_MIN;
    } else {
        x->min = x->setMin;
        x->max = x->setMax;
    }
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valLeft = val;
    f0ext_theFunction(x);
}
void f0ext_set(t_f0ext *x, t_floatarg val1, t_floatarg val2) {
    if (val1 < val2) {
        x->min = val1;
        x->max = val2;
        x->setMin = val1;
        x->setMax = val2;
    } else {
        x->min = val2;
        x->max = val1;
        x->setMin = val2;
        x->setMax = val1;
    }
    x->setFlag = 2;
}
void f0ext_theFunction(t_f0ext *x) {
    if (x->valLeft > x->max) {
        x->max = x->valLeft;
    }
    if (x->valLeft < x->min) {
        x->min = x->valLeft;
    }
    outlet_float(x->out3, x->max);
    outlet_float(x->out2, (x->max - x->min) / 2.0 + x->min);
    outlet_float(x->out, x->min);
}
void f0_range_setup(void) {
    f0ext_class = class_new(gensym("f0_range"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_GIMME, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addmethod(f0ext_class, (t_method)f0ext_set, gensym("set"), A_DEFFLOAT, A_DEFFLOAT, 0);
    post("f0_range v3.0.0; distributed under GNU GPL license");
}
