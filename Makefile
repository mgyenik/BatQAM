# BatQAM Makefile
BINARY = batqam
OBJS = cdcacm.o
OPENCM3_DIR = libopencm3
LDSCRIPT = stm32f4-discovery.ld
include libopencm3.target.mk 
