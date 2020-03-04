#include <malloc.h>
#include <stdio.h>

#define PI 3.14159
typedef double (*VirtualMethodPointer) (void*);
typedef VirtualMethodPointer *VTableType;

struct Shape{
    VTableType vptr;
};

double Shape_area(Shape * _this){
    return 0.0;
}

void Shape_draw(Shape * _this){
}

VirtualMethodPointer Shape_Vtbl[] = {
        (VirtualMethodPointer)Shape_area,
        (VirtualMethodPointer)Shape_draw
};


Shape * Shape_ctor(Shape * _this){
    _this->vptr = Shape_Vtbl;
    return _this;
}

struct Circle{
    VTableType Vptr;
    double radius;
};

double Circle_area(Circle *_this){
        return (double)(PI * _this->radius * _this->radius);
}
void Circle_draw(Circle * _this){
        double i = 0, j = 0;
        for(i = -_this->radius; i <= _this->radius; i++){
                for(j = -_this->radius; j <= _this->radius; j++){
                        double d = (i*2/_this->radius)*(i*2/_this->radius)+
                                        (j/_this->radius)*(j/_this->radius);
                        if(d>0.95 && d<1.08){
                                printf("*");
                        }else{
                                printf(" ");
                        }
                }
                printf("\n");
        }
}

VirtualMethodPointer Circle_Vtbl[] = {
        (VirtualMethodPointer)Circle_area,
        (VirtualMethodPointer)Circle_draw
};

Circle * Circle_ctor(Circle * _this,  double newRadius){
    Shape_ctor((Shape*)_this);
    _this->Vptr = Circle_Vtbl;
    _this->radius = newRadius;
    return _this;
}

struct Triangle{
    VTableType Vptr;
    int base;
    int height;
};

double Triangle_area(Triangle * _this){
         return (double)(_this->base * _this->height /2);
}

void Triangle_draw(Triangle * _this){
        int i = 0, j = 0;
        for(i = 0; i < _this->height; i++){
                for(j = 0; j <= i; j++){
                        if(i == _this->height - 1){
                                printf("* ");
                        }else if (j == 0 || j == i){
                                printf("* ");
                        }else{
                                printf("  ");
                        }
                }
                printf("\n");
        }
}

VirtualMethodPointer Triangle_Vtbl[] = {
        (VirtualMethodPointer)Triangle_area,
        (VirtualMethodPointer)Triangle_draw
};

Triangle * Triangle_ctor(Triangle * _this, int height, int base){
    Shape_ctor((Shape*)_this);
    _this->Vptr = Triangle_Vtbl;
    _this->base = base;
    _this->height = height;
    return _this;
}

struct Square{
    VTableType Vptr;
    int length;
};

double Square_area(Square * _this){
        return (double)(_this->length * _this->length);
}

void Square_draw(Square * _this){
        int i = 0;
        for(i = 0; i < _this->length; i++){
                printf("* ");
        }
	printf("\n");
        int j = 0;
        for(i = 0; i < _this->length - 2; i++){
                printf("*");
                for(j = 0; j < _this->length - 2; j++){
                        printf("  ");
                }
                printf(" *");
        	printf("\n");
	}

        for(i = 0; i < _this->length; i++){
                printf("* ");
        }
	printf("\n");
}

VirtualMethodPointer Square_Vtbl[]={
        (VirtualMethodPointer)Square_area,
        (VirtualMethodPointer)Square_draw
};
Square * Square_ctor(Square * _this, int newLength){
    Shape_ctor((Shape *)_this);
    _this->length = newLength;
    _this->Vptr = Square_Vtbl;
    return _this;
}

struct Rectangle{
    VTableType Vptr;
    int width;
    int length;
};

double Rectangle_area(Rectangle * _this){
    return _this->width * _this->length;
}

void Rectangle_draw(Rectangle * _this){
    int i = 0, j = 0;
    for(i = 0; i < _this->length; i++){
                printf("* ");
    }
	printf("\n");
    for(i = 0; i < _this->width - 2; i++){
        printf("* ");
        for(j = 0;  j< _this->length - 2; j++){
            printf("  ");
        }
        printf("*");
        printf("\n");
    }
    for(i = 0; i < _this->length; i++){
        printf("* ");
    }
	printf("\n");
}

VirtualMethodPointer Rectangle_Vtbl[]={
        (VirtualMethodPointer)Rectangle_area,
        (VirtualMethodPointer)Rectangle_draw
};

Rectangle * Rectangle_ctor(Rectangle * _this,  int length, int width){
    Shape_ctor((Shape *)_this);
    _this->Vptr = Rectangle_Vtbl;
    _this->width = width;
    _this->length = length;
    return _this;
}

int main(){
    char ft[]="FirstTriangle";
    char st[]="SecondTriangle";
    char fc[]="FirstCircle";
    char sc[]="SecondCircle";
    char fs[]="FirstSquare";
    char ss[]="SecondSqaure";
    char fr[]="FirstRectangle";
    char sr[]="SecondRectangle";
    Shape *sh[] = {
        (Shape*)Triangle_ctor((Triangle*)malloc(sizeof(Triangle)), 5, 5),
        (Shape*)Triangle_ctor((Triangle*)malloc(sizeof(Triangle)), 4, 3),
        (Shape*)Circle_ctor((Circle*)malloc(sizeof(Circle)), 5),
        (Shape*)Circle_ctor((Circle*)malloc(sizeof(Circle)), 10),
        (Shape*)Square_ctor((Square*)malloc(sizeof(Square)), 5),
        (Shape*)Square_ctor((Square*)malloc(sizeof(Square)), 10),
        (Shape*)Rectangle_ctor((Rectangle*)malloc(sizeof(Rectangle)), 4, 8),
        (Shape*)Rectangle_ctor((Rectangle*)malloc(sizeof(Rectangle)), 8, 4)
    };
   int i = 0;
    for(i = 0; i < sizeof(sh)/sizeof(*sh); i++){
        printf("Area: %lf\n", (sh[i]->vptr[0])(sh[i]));
        printf("\n", (sh[i]->vptr[1])(sh[i]));
    }

    for(i = 0; i < sizeof(sh)/sizeof(*sh); i++){
        free(sh[i]);
    }

    return 0.0;
}

//        (Shape*)Circle_ctor((Circle*)malloc(sizeof(Circle)),fc, 5),
//        (Shape*)Circle_ctor((Circle*)malloc(sizeof(Circle)), sc, 10),
//        (Shape*)Square_ctor((Square*)malloc(sizeof(Square)),fs, 5),
//        (Shape*)Square_ctor((Square*)malloc(sizeof(Square)),ss, 10),
//        (Shape*)Rectangle_ctor((Rectangle*)malloc(sizeof(Rectangle)),fr, 4, 8),
//        (Shape*)Rectangle_ctor((Rectangle*)malloc(sizeof(Rectangle)),sr, 8, 4)
