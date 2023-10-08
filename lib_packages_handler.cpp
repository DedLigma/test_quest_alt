#include "lib_packages_handler.h"

#include <curl/curl.h>
#include <curl/easy.h>

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json get_packages(std::string url);
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

int main_packages_handler(std::string url1, std::string url2, json& first_have_second_no,
                    json& first_no_second_have, json& version_release_difference) {
  const std::string base_url = "https://rdb.altlinux.org/api/export/branch_binary_packages";

  url1 = base_url + url1;
  json url1_data = get_packages(url1);

  if (url1_data == 1) {
    std::cout << "The export packages from the" << url1 << " was performed with errors!\n";
    return 1;
  }

  url2 = base_url + url2;
  json url2_data = get_packages(url2);

  if (url2_data == 1) {
    std::cout << "The export packages from the" << url2 << " was performed with errors!\n";
    return 1;
  }

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
      if (http_code == 200) {
        json response_json = json::parse(response);
        return response_json;
      } else {
        std::cout << "HTTP error - " << http_code << ".\n";
      }
    } else {
      std::cout << "Error by HTTP request.\n";
    }
  } else {
    std::cerr << "Error by libcurl initialization.\n";
  }
  return 1;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  size_t total_size = size * nmemb;
  static_cast<std::string*>(userp)->append(static_cast<char*>(contents), total_size);
  return total_size;
}
