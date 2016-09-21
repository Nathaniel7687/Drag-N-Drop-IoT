DEL=rm
CC=gcc
#CC=arm-linux-gnueabihf-gcc

CFLAGS+=-static
CFLAGS+=-pthread
CFLAGS+=-lpthread
CFLAGS+=-g
CFLAGS+=-Wall
#CFLAGS+=-Werror

S_TARGET=sensor
A_TARGET=actuator
INCDIR=./inc
SRCDIR=./src
OBJDIR=./src/obj
S_SRCS=$(wildcard $(SRCDIR)/*Sensor.c) uart_api.c
S_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(S_SRCS)))
A_SRCS=$(wildcard $(SRCDIR)/*Actuator.c) uart_api.c
A_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(A_SRCS)))

all: $(S_TARGET) $(A_TARGET)

$(S_TARGET): $(S_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(A_TARGET): $(A_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(S_OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I $(INCDIR) -c $(CFLAGS) $< -o $@

$(A_OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -I $(INCDIR) -c $(CFLAGS) $< -o $@

clean:
	$(DEL) -rf $(OBJDIR)/*.o
	$(DEL) -rf $(TARGET)
