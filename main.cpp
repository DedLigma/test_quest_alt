#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "lib_packages_handler.h"

using json = nlohmann::json;

std::string url_slash(const std::string& url);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "No specified file!\n There may be many packages and all of them will be displayed in the "
                 "terminal.\n Are you sure you want to continue? [y/N] ";
    std::string answer;
    std::cin >> answer;
    if (answer != "y" && answer != "Y") return 0;
  }
  const char* filename = argv[1];

  std::string url1, url2;
  std::cout << "Enter first branch name (e.x. p10, /p10, sisyphus, etc.).\n";
  std::cin >> url1;
  std::cout << "Enter second branch name.\n";
  std::cin >> url2;
  url1 = url_slash(url1);
  url2 = url_slash(url2);

  json first_have_second_no, first_no_second_have, version_release_difference;
  if (main_packages_handler(url1, url2, first_have_second_no, first_no_second_have,
                            version_release_difference) == 1)
    return 0;




  return 0;
}

std::string url_slash(const std::string& url) {
  if (url[0] == '/')
    return url;
  else
    return '/' + url;
}
