#HOST?=$(shell ../default-host.sh)
#HOSTARCH:=$(shell ../target-triplet-to-arch.sh $(HOST))
CC=i686-elf-gcc
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=
LIBDIR?=$(PREFIX)/lib
 
DESTDIR?=
PREFIX?=/usr/local/boemiOS
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_boemios_kernel -I$(INCLUDEDIR)
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -L$(LIBDIR)
LIBS:=$(LIBS) -nostdlib -lk -lgcc
#LIBS:=$(LIBS) -nostdlib -lgcc
 
#ARCHDIR:=arch/$(HOSTARCH)
ARCHDIR:=arch/i386
 
include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)
 
OBJS:=\
$(KERNEL_ARCH_OBJS) \
kernel.o \
 
CRTI_OBJ:=$(ARCHDIR)/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=$(ARCHDIR)/crtn.o
 
ALL_OUR_OBJS:=\
$(CRTI_OBJ) \
$(OBJS) \
$(CRTN_OBJ) \
 
OBJ_LINK_LIST:=\
$(CRTI_OBJ) \
$(OBJS) \
$(CRTN_OBJ) \
 
#$(CRTEND_OBJ) \
#$(CRTBEGIN_OBJ) \
#OBJ_LINK_LIST:=\
#$(OBJS) \
 
all: boemios.kernel
 
.PHONY: all clean install install-headers install-kernel
 
boemios.kernel: $(OBJ_LINK_LIST) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)
 
%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
 
%.o: %.S
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
 
clean:
	rm -f boemios.kernel $(OBJS) $(ALL_OUR_OBJS) *.o */*.o */*/*.o

test-kernel: boemios.kernel
	qemu-system-i386 -kernel boemios.kernel
 
install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)
 
install-kernel: boemios.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp boemios.kernel $(DESTDIR)$(BOOTDIR)
