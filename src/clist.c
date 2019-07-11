#include "../include/clist.h"
#include "../include/celement.h"
#include "../include/errcodes.h"
#include <stdio.h>
#include <stdlib.h>

clist_t * new_clist(void){
	clist_t * new = (clist_t *) malloc(sizeof(clist_t));
	new->size = 0;
	new->head = NULL;
	new->tail = NULL;
	return new;
}

void destroy_clist(clist_t *list){
	while(list->size)
		cremove(list, 0);
	printf("Aquii\n");
	free(list);
	return;
}

void cinsert(clist_t *list, int index, void *value){
	if(index > list->size || index < 0){
		fprintf(stderr, "Index out of range\n");
		exit(ERR_INDEX);
	}
	celement_t *element = new_celement(value);
	if(!list->size){
		list->head = list->tail = element;
	}else if(!index){
		element->next = list->head;
	}else{
		celement_t *iter = list->head;
		int i;
		/* Itera até o elemento anterior a posição na qual o novo será inserido */
		for(i = 0; i < index - 1; i++)
			iter = iter->next;

		element->next = iter->next;
		iter->next = element;
	}
	if(!index)
		list->head = element;
	if(index == list->size)
		list->tail = element;
	list->size++;
	return;
}

void cappend(clist_t *list, void *value){
	cinsert(list, list->size, value);
	return;
}

void * cremove(clist_t *list, int index){
	if(index > list->size - 1 || index < 0){
		fprintf(stderr, "Index out of range\n");
		exit(ERR_INDEX);
	}
	if(!list->size){
		fprintf(stderr, "No elements to remove\n");
		exit(ERR_EMPTY);
	}
	celement_t *toremove = NULL;
	if(!index){
		toremove = list->head;
		if(list->size > 1)
			list->head = list->head->next;
		else
			list->head = list->tail = NULL;
	}else{
		celement_t *iter = list->head, *toremove = NULL;
		int i;
		for(i = 0; i < index - 1; i++)
			iter = iter->next;
		printf("%p\n", (void *) iter);
		toremove = iter->next;
		iter->next = toremove->next;
		if(index == list->size - 1)
			list->tail = iter;
	}

	void *ret = toremove->value;
	destroy_celement(toremove);
	return ret;
}

void * cat(clist_t *list, int index){
	if(index > list->size - 1 || index < 0){
		fprintf(stderr, "Index out of range\n");
		exit(ERR_INDEX);
	}
	celement_t *iter = list->head;
	int i;
	for(i = 0; i < index; i++)
		iter = iter->next;
	return iter->value;
}
