## HTTP Requests in C

---

### Lazy Way — system() + curl
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    system("curl -s 'https://api.weatherapi.com/v1/current.json?key=YOUR_API_KEY&q=Lagos'");
    return 0;
}
```

---

### Proper Way — libcurl
```c
#include <stdio.h>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL,
            "https://api.weatherapi.com/v1/current.json?key=YOUR_API_KEY&q=Lagos");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl error: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    return 0;
}
```

**Compile**
```bash
sudo apt install libcurl4-openssl-dev
gcc main.c -o main -lcurl && ./main
```

---

### Why system("curl ...") is bad
```
no error handling     if curl fails, you don't know why
can't capture output  just prints to stdout raw
security risk         never put user input into system()
not portable          curl must be installed on the machine
```

## libcurl CRUD in C

using jsonplaceholder.typicode.com as test API

---

### Callback (needed to capture response for all requests)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// libcurl calls this function as data arrives
// we append each chunk to a growing buffer
struct Response {
    char *data;
    size_t size;
};

size_t callback(void *ptr, size_t size, size_t nmemb, struct Response *res) {
    size_t total = size * nmemb;
    res->data = realloc(res->data, res->size + total + 1);
    memcpy(res->data + res->size, ptr, total);
    res->size += total;
    res->data[res->size] = '\0';
    return total;
}
```

---

### GET — read one todo
```c
void get_request() {
    CURL *curl = curl_easy_init();
    struct Response res = {malloc(1), 0};

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        CURLcode code = curl_easy_perform(curl);
        if (code != CURLE_OK)
            fprintf(stderr, "GET error: %s\n", curl_easy_strerror(code));
        else
            printf("GET response:\n%s\n\n", res.data);

        curl_easy_cleanup(curl);
        free(res.data);
    }
}
```

---

### POST — create a new todo
```c
void post_request() {
    CURL *curl = curl_easy_init();
    struct Response res = {malloc(1), 0};

    const char *body = "{\"title\": \"buy milk\", \"completed\": false, \"userId\": 1}";

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        CURLcode code = curl_easy_perform(curl);
        if (code != CURLE_OK)
            fprintf(stderr, "POST error: %s\n", curl_easy_strerror(code));
        else
            printf("POST response:\n%s\n\n", res.data);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(res.data);
    }
}
```

---

### PUT — update entire todo
```c
void put_request() {
    CURL *curl = curl_easy_init();
    struct Response res = {malloc(1), 0};

    const char *body = "{\"id\": 1, \"title\": \"updated title\", \"completed\": true, \"userId\": 1}";

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        CURLcode code = curl_easy_perform(curl);
        if (code != CURLE_OK)
            fprintf(stderr, "PUT error: %s\n", curl_easy_strerror(code));
        else
            printf("PUT response:\n%s\n\n", res.data);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(res.data);
    }
}
```

---

### PATCH — update part of a todo
```c
void patch_request() {
    CURL *curl = curl_easy_init();
    struct Response res = {malloc(1), 0};

    const char *body = "{\"completed\": true}";

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        CURLcode code = curl_easy_perform(curl);
        if (code != CURLE_OK)
            fprintf(stderr, "PATCH error: %s\n", curl_easy_strerror(code));
        else
            printf("PATCH response:\n%s\n\n", res.data);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(res.data);
    }
}
```

---

### DELETE — delete a todo
```c
void delete_request() {
    CURL *curl = curl_easy_init();
    struct Response res = {malloc(1), 0};

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        CURLcode code = curl_easy_perform(curl);
        if (code != CURLE_OK)
            fprintf(stderr, "DELETE error: %s\n", curl_easy_strerror(code));
        else
            printf("DELETE response:\n%s\n\n", res.data);

        curl_easy_cleanup(curl);
        free(res.data);
    }
}
```

---

### main.c (put it all together)
```c
int main() {
    get_request();
    post_request();
    put_request();
    patch_request();
    delete_request();
    return 0;
}
```

---

### Compile and run
```bash
gcc main.c -o main -lcurl && ./main

# pretty print json
gcc main.c -o main -lcurl && ./main | jq .
```

---

### Summary
```
GET     CURLOPT_URL + perform                  read
POST    CURLOPT_POSTFIELDS + Content-Type      create
PUT     CURLOPT_CUSTOMREQUEST "PUT"            replace entire resource
PATCH   CURLOPT_CUSTOMREQUEST "PATCH"          update part of resource
DELETE  CURLOPT_CUSTOMREQUEST "DELETE"         delete resource
```

