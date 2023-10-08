#include <curl/curl.h>
#include <curl/easy.h>

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

json get_packages(std::string url);
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

int main() {
  const std::string base_url = "https://rdb.altlinux.org/api/export/branch_binary_packages";
  std::string url1 = "/p10";
  url1 = base_url + url1;
  json aaa = get_packages(url1);
  std::cout << aaa;

  return 0;
}

json get_packages(std::string url) {
  CURL* curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    std::string response;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
      long http_code = 0;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
      // if (http_code == 0) {
      json ans = json::parse(response);
      return ans;
      // } else {
      // std::cout << "HTTP error - " << http_code << ".\n";
      // }
    }
  } else {
    std::cerr << "Error by libcurl initialization.\n";
  }
  return -1;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  size_t total_size = size * nmemb;
  static_cast<std::string*>(userp)->append(static_cast<char*>(contents), total_size);
  return total_size;
}
