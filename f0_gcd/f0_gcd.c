//      ----------------------------------------------------------
//      -- fredrik olofsson 010505 (rev.011004                  --
//      -- divide by 0 bugfix 060507 (051228)                   --
//      -- ported to pd 060511                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    long valLeft;
    long valRight;
    long valOut;
    t_outlet *out;
} t_f0ext;

long greatestCommonDivisor(long a, long b);

void *f0ext_new(void) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    inlet_new(&x->ob, &x->ob.ob_pd, gensym("float"), gensym("ft1"));
    x->valLeft = 0;
    x->valRight = 0;
    x->out = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    outlet_float(x->out, (t_float)x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valLeft = (long)val;
    x->valOut = greatestCommonDivisor(x->valLeft, x->valRight);
    f0ext_bang(x);
}
void f0ext_ft1(t_f0ext *x, t_floatarg val) {
    x->valRight = (long)val;
}
void f0ext_list(t_f0ext *x, t_symbol *s, int argc, t_atom *argv) {
    long a = 0, b = 0;
    long i;
    a = atom_getfloat(argv);
    for (i = 1; i < argc; i++) {
        b = atom_getfloat(argv + i);
        a = greatestCommonDivisor(a, b);
    }
    x->valOut = a;
    f0ext_bang(x);
}
long greatestCommonDivisor(long a, long b) {
    if (b == 0) {
        return 0;
    }
    if ((a % b) != 0) {
        return greatestCommonDivisor(b, a % b);
    } else {
        return fabs(b);
    }
}
void f0_gcd_setup(void) {
    f0ext_class = class_new(gensym("f0_gcd"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addmethod(f0ext_class, (t_method)f0ext_ft1, gensym("ft1"), A_DEFFLOAT, 0);
    class_addlist(f0ext_class, f0ext_list);
    post("f0_gcd v3.0.0; distributed under GNU GPL license");
}
