#include "widgetlist.h"


widget_list_t *newWidgetList()
{
	widget_list_t *list;
	list = (widget_list_t *)malloc(sizeof(widget_list_t));
	
	widget_element_t *head, *tail;
	
	head = (widget_element_t *)malloc(sizeof(widget_element_t));
	head->widget = NULL;
	head->prev = NULL;
	list->head = head;
	
	tail = (widget_element_t *)malloc(sizeof(widget_element_t));
	tail->widget = NULL;
	tail->next = NULL;
	
	tail->prev = head;
	head->next = tail;
	
	list->tail = tail;
	return list;
}


void insertHead(widget_list_t *list, GtkWidget *widget,char *label)
{
	widget_element_t *temp;
	widget_element_t *currelement;	
	
	
	currelement = (widget_element_t *)malloc(sizeof(widget_element_t));
	currelement->widget = widget;	
	currelement->label = label;
	
	currelement->prev = list->head;
	currelement->next = list->head->next;
	list->head->next->prev = currelement;
	list->head->next = currelement;
	
	return ;
}

void insertTail(widget_list_t *list, GtkWidget *widget,gchar *label)
{
	widget_element_t *temp;
	widget_element_t *currelement;	
	
	
	currelement = (widget_element_t *)malloc(sizeof(widget_element_t));
	currelement->widget = widget;	
	currelement->label = label;
	
	currelement->next = list->tail;
	currelement->prev = list->tail->prev;
	list->tail->prev->next = currelement;
	list->tail->prev = currelement;
	
	return ;
}


char isListEmpty(widget_list_t *list)
{
	if(list->head->next == list->tail)
	{
		return 1;
	}
	return 0;
}

widget_element_t *returnHead(widget_list_t *list)
{
	if(isListEmpty(list) == 1)
	{
		return NULL;
	}
	return list->head->next;
}

widget_element_t *returnTail(widget_list_t *list)
{
	if(isListEmpty(list) == 1)
	{
		return NULL;
	}
	return list->tail->prev;
}


void popHead(widget_list_t *list)
{
	if(isListEmpty(list))
	{
		return;
	}
	
	widget_element_t *temp;
	temp = list->head->next;
	list->head->next = temp->next;
	temp->next->prev = list->head;
	free(temp);
}

void poptail(widget_list_t *list)
{
	if(isListEmpty(list))
	{
		return;
	}
	
	widget_element_t *temp;
	temp = list->tail->prev;
	list->tail->prev = temp->prev;
	temp->prev->next = list->tail;
	free(temp);
}

widget_element_t *returnNext(widget_list_t *list, widget_element_t *ele)
{
	if(ele->next == list->tail)
	{
		return NULL;
	}
	return ele->next;
}

widget_element_t *returnPrev(widget_list_t *list, widget_element_t *ele)
{
	if(ele->prev == list->head)
	{
		return NULL;
	}
	return ele->prev;
}
