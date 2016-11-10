DEL=rm
CC=gcc
#CC=arm-linux-gnueabihf-gcc

# CFLAGS+=-static
CFLAGS+=-pthread
CFLAGS+=-lpthread
CFLAGS+=-g
CFLAGS+=-Wall

S_TARGET=sendProgram
R_TARGET=recvDeviceInfo

LDLIBS=$(shell mysql_config --libs)
INCDIR=./inc
SRCDIR=./src
OBJDIR=./src/obj
S_SRCS=$(wildcard $(SRCDIR)/*sendProgram.c)
S_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(S_SRCS)))
R_SRCS=$(wildcard $(SRCDIR)/*recvDeviceInfo.c)
R_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(R_SRCS)))

BCC=arm-linux-gnueabihf-gcc

BS_TARGET=./PiBuild/sensor
BA_TARGET=./PiBuild/actuator
BINCDIR=./PiBuild/inc
BSRCDIR=./PiBuild/src
BOBJDIR=./PiBuild/src/obj
BS_SRCS=$(wildcard $(BSRCDIR)/*Sensor.c) uart_api.c
BS_OBJS=$(patsubst %.c,$(BOBJDIR)/%.o,$(notdir $(BS_SRCS)))
BA_SRCS=$(wildcard $(BSRCDIR)/*Actuator.c) uart_api.c
BA_OBJS=$(patsubst %.c,$(BOBJDIR)/%.o,$(notdir $(BA_SRCS)))

all: $(S_TARGET) $(R_TARGET)

$(S_TARGET): $(S_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(R_TARGET): $(R_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(S_OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I $(INCDIR) -c $(CFLAGS) $< -o $@

$(R_OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I $(INCDIR) -c $(CFLAGS) $< -o $@

clean:
	$(DEL) -rf $(OBJDIR)/*.o
	$(DEL) -rf $(S_TARGET) $(R_TARGET)

build: $(BS_TARGET) $(BA_TARGET)

$(BS_TARGET): $(BS_OBJS)
	$(BCC) -march=armv7-a $(CFLAGS) $(BCFLAGS) $^ -o $@

$(BA_TARGET): $(BA_OBJS)
	$(BCC) -march=armv7-a $(CFLAGS) $(BCFLAGS) $^ -o $@

$(BS_OBJS): $(BOBJDIR)/%.o: $(BSRCDIR)/%.c
	@mkdir -p $(BOBJDIR)
	$(BCC) -I $(BINCDIR) -c $(CFLAGS) $(BCFLAGS) $< -o $@

$(BA_OBJS): $(BOBJDIR)/%.o: $(BSRCDIR)/%.c
	@mkdir -p $(BOBJDIR)
	$(BCC) -I $(BINCDIR) -c $(CFLAGS) $(BCFLAGS) $< -o $@

bclean:
	$(DEL) -rf $(BOBJDIR)/*.o
	$(DEL) -rf $(BS_TARGET) $(BA_TARGET)
