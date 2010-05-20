/*
 * malloc.c: safe wrappers around malloc, realloc, free, strdup
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"

/*
 * smalloc should guarantee to return a useful pointer - Halibut
 * can do nothing except die when it's out of memory anyway.
 */
void *smalloc(size_t size) {
    void *p;
    p = malloc(size);
    if (!p) {
        fprintf(stderr,"out of memory");
        abort();
    }
    return p;
}

/*
 * sfree should guaranteeably deal gracefully with freeing NULL
 */
void sfree(void *p) {
    if (p) {
        free(p);
    }
}

/*
 * srealloc should guaranteeably be able to realloc NULL
 */
void *srealloc(void *p, size_t size) {
    void *q;
    if (p) {
        q = realloc(p, size);
    } else {
        q = malloc(size);
    }
    if (!q) {
        fprintf(stderr,"out of memory");
        abort();
    }
    return q;
}

/*
 * dupstr is like strdup, but with the never-return-NULL property
 * of smalloc (and also reliably defined in all environments :-)
 */
char *dupstr(const char *s) {
    char *r = smalloc(1+strlen(s));
    strcpy(r,s);
    return r;
}
