DEL=rm
CC=gcc
#CC=arm-linux-gnueabihf-gcc

CFLAGS+=-static
CFLAGS+=-pthread
CFLAGS+=-lpthread
CFLAGS+=-g
CFLAGS+=-Wall
#CFLAGS+=-Werror

S_TARGET=sendDeviceInfo
R_TARGET=recvProgram
INCDIR=./inc
SRCDIR=./src
OBJDIR=./src/obj
S_SRCS=$(wildcard $(SRCDIR)/*sendDeviceInfo.c) uart_api.c
S_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(S_SRCS)))
R_SRCS=$(wildcard $(SRCDIR)/*recvProgram.c) uart_api.c
R_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(R_SRCS)))

all: $(S_TARGET) $(R_TARGET)

$(S_TARGET): $(S_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(R_TARGET): $(R_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(S_OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I $(INCDIR) -c $(CFLAGS) $< -o $@

$(R_OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I $(INCDIR) -c $(CFLAGS) $< -o $@

clean:
	$(DEL) -rf $(OBJDIR)/*.o
	$(DEL) -rf $(S_TARGET) $(R_TARGET)
