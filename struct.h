#include <limits>
#include <string>

using namespace std;

#ifndef STRUCT_LAPTOPS
#define STRUCT_LAPTOPS

struct laptops {
    char firmware[100];
    char model[100];
    float price;
    char processor[100];
    int RAM_Volume;
    int diskVolume;
    char videocard[100];
    float screenSize;
    int availability;
    laptops* prev = nullptr;
    laptops* next = nullptr;
};
#endif // !STRUCT_LAPTOPS