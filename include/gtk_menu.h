#ifndef GTK_MENU_H
#define GTK_MENU_H
#include <gtk/gtk.h>
#include "widgetlist.h"
#include "customerinfo.h"
#include "network.h"
#include "network_utils.h"
#include "net_message.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "reqstatus.h"
#include "requirements.h"
#include "wftime.h"
#include "roomrequest.h"

typedef struct 
{
	clientId_t *thisClient;
	GtkWidget *window;
	int idNo;
	void *info1;
	void *info2;
}client_state_t;

void loginScreen(client_state_t *client);
void welcomeScreen(client_state_t *client);
void newRequest(client_state_t *client);
void viewRequest(client_state_t *client);
void option_menu(client_state_t *client);
void show_Failure(GtkWidget *widget, gpointer window);
void show_Success(GtkWidget *widget, gpointer window);
gboolean exit_system(GtkWidget *entry1, gpointer a1);

#endif
