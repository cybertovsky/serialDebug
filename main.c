#include <gtk/gtk.h>

// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include "Serial_Port_Library/Serial_Port.h"

void destroy(GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char* argv[])
{
	GtkWidget* window;

    TSerialPortID tty;
    unsigned int Baud_Rate = 115200;
    SerialPortOpen("/dev/ttyUSB0",Baud_Rate,SERIAL_PORT_PARITY_NONE,&tty);

    SerialPortWriteByte(tty,'h');
    int flag = SerialPortIsByteAvailable(tty,"xx");
    printf("%d\n", flag);

	GtkWidget* button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(window, "destroy",G_CALLBACK(destroy), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
