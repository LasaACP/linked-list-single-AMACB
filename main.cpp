#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Airport {
    char    code[5];
    double  longitude;
    double  latitude;
};

double dist(const Airport&, const Airport&);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
    std::ifstream infile;
    int c = 0;
    char cNum[10];
    std::vector<Airport*> airportArr;
    int airportCount;

    Airport* aus;

    infile.open("./USAirportCodes.csv", std::ifstream::in);
    if (infile.is_open()) {
        // skip first line
        std::string dummyLine;
        getline(infile, dummyLine);
        for (; infile.good(); ++c) {
            Airport* airport = new Airport();
            airportArr.push_back(airport);
            infile.getline(airport->code, 256, ',');

            infile.getline(cNum, 256, ',');
            airport->longitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            airport->latitude = atof(cNum);

            if (strcmp(airport->code, "AUS") == 0) {
                std::cout << "AUS found" << std::endl;
                aus = airport;
            }
        }
        airportCount = c-1;
        infile.close();
    } else {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }

    std::cout << "Num airports: " << airportCount << std::endl;

    std::vector<Airport*> within_100;
    std::copy_if(airportArr.begin(), airportArr.end(), std::back_inserter(within_100), [aus] (Airport* a) {
        return dist(*aus, *a) <= 100;
    });
    auto max_iter = std::max_element(airportArr.begin(), airportArr.end(), [aus] (Airport* left, Airport* right) {
        return dist(*aus, *left) < dist(*aus, *right);
    });

    std::cout << "Max dist: " << (*max_iter)->code << " with distance " << dist(**max_iter, *aus) << std::endl;
    std::cout << "Within 100km: ";
    for (size_t i = 0; i < within_100.size(); ++i) {
        std::cout << within_100[i]->code << ",";
    }
    
    std::cout << std::endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

double deg2rad(double deg) {
    return (deg * pi / 180);
}
double rad2deg(double rad) {
    return (rad * 180 / pi);
}
double dist(const Airport& a, const Airport& b) {
    return distanceEarth(a.latitude, a.longitude, b.latitude, b.longitude);
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
