gcc svc.S -c -o svc.o
objcopy -j .text -O binary svc.o svc.img
