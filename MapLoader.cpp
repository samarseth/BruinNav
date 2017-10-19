#include "provided.h"
#include <string>
#include <vector>
#include "MyMap.h"
#include <fstream>
#include <iostream>

using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    vector<StreetSegment> storeData;
    string dataInLine;
    string m_mapFile;
    StreetSegment streetSeg;
};

MapLoaderImpl::MapLoaderImpl()
{}

MapLoaderImpl::~MapLoaderImpl()
{}

bool MapLoaderImpl::load(string mapFile) // loads the file and returns a boolean which indicates whether the file was loaded or not
{
    string s; // string holds the line
    
    ifstream dataFile(mapFile); // used to load the data file
    
    if (!dataFile)
        return false;
    while (getline(dataFile,s))
    {
        StreetSegment seg;
        string name=s;
        seg.streetName=s;
        
        string checker[4]; // declares a 4 membered array of strings
        
        char a; 
        int n=0;
        string cd;
        while(dataFile.get(a) && a!='\n') // checks for the end of a line 
        {
            if (a==' '|| a==',')
            {
                dataFile.get(a);
                
                if (a==' ') // checks for a space
                {
                    checker[n]=cd;
                    cd="";
                    n++;
                    continue;
                }
                else
                {
                    checker[n]=cd;
                    cd="";
                    cd+=a;
                    n++;
                    continue;
                }
            }
            cd+=a;
        }
        checker[n]=cd;
        GeoCoord start(checker[0],checker[1]); // initializes a new GoeCoord with checker[0] as start and checker[1] as end
        GeoCoord end(checker[2],checker[3]);
        GeoSegment geo(start, end);
        seg.segment=geo;
        int k;
        dataFile>>k;
        dataFile.get(a);
        for(int i=0; i<k; i++)
        {
            Attraction a;
            string nameA, lata, longi;
            char b;
            while(dataFile.get(b) && b!='\n')
            {
                if (b=='|')
                {
                    while(dataFile.get(b) && b!=',')
                    {
                        lata+=b;
                    }
                    while(dataFile.get(b) && b!='\n')
                    {
                        longi+=b;
                    }
                    break;
                }
                nameA+=b;
            }
            a.name=nameA;
            GeoCoord g(lata, longi);
            a.geocoordinates=g;
            seg.attractions.push_back(a);
        }
        storeData.push_back(seg);
    }
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
    return storeData.size();
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    
    if (segNum < getNumSegments()-1)
    {
        seg = storeData[segNum];
        return true;
    }
	return false;  // This compiles, but may not be correct
}





//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}


//int main()
//{
//    MapLoaderImpl map;
//    
//    map.load("/Users/samarseth/Desktop/dataFile.txt");
//    
//    StreetSegment seg;
//    
//    map.getSegment(107, seg);
//    
//    cout<<seg.streetName<<endl;
//    
//    cout<<seg.attractions[0].name<<endl;
//    cout << seg.attractions[0].geocoordinates.latitudeText << endl;
//    cout << seg.attractions[0].geocoordinates.longitudeText << endl;
//    cout << seg.attractions[0].geocoordinates.latitude << endl;
//    cout << seg.attractions[0].geocoordinates.longitude << endl;
//    int counter = 0;
//    
//    for (int i = 0; i< map.getNumSegments(); i++)
//    {
//        StreetSegment s;
//        map.getSegment(i, s);
//        counter+= s.attractions.size();
//    }
//    cout << counter << endl;
//    
//    MapLoader m;
//    m.load("/Users/samarseth/Desktop/dataFile.txt");
//    AttractionMapper a;
//    a.init(m);
//}

//int main()
//{
//    MapLoader ml;
//    ml.load("");
//}
