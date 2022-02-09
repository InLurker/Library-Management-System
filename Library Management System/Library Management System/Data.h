#pragma once
#ifndef DATA_H
#define DATA_H

#include<vector>
#include<string>
#include<filesystem>
#include<fstream>
#include"Book.h"

using namespace std;

book getDataList(string filename);

#endif