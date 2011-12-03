#ifndef WIDGETLIST_H
#define WIDGETLIST_H
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct widgetelement
{
	GtkWidget *widget;
	gchar *label; // this if you want cataloging
	struct widgetelement *prev;
	struct widgetelement *next;
}widget_element_t;

typedef struct
{
	widget_element_t *head;
	widget_element_t *tail;
}widget_list_t;

widget_list_t *newWidgetList();
void insertHead(widget_list_t *list, GtkWidget *widget,char *label);
void insertTail(widget_list_t *list, GtkWidget *widget,char *label);
char isListEmpty(widget_list_t *list);
widget_element_t *returnHead(widget_list_t *list);
widget_element_t *returnTail(widget_list_t *list);
void popHead(widget_list_t *list);
void poptail(widget_list_t *list);
widget_element_t *returnNext(widget_list_t *list, widget_element_t *ele);
widget_element_t *returnPrev(widget_list_t *list, widget_element_t *ele);

#endif
