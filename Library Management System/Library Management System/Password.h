#pragma once
#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <fstream>
#include <filesystem>

std::string base64_encode(const std::string& in); //converts normal ASCII to base64
void savePassword(const std::string& newPasswword); //saves password into text file
bool checkPassword(const std::string& toCheck); //checks the validity of password

#endif