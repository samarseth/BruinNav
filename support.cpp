//
//  support.cpp
//  CS32Proj4
//
//  Created by Samar Seth on 3/16/17.
//  Copyright © 2017 Samar Seth. All rights reserved.
//

#include "provided.h"
#include <stdio.h>
#include "support.h"


bool operator==(const GeoCoord &src, const GeoCoord &other) 
{
    if (other.latitude == src.latitude && other.longitude == src.longitude)
        return true;
    return false;
}
bool operator>(const GeoCoord &src, const GeoCoord &other) 
{
    if (src.latitude == other.latitude)
        return src.longitude > other.longitude;
    return src.latitude > other.latitude;
}
bool operator<(const GeoCoord &src, const GeoCoord &other)
{
    if (src.latitude == other.latitude)
        return src.longitude < other.longitude;
    return src.latitude < other.latitude;
}
