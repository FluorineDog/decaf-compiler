#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct string{
  int len;
  char* content;
}string;

int readint(){
  int tmp;
  scanf("%d", &tmp);
  printf("tmp=%d", tmp);
  return tmp;
}

int refint(int ref){
  printf("ref=%d", ref);
  return ref; 
}

void* dog_malloc(int byte){
  return malloc(byte);
}

string* readline(){
  char* str = malloc(100);
  scanf("%s", str);
  string* mem = (string*)dog_malloc(sizeof(string));
  mem->content = str;
  mem->len = strlen(str);
  return mem;
}

void printss(string* a){
  printf("%d:%s\n", a->len,  a->content);
}

string* string_cat(string* a, string* b) {
  assert(a/* string a should not be null */);
  assert(b/* string b should not be null */);
  int newlen = a->len + b->len;
  char* str = dog_malloc(newlen + 1);
  string* mem = (string*)dog_malloc(sizeof(string));
  mem->content = str;
  mem->len = newlen;
  return mem;
}