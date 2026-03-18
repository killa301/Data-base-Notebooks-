#pragma once
#include "struct.h"
#include "deleteStruct.cpp"

using namespace std;

#ifndef DELETE_STRUCT
#define DELETE_STRUCT

static laptops* deleteList(laptops* lst);
static laptops* deleteElem(laptops* lst, int position);

#endif // !DELETE_STRUCT

