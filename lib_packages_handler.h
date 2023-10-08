#ifndef PACKAGES_HANDLER_LIB_H
#define PACKAGES_HANDLER_LIB_H

#include <nlohmann/json.hpp>

int main_packages_handler(std::string url1, std::string url2, nlohmann::json& first_have_second_no,
                    nlohmann::json& first_no_second_have, nlohmann::json& version_release_difference);

#endif  
