#pragma once

#include <fstream>

#include "struct.h"
#include "funcWithFiles.cpp"

using namespace std;

#ifndef FUNC_WITH_FILES
#define FUNC_WITH_FILES

static fstream new_DB();
static void save_DB(laptops* lst);
static laptops* load_DB(laptops* tail);
static void clear();
static void remove_DB();

#endif // !FUNC_WITH_FILES