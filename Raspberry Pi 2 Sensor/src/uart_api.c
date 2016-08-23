#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include "uart_api.h"

volatile int STOP = FALSE;
void signal_handler_IO(void);   /* signal handler function */
int wait_flag = TRUE;		/* not recv signal == TRUE */
static struct termios uart_oldtio, uart_newtio;

/* Serial Device Open */
int user_uart_open(char *device)
{
	int uart_dev = -1;
	char openDevice[20];

	sprintf(openDevice, "%s", device);

	uart_dev = open(openDevice, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(uart_dev < 0) {
		perror(openDevice);
		return -1;
	}

	return uart_dev;
}

/*
    Serial Device Close
 */
void user_uart_close (int uart_dev)
{
	tcsetattr(uart_dev, TCSANOW, &uart_oldtio);
	close(uart_dev);
}
/*
    terminal setting
 */
void user_uart_config(int uart_dev, int baud, int bits, int parity, int stops)
{
	struct sigaction saio;           /* signal action�� ���� */

	/* install the signal handler before making the device asynchronous */
	saio.sa_handler = (void*)signal_handler_IO;
	//saio.sa_mask = 0;
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	sigaction(SIGIO, &saio, NULL);

	/* set SIGIO signal */
	fcntl(uart_dev, F_SETOWN, getpid());
	/* file descriptor asynchronous */
	fcntl(uart_dev, F_SETFL, FASYNC);

	tcgetattr(uart_dev, &uart_oldtio); /* save current port settings */

	/* port setting for Non canonical input processing */
	switch(baud)
	{
	case 9600:    uart_newtio.c_cflag |= B9600; break;
	case 19200:   uart_newtio.c_cflag |= B19200; break;
	case 38400:   uart_newtio.c_cflag |= B38400; break;
	case 57600:   uart_newtio.c_cflag |= B57600; break;
	case 115200:  uart_newtio.c_cflag |= B115200; break;
	default:     uart_newtio.c_cflag |= B0; break;
	}

	switch(bits)
	{
	case 5:  uart_newtio.c_cflag |= CS5; break;
	case 6:  uart_newtio.c_cflag |= CS6; break;
	case 7:  uart_newtio.c_cflag |= CS7; break;
	case 8:  uart_newtio.c_cflag |= CS8; break;
	default: uart_newtio.c_cflag |= CS8; break;
	}

	switch(parity)
	{
	case UART_PAREVEN:
		uart_newtio.c_cflag |= PARENB;
		break;
	case UART_PARODD:
		uart_newtio.c_cflag |= PARENB|PARODD;
		break;
	default:
		break;
	}

	switch(stops)
	{
	case UART_STOP_BITS_2:
		uart_newtio.c_cflag |= CSTOPB;
		break;
	default:
		break;
	}

	uart_newtio.c_cflag |= CLOCAL | CREAD;
	uart_newtio.c_iflag = IGNPAR | ICRNL;
	uart_newtio.c_oflag = 0;
	uart_newtio.c_lflag = ~(ICANON | ECHO | ECHOE | ISIG);
	//uart_newtio.c_cc[VMIN]=4;
	uart_newtio.c_cc[VMIN]=1;
	uart_newtio.c_cc[VTIME]=0;
	tcflush(uart_dev, TCIFLUSH);
	tcsetattr(uart_dev,TCSANOW,&uart_newtio);
}

int user_uart_write(int uart_dev, unsigned char *ubuf, int size)
{
	printf("send message: %s\n",ubuf);
	return write(uart_dev, ubuf, size);
}


/*
    Serial Data Read
 */
int user_uart_read(int uart_dev, unsigned char *ubuf, int size)
{
	int res = 0;

	/* loop while waiting for input. normally we would do something	useful here */
	while(STOP == FALSE) {
		/* after receiving SIGIO, wait_flag = FALSE, input is available and can be read */
		if(wait_flag == FALSE) {
			res = read(uart_dev, ubuf, size);
			wait_flag = TRUE;      /* wait for new input */
			break;
		}
	}

	return res;
}

/*
    Signal Processing
 */
void signal_handler_IO(void)
{
	wait_flag = FALSE;
}
