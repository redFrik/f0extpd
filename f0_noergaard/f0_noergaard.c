//      ----------------------------------------------------------
//      -- fredrik olofsson 010614 (rev.011004)                 --
//      -- ported to pd 060511                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    long valOut;
    t_outlet *out;
} t_f0ext;

long f0ext_theFunction(long index);
long count_bits(long n);

void *f0ext_new(void) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    x->valOut = 0;
    x->out = outlet_new(&x->ob, gensym("float"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    outlet_float(x->out, x->valOut);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    if (val >= 0) {
        x->valOut = f0ext_theFunction((long)val);
        f0ext_bang(x);
    } else {
        post("f0_noergaard warning: only possitive indexes");
    }
}
long f0ext_theFunction(long index) {
    long i, len, res = 0;
    len = count_bits(index);
    for (i = len - 1; i >= 0; i--) {
        if ((index >> i) & 01) {
            res++;
        } else {
            if (res >= 0) {
                res= 0 - res;
            } else {
                res = fabs(res);
            }
        }
    }
    return res;
}
long count_bits(long n) {
    long i = 0;
    for(; n != 0; n = n >> 1) {
        i++;
    }
    return i;
}
void f0_noergaard_setup(void) {
    f0ext_class = class_new(gensym("f0_noergaard"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    post("f0_noergaard v3.0.0; distributed under GNU GPL license");
}
