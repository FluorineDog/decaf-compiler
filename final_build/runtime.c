#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int global;
int* global_arr = &global;
void* global_arr_ptr = (void*)&global;

typedef struct __entry {
  unsigned long long fid;
  void* fptr;
} __entry;

// this is symtable for simgle class
typedef struct __sym_table {
  unsigned long long len;
  __entry table[1];
} __sym_table;

typedef struct string {
  int len;
  char* content;
} string;

int readint() {
  int tmp;
  scanf("%d", &tmp);
  // printf("tmp=%d", tmp);
  return tmp;
}

int refint(int ref) {
  printf("ref=%d", ref);
  return ref;
}

void* dog_malloc(int byte) { return malloc(byte); }

string* readline() {
  char* str = malloc(100);
  scanf("%s", str);
  string* mem = (string*)dog_malloc(sizeof(string));
  mem->content = str;
  mem->len = strlen(str);
  return mem;
}

void printstring(string* a) { printf("(%d)%s ", a->len, a->content); }

void printbool(bool a) { printf("%s ", a ? "true" : "false"); }

void printint(int a) { printf("%d ", a); }

void printdouble(double a) { printf("%lf ", a); }

string* string_cat(string* a, string* b) {
  assert(a /* string a should not be null */);
  assert(b /* string b should not be null */);
  int newlen = a->len + b->len;
  char* str = dog_malloc(newlen + 1);
  string* mem = (string*)dog_malloc(sizeof(string));
  mem->content = str;
  strcpy(str, a->content);
  strcpy(str + a->len, b->content);
  mem->len = newlen;
  return mem;
}

void* load_ptr(__sym_table* table, int id) {
  // sorted
  int beg = 0;
  int end = table->len;
  // fprintf(stderr, "beg=%d, end=%d", beg, end);
  while (end != beg) {
    int mid = (beg + end) / 2;
    if (table->table[mid].fid < id) {
      beg = mid + 1;
    } else {
      end = mid;
    }
  }
  __entry res = table->table[beg];
  if (res.fid == id) {
    return res.fptr;
  } else if(true) {
    return NULL;
  }
}

void fuck(){
  int (*f)(int) = NULL;
  int k = f(5);
}
