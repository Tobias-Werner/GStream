//
// Created by tobias on 14.06.18.
//

#include "data_types/Geometry.h"
#include <make_unique.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace STREAM;

Geometry::Geometry() {
    auto bytes = createHeader(POINT, 0, false, false, false, false, true);
}

bool Geometry::isEmpty() {
    return data[1] & 0x10;
}

std::vector<u_char> Geometry::asTWKB() const {
    return this->data;
}

Geometry::Geometry(const STREAM::Geometry &other) {
    this->data.insert(this->data.begin(), other.data.begin(), other.data.end());
}

Geometry::Geometry(const void *twkb, size_t size) {
    const auto bytes = static_cast<const unsigned char *>(twkb);
    this->data = vector<u_char>(bytes, bytes + size);
}

Geometry::Geometry(const string &wkt_str, const signed char &precisionXY) {
    try {

        const char *current = wkt_str.c_str();
        const char *begin = current;
        char *end_double;

        while (*current == ' ') current++; // Eliminate whitespaces

        // Check if its a point geometry
        if (*current++ == 'P' &&
            *current++ == 'O' &&
            *current++ == 'I' &&
            *current++ == 'N' &&
            *current++ == 'T') {

            while (*current == ' ') current++; // Eliminate whitespaces

            if (*current == '(') current++;

            while (*current == ' ') current++; // Eliminate whitespaces

            double x = strtod(current, &end_double);
            current = end_double;
            double y = strtod(current, &end_double);
            current = end_double;

            while (*current == ' ') current++; // Eliminate whitespaces

            if (*current == ')') {
                bytes_t twkb = createHeader(POINT, precisionXY, false, false, false, false, false);
                auto locations = encode(Vector2D(x, y), precisionXY);
                append(twkb, locations);

                this->data = vector<u_char>{twkb.begin(), twkb.end()};
                //this->data = move(vector<u_char>{make_move_iterator(twkb.begin()), make_move_iterator(twkb.end())});
            }

        } else {
            current = begin;
            if (*current++ == 'M' &&
                *current++ == 'U' &&
                *current++ == 'L' &&
                *current++ == 'T' &&
                *current++ == 'I' &&
                *current++ == 'P' &&
                *current++ == 'O' &&
                *current++ == 'I' &&
                *current++ == 'N' &&
                *current++ == 'T') {

                while (*current == ' ') current++; // Eliminate whitespaces

                if (*current == '(') current++;

                while (*current == ' ') current++; // Eliminate whitespaces

                std::list<int32_t> coordinates;


                while (true) {
                    double x = strtod(current, &end_double);
                    int32_t xShrinked = shrink(x, precisionXY);
                    coordinates.push_back(xShrinked); // x

                    current = end_double;
                    double y = strtod(current, &end_double);
                    int32_t yShrinked = shrink(y, precisionXY);
                    coordinates.push_back(yShrinked); // y
                    current = end_double;

                    while (*current == ' ') current++; // Eliminate whitespaces
                    if (*current != ',') break;
                    else current++;
                }

                if (*current == ')') {
                    bytes_t twkb = createHeader(MULTIPOINT, precisionXY, false, false, false, false, false);

                    auto bytes = Geometry::encodeVarint(coordinates.size() / 2);
                    append(twkb, bytes);

                    auto it = coordinates.begin();
                    auto end = coordinates.end();

                    auto x = *it++;
                    auto y = *it++;

                    auto zigZagX = encodeZigZag(x);
                    auto zigZagY = encodeZigZag(y);

                    auto varintX = encodeVarint(zigZagX);
                    auto varintY = encodeVarint(zigZagY);

                    append(twkb, varintX);
                    append(twkb, varintY);

                    int32_t xPrev = x;
                    int32_t yPrev = y;

                    while (true) {

                        x = *it++;
                        y = *it++;

                        int32_t xDiff = x - xPrev;
                        int32_t yDiff = y - yPrev;

                        zigZagX = encodeZigZag(xDiff);
                        zigZagY = encodeZigZag(yDiff);

                        varintX = encodeVarint(zigZagX);
                        varintY = encodeVarint(zigZagY);

                        append(twkb, varintX);
                        append(twkb, varintY);

                        xPrev = x;
                        yPrev = y;

                        if (it == end)
                            break;
                    }

                    this->data = vector<u_char>{twkb.begin(), twkb.end()};

                }

            }
        }
    } catch (exception ex) {
        cout << "Error: " << ex.what() << endl;
    }

}

Geometry::Geometry(const string &wkt_str, const signed char &precisionXY, const u_char &precisionZ) {
    try {

        const char *current = wkt_str.c_str();
        const char *begin = current;
        char *end_double;

        while (*current == ' ') current++; // Eliminate whitespaces

        // Check if its a point geometry
        if (*current++ == 'P' &&
            *current++ == 'O' &&
            *current++ == 'I' &&
            *current++ == 'N' &&
            *current++ == 'T') {

            while (*current == ' ') current++; // Eliminate whitespaces

            if (*current == '(') current++;

            while (*current == ' ') current++; // Eliminate whitespaces

            double x = strtod(current, &end_double);
            current = end_double;
            double y = strtod(current, &end_double);
            current = end_double;
            double z = strtod(current, &end_double);
            current = end_double;

            while (*current == ' ') current++; // Eliminate whitespaces

            if (*current == ')') {
                bytes_t twkb = createHeader(POINT, precisionXY, false, false, false, true, false, precisionZ);
                auto locations = encode(Vector3D(x, y, z), precisionXY, static_cast<signed char>(precisionZ));
                append(twkb, locations);

                this->data = move(vector<u_char>{make_move_iterator(twkb.begin()), make_move_iterator(twkb.end())});
            }

        }
    } catch (exception ex) {
        cout << "Error: " << ex.what() << endl;
    }

}

Geometry::Geometry(const string &wkt_str, const signed char &precisionXY, const u_char &precisionZ,
                   const u_char &precisionT) {
    try {

        const char *current = wkt_str.c_str();
        const char *begin = current;
        char *end_double;

        while (*current == ' ') current++; // Eliminate whitespaces

        // Check if its a point geometry
        if (*current++ == 'P' &&
            *current++ == 'O' &&
            *current++ == 'I' &&
            *current++ == 'N' &&
            *current++ == 'T') {

            while (*current == ' ') current++; // Eliminate whitespaces

            if (*current == '(') current++;

            while (*current == ' ') current++; // Eliminate whitespaces

            double x = strtod(current, &end_double);
            current = end_double;
            double y = strtod(current, &end_double);
            current = end_double;
            double z = strtod(current, &end_double);
            current = end_double;
            double t = strtod(current, &end_double);
            current = end_double;

            while (*current == ' ') current++; // Eliminate whitespaces

            if (*current == ')') {

                bytes_t twkb = createHeader(POINT, precisionXY, false, false, false, true, false, precisionZ,
                                            precisionT);
                auto locations = encode(Vector4D(x, y, z, t), precisionXY, static_cast<signed char>(precisionZ),
                                        static_cast<signed char>(precisionT));
                append(twkb, locations);

                this->data = move(vector<u_char>{make_move_iterator(twkb.begin()), make_move_iterator(twkb.end())});
            }


        }
    } catch (exception ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

string Geometry::asWKT() {
    try {

        auto bytePtr = data.begin();

        stringstream stream;

        u_char type = (0x0F & *bytePtr);
        int32_t precisionXY = decodeZigZag(0x0F & (*bytePtr >> 4));

        bytePtr++;

        bool bbox = (*bytePtr & 0x01);
        bool sizes = (*bytePtr & 0x02);
        bool idlist = (*bytePtr & 0x04);
        bool extendedDimensions = (*bytePtr & 0x08);
        bool emptyGeom = (*bytePtr & 0x10);

        bytePtr++;

        switch (type) {
            case POINT: {
                stream << "POINT (";

                if (extendedDimensions) {


                    // Z dimension
                    if (*bytePtr & 0x01) {


                    }

                    // Z and T dimension
                    if (*bytePtr & 0x02) {

                    }

                } else {

                    auto x = readDouble(bytePtr, precisionXY);
                    auto y = readDouble(bytePtr, precisionXY);

                    stream << setprecision(precisionXY) << fixed << x << " " << y;
                }

                stream << ")";

                break;
            }
            case LINESTRING:
                stream << "LINESTRING (";
                break;

            case MULTIPOINT :
                stream << "MULTIPOINT (";
                if (extendedDimensions) {


                    // Z dimension
                    if (*bytePtr & 0x01) {


                    }

                    // Z and T dimension
                    if (*bytePtr & 0x02) {

                    }

                } else {

                    auto numPoints = readUnsignedInt(bytePtr);

                    double x = readDouble(bytePtr, precisionXY);
                    double y = readDouble(bytePtr, precisionXY);

                    stream << setprecision(precisionXY) << fixed << x << " " << y;

                    for (size_t i = 1; i < numPoints; i++) {
                        x += readDouble(bytePtr, precisionXY);
                        y += readDouble(bytePtr, precisionXY);

                        stream << setprecision(precisionXY) << fixed << "," << x << " " << y;
                    }

                }

                stream << ")";

                auto s = stream.str();

                break;
        }

        return stream.str();
    }
    catch (exception ex) {
        cout << "Error: " << ex.what() << endl;
    }


    return "Error";
}

uint32_t Geometry::encodeZigZag(const int32_t &value) {
    return static_cast<uint32_t >((value << 1) ^ (value >> 31));
}

int32_t Geometry::decodeZigZag(const uint32_t &value) {
    return -(value & 1) ^ (value >> 1);
}

bytes_t Geometry::encode(const double &value, const signed char &precision) {
    return encodeVarint(encodeZigZag(Geometry::shrink(value, precision)));
}

void Geometry::append(bytes_t &twkb) {}

template<typename T, typename... Types>
void Geometry::append(bytes_t &twkb, const T &var1, const Types... var2) {
    twkb.insert(twkb.end(), var1.begin(), var1.end());
    append(twkb, var2...);
}


bytes_t Geometry::encode(const Vector2D &vector, const signed char &precisionXY) {

    bytes_t bytes;

    append(bytes, encode(vector.x, precisionXY));
    append(bytes, encode(vector.y, precisionXY));

    return bytes;
}

bytes_t Geometry::encode(const Vector3D &vector, const signed char &precisionXY, const u_char precisionZ) {

    auto bytes = encode(vector, precisionXY);
    append(bytes, encode(vector.z, precisionZ));

    return bytes;
}

bytes_t Geometry::encode(const Vector4D &vector, const signed char &precisionXY, const u_char precisionZ,
                         const u_char precisionT) {

    auto bytes = encode(vector, precisionXY, precisionZ);
    append(bytes, encode(vector.t, precisionT));

    return bytes;
}

int32_t Geometry::decodeVarint(const bytes_t &bytes) {

    int32_t result = 0x00;

    size_t i = bytes.size();
    for (auto elem = bytes.rbegin(); elem != bytes.rend(); ++elem, i--) {
        result |= (*elem & 0x7F);
        result <<= (i - 1 > 0) ? 7 : 0;
    }

    return result;
}

bytes_t Geometry::encodeVarint(uint32_t value) {
    bytes_t result;

    do {
        result.push_back(0x80 | (value & 0x7F));
        value >>= 7;
    } while (value > 0x00);

    result.back() &= 0x7F;

    return result;
}


bytes_t Geometry::createHeader(const u_char &type, const signed char &precisionXY, const bool &bbox, const bool &sizes,
                               const bool &idlist, const bool &extendedDimensions,
                               const bool &emptyGeom) {

    u_char header = type | encodeZigZag(precisionXY) << 4;
    bytes_t twkb({header});

    u_char metadataHeader = 0x00;
    metadataHeader |= (bbox) ? 0x01 : 0x00;
    metadataHeader |= (sizes) ? 0x02 : 0x00;
    metadataHeader |= (idlist) ? 0x04 : 0x00;
    metadataHeader |= (extendedDimensions) ? 0x08 : 0x00;
    metadataHeader |= (emptyGeom) ? 0x10 : 0x00;
    twkb.push_back(metadataHeader);

    return twkb;
}

bytes_t Geometry::createHeader(const u_char &type, const signed char &precisionXY, const bool &bbox, const bool &sizes,
                               const bool &idlist, const bool &extendedDimensions,
                               const bool &emptyGeom, const u_char &precisionZ) {

    auto twkb = createHeader(type, precisionXY, bbox, sizes, idlist, extendedDimensions, emptyGeom);
    u_char extendedInformation = 0x01;
    extendedInformation |= (precisionZ << 2);
    twkb.push_back(extendedInformation);
    return twkb;
}

bytes_t Geometry::createHeader(const u_char &type, const signed char &precisionXY, const bool &bbox, const bool &sizes,
                               const bool &idlist, const bool &extendedDimensions,
                               const bool &emptyGeom, const u_char &precisionZ, const u_char &precisionT) {

    auto twkb = createHeader(type, precisionXY, bbox, sizes, idlist, extendedDimensions, emptyGeom);
    u_char extendedInformation = 0x03;
    extendedInformation |= (precisionZ << 2);
    extendedInformation |= (precisionT << 5);
    twkb.push_back(extendedInformation);
    return twkb;
}

uint32_t Geometry::readUnsignedInt(vector<u_char>::iterator &iterator) {
    size_t countBytes = 0;
    uint32_t result = 0x00000000;

    while (*iterator & 0x80) {
        result |= ((*iterator) & 0x7F) << 7 * countBytes;
        iterator++;
        countBytes++;
    }

    result |= ((*iterator) & 0x7F) << 7 * countBytes;
    iterator++;

    return result;
}

double Geometry::readDouble(vector<u_char>::iterator &iterator, int32_t precision) {

    auto encoded = readUnsignedInt(iterator);
    auto decoded = (double) decodeZigZag(encoded);
    auto divisor = pow10(precision);
    auto re = decoded / divisor;

    return re;
}


uint32_t Geometry::pow10(uint8_t exponent) {
    static uint32_t pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    return pow10[exponent];
}

int32_t Geometry::shrink(const double &value, const signed char &precision) {

    const bool negative = (precision < 0);
    uint8_t p = (negative) ? static_cast<uint8_t>(-precision) : static_cast<uint8_t>(precision);
    auto unrounded = (negative) ? pow10(p) / value : pow10(p) * value;
    return static_cast<int32_t>(round(unrounded));
}


double Geometry::haversine(double lat1, double lon1, double lat2, double lon2) {

    double latRad1 = DegreeToRadian(lat1);
    double latRad2 = DegreeToRadian(lat2);
    double lonRad1 = DegreeToRadian(lon1);
    double lonRad2 = DegreeToRadian(lon2);

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    double computation = asin(
            sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * EarthRadiusKm * computation;
}

void Geometry::Local2Global(const double &lat, const double &lon, const double &northDiff, const double &eastDiff,
                            double &xDiff, double &yDiff, double &zDiff) {
    xDiff = -sin(lat) * cos(lon) * northDiff + -sin(lon) * eastDiff;
    yDiff = -sin(lat) * sin(lon) * northDiff + cos(lon) * eastDiff;
    zDiff = cos(lat) * northDiff;
}

void Geometry::XYZ2LatLon(const double &x, const double &y, const double &z, double &lat, double &lon) {

    double radius = 6372.8 * 1000;
    lon = atan2(y, x);
    lat = asin(z / radius);
}

void Geometry::LatLon2XYZ(const double &lat, const double &lon, double &x, double &y, double &z) {

    double radius = 6372.8 * 1000;
    x = cos(lon) * cos(lat) * radius;
    y = sin(lon) * cos(lat) * radius;
    z = sin(lat) * radius;
}

double Geometry::getDistance(Geometry *geom, Geometry *other) {
    int type1, type2;
    int dimension1, dimension2;
    int precision1, precision2;

    vector<u_char>::iterator it1;
    vector<u_char>::iterator it2;

    geom->readMetadata(it1, type1, dimension1, precision1);
    other->readMetadata(it2, type2, dimension2, precision2);

    if (dimension1 != dimension2 || type1 != type2) {
        // Error Handling
    } else {

        switch (dimension1) {
            case 2 : {

                switch (type1) {
                    case POINT : {

                        double lon1 = geom->readDouble(it1, precision1);
                        double lat1 = geom->readDouble(it1, precision1);
                        double lon2 = other->readDouble(it2, precision2);
                        double lat2 = other->readDouble(it2, precision2);

                        double distance = haversine(lat1, lon1, lat2, lon2);

                        return distance;

                    }
                    case LINESTRING: {

                        break;
                    }
                    case POLYGON: {

                        break;
                    }
                }
            }

            case 3 :
                break;
            case 4 :
                break;
            default:
                break;
        }
    }
    return 1.0;
}

void Geometry::result(AResultHandler &result_handler) {
    result_handler.add(*this);
}

unique_ptr<ADataType> Geometry::copy() {
    return make_unique<Geometry>(*this);
}

// geom: multipoint
// other: point
bool Geometry::pointOverlapsMultipoint(Geometry *multipoint, Geometry *point, const double tolerance) {

    int type1, type2;
    int dimension1, dimension2;
    list<double> coordinates1, coordinates2;

    multipoint->readMetadataAndCoordinates(type1, dimension1, coordinates1);
    point->readMetadataAndCoordinates(type2, dimension2, coordinates2);

    if (dimension1 != dimension2 || type1 != MULTIPOINT || type2 != POINT) {
        // Error Handling
    } else {

        switch (dimension1) {
            case 2 : {


                auto itPoint = coordinates2.begin();
                auto &latP = *itPoint++;
                auto &lonP = *itPoint;

                auto itMP = coordinates1.begin();

                while (itMP != coordinates1.end()) {

                    auto &latMP = *itMP++;
                    auto &lonMP = *itMP++;

                    if (haversine(latP, lonP, latMP, lonMP) < tolerance)
                        return true;

                }

                return false;
            }

            case 3 :
                break;
            case 4 :
                break;
            default:
                return false;
        }
    }
}

void Geometry::readMetadataAndCoordinates(int &type, int &dimension, std::list<double> &result) {
    int precision;
    vector<u_char>::iterator iterator;
    this->readMetadata(iterator, type, dimension, precision);
    this->readCoordinates(iterator, type, dimension, precision, result);
}

void Geometry::readMetadata(vector<u_char>::iterator &iterator, int &type, int &dimension, int &precision) {

    iterator = data.begin();

    type = *iterator & 0x0F;
    precision = (*iterator & 0xF0) >> 4;

    precision = decodeZigZag(precision);

    iterator++;
    dimension = (!(*iterator & 0x08)) ? 2 : (*(++iterator) & 0x02) ? 4 : 3;

    iterator++;

}

void Geometry::readCoordinates(vector<u_char>::iterator &iterator, int &type, int &dimension, int &precision,
                               std::list<double> &result) {

    switch (type) {
        case POINT: {
            for (size_t i = 0; i < dimension; i++)
                result.push_back(readDouble(iterator, precision));
        }
            break;
        case LINESTRING:
            break;
        case POLYGON:
            break;
        case MULTIPOINT: {

            auto numPoints = readUnsignedInt(iterator);

            vector<double> coordinates(dimension, 0.0);

            for (size_t i = 0; i < numPoints; i++)
                for (size_t j = 0; j < dimension; j++) {
                    coordinates[j] += readDouble(iterator, precision);
                    result.push_back(coordinates[j]);
                }
        }
            break;
    }

}



















