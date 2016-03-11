#pragma once

#ifdef __cpluplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#ifndef __unix__
#error "only linux supported"
#endif

#ifdef __cplusplus
extern "C" {
#endif

long svcInit(const char *svc_image, size_t off);
long svcClose();

enum {
  SVCINIT_NO_ERR = 0,

  SVCINIT_IMAGE_OPEN_ERR = -1,
  SVCINIT_IMAGE_SIZE_ERR = -2,
  SVCINIT_MEM_MAP_ERR = -3,
};

static long (*svc)(long SVC) = (long (*)(long))0x20000000;
static const char *(*svcQueryName)(long SVC) = (const char *(*)(long))0x20000010;
static void (*svcRegister)(long SVC, void *ptr, const char *name) = (void (*)(long, void *, const char *))0x20000020;

#ifdef __cplusplus
}
#endif
