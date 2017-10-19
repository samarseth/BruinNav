#ifndef support_h
#define support_h
#include "provided.h"
#include <string>
using namespace std;
class GeoCoord;
bool operator==(const GeoCoord &a, const GeoCoord& other);
bool operator<(const GeoCoord& a, const GeoCoord& other);
bool operator>(const GeoCoord&a, const GeoCoord& other);

#endif /* support_h */
