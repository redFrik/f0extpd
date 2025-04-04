//      ----------------------------------------------------------
//      -- fredrik olofsson 010522 (rev.011004)                 --
//      -- ported to pd 060511                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_int size;
    t_float x1;
    t_float y1;
    t_float z1;
    t_float x2;
    t_float y2;
    t_float z2;
    t_float valOut;
    t_outlet *out;
} t_f0ext;

void beraknaAvstand(t_f0ext *x);

void *f0ext_new(t_floatarg val) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    x->x1 = 0.0;
    x->y1 = 0.0;
    x->z1 = 0.0;
    x->x2 = 0.0;
    x->y2 = 0.0;
    x->z2 = 0.0;
    x->valOut = 0.0;
    x->out = outlet_new(&x->ob, gensym("float"));
    if ((t_int)val == 2) {
        floatinlet_new(&x->ob, &x->y1);
    } else if ((t_int)val == 3) {
        floatinlet_new(&x->ob, &x->y1);
        floatinlet_new(&x->ob, &x->z1);
    }
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    beraknaAvstand(x);
    outlet_float(x->out, x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->x1 = val;
    f0ext_bang(x);
}
void f0ext_list(t_f0ext *x, t_symbol *s, int argc, t_atom *argv) {
    if (argc > 3) {
        post("f0_distance warning: max 3 dimensions");
    }
    switch (argc) {
        case 3:
            x->z1 = atom_getfloat(argv + 2);
        case 2:
            x->y1 = atom_getfloat(argv + 1);
        case 1:
            x->x1 = atom_getfloat(argv);
    }
    f0ext_bang(x);
}
void f0_distance_setup(void) {
    f0ext_class = class_new(gensym("f0_distance"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_DEFFLOAT, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addlist(f0ext_class, f0ext_list);
    post("f0_distance v3.0.0; distributed under GNU GPL license");
}
void beraknaAvstand(t_f0ext *x) {
    float xx, yy, zz;
    xx = x->x1 - x->x2;
    yy = x->y1 - x->y2;
    zz = x->z1 - x->z2;
    x->valOut = fabs(sqrt(pow(xx, 2) + pow(yy, 2) + pow(zz, 2)));
    x->x2 = x->x1;
    x->y2 = x->y1;
    x->z2 = x->z1;
}
