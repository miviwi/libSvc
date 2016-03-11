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
  if(fstat(fd, &sb) < 0 || (sb.st_size-off) < 489) {
    close(fd);
    return SVCINIT_IMAGE_SIZE_ERR;
  }

  void *addr = mmap((void *)svc, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_FIXED, fd, off);
  if(addr == (void *)-1) {
    close(fd);
    return SVCINIT_MEM_MAP_ERR;
  }

  close(fd);
  return SVCINIT_NO_ERR;
}

long svcClose()
{
  munmap((void *)svc, 0x1000);
}

#ifdef __cplusplus
}
#endif
