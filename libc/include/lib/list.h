#ifndef __H_LIST_H__
#define __H_LIST_H__

typedef struct list_head {
	struct list_head *prev;
	struct list_head *next;
}list_head;


#define INIT_LIST(l) { \
	l->next = l; \
	l->prev = l; \
}

inline void list_insert_after(list_head *head, list_head *item) {
	head->next = item;
	item->prev = head;
}

#define list_foreach(head, l)  \
	for (l = head->next; l != head; l = l->next) \


inline void list_insert_tail(list_head *head, list_head *item) {
	list_head *i, *last;

	last = head;

	list_foreach(head, i) {
		last = i;
	}

	list_insert_after(last, item);
}
#endif
