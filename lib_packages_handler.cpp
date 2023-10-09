#include "lib_packages_handler.h"

#include <curl/curl.h>
#include <curl/easy.h>

#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void get_version_release_difference(const json& first_data, const json& second_data, json& result,
                                    std::string message);
void get_unique_packages(const json& first_data, const json& second_data, json& result, std::string message);
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

  get_unique_packages(url1_data, url2_data, first_have_second_no, "Unique packages in 1st branch progress: ");
  get_unique_packages(url1_data, url2_data, first_no_second_have, "Unique packages in 2nd branch progress: ");
  get_version_release_difference(url1_data, url2_data, version_release_difference,
                                 "Version release difference packages progress: ");

  return 0;
}

void get_version_release_difference(const json& first_data, const json& second_data, json& result,
                                    std::string message) {
  result["length"] = 0;
  result["packages"] = json::array();

  for (size_t i = 0; i < first_data["packages"].size(); i++) {
    bool is_found = false;
    for (const auto& element2 : second_data["packages"]) {
      if (first_data["packages"][i]["arch"] == element2["arch"] &&
          first_data["packages"][i]["disttag"] == element2["disttag"] &&
          first_data["packages"][i]["name"] == element2["name"] &&
          first_data["packages"][i]["release"] == element2["release"] &&
          first_data["packages"][i]["source"] == element2["source"] &&
          first_data["packages"][i]["version"] > element2["version"]) {
        is_found = true;
        break;
      }
    }
    if (is_found) {
      result["packages"].push_back(first_data["packages"][i]);
    }
    double progress = static_cast<double>(i) / first_data["packages"].size() * 100.0;
    std::cout << message << std::fixed << std::setprecision(2) << progress << "%\r";
    std::cout.flush();
  }
  std::cout << '\n';
  result["length"] = result["packages"].size();
}

void get_unique_packages(const json& first_data, const json& second_data, json& result, std::string message) {
  result["length"] = 0;
  result["packages"] = json::array();

  for (size_t i = 0; i < first_data["packages"].size(); i++) {
    bool is_found = false;
    for (const auto& element2 : second_data["packages"]) {
      if (first_data["packages"][i] == element2) {
        is_found = true;
        break;
      }
    }
    if (!is_found) {
      result["packages"].push_back(first_data["packages"][i]);
    }
    double progress = static_cast<double>(i) / first_data["packages"].size() * 100.0;
    std::cout << message << std::fixed << std::setprecision(2) << progress << "%\r";
    std::cout.flush();
  }
  std::cout << '\n';
  result["length"] = result["packages"].size();
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
