#include <stdio.h>
#include <stdlib.h>

typedef struct _payload {
	int x;
	int y;
	int idx;
} payload;

typedef struct _node {
	struct _node *pre;
	struct _node *next;
	payload data;
} node;

#define MAX_NODE_CNT (10000 + 1)

node pool[MAX_NODE_CNT];
node *node_ptrs[MAX_NODE_CNT];
int node_cnt;

node HEAD;
node TAIL;

void init()
{
	HEAD.pre = &HEAD;
	HEAD.next = &TAIL;
	TAIL.pre = &HEAD;
	TAIL.next = &TAIL;
	node_cnt = 0;
}

void add_node(int x, int y, int idx)
{
	node *p = &pool[node_cnt];
	node *tar = &HEAD;
	
	p->next = tar->next;
	p->pre = tar;

	tar->next->pre = p;
	tar->next = p;

	p->data.idx = idx;
	p->data.x = x;
	p->data.y = y;
	node_ptrs[idx] = p;

	node_cnt++;
}

void del_node(int idx)
{
	node *p = node_ptrs[idx];

	p->pre->next = p->next;
	p->next->pre = p->pre;
}

void print_nodes()
{
	node *p = HEAD.next;

	while (p != &TAIL) {
		printf("(%d, %d) %d \n", p->data.x, p->data.y, p->data.idx);
		p = p->next;
	}
}


int main()
{
	int i;
	
	init();

	for (i = 0; i < 100; i++) {
		add_node(rand() % 1000, rand() % 1000, i);
	}

	for (i = 15; i < 95; i++) {
		del_node(i);
	}
	print_nodes();

	return 0;
}

