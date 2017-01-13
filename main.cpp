#include <iostream>
#include <fstream>
#include <cmath> 
#include <vector>
#include "slist.h"

using namespace std;

class Airport
{
public:
    char	code[5];
    double	longitude;
    double	latitude;
    
};

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main()
{
    ifstream infile;
    int i = 0;
    char cNum[10] ;
    LinkedList<Airport*> airportArr;
    int airportCount;
	int c = 0;
	
	Airport* aus;
    
    infile.open ("./USAirportCodes.csv", ifstream::in);
    if (infile.is_open()) {
    	// skip first line
    	string dummyLine;
    	getline(infile, dummyLine);
        while (infile.good()) {
        	Airport* airport = new Airport();
            airportArr.push(airport);
            infile.getline(airport->code, 256, ',');
            
            infile.getline(cNum, 256, ',');
            airport->longitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            airport->latitude = atof(cNum);
            
            if (strcmp(airport->code,"AUS") == 0) {
            	cout << "AUS found" << endl;
            	aus = airport;
            }
            ++i, ++c;
        }
        airportCount = c-1;
        infile.close();
    }
    else
    {
        cout << "Error opening file";
    }
    
    cout << "Num airports: " << airportCount << endl;
    Airport* max = aus;
    double max_d = 0;
    vector<Airport*> within_100;
    for (int i = 0; i < airportArr.size(); ++i) {
    	Airport* current = airportArr[i];
    	if (current != aus) {
    		double dist = distanceEarth(aus->longitude, aus->latitude, current->longitude, current->latitude);
    		if (dist > max_d) {
    			max = current;
    			max_d = dist;
    		}
    		if (dist <= 100) {
    			within_100.push_back(current);
    		}
    	}
    }
    cout << "Max dist: " << max->code << " with distance " << max_d << endl;
    cout << "Within 100km: ";
    for (int i = 0; i < within_100.size(); ++i) {
    	cout << within_100[i]->code << ",";
    }
    
}



#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

double deg2rad(double deg) {
  return (deg * pi / 180);
}
double rad2deg(double rad) {
  return (rad * 180 / pi);
}
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}