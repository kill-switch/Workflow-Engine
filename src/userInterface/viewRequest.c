#include "gtk_menu.h"

gboolean viewRequest_delete (GtkWidget *entry1, gpointer a1)
{
	client_state_t *client = (client_state_t *)a1;
	//request newreq = *(request *)client->info1;

	netMessage_t message;
	bzero(&message, sizeof(netMessage_t));
	message.opcode = REQUEST_REMOVE;
	//message.details = newreq.reqno;
	if(sendData(client->thisClient, &message, sizeof(netMessage_t)) == 0)
	{
		show_Failure(entry1, client->window);
	}
	else
	{
		recieveData(client->thisClient, &message, sizeof(netMessage_t));
		if(message.opcode == SUCCESS_PROCESS)
		{
			show_Success(entry1, client->window);
		}
		if(message.opcode == FAILURE_PROCESS)
		{
			show_Failure(entry1, client->window);
		}
	
	}
	return TRUE;
}






gboolean viewRequest_back (GtkWidget *entry1, gpointer a1)
{
	client_state_t *client = (client_state_t *)a1;
	gtk_widget_hide_all(client->window);
	option_menu(client);
	return TRUE;
}



void viewRequest(client_state_t *client)
{
	GtkWidget *box_main;
	GtkWidget *box_request;
	GtkWidget *box_tools;
	GtkWidget *instruct;// has to make a list to show all items
	GtkWidget *prev;
	GtkWidget *next;
	GtkWidget *user_delete;
	GtkWidget *admin_accept;
	GtkWidget *admin_deny;
	GtkWidget *admin_run_algo;
	GtkWidget *back;
	
	client->window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title(GTK_WINDOW(client->window), "Ticking System");
	gtk_window_set_default_size(GTK_WINDOW(client->window), 200, 150);
	gtk_window_set_position(GTK_WINDOW(client->window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(client->window), "destroy",G_CALLBACK(exit_system), client);
	
	box_main = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(client->window), box_main);

	// ** request detail box**//	
	box_request = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_main), box_request, TRUE, TRUE, 5);
	
	instruct = gtk_label_new("request details will come here\n");
	gtk_box_pack_start(GTK_BOX(box_request), instruct, TRUE, TRUE, 5);
	
	box_tools = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_main), box_tools, TRUE, TRUE, 5);
	
	prev = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
	gtk_box_pack_start(GTK_BOX(box_tools), prev, TRUE, TRUE, 5);
	
	next = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);	
	gtk_box_pack_start(GTK_BOX(box_tools), next, TRUE, TRUE, 5);
	
	if(client->idNo == 0)
	{
		admin_accept = gtk_button_new_with_label("accept");	
		gtk_box_pack_start(GTK_BOX(box_tools), admin_accept, TRUE, TRUE, 5);
		
		admin_deny = gtk_button_new_with_label("reject");	
		gtk_box_pack_start(GTK_BOX(box_tools), admin_deny, TRUE, TRUE, 5);
		
		admin_run_algo = gtk_button_new_with_label("Run ALgo");	
		gtk_box_pack_start(GTK_BOX(box_tools), admin_run_algo, TRUE, TRUE, 5);
		gtk_widget_show(admin_accept);
		gtk_widget_show(admin_deny);
		gtk_widget_show(admin_run_algo);
	}
	else
	{
		user_delete = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);	
		gtk_box_pack_start(GTK_BOX(box_tools), user_delete, TRUE, TRUE, 5);
		gtk_widget_show(user_delete);
	}
	
	back = gtk_button_new_with_label("Back");
	gtk_box_pack_start(GTK_BOX(box_main), back, TRUE, TRUE, 5);
	g_signal_connect(back, "clicked", G_CALLBACK(viewRequest_back), client);
	
	gtk_widget_show(back);
	gtk_widget_show(next);
	gtk_widget_show(prev);
	gtk_widget_show(box_tools);
	gtk_widget_show(instruct);
	gtk_widget_show(box_request);
	gtk_widget_show(box_main);
	gtk_widget_show(client->window);
	
}
