//      ----------------------------------------------------------
//      -- fredrik olofsson 020115                              --
//      -- fix for output on right input 060507                 --
//      -- ported to pd 060511                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valLeft;
    t_float valMiddle;
    t_float valRight;
    t_float valOutLeft;
    t_float valOutRight;
    t_outlet *outLeft;
    t_outlet *outRight;
} t_f0ext;

void f0ext_theFunction(t_f0ext *x);

void *f0ext_new(t_symbol *s, int argc, t_atom *argv) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valMiddle);
    floatinlet_new(&x->ob, &x->valRight);
    x->valLeft = 0.0;
    x->valOutLeft = 0.0;
    x->valOutRight = 0.0;
    x->valMiddle = 0.15;
    x->valRight = 0.3;
    switch (argc) {
        case 2:
            x->valRight = atom_getfloat(argv + 1);
        case 1:
            x->valMiddle = atom_getfloat(argv);
    }
    x->outLeft = outlet_new(&x->ob, gensym("float"));
    x->outRight = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    f0ext_theFunction(x);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valLeft = val;
    f0ext_theFunction(x);
}
void f0ext_set(t_f0ext *x, t_floatarg val) {
    x->valOutLeft = val;
}
void f0ext_theFunction(t_f0ext *x) {
    t_float St0, St1, Bt0, Bt1, a, g, Yt0;
    a = x->valMiddle;
    g = x->valRight;
    Yt0 = x->valLeft;
    St1 = x->valOutLeft;
    Bt1 = x->valOutRight;
    St0 = a * Yt0 + (1.0 - a) * (St1 + Bt1);  //DES - Double Exponential Smoothing
    Bt0 = g * (St0 - St1) + (1.0 - g) * Bt1;
    x->valOutLeft = St0;
    x->valOutRight = Bt0;
    outlet_float(x->outRight, x->valOutRight);
    outlet_float(x->outLeft, x->valOutLeft);
}
void f0_smooth2_setup(void) {
    f0ext_class = class_new(gensym("f0_smooth2"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_GIMME, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addmethod(f0ext_class, (t_method)f0ext_set, gensym("set"), A_DEFFLOAT, 0);
    post("f0_smooth2 v3.0.0; distributed under GNU GPL license");
}
