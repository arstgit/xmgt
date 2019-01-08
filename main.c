#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static void process_data (struct MemoryStruct *userp) {
  char * tic = "magnet:?xt=urn:btih:";
  char * toc = "\"";
  char * magnet;
  char * raw = userp->memory;

  while ((magnet = strstr(raw, tic)) != NULL) {
    raw = strstr(magnet, toc);
    
    while (magnet < raw) {
      putchar(*magnet++);
    }
    printf("\n");
  }
}
  
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    fprintf(stderr, "not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(int argc, char **argv) {
  CURL *curl_handle;
  CURLcode res;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);
  chunk.size = 0;
 
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
 
  curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  res = curl_easy_perform(curl_handle);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }
  else {
    process_data(&chunk);
  }
 
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  free(chunk.memory);

  return 0;
}
