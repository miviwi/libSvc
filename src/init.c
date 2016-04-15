#include <svc.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#ifdef __cplusplus
extern "C" {
#endif

long svcInit(const char *svc_image, size_t off)
{
  int fd = open(svc_image, O_RDONLY);
  if(fd < 0) return SVCINIT_IMAGE_OPEN_ERR;

  struct stat sb;
  if(fstat(fd, &sb) < 0 || (sb.st_size-off) < 105) {
    close(fd);
    return SVCINIT_IMAGE_SIZE_ERR;
  }

  void *text = mmap((void *)svc, 0x1000, PROT_READ|PROT_EXEC,
      MAP_PRIVATE|MAP_FIXED, fd, off);
  void *data = mmap((void *)((long)svc+0x1000), 0x1000, PROT_READ|PROT_WRITE,
      MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0);
  if(text == (void *)-1 || data == (void *)-1) {
    close(fd);
    return SVCINIT_MEM_MAP_ERR;
  }

  close(fd);
  return SVCINIT_NO_ERR;
}

long svcClose()
{
  if(munmap((void *)svc, 0x2000) < 0) return SVCINIT_MEM_MAP_ERR;
  return SVCINIT_NO_ERR;
}

#ifdef __cplusplus
}
#endif
