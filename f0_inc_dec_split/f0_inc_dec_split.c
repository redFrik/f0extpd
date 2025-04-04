//      ----------------------------------------------------------
//      -- fredrik olofsson 040226                              --
//      -- ported to pd 060511                                  --
//      -- converted from abstraction with the same name        --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valLeft;
    t_float valLast;
    t_float valDefault;
    short flag;
    t_outlet *out;
    t_outlet *out2;
} t_f0ext;

void theFunction(t_f0ext *x);

void *f0ext_new(t_floatarg val) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valLast);
    x->valLeft = 0.0;
    x->flag = 0;
    if (val != 0) {
        x->valLast = val;
        x->valDefault = val;
    } else {
        x->valLast = 0.0;
        x->valDefault = 0.0;
    }
    x->out = outlet_new(&x->ob, gensym("float"));
    x->out2 = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    theFunction(x);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valLeft = val;
    theFunction(x);
}
void f0ext_reset(t_f0ext *x) {
    x->valLast = x->valDefault;
}
void theFunction(t_f0ext *x) {
    if (x->valLeft > x->valLast) {
        outlet_float(x->out, x->valLeft);
        x->flag = 0;
        x->valLast = x->valLeft;
    } else if (x->valLeft < x->valLast) {
        outlet_float(x->out2, x->valLeft);
        x->flag = 1;
        x->valLast = x->valLeft;
    } else {
        if (x->flag == 0) {
            outlet_float(x->out, x->valLeft);
        } else {
            outlet_float(x->out2, x->valLeft);
        }
    }
}
void f0_inc_dec_split_setup(void) {
    f0ext_class = class_new(gensym("f0_inc_dec_split"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_DEFFLOAT, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addmethod(f0ext_class, (t_method)f0ext_reset, gensym("reset"), 0);
    post("f0_inc_dec_split v3.0.0; distributed under GNU GPL license");
}
