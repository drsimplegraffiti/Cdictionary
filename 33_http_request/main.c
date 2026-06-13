
#include <curl/curl.h>
#include <stdio.h>

int main() {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(
        // curl, CURLOPT_URL,
        // "https://api.weatherapi.com/v1/current.json?key=YOUR_API_KEY&q=Lagos");

        curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl error: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }
  return 0;
}

// sudo apt install libcurl4-openssl-dev
// gcc main.c -o main -lcurl && ./main
// gcc main.c -o main -lcurl && ./main | jq .
