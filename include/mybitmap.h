#ifndef MYBITMAP_H
#define MYBITMAP_H

typedef struct{
    char *blocks;
    int length;
}mybitmap_t;

mybitmap_t* mybitmap_create(int length);
void mybitmap_destroy(mybitmap_t *bitmap);
int mybitmap_set(mybitmap_t *bitmap,int index, int value);
int mybitmap_get(mybitmap_t *bitmap,int index);
void mybitmap_setallzero(mybitmap_t *bitmap);

#endif
