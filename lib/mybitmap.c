#include "mybitmap.h"

#include <lib.h>

mybitmap_t *mybitmap_create(int length) {
    mybitmap_t *bitmap =(mybitmap_t*) kmalloc(sizeof(mybitmap_t));
    bitmap->length = length;
    if (length % 8 != 0) length += 8;
    bitmap->blocks =(char*) kmalloc(length / 8);
    return bitmap;
}

void mybitmap_destroy(mybitmap_t *bitmap) {
    kfree(bitmap->blocks);
    kfree(bitmap);
}

int mybitmap_set(mybitmap_t *bitmap, int index, int value) {
    if (index >= 0 && index < bitmap->length) {
        int block = index / 8;
        int blockindex = index % 8;
        if (value == 0) {
            bitmap->blocks[block] = bitmap->blocks[block] & (~(1 << (7 - blockindex)));
            return 0;

        } else if (value == 1) {
            bitmap->blocks[block] = (bitmap->blocks[block] | (1 << (7 - blockindex)));
            return 0;
        }
    }
    return 1;
}
int mybitmap_get(mybitmap_t *bitmap, int index) {
    if (index >= 0 && index < bitmap->length) {
        int block = index / 8;
        int blockindex = index % 8;
        return (bitmap->blocks[block] >> (7 - blockindex)) & 1;
    } else {
        return -1;
    }
}

void mybitmap_setallzero(mybitmap_t *bitmap) {
    int blocks_num=bitmap->length/8;
    if(bitmap->length%8 != 0) blocks_num++;
    for (int i = 0; i < blocks_num; i++) {
        bitmap->blocks[i]=0;
    }
}
