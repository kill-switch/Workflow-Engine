#include "gtk_menu.h"

gboolean exit_system(GtkWidget *entry1, gpointer a1)
{
	client_state_t *client = (client_state_t *)a1;
	
	netMessage_t message;
	bzero(&message,sizeof(netMessage_t));
	message.opcode = DISCONNECT_SIG;
	//sendData(client->thisClient, &message, sizeof(netMessage_t));
	printf("SENDING DISCONNECT DATA\n");
	gtk_widget_hide_all(client->window);
	
	sleep(1);
	gtk_main_quit();
}



void show_Success(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Task Completed", "title");
  gtk_window_set_title(GTK_WINDOW(dialog), "Server Message");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void show_Failure(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Task Failed", "title");
  gtk_window_set_title(GTK_WINDOW(dialog), "Server Message");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}



gboolean update_1(GtkWidget *entry1, gpointer a1)
{
	client_state_t *client = (client_state_t *)a1;
	widget_list_t *widlist = (widget_list_t *)client->info1;
	widget_element_t *tempele;
	roomreq newreq;
	netMessage_t message;
	bzero(&newreq, sizeof(roomreq));
	
	
	tempele = returnTail(widlist);
	if(gtk_entry_get_text(GTK_ENTRY(tempele->widget)) != NULL)
	{
		newreq.noofpeople = atoi(gtk_entry_get_text(GTK_ENTRY(tempele->widget)));
	
	}
	
	poptail(widlist);
	
	tempele = returnTail(widlist);	
	char *str = NULL;
	if(gtk_entry_get_text(GTK_ENTRY(tempele->widget)) != NULL)
	{
		str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(tempele->widget)),"\0" , NULL);
		char temp[10];
		int j = 0;
		int i;
	
		for(i = 0; str[i] != '/'; i++)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
		temp[j] ='\0';
		newreq.start_time.day = atoi(temp);
		newreq.end_time.day= atoi(temp);
		j = 0;
		for(; str[i] != '/'; i++)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
		temp[j] ='\0';
		newreq.start_time.month = atoi(temp);
		newreq.end_time.month= atoi(temp);
		j =0;
		
		for(; str[i] != '\0'; i++)
		{
			temp[j] = str[i];
			j++;
		}
		
		temp[j] ='\0';
		newreq.start_time.year = atoi(temp);
		newreq.end_time.year= atoi(temp);
		printf("%d %d %d\n",newreq.start_time.day,newreq.start_time.month,newreq.start_time.year);
		g_free(str);
	}
	poptail(widlist);	
	
	tempele = returnTail(widlist);
	if(gtk_entry_get_text(GTK_ENTRY(tempele->widget)) != NULL)
	{
		newreq.start_time.hour = atoi(gtk_entry_get_text(GTK_ENTRY(tempele->widget)))/100;
		newreq.start_time.minute = atoi(gtk_entry_get_text(GTK_ENTRY(tempele->widget)))%100;
	}
	poptail(widlist);
	
	tempele = returnTail(widlist);
	if(gtk_entry_get_text(GTK_ENTRY(tempele->widget)) != NULL)
	{
		newreq.end_time.hour = atoi(gtk_entry_get_text(GTK_ENTRY(tempele->widget)))/100;
		newreq.end_time.minute = atoi(gtk_entry_get_text(GTK_ENTRY(tempele->widget)))%100;
	}
	poptail(widlist);
	
	tempele = returnTail(widlist);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		newreq.roomspecs.whiteboard = 1;
	}
	else
	{
		newreq.roomspecs.whiteboard = 0;
	}
	poptail(widlist);
	
	tempele = returnTail(widlist);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		newreq.roomspecs.lcd = 1;
	}
	else
	{
		newreq.roomspecs.lcd = 0;
	}
	poptail(widlist);
	
	tempele = returnTail(widlist);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		newreq.roomspecs.aircond = 1;
	}
	else
	{
		newreq.roomspecs.aircond = 0;
	}
	poptail(widlist);

	tempele = returnTail(widlist);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		poptail(widlist);
		tempele = returnTail(widlist);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
		{
			newreq.roomspecs.projector = 2;	
		}
		else
		{
			newreq.roomspecs.projector = 1;
		}
		poptail(widlist);
				
		
	}
	else
	{
		newreq.roomspecs.projector = 0;
		poptail(widlist);
		poptail(widlist);
	}
	
	tempele = returnTail(widlist);
	printf("%s\n",tempele->label);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		poptail(widlist);
		tempele = returnTail(widlist);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
		{
			newreq.roomspecs.soundsys = 2;	
		}
		else
		{
			newreq.roomspecs.soundsys = 1;
		}
		poptail(widlist);	
	}
	else
	{
		newreq.roomspecs.soundsys = 0;
		poptail(widlist);
		poptail(widlist);
	}
	
	tempele = returnTail(widlist);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		poptail(widlist);
		tempele = returnTail(widlist);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
		{
			newreq.roomspecs.audiorec = 2;	
		}
		else
		{
			newreq.roomspecs.audiorec = 1;
		}
		poptail(widlist);
				
		
	}
	else
	{
		newreq.roomspecs.audiorec = 0;
		poptail(widlist);
		poptail(widlist);
	}
	
	tempele = returnTail(widlist);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
	{
		poptail(widlist);
		tempele = returnTail(widlist);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tempele->widget)))
		{
			newreq.roomspecs.videorec = 2;	
		}
		else
		{
			newreq.roomspecs.videorec = 1;
		}
		poptail(widlist);
				
		
	}
	else
	{
		newreq.roomspecs.videorec = 0;
		poptail(widlist);
		poptail(widlist);
	}
	
	printf("No of People : %d\n",newreq.noofpeople);
	printf(" Date :%d %d %d\n", newreq.start_time.day, newreq.start_time.month, newreq.start_time.year);
	printf("Start Time : %d %d\n", newreq.start_time.hour, newreq.start_time.minute);
	printf("End Time : %d %d\n", newreq.end_time.hour, newreq.end_time.minute);
	printf(" whit board :%d\n",newreq.roomspecs.whiteboard );
	
	printf(" lcd :%d\n",newreq.roomspecs.lcd );

	printf(" aircond :%d\n",newreq.roomspecs.aircond );

	printf(" projector :%d\n",newreq.roomspecs.projector );

	printf(" soundsys :%d\n",newreq.roomspecs.soundsys );

	printf(" audiorec :%d\n",newreq.roomspecs.audiorec );
	
	printf(" videorec :%d\n",newreq.roomspecs.videorec );
	// JUST SEND THIS TO SERVER
	bzero(&message, sizeof(netMessage_t));
	message.opcode = REQUEST_WRITE;
	bcopy(&newreq, message.buffer, sizeof(roomreq));
	
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
	
	
	gtk_widget_hide_all(client->window);
	option_menu(client);

}



void toggle_title(GtkWidget *widget, gpointer check_proj_audio)
{
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) 
  {
	gtk_widget_set_sensitive(check_proj_audio, TRUE);	      	
  } 
  else
  {
  	gtk_widget_set_sensitive(check_proj_audio, FALSE);
  }

}

gboolean newRequest_back (GtkWidget *entry1, gpointer a1)
{
	client_state_t *client = (client_state_t *)a1;
	gtk_widget_hide_all(client->window);
	option_menu(client);
}


void newRequest(client_state_t *client)
{
	roomreq newreq;
	
	GtkWidget *box;
	GtkWidget *box2;
	GtkWidget *box_date;
	GtkWidget *box_starttime;
	GtkWidget *box_endtime;
	GtkWidget *instruct;
	GtkWidget *instruct_noofpeople;
	GtkWidget *instruct_date;
	GtkWidget *instruct_starttime;
	GtkWidget *instruct_endtime;
	GtkWidget *entry_noofpeople;
	GtkWidget *entry_date;
	GtkWidget *entry_starttime;
	GtkWidget *entry_endtime;
	
	GtkWidget *box_whiteboard;
	GtkWidget *check_whiteboard;
	
	GtkWidget *box_lcd;
	GtkWidget *check_lcd;
	
	GtkWidget *box_air;
	GtkWidget *check_air;
	
	GtkWidget *box_proj;
	GtkWidget *check_proj;
	GtkWidget *check_proj_audio;
	
	GtkWidget *box_sound;
	GtkWidget *check_sound;
	GtkWidget *check_sound_mic;
	
	GtkWidget *box_audio;
	GtkWidget *check_audio;
	GtkWidget *check_audio_mic;
	
	GtkWidget *box_vedio;
	GtkWidget *check_vedio;
	GtkWidget *check_vedio_mic;
	
	GtkWidget *submit;
	GtkWidget *back;
	
	widget_list_t *widlist;
	widlist = newWidgetList();
	
	
	client->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title(GTK_WINDOW(client->window), "Ticking System");
	gtk_window_set_default_size(GTK_WINDOW(client->window), 100, 75);
	gtk_window_set_position(GTK_WINDOW(client->window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(client->window), "destroy",G_CALLBACK(exit_system), client);
		
	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(client->window), box);
	
	instruct = gtk_label_new("insert Details\n");
	gtk_box_pack_start(GTK_BOX(box), instruct, TRUE, TRUE, 5);

	//*************** no of people******************//
	box2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box2, TRUE, TRUE, 5);
	
	instruct_noofpeople = gtk_label_new("No of people\n");
	gtk_box_pack_start(GTK_BOX(box2), instruct_noofpeople, TRUE, TRUE, 5);
	
	entry_noofpeople = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box2), entry_noofpeople, TRUE, TRUE, 5);
	
	insertHead(widlist, entry_noofpeople,"Entry no of people");
	//*************** date ******************//
	box_date = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_date, TRUE, TRUE, 5);
	
	instruct_date = gtk_label_new("DATE : (dd/mm/yyyy)");
	gtk_box_pack_start(GTK_BOX(box_date), instruct_date, TRUE, TRUE, 5);
	
	
	entry_date = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box_date), entry_date, TRUE, TRUE, 5);
    insertHead(widlist, entry_date,"date");
	//*************** start time input******************//
	box_starttime = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_starttime, TRUE, TRUE, 5);
	
	instruct_starttime = gtk_label_new("Starttime : xxxx hrs");
	gtk_box_pack_start(GTK_BOX(box_starttime), instruct_starttime, TRUE, TRUE, 5);
	
	entry_starttime = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box_starttime), entry_starttime, TRUE, TRUE, 5);
	
	insertHead(widlist, entry_starttime,"Entry start time");	
	//*************** end time input******************//
	box_endtime = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_endtime, TRUE, TRUE, 5);
	
	instruct_endtime = gtk_label_new("Endtime : xxxxhrs");
	gtk_box_pack_start(GTK_BOX(box_endtime), instruct_endtime, TRUE, TRUE, 5);
	
	entry_endtime = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box_endtime), entry_endtime, TRUE, TRUE, 5);
	
	insertHead(widlist, entry_endtime,"Entry endtime");
	//*********** whitboard radio **************//

	box_whiteboard = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_whiteboard, TRUE, TRUE, 5);	
		
	check_whiteboard = gtk_check_button_new_with_label("White Board");
	gtk_box_pack_start(GTK_BOX(box_whiteboard), check_whiteboard, TRUE, TRUE, 5);	
	insertHead(widlist, check_whiteboard,"check_whiteboard");
	//*********** lcd Display *****************//
	box_lcd = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_lcd, TRUE, TRUE, 5);	
		
	check_lcd = gtk_check_button_new_with_label("LCD display");
	gtk_box_pack_start(GTK_BOX(box_lcd), check_lcd, TRUE, TRUE, 5);
	insertHead(widlist, check_lcd,"check_lcd");
	//**********air cond****************//
	box_air = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_air, TRUE, TRUE, 5);	
		
	check_air = gtk_check_button_new_with_label("Air-conditioning");
	gtk_box_pack_start(GTK_BOX(box_air), check_air, TRUE, TRUE, 5);
	insertHead(widlist, check_air,"check_air");
	//*************** proj **************//
	box_proj = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_proj, TRUE, TRUE, 5);	
		
	check_proj = gtk_check_button_new_with_label("projector");
	gtk_box_pack_start(GTK_BOX(box_proj), check_proj, TRUE, TRUE, 5);
	insertHead(widlist, check_proj,"check_proj");
	
	check_proj_audio = gtk_check_button_new_with_label("Audio Facilities");
	gtk_box_pack_start(GTK_BOX(box_proj), check_proj_audio, TRUE, TRUE, 5);
	gtk_widget_set_sensitive(check_proj_audio, FALSE);
	g_signal_connect(check_proj, "clicked", G_CALLBACK(toggle_title), (gpointer) check_proj_audio);
	insertHead(widlist, check_proj_audio,"check_proj_audio");
	
	//*************** sound **************//
	box_sound = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_sound, TRUE, TRUE, 5);	
		
	check_sound = gtk_check_button_new_with_label("Sound System");
	gtk_box_pack_start(GTK_BOX(box_sound), check_sound, TRUE, TRUE, 5);
	insertHead(widlist, check_sound,"check_sound");
	
	check_sound_mic = gtk_check_button_new_with_label("Microphones");
	gtk_box_pack_start(GTK_BOX(box_sound), check_sound_mic, TRUE, TRUE, 5);
	gtk_widget_set_sensitive(check_sound_mic, FALSE);
	g_signal_connect(check_sound, "clicked", G_CALLBACK(toggle_title), (gpointer) check_sound_mic);
	insertHead(widlist, check_sound_mic,"check_sound_mic");
	
	//*************** audio rec **************//
	box_audio = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_audio, TRUE, TRUE, 5);	
		
	check_audio = gtk_check_button_new_with_label("Audio Recording");
	gtk_box_pack_start(GTK_BOX(box_audio), check_audio, TRUE, TRUE, 5);
	insertHead(widlist, check_audio,"check_audio");
	
	check_audio_mic = gtk_check_button_new_with_label("Microphones");
	gtk_box_pack_start(GTK_BOX(box_audio), check_audio_mic, TRUE, TRUE, 5);
	gtk_widget_set_sensitive(check_audio_mic, FALSE);
	g_signal_connect(check_audio, "clicked", G_CALLBACK(toggle_title), (gpointer) check_audio_mic);
	insertHead(widlist, check_audio_mic,"check_audio_mic");
	
	//*************** vedio rec **************//
	box_vedio = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_vedio, TRUE, TRUE, 5);	
		
	check_vedio = gtk_check_button_new_with_label("Video Recording");
	gtk_box_pack_start(GTK_BOX(box_vedio), check_vedio, TRUE, TRUE, 5);
	insertHead(widlist, check_vedio,"check_vedio");
	
	check_vedio_mic = gtk_check_button_new_with_label("Microphones");
	gtk_box_pack_start(GTK_BOX(box_vedio), check_vedio_mic, TRUE, TRUE, 5);
	gtk_widget_set_sensitive(check_vedio_mic, FALSE);
	g_signal_connect(check_vedio, "clicked", G_CALLBACK(toggle_title), (gpointer) check_vedio_mic);
	insertHead(widlist, check_vedio_mic,"check_vedio_mic");

	// ************ buttons ***************//
	submit = gtk_button_new_with_label("Submit");
	gtk_box_pack_start(GTK_BOX(box), submit, TRUE , TRUE , 5);
	client->info1 = widlist;
	g_signal_connect(submit, "clicked", G_CALLBACK(update_1), client);
	
	back = gtk_button_new_with_label("Back");
	gtk_box_pack_start(GTK_BOX(box), back, TRUE , TRUE , 5);
	g_signal_connect(back, "clicked", G_CALLBACK(newRequest_back), client);
	
	gtk_widget_show(submit);
	gtk_widget_show(back);

	gtk_widget_show(check_vedio_mic);
	gtk_widget_show(check_vedio);
	gtk_widget_show(box_vedio);
	
	gtk_widget_show(check_audio_mic);
	gtk_widget_show(check_audio);
	gtk_widget_show(box_audio);
	
	gtk_widget_show(check_sound_mic);
	gtk_widget_show(check_sound);
	gtk_widget_show(box_sound);
	
	gtk_widget_show(check_proj_audio);
	gtk_widget_show(check_proj);
	gtk_widget_show(box_proj);
	
	gtk_widget_show(check_air);
	gtk_widget_show(box_air);
	
	gtk_widget_show(check_lcd);
	gtk_widget_show(box_lcd);
	
	gtk_widget_show(check_whiteboard);
	gtk_widget_show(box_whiteboard);
	
	gtk_widget_show(entry_endtime);
	gtk_widget_show(instruct_endtime);
	gtk_widget_show(box_endtime);
	
	gtk_widget_show(entry_starttime);
	gtk_widget_show(instruct_starttime);
	gtk_widget_show(box_starttime);
	
	gtk_widget_show(entry_date);
	gtk_widget_show(instruct_date);
	gtk_widget_show(box_date);
	gtk_widget_show(entry_noofpeople);
	gtk_widget_show(instruct_noofpeople);
	gtk_widget_show(box2);
	gtk_widget_show(instruct);
	gtk_widget_show(box);
	gtk_widget_show(client->window);
}

