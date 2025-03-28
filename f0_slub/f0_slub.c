//      ----------------------------------------------------------
//      -- fredrik olofsson 040331                              --
//      -- ported to pd 060511                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#include <m_pd.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    t_float valRight;
    t_float dummy;
} t_f0ext;

void f0ext_theFunction(t_f0ext *x);

void *f0ext_new(t_floatarg val) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    floatinlet_new(&x->ob, &x->valRight);
    if (val == 0.0) {
        x->valRight = 7.0;
    } else {
        x->valRight = val;
    }
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    f0ext_theFunction(x);
}
void f0ext_float(t_f0ext *x, t_floatarg val) {
    x->valRight = val;
    f0ext_theFunction(x);
}
void f0ext_theFunction(t_f0ext *x) {
    long
    i
    ,
    j
    ,
    k
    ,
    l
    ,
    m
    ;
    m
    =
    (long)round
    (
     pow
     (
      2
      ,
      x->valRight
      )
     )
    ;
    for
        (
         i
         =
         0
         ;
         i
         <
         m
         ;
         i++
         )
    {
        for
            (j=
             0
             ;
             j
             <
             m
             ;
             j++
             )
        {        for
            (
             k
             =0
             ;
             k<
             m
             ;
             k++
             )
        {
            for
                
                (
                 l
                 =
                 0;
                 l
                 <
                 m
                 ;
                 l++
                 )
            {
                x->dummy += fmod(
                     l                ,
                     3.1415
                     )
                ;
            }
        }}
    }
}
void f0_slub_setup(void) {
    f0ext_class = class_new(gensym("f0_slub"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, A_DEFFLOAT, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    post("f0_slub v3.0.0; distributed under GNU GPL license");
}
