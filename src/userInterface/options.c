#include "gtk_menu.h"



gboolean button1_option (GtkWidget *entry1, gpointer ptr)
{
	client_state_t *client = (client_state_t *)ptr;
	gtk_widget_hide_all(client->window);
	newRequest(client);
	return TRUE;
}
gboolean button2_option (GtkWidget *entry1, gpointer ptr)
{
	client_state_t *client = (client_state_t *)ptr;
	gtk_widget_hide_all(client->window);
	viewRequest(client);
	return TRUE;
}

gboolean button3_option (GtkWidget *entry1, gpointer ptr)
{
	client_state_t *client = (client_state_t *)ptr;
	gtk_widget_hide_all(client->window);
	
	return TRUE;
}



void option_menu(client_state_t *client)
{
	GtkWidget *box;
	GtkWidget *instruct;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;
	GtkWidget *button4;
	
	client->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(client->window), "Ticketing System");
	
	gtk_window_set_default_size(GTK_WINDOW(client->window), 200, 200);
	gtk_window_set_position(GTK_WINDOW(client->window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(client->window), "destroy",G_CALLBACK(exit_system), client);
	
	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(client->window), box);
	
	instruct = gtk_label_new("Please select your option\n");
	gtk_box_pack_start(GTK_BOX(box), instruct, TRUE, TRUE, 5);
	if(client->idNo == 0)
	{
		button1 = gtk_button_new_with_label("Shut down Server");
		gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 5);
		g_signal_connect(GTK_OBJECT(button1), "clicked",G_CALLBACK( button1_option), client);
	}
	else
	{
		button1 = gtk_button_new_with_label("Register a Request");
		gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 5);
		g_signal_connect(GTK_OBJECT(button1), "clicked",G_CALLBACK( button1_option), client);
	}
	
	
	button2 = gtk_button_new_with_label("View Previous Request");
	gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 5);
	g_signal_connect(GTK_OBJECT(button2), "clicked",G_CALLBACK( button2_option), client);
	
	button3 = gtk_button_new_with_label("View Credentials");
	gtk_box_pack_start(GTK_BOX(box), button3, TRUE, TRUE, 5);
	g_signal_connect(GTK_OBJECT(button3), "clicked", G_CALLBACK( button3_option),client);
	
	button4 = gtk_button_new_with_label("Logout");
	gtk_box_pack_start(GTK_BOX(box), button4, TRUE, TRUE, 5);
	g_signal_connect(GTK_OBJECT(button4), "clicked",G_CALLBACK(exit_system), client);

	gtk_widget_show(button1);
	gtk_widget_show(button2);
	gtk_widget_show(button3);
	gtk_widget_show(button4);
	gtk_widget_show(instruct);
	gtk_widget_show(box);
	gtk_widget_show(client->window);
}


