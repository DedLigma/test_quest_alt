#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "lib_packages_handler.h"

using json = nlohmann::json;

std::string url_slash(const std::string& url);

int main(int argc, char* argv[]) {
  std::string filename_first_have = "first_have.json";
  std::string filename_second_have = "second_have.json";
  std::string filename_release_difference = "release_difference.json";
  if (argc < 4) {
    std::cout << "Not all files have been specified. 3 files (first_have.json, second_have.json, "
                 "release_difference.json) will be created and REWRITTED. Do you want to continue? [y/N] ";
    std::string answer;
    std::cin >> answer;
    if (answer != "y" && answer != "Y") return 0;
  } else {
    filename_first_have = argv[1];
    filename_second_have = argv[2];
    filename_release_difference = argv[3];
  }

  std::string branch1, branch2;
  std::cout << "Enter first branch name (e.g. p10, /p10, sisyphus, etc.).\n";
  std::cin >> branch1;
  std::cout << "Enter second branch name.\n";
  std::cin >> branch2;
  std::string url1 = url_slash(branch1);
  std::string url2 = url_slash(branch2);
  
  if(url1 == url2) {
    std::cout << "Error! The branch names are the same.\n";
    return 0;
  }

  json first_have_second_no, first_no_second_have, version_release_difference;
  if (main_packages_handler(url1, url2, first_have_second_no, first_no_second_have,
                            version_release_difference) == 1)
    return 0;

  std::ofstream file_first_have(filename_first_have);
  if (file_first_have.is_open()) {
    file_first_have << first_have_second_no.dump(2);
    file_first_have.close();
    std::cout << "All packages that are in " << branch1 << " but not in " << branch2 << " were written to "
              << filename_first_have << " successfully.\n";
  } else {
    std::cout << "Error by opening " << filename_first_have << '\n';
  }

  std::ofstream file_second_have(filename_second_have);
  if (file_second_have.is_open()) {
    file_second_have << first_no_second_have.dump(2);
    file_second_have.close();
    std::cout << "All packages that are in " << branch2 << " but not in " << branch1 << " were written to "
              << filename_second_have << " successfully.\n";
  } else {
    std::cout << "Error by opening " << filename_second_have << '\n';
  }

  std::ofstream file_release_difference(filename_release_difference);
  if (file_release_difference.is_open()) {
    file_release_difference << version_release_difference.dump(2);
    file_release_difference.close();
    std::cout << "all packages whose version release version is larger in the " << branch1 << " than in the "
              << branch2 << " were written to " << filename_release_difference << " successfully.\n";
  } else {
    std::cout << "Error by opening " << filename_release_difference << '\n';
  }

  return 0;
}

std::string url_slash(const std::string& branch) {
  if (branch[0] == '/')
    return branch;
  else
    return '/' + branch;
}
