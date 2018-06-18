typedef struct string{
  char* content;
  int len;
}string;

void* dog_malloc(int byte);
int readint();
string* readline();
string* string_cat(string* a, string* b);
