#ifndef __ALLOC_H_
#define __ALLOC_H_

typedef void (*init_struct)(void);

void *create_pool(size_t item, unsigned int blocksize);
void init_pool((*

