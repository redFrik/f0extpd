//      ----------------------------------------------------------
//      -- fredrik olofsson 040301                              --
//      -- ported to pd 060510                                  --
//      -- converted from abstraction with the same name        --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valLeft;
    t_float valMiddle;
    t_float valRight;
    t_float min;
    t_float max;
    short flag;
    t_outlet *out;
    t_outlet *out2;
} t_f0ext;

void f0ext_theFunction(t_f0ext *x);

void *f0ext_new(t_symbol *s, int argc, t_atom *argv) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valMiddle);
    floatinlet_new(&x->ob, &x->valRight);
    x->valLeft = 0.0;
    x->valMiddle = 0.0;
    x->valRight = 1.0;
    x->min = 0.0;
    x->max = 0.0;
    x->flag = 0;
    switch (argc) {
        case 2:
            x->valRight = atom_getfloat(argv + 1);
        case 1:
            x->valMiddle = atom_getfloat(argv);
    }
    x->out = outlet_new(&x->ob, gensym("float"));
    x->out2 = outlet_new(&x->ob, gensym("list"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    x->min = 0.0;
    x->max = 0.0;
    x->flag = 0;
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valLeft = val;
    f0ext_theFunction(x);
}
void f0ext_factor(t_f0ext *x) {
    float rangeIn, rangeOut;
    t_atom daList[3];
    rangeIn = fabs(x->max - x->min);
    rangeOut = fabs(x->valRight - x->valMiddle);
    SETFLOAT(daList, 0);  //index for routing
    if (rangeIn == 0.0) {
        SETFLOAT(daList + 1, 0.0);
        SETFLOAT(daList + 2, rangeOut);
    } else if (rangeOut == 0.0) {
        SETFLOAT(daList + 1, rangeIn);
        SETFLOAT(daList + 2, 0.0);
    } else if (rangeIn <= rangeOut) {
        SETFLOAT(daList + 1, 1.0);
        SETFLOAT(daList + 2, 1.0 / (rangeIn / rangeOut));
    } else {
        SETFLOAT(daList + 1, 1.0 / (rangeOut / rangeIn));
        SETFLOAT(daList + 2, 1.0);
    }
    outlet_list(x->out2, gensym("list"), 3, daList);
}
void f0ext_range(t_f0ext *x) {
    t_atom daList[3];
    SETFLOAT(daList, 1);  //index for routing
    if (x->min <= x->max) {
        SETFLOAT(daList + 1, x->min);
        SETFLOAT(daList + 2, x->max);
    } else {
        SETFLOAT(daList + 1, x->max);
        SETFLOAT(daList + 2, x->min);
    }
    outlet_list(x->out2, gensym("list"), 3, daList);
}
void f0ext_set(t_f0ext *x, t_floatarg min, t_floatarg max) {
    x->min = min;
    x->max = max;
}
void f0ext_theFunction(t_f0ext *x) {
    float v, o, rangeIn, rangeOut;
    v = x->valLeft;
    if ((x->flag == 0) && (x->min == x->max)) {
        x->flag = 1;
        x->min = v;
        x->max = v;
    }
    if (v < x->min) {
        x->min = v;
    }
    if (v > x->max) {
        x->max = v;
    }
    rangeIn = fabs(x->max - x->min);
    rangeOut = fabs(x->valRight - x->valMiddle);
    if (rangeIn == 0.0) {
        if (x->valMiddle <= x->valRight) {
            o = x->valMiddle;
        } else {
            o = x->valRight;
        }
    } else if (x->valMiddle <= x->valRight) {
        o = fabs((v - x->min) / rangeIn * rangeOut) + x->valMiddle;
    } else {
        o = fabs((v - x->max) / rangeIn * rangeOut) + x->valRight;
    }
    outlet_float(x->out, o);
}
void f0_auto_scale_setup(void) {
    f0ext_class = class_new(gensym("f0_auto_scale"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_GIMME, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addmethod(f0ext_class, (t_method)f0ext_factor, gensym("factor"), 0);
    class_addmethod(f0ext_class, (t_method)f0ext_range, gensym("range"), 0);
    class_addmethod(f0ext_class, (t_method)f0ext_set, gensym("set"), A_DEFFLOAT, A_DEFFLOAT, 0);
    post("f0_auto_scale v3.0.0; distributed under GNU GPL license");
}
