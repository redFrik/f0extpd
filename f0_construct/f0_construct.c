//      ----------------------------------------------------------
//      -- fredrik olofsson 010502 (rev.011004)                 --
//      -- ported to pd 060510                                  --
//      -- updated 250318 using pd-lib-builder                  --
//      ----------------------------------------------------------

#define LONG_MIN -2147483647
#define LONG_MAX 2147483647

#include <m_pd.h>
#include <stdlib.h>
#include <math.h>

static t_class *f0ext_class;

typedef struct _f0ext {
    t_object ob;
    long valLeft;
    long mapping;
    long variant;
    long cols;
    long rows;
    long width;
    long height;
    t_float stepX;
    t_float stepY;
    long movementX;
    long movementY;
    long x;
    long y;
    long dx;
    long dy;
    t_outlet *out;
} t_f0ext;

void start(t_f0ext *x);
void drawFO(t_f0ext *x);
void variant1(t_f0ext *x);
void variant2(t_f0ext *x);
void variant3(t_f0ext *x);
void variant4(t_f0ext *x);
void variant5(t_f0ext *x);
void variant6(t_f0ext *x);
void mapping1(t_f0ext *x, int iCol, int jRow);
void mapping2(t_f0ext *x, int iCol, int jRow);
void mapping3(t_f0ext *x, int iCol, int jRow);
void mapping4(t_f0ext *x, int iCol, int jRow);
void mapping5(t_f0ext *x, int i, int iCol, int jRow);
void mapping6(t_f0ext *x, int i, int iCol, int jRow);
void mapping7(t_f0ext *x, int i, int iCol, int jRow);
void mapping8(t_f0ext *x, int j, int iCol, int jRow);
void mapping9(t_f0ext *x, int j, int iCol, int jRow);
void mapping10(t_f0ext *x, int j, int iCol, int jRow);
void mapping11(t_f0ext *x, int i, int j, int iCol, int jRow);
void mapping12(t_f0ext *x, int i, int j, int iCol, int jRow);
void mapping13(t_f0ext *x, int i, int j, int iCol, int jRow);
void mapping14(t_f0ext *x, int i, int j, int iCol, int jRow);
void mapping15(t_f0ext *x, int i, int j, int iCol, int jRow);
void mapping16(t_f0ext *x, int i, int j, int iCol, int jRow);
void slumpaRiktningX(t_f0ext *x);
void slumpaRiktningY(t_f0ext *x);
void slumpaRiktningXY(t_f0ext *x);
int mirrorX(t_f0ext *x, int ox);
int mirrorY(t_f0ext *x, int oy);
short myRandom();
void draw(t_f0ext *x, int ox, int oy);

void *f0ext_new(t_symbol *s, int argc, t_atom *argv) {
    t_f0ext *x = (t_f0ext *)pd_new(f0ext_class);
    x->valLeft = 2000;
    x->mapping = 1;
    x->variant = 1;
    x->cols = 3;
    x->rows = 2;
    x->width = 200;
    x->height = 200;
    x->stepX = 1.0;
    x->stepY = 1.0;
    x->movementX = 95;
    x->movementY = 93;
    x->x = 10;
    x->y = 10;
    x->dx = 1;
    x->dy = 1;
    x->out = outlet_new(&x->ob, gensym("list"));
    return (void *)x;
}
void f0ext_bang(t_f0ext *x) {
    start(x);
}
void f0ext_float(t_f0ext *x, t_floatarg iterations) {
    if (iterations >= 1) {
        x->valLeft = (long)iterations;
        f0ext_bang(x);
    }
}
void f0ext_mapping(t_f0ext *x, t_floatarg m) {
    if ((m >= 1) && (m <= 16)) {
        x->mapping = (long)m;
    }
}
void f0ext_variant(t_f0ext *x, t_floatarg v) {
    if ((v >= 1) && (v <= 6)) {
        x->variant = (long)v;
    }
}
void f0ext_cols(t_f0ext *x, t_floatarg col) {
    if (col >= 1) {
        x->cols = (long)col;
    }
}
void f0ext_rows(t_f0ext *x, t_floatarg row) {
    if (row >= 1) {
        x->rows = (long)row;
    }
}
void f0ext_width(t_f0ext *x, t_floatarg max_X) {
    if (max_X >= 1) {
        x->width = (long)max_X;
    }
}
void f0ext_height(t_f0ext *x, t_floatarg max_Y) {
    if (max_Y >= 1) {
        x->height = (long)max_Y;
    }
}
void f0ext_stepX(t_f0ext *x, t_float stepX) {
    x->stepX = stepX;
}
void f0ext_stepY(t_f0ext *x, t_float stepY) {
    x->stepY = stepY;
}
void f0ext_movementX(t_f0ext *x, t_floatarg movementX) {
    if ((movementX >= 0) && (movementX <= 100)) {
        x->movementX = (long)movementX;
    }
}
void f0ext_movementY(t_f0ext *x, t_floatarg movementY) {
    if ((movementY >= 0) && (movementY <= 100)) {
        x->movementY = (long)movementY;
    }
}
void start(t_f0ext *x) {
    //srand(((unsigned int)time(0))|1);
    for (int i = 0; i < x->valLeft; i++) {
        drawFO(x);
        x->x += x->dx * x->stepX;                   // flytta position x
        if (x->x < 1) {                             // om vänster kant
            x->dx = myRandom() % 2;                 //   vänd eller stå still i x-led
        } else if (x->x > (x->width / x->cols)) {   // om höger kant
            x->dx = 0 - myRandom() % 2;             //   vänd eller stå still i x-led
        }
        x->y += x->dy * x->stepY;                   // flytta position y
        if (x->y < 1) {                             // om övre kanten
            x->dy = myRandom() % 2;                 //   vänd eller stå still i y-led
        } else if (x->y > (x->height / x->rows)) {  // om nedre kanten
            x->dy = 0 - myRandom() % 2;             //   vänd eller stå still i y-led
        }
        switch (x->variant) {
            case 1:
                variant1(x);
                break;
            case 2:
                variant2(x);
                break;
            case 3:
                variant3(x);
                break;
            case 4:
                variant4(x);
                break;
            case 5:
                variant5(x);
                break;
            case 6:
                variant6(x);
                break;
        }
    }
}
void variant1(t_f0ext *x) {                                     // 1. slumpa riktningar individuellt
    if ((myRandom() % 100) >= x->movementX) {
        slumpaRiktningX(x);
    }
    if ((myRandom() % 100) >= x->movementY) {
        slumpaRiktningY(x);
    }
}
void variant2(t_f0ext *x) {                                     // 2. slumpa alltid riktningar tillsammans
    slumpaRiktningXY(x);
}
void variant3(t_f0ext *x) {                                     // 3. slumpa riktningar individuellt
    if ((myRandom() % 100) >= x->movementX) {
        if ((x->dx == 0) && (x->x >= 1)) {                      //      dra åt vänster
            x->dx = -1;
        } else {
            x->dx = 0;
        }
    }
    if ((myRandom() % 100) >= x->movementY) {
        if ((x->dy == 0) && (x->y >= 1)) {                      //      dra uppåt
            x->dy = -1;
        } else {
            x->dy = 0;
        }
    }
}
void variant4(t_f0ext *x) {                                     // 4. slumpa riktningar individuellt
    if ((myRandom() % 100) >= x->movementX) {
        if ((x->dx == 0) && (x->x >= 1)) {                      //      dra åt vänster
            x->dx = -1;
        } else {
            x->dx = 0;
        }
    }
    if ((myRandom() % 100) >= (x->movementY)) {
        if ((x->dy == 0) && (x->y <= (x->height / x->rows))) {  //      dra nedåt
            x->dy = 1;
        } else {
            x->dy = 0;
        }
    }
}
void variant5(t_f0ext *x) {                                     // 5. slumpa riktningar individuellt
    if ((myRandom() % 100) >= x->movementX) {
        if ((x->dx == 0) && (x->x <= (x->width / x->cols))) {   //      dra åt höger
            x->dx = 1;
        } else {
            x->dx = 0;
        }
    }
    if ((myRandom() % 100) >= x->movementY) {
        if ((x->dy == 0) && (x->y >= 1)) {                      //      dra uppåt
            x->dy = -1;
        } else {
            x->dy = 0;
        }
    }
}
void variant6(t_f0ext *x) {                                     // 6. slumpa riktningar individuellt
    if ((myRandom() % 100) >= x->movementX) {
        if ((x->dx == 0) && (x->x <= (x->width / x->cols))) {   //      dra åt höger
            x->dx = 1;
        } else {
            x->dx = 0;
        }
    }
    if ((myRandom() % 100) >= x->movementY) {
        if ((x->dy == 0) && (x->y <= (x->height / x->rows))) {  //      dra nedåt
            x->dy = 1;
        } else {
            x->dy = 0;
        }
    }
}

//----------------------------------------------------------------------------------------------
void slumpaRiktningXY(t_f0ext *x) {
    while ((x->dx == 0) && (x->dy == 0)) {                      // kolla att inte båda riktningar blir 0
        x->dx = myRandom() % 3 - 1;
        x->dy = myRandom() % 3 - 1;
    }
}
void slumpaRiktningX(t_f0ext *x) {
    x->dx = myRandom() % 3 - 1;
}
void slumpaRiktningY(t_f0ext *x) {
    x->dy = myRandom() % 3 - 1;
}

//----------------------------------------------------------------------------------------------
void drawFO(t_f0ext *x) {
    for(int i = 0; i < x->cols; i++) {
        for(int j = 0; j < x->rows; j++) {
            int iCol= (x->width / x->cols) * i;
            int jRow= (x->height / x->rows) * j;
            switch (x->mapping) {                               // kolla mapping
                case 1:
                    mapping1(x, iCol, jRow);
                    break;
                case 2:
                    mapping2(x, iCol, jRow);
                    break;
                case 3:
                    mapping3(x, iCol, jRow);
                    break;
                case 4:
                    mapping4(x, iCol, jRow);
                    break;
                case 5:
                    mapping5(x, i, iCol, jRow);
                    break;
                case 6:
                    mapping6(x, i, iCol, jRow);
                    break;
                case 7:
                    mapping7(x, i, iCol, jRow);
                    break;
                case 8:
                    mapping8(x, j, iCol, jRow);
                    break;
                case 9:
                    mapping9(x, j, iCol, jRow);
                    break;
                case 10:
                    mapping10(x, j, iCol, jRow);
                    break;
                case 11:
                    mapping11(x, i, j, iCol, jRow);
                    break;
                case 12:
                    mapping12(x, i, j, iCol, jRow);
                    break;
                case 13:
                    mapping13(x, i, j, iCol, jRow);
                    break;
                case 14:
                    mapping14(x, i, j, iCol, jRow);
                    break;
                case 15:
                    mapping15(x, i, j, iCol, jRow);
                    break;
                case 16:
                    mapping16(x, i, j, iCol, jRow);
                    break;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------
void mapping1(t_f0ext *x, int iCol, int jRow) {                 // no flip
    draw(x, x->x + iCol, x->y + jRow);
}
void mapping2(t_f0ext *x, int iCol, int jRow) {                 // flip all x
    draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
}
void mapping3(t_f0ext *x, int iCol, int jRow) {                 // flip all y
    draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
}
void mapping4(t_f0ext *x, int iCol, int jRow) {                 // flip all xy
    draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
}
//--
void mapping5(t_f0ext *x, int i, int iCol, int jRow) {          // flip odd col x
    if ((i % 2) == 1) {
        draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping6(t_f0ext *x, int i, int iCol, int jRow) {          // flip odd col y
    if ((i % 2) == 1) {
        draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping7(t_f0ext *x, int i, int iCol, int jRow) {          // flip odd col xy
    if ((i % 2) == 1) {
        draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
//--
void mapping8(t_f0ext *x, int j, int iCol, int jRow) {          // flip odd row x
    if ((j % 2) == 1) {
        draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping9(t_f0ext *x, int j, int iCol, int jRow) {          // flip odd row y
    if ((j % 2) == 1) {
        draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping10(t_f0ext *x, int j, int iCol, int jRow) {         // flip odd row xy
    if ((j % 2) == 1) {
        draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
//--
void mapping11(t_f0ext *x, int i, int j, int iCol, int jRow) {  // flip odd col & even row x, flip even col & odd row x
    if (((i % 2) == 1) && ((j % 2) == 0)) {
        draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
    } else if (((i % 2) == 0) && ((j % 2) == 1)) {
        draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping12(t_f0ext *x, int i, int j, int iCol, int jRow) {  // flip odd col & even row y, flip even col & odd row y
    if (((i % 2) == 1) && ((j % 2) == 0)) {
        draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
    } else if (((i % 2) == 0) && ((j % 2) == 1)) {
        draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping13(t_f0ext *x, int i, int j, int iCol, int jRow) {  // flip odd col & even row xy, flip even col & odd row xy
    if (((i % 2) == 1) && ((j % 2) == 0)) {
        draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
    } else if (((i % 2) == 0) && ((j % 2) == 1)) {
        draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
//--
void mapping14(t_f0ext *x, int i, int j, int iCol, int jRow) {  // flip even col & even row x, flip odd col & odd row x
    if (((i % 2) == 0) && ((j % 2) == 0)) {
        draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
    } else if (((i % 2) == 1) && ((j % 2) == 1)) {
        draw(x, mirrorX(x, x->x) + iCol, x->y + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping15(t_f0ext *x, int i, int j, int iCol, int jRow) {  // flip even col & even row y, flip odd col & odd row y
    if (((i % 2) == 0) && ((j % 2) == 0)) {
        draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
    } else if (((i % 2) == 1) && ((j % 2) == 1)) {
        draw(x, x->x + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
void mapping16(t_f0ext *x, int i, int j, int iCol, int jRow) {  // flip even col & even row xy, flip odd col & odd row xy
    if (((i % 2) == 0) && ((j % 2) == 0)) {
        draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
    } else if (((i % 2) == 1) && ((j % 2) == 1)) {
        draw(x, mirrorX(x, x->x) + iCol, mirrorY(x, x->y) + jRow);
    } else {
        draw(x, x->x + iCol, x->y + jRow);
    }
}
int mirrorX(t_f0ext *x, int ox) {
    return round(x->width / x->cols - ox);
}
int mirrorY(t_f0ext *x, int oy) {
    return round(x->height / x->rows - oy);
}
short myRandom() {
    return (short)rand();
}
void draw(t_f0ext *x, int ox, int oy) {
    t_atom lista[4];
    SETFLOAT(lista, (t_float)ox);
    SETFLOAT(lista + 1, (t_float)oy);
    SETFLOAT(lista + 2, (t_float)ox + 1);
    SETFLOAT(lista + 3, (t_float)oy + 1);
    outlet_list(x->out, gensym("list"), 4, lista);
}
void f0_construct_setup(void) {
    f0ext_class = class_new(gensym("f0_construct"), (t_newmethod)f0ext_new, 0, sizeof(t_f0ext), 0, 0);
    class_addbang(f0ext_class, (t_method)f0ext_bang);
    class_addfloat(f0ext_class, f0ext_float);
    class_addmethod(f0ext_class, (t_method)f0ext_mapping, gensym("mapping"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_variant, gensym("variant"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_cols, gensym("cols"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_rows, gensym("rows"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_width, gensym("width"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_height, gensym("height"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_stepX, gensym("stepX"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_stepY, gensym("stepY"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_movementX, gensym("movementX"), A_DEFFLOAT, 0);
    class_addmethod(f0ext_class, (t_method)f0ext_movementY, gensym("movementY"), A_DEFFLOAT, 0);
    post("f0_construct v3.0.0; distributed under GNU GPL license");
}
