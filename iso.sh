#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/afsos.kernel isodir/boot/afsos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "afsos" {
	multiboot /boot/afsos.kernel
}
EOF
grub-mkrescue -o afsos.iso isodir
