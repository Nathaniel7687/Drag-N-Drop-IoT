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
