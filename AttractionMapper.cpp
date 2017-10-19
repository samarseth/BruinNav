#include "provided.h"
#include <string>
#include "MyMap.h"
#include <cctype>
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> mapVar;
};

AttractionMapperImpl::AttractionMapperImpl()
{}

AttractionMapperImpl::~AttractionMapperImpl()
{}

void AttractionMapperImpl::init(const MapLoader& ml) // used to initialize teh attraction mapper class
{
    StreetSegment seg;
    for(int i = 0; i < ml.getNumSegments(); i++)
    {    
        ml.getSegment(i, seg);
        for (int k = 0; k < seg.attractions.size(); k++)
        {
            string temp;
            for (int j = 0; j< seg.attractions[k].name.size(); j++)
            {
              temp += tolower(seg.attractions[k].name[j]); // converts the attraction mapper name to lowercase
            }
//            cout << temp;
//            cout << seg.attractions[k].geocoordinates.latitudeText << endl;
            mapVar.associate(temp, seg.attractions[k].geocoordinates);
        }
    }
//    cerr << mapVar.size() << endl;
}
bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const // copies the geocoord associate with taht attraction into the GeoCoord that is passes in as a parameter
{
    for (int i=0; i<attraction.size(); i++)
    {
        attraction[i]=tolower(attraction[i]);
    }
    const GeoCoord * gcTemp= mapVar.find(attraction); // uses the find function of myMap to find the required node of the BST
    if (gcTemp != nullptr) // only executes this block if the pointer is not nullptr
    {
        gc.latitude = (*gcTemp).latitude;
        gc.latitudeText = (*gcTemp).latitudeText;
        gc.longitude = (*gcTemp).longitude;
        gc.longitudeText = (*gcTemp).longitudeText;
        return true; // returns true if the new geocoord is loaded into the one passed in as a parameter
    }
	return false;  // This compiles, but may not be correct
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}


