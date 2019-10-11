//
// Created by tobias on 14.06.18.
//

#ifndef STREAMS_STREAM_GEOM_H
#define STREAMS_STREAM_GEOM_H

#include "ADataType.h"
#include <list>
#include <vector>
#include <math.h>


namespace STREAM {

    using bytes_t = std::list<uint8_t>;

    enum GeomType {
        POINT = 0x01,
        LINESTRING = 0x02,
        POLYGON = 0x03,
        MULTIPOINT = 0x04
    };

    class Vector2D {

    public:
        double x, y;

        Vector2D() : x(0.0), y(0.0) {}

        Vector2D(double x, double y) : x(x), y(y) {}

        Vector2D(const Vector2D &other) : Vector2D(other.x, other.y) {}

        Vector2D operator-(Vector2D &rhs) {
            return Vector2D(this->x - rhs.x, this->y - rhs.y);
        }

        Vector2D operator+(Vector2D &rhs) {
            return Vector2D(this->x + rhs.x, this->y + rhs.y);
        }


    };

    class Vector3D : public Vector2D {

    public:
        double z;

        Vector3D() : Vector2D(0.0, 0.0), z(0.0) {}

        Vector3D(double x, double y, double z) : Vector2D(x, y), z(z) {}

        Vector3D operator-(Vector3D &rhs) {
            return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
        }

        Vector3D operator+(Vector3D &rhs) {
            return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
        }

    };

    class Vector4D : public Vector3D {

    public:
        double t;

        Vector4D() : Vector3D(0.0, 0.0, 0.0), t(0.0) {}

        Vector4D(double x, double y, double z, double t) : Vector3D(x, y, z), t(t) {}

        Vector4D operator-(Vector4D &rhs) {
            return Vector4D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->t - rhs.t);
        }

        Vector4D operator+(Vector4D &rhs) {
            return Vector4D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->t + rhs.t);
        }
    };

    class Geometry : public STREAM::ADataType {

    private:

        void readPoint(const char *current, const signed char &precisionXY);

        void readPoint(const char *current, const signed char &precisionXY, const u_char &precisionZ);

        void readLinestring(const char *current, const signed char &precisionXY);

        void readLinestring(const char *current, const signed char &precisionXY, const u_char &precisionZ);

        void readPolygon(const char *current, const signed char &precisionXY);

        void readPolygon(const char *current, const signed char &precisionXY, const u_char &precisionZ);

        void readMultipoint(const char *current, const signed char &precisionXY);

        void readMultipoint(const char *current, const signed char &precisionXY, const u_char &precisionZ);

        static bytes_t encode(const double &value, const signed char &precision);

        static void append(bytes_t &twkb);

        template<typename T, typename... Types>
        static void append(bytes_t &twkb, const T &var1, const Types... var2);

        static bytes_t encode(const Vector2D &vector, const signed char &precisionXY);

        static bytes_t encode(const Vector3D &vector, const signed char &precisionXY, const u_char precisionZ);

        static bytes_t encode(const Vector4D &vector, const signed char &precisionXY, const u_char precisionZ,
                              const u_char precisionT);

        static int32_t decodeVarint(const bytes_t &bytes);

        static bytes_t encodeVarint(uint32_t value);

        static bytes_t
        createHeader(const u_char &type, const signed char &precisionXY, const bool &bbox, const bool &sizes,
                     const bool &idlist, const bool &extendedDimensions,
                     const bool &emptyGeom);

        static bytes_t
        createHeader(const u_char &type, const signed char &precisionXY, const bool &bbox, const bool &sizes,
                     const bool &idlist, const bool &extendedDimensions,
                     const bool &emptyGeom, const u_char &precisionZ);

        static bytes_t
        createHeader(const u_char &type, const signed char &precisionXY, const bool &bbox, const bool &sizes,
                     const bool &idlist, const bool &extendedDimensions,
                     const bool &emptyGeom, const u_char &precisionZ, const u_char &precisionT);

        static uint32_t readUnsignedInt(std::vector<u_char>::iterator &iterator);

        static double readDouble(std::vector<u_char>::iterator &iterator, int32_t precision);

        static uint32_t encodeZigZag(const int32_t &value);

        static int32_t decodeZigZag(const uint32_t &value);

        constexpr const static double EarthRadiusKm = 6372.8 * 1000;

    protected:

        std::vector<u_char> data;


    public:

        Geometry();

        Geometry(const Geometry &other);

        Geometry(const void *twkb, size_t size);

        Geometry(const std::string &wkt_str, const signed char &precisionXY);

        Geometry(const std::string &wkt_str, const signed char &precisionXY, const u_char &precisionZ);

        Geometry(const std::string &wkt_str, const signed char &precisionXY, const u_char &precisionZ,
                 const u_char &precisionT);

        bool isEmpty();

        std::string asWKT();

        void readMetadataAndCoordinates(int &type, int &dimension, std::list<double> &result);

        void readCoordinates(std::vector<u_char>::iterator &iterator, int &type, int &dimension, int &precision,
                             std::list<double> &result);

        void readMetadata(std::vector<u_char>::iterator &iterator, int &type, int &dimension, int &precision);

        static double haversine(double lat1, double lon1, double lat2, double lon2);

        static inline double DegreeToRadian(double angle) { return M_PI * angle / 180.0; };

        static double getDistance(Geometry *geom, Geometry *other);

        static bool pointOverlapsMultipoint(Geometry *multipoint, Geometry *point, const double tolerance);

        static void Local2Global(const double &lat, const double &lon, const double &northDiff, const double &eastDiff,
                                 double &xDiff, double &yDiff, double &zDiff);

        static void LatLon2XYZ(const double &lat, const double &lon, double &x, double &y, double &z);

        static void XYZ2LatLon(const double &x, const double &y, const double &z, double &lat, double &lon);

        virtual std::unique_ptr<ADataType> copy() override;

        virtual void result(STREAM::AResultHandler &result_handler) override;


        std::vector<u_char> asTWKB() const;

        static uint32_t pow10(uint8_t exponent);

        static int32_t shrink(const double &value, const signed char &precision);


    };

}


#endif //STREAMS_STREAM_GEOM_H
