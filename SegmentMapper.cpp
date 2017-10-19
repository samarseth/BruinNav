#include "provided.h"
#include <vector>
#include "MyMap.h"
#include "support.h"
using namespace std;



// remember to put the GeoCoord operation overload in the support thingy

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<GeoCoord,vector<StreetSegment>> mapVar2; 
};

SegmentMapperImpl::SegmentMapperImpl()
{}

SegmentMapperImpl::~SegmentMapperImpl()
{}

void SegmentMapperImpl::init(const MapLoader& ml) // initializes the SegmentMapper
{
    for (int i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment seg;
        ml.getSegment(i, seg);
        
        if(mapVar2.find(seg.segment.end) != nullptr) // checks in mapVar2 whether that was found or not
        {
            mapVar2.find(seg.segment.end)->push_back(seg); 
        }
        else
        {
            vector<StreetSegment> storeData2;
            storeData2.push_back(seg);
            mapVar2.associate(seg.segment.end,storeData2);
        }
        if(mapVar2.find(seg.segment.start) != nullptr)
        {
            mapVar2.find(seg.segment.start)->push_back(seg); 
        }
        else
        {
            vector<StreetSegment> storeData;
            storeData.push_back(seg);
            mapVar2.associate(seg.segment.start, storeData);
        }
        if (seg.attractions.size() > 0) // if attractions are present in the vector
        {
            for (int k = 0; k <seg.attractions.size(); k++)
            {
            if(mapVar2.find(seg.attractions[k].geocoordinates) != nullptr) // if the attraction is found in the custom made BST
                {
                    mapVar2.find(seg.attractions[k].geocoordinates)->push_back(seg);
                }
            else
                {
                    vector<StreetSegment> storeData3;
                    storeData3.push_back(seg);
                    mapVar2.associate(seg.attractions[k].geocoordinates, storeData3);
                }
           }
        }
    }
     
}
vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
   
    const vector<StreetSegment> * tempStuff = mapVar2.find(gc); // finds the association of GeoCoord gc in the BST
    vector<StreetSegment> segments;
    if(tempStuff!=nullptr) // checks whether tempStuff is a nullptr or not
        return *mapVar2.find(gc);
    return segments; // return a vector of StreetSegment

}
//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}
vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
