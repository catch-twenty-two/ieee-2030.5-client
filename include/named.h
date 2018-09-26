#pragma once

typedef struct _Named {
  struct _Named *next;
  char *name;
  void *data;
} Named;

void *find_by_name (void *l, char *name);
void *get_by_name (void *l, char *name, int size);
Named *named_insert (Named *l, char *name, void *data);
void *_named_insert_sorted (void *h, void *x);
void *named_insert_sorted (void *head, char *name, void *data);
int find_index_by_name (void *l, char *name);


