#pragma once
#ifndef DATA_H
#define DATA_H

#include<vector>
#include<string>
#include<filesystem>
#include<fstream>
#include"Book.h"

book getDataList(const std::string& filename);
std::string base64_encode(const std::string& in);

#endif
