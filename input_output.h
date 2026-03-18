#pragma once

#include "struct.h"
#include "input_output.cpp"

using namespace std;

#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

static laptops* addLaptop(laptops* tail);
static void printLaptop(laptops* lst);
static void printList(laptops* lst);
static void changeElem(laptops* head, int position);

#endif // !INPUT_OUTPUT