#include "provided.h"
#include <string>
#include <vector>
#include <list>
#include "MyMap.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
    int route_node(void);
    int addChildrenToFringe(GeoCoord entry);
    int listroute(void);
    MyMap<string, GeoCoord> closed_list_nodes; 
    AttractionMapper a;
    SegmentMapper b;
    class Node
    {
    public:
        GeoCoord g;
        double priority;
        double distanceTravelled;
        vector<NavSegment> navSegs;
        
        void updatePriority(double d, GeoCoord destination)
        {}
    };
    map<Node, Node> fringe_list_nodes;
    string angleToDirection(GeoSegment gs) const
    {
        double angle = angleOfLine(gs);
        string directionMoved;
        if(angle >=0 && angle <= 22.5)
            directionMoved = "east";
        else if(angle > 22.5 && angle <= 67.5)
            directionMoved = "northeast";
        else if(angle > 67.5 && angle <= 112.5)
            directionMoved = "north";
        else if(angle > 112.5 && angle <= 157.5)
            directionMoved = "northwest";
        else if(angle > 157.5 && angle <= 202.5)
            directionMoved = "west";
        else if(angle > 202.5 && angle <= 247.5)
            directionMoved = "southwest";
        else if(angle > 247.5 && angle <= 292.5)
            directionMoved = "south";
        else if(angle > 292.5 && angle <= 337.5)
            directionMoved = "southeast";
        else if(angle > 337.5 && angle <= 360)
            directionMoved = "east";
        return directionMoved;
    }
    
//    map<Node, Node> 
    
};

NavigatorImpl::NavigatorImpl()
{}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    MapLoader ml;
    bool c = ml.load(mapFile);
    a.init(ml);
    SegmentMapper b;
    b.init(ml);
    if (c) {
        return true;
    }
    return false;  
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    
    GeoCoord geo;
    a.getGeoCoord(start, geo);
    if (!a.getGeoCoord(start, geo))
        return NAV_BAD_SOURCE;
    GeoCoord geo2;
    a.getGeoCoord(end, geo2);
    if (!a.getGeoCoord(end, geo2))
        return NAV_BAD_DESTINATION;
    
    double tdist = distanceEarthMiles(geo, geo2);
    //    double angle = angleBetween2Lines(geo,geo2);
    
    vector<StreetSegment> StartGeoCoord;
    StartGeoCoord = b.getSegments(geo);
    
//    fringe_list_nodes.push_back(geo);
//    int i = route_node();
    
    /* Now closed list has a route from source to destination but other nodes are there */
    /* in the tree. So for the route start from end & got to first */
    /* Now use tree Mymap  */
    return NAV_NO_ROUTE;
}


//
int NavigatorImpl::route_node()
{
    GeoCoord entry;
    vector<StreetSegment> temp = b.getSegments(entry);
    if (fringe_list_nodes.empty())
    {
        return 0; /* No route - to destination */
    }
    /* Check if attaction is in the same segment - Compute distance later */
    /* Check by String - Segement Name & Attaction Name in map table */
    /* This is the final destination  Do the mapping latter */
    else 
    {
//        closed_list_nodes.add(entry);
        addChildrenToFringe(entry);
        return route_node();
    }
    return 0;
}
 

int NavigatorImpl::addChildrenToFringe(GeoCoord entry)
{
    // Each segement contains start & end
    /* Get the segement Start point Node - for attraction there is 1 segment 1 start, 1 end */  
    vector<StreetSegment> seg = b.getSegments(entry) ; /* There is only 1 Street in this vector */
    
    struct dist_n {
        GeoCoord node;
        double dist;
    } dist_node[100]; // make this a list
    MapLoader ml;
//    double pdist =  distanceEarthMiles(entry,end); /* Distance between parant & end */
//    for (int no_ent=0, i =0 ; seg.getNumSegments() ; i++) 
//    {
//        int i =0;
//        StreetSegment st =  ml.getSegment(i, seg) ; 
        /* Do not add the same node again */
//        if ( (st.start == entry ) || (st.end == entry) )
//        {}

    int no_ent = 0;
//        double ddist = pdist +  distanceEarthMiles(st.start, entry); /* Distance between parant & Child */
//        double l2dist = distanceEarthMiles(st.start, geo2);   /* Distance between child & goal */
//        dist_node[no_ent].node = st;
//        dist_node[no_ent].dist = ddist + l2dist;
        no_ent++;
//    } 
    /* Sort dist_node in ascending order */
//    for (i=0; i <  no_ent; i++) { // can make a lis as well
        /* Place holder for sorting of dist_node */
        /* Chnage to list template, and then simply call list.sort() */
    
    return no_ent;
}
    /* Add to fringe list */
//    for (i=0; i < no_ent; i++ ) {
//        fringe_list_nodes.push_back(dist_node[i]);
//    }
    /* Get the segment End point */
 

int NavigatorImpl::listroute(void)
{
    /* Browse the list from bottom up */
    return 0;
    
}
//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
