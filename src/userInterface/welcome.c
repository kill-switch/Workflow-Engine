#include "gtk_menu.h"


gboolean update3 (GtkWidget *entry1, gpointer a1)
{
	
	client_state_t *client = (client_state_t *)a1; 
	
	customerinfo cum;
	bzero(&cum ,sizeof(customerinfo));
	netMessage_t message;
	
	gchar *str = NULL;
	int i;
	str = g_strconcat(gtk_entry_get_text(GTK_ENTRY((GtkWidget *)client->info1)),"\0" , NULL);
	
	
	for(i = 0; str[i] != '\0'; i++)
	{
		cum.userId[i] = str[i];
	}
	cum.userId[i]= '\0';
	g_free(str);
	gchar *str2 = NULL;
	str2 = g_strconcat(gtk_entry_get_text(GTK_ENTRY((GtkWidget *)client->info2)),"\0", NULL );
	
	for(i = 0; str2[i] != '\0'; i++)
	{
		cum.pass[i] = str2[i];
	}
	cum.pass[i]= '\0';
		
	g_free(str2);
	bzero(&message, sizeof(netMessage_t));
	
	message.opcode = PASSWORD_MESSAGE;
	message.details = 0;
	bcopy(&cum, message.buffer, sizeof(customerinfo));

	if(sendData(client->thisClient, &message, sizeof(netMessage_t)) == 0)
	{
	
		show_Failure(entry1, client->window);
	}
	else
	{
		recieveData(client->thisClient, &message, sizeof(netMessage_t));
		if(message.opcode == PASSWORD_MESSAGE && message.details >= 0)
		{
			show_Success(entry1, client->window);
			client->idNo = message.details;
			gtk_widget_hide_all(client->window);
			option_menu(client);
		}
		else
		{
			show_Failure(entry1, client->window);
		}
	}
	return TRUE;
}


void loginScreen(client_state_t *client)
{

	GtkWidget *box;
	GtkWidget *instruct;
	GtkWidget *instruct2;
	GtkWidget *enter;
	GtkWidget *entry;
	GtkWidget *entry2;
	GtkWidget *username;
	GtkWidget *password;
	
	
	client->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(client->window), "hello");
	gtk_window_set_default_size(GTK_WINDOW(client->window), 200, 200);
	gtk_window_set_position(GTK_WINDOW(client->window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(client->window), "destroy",G_CALLBACK(gtk_main_quit), client->window);
	
	box = gtk_vbox_new (FALSE, 0);                                // Create the vbox
    gtk_container_add(GTK_CONTAINER(client->window), box);                // Add the vbox to the window
		
	instruct = gtk_label_new("Username");
	gtk_box_pack_start (GTK_BOX (box), instruct, TRUE, TRUE, 5);  // Add the widget to the vbox (first item)
    
    username = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box), username, TRUE, TRUE, 5);
	
	instruct2 = gtk_label_new("Password");
	gtk_box_pack_start (GTK_BOX (box), instruct2, TRUE, TRUE, 5);  // Add the widget to the vbox (first item)
    
    password = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box), password, TRUE, TRUE, 5);
	gtk_widget_grab_focus(password);
	gtk_widget_grab_focus(username);  
  
  	client->info1 = username;
  	client->info2 = password;
  	entry = gtk_button_new_with_label("Login");
  	gtk_box_pack_start (GTK_BOX (box), entry, TRUE, TRUE, 5);
  	g_signal_connect(entry, "clicked", G_CALLBACK(update3), client);
  	
	entry2 = gtk_button_new_with_label("Register");
  	gtk_box_pack_start (GTK_BOX (box), entry2, TRUE, TRUE, 5);
    
   
   	gtk_widget_show(entry2);
    gtk_widget_show(box);  
    gtk_widget_show(password);
    gtk_widget_show(username);
    gtk_widget_show(instruct2);
    gtk_widget_show(instruct);
  	gtk_widget_show(entry);
	gtk_widget_show(client->window);
}

static void enterNextScreen(GtkWidget *widget, gpointer data)
{
	client_state_t *client = (client_state_t *)data;
	gtk_widget_hide_all(client->window);
	loginScreen(client);
}


void welcomeScreen(client_state_t *client)
{

	GtkWidget *box;
	GtkWidget *instruct;
	GtkWidget *instruct2;
	GtkWidget *enter;
	GtkWidget *entry;
	GtkWidget *entry2;
	GtkWidget *username;
	GtkWidget *password;	
	
	client->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(client->window), "Ticking System");
	gtk_window_set_default_size(GTK_WINDOW(client->window), 75, 50);
	gtk_window_set_position(GTK_WINDOW(client->window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(client->window), "destroy",G_CALLBACK(gtk_main_quit), client->window);
	
    box = gtk_vbox_new (FALSE, 0);                                // Create the vbox
    gtk_container_add(GTK_CONTAINER(client->window), box);                // Add the vbox to the window
    
	instruct = gtk_label_new("Ticketing System");
	gtk_box_pack_start (GTK_BOX (box), instruct, TRUE, TRUE, 5);  // Add the widget to the vbox (first item)
    gtk_widget_show(instruct);        
   
   	enter = gtk_button_new_with_label("Enter");
   	g_signal_connect(enter , "clicked", G_CALLBACK(enterNextScreen),client);
   	gtk_box_pack_start (GTK_BOX (box), enter, TRUE, TRUE, 5);
   
   
   	gtk_widget_show(enter);
    gtk_widget_show(box); 
	gtk_widget_show(client->window);
}




/*
int main(int argc, char *argv[])
{
	client_state_t client;
	gtk_init(&argc, &argv);
	welcomeScreen(&client);
	gtk_main();
}
*/
