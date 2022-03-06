#pragma once
#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <fstream>
#include <filesystem>

std::string base64_encode(const std::string& in);
void savePassword(const std::string& newPasswword);
bool checkPassword(const std::string& toCheck);

#endif