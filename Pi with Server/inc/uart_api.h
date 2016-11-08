#define FALSE 0
#define TRUE 1

#define UART_PARNONE	0	/* Defines for setting parity */
#define UART_PARODD	    1
#define UART_PAREVEN	2

#define UART_STOP_BITS_1    0
#define UART_STOP_BITS_2    1

/* UART API Function Prototypes */

int user_uart_open (char *device);
void user_uart_close (int uart_dev);
void user_uart_config(int uart_dev, int baud, int bits,int parity, int stops);
int user_uart_write(int uart_dev, unsigned char *ubuf, int size);
int user_uart_read(int uart_dev, unsigned char *ubuf, int size);
