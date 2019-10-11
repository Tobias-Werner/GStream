//
// Created by tobias on 25.01.18.
//


#include "tests.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <Manager.h>
#include <result_handler/ConsoleResultHandler.h>
#include "parser/CQLParser.h"
#include <sqlite3.h>
#include <math.h>
#include <data_types/Geometry.h>

using namespace std;

static sqlite3 *db;

void exec(std::string sql) {

    sqlite3_stmt *stmt;
    sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);

    if (sqlite3_errcode(db) != SQLITE_OK) {
        std::string error(sqlite3_errmsg(db));
        if (error != "")
            std::cout << error << std::endl;
    }

    auto num = sqlite3_column_count(stmt);
    if (num > 0) {
        for (size_t i = 0; i < num; i++) {
            std::cout << sqlite3_column_name(stmt, i) << "\t";
        }
        std::cout << std::endl;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (num > 0) {
            for (size_t i = 0; i < num; i++) {
                switch (sqlite3_column_type(stmt, i)) {
                    case SQLITE_INTEGER : {
                        std::cout << sqlite3_column_int64(stmt, i) << "\t\t\t\t";
                        break;
                    }
                    case SQLITE_FLOAT : {
                        std::cout << sqlite3_column_double(stmt, i) << "\t\t\t\t";
                        break;
                    }
                    case SQLITE_TEXT : {
                        std::cout << sqlite3_column_text(stmt, i) << "\t\t\t\t";
                        break;
                    }
                    case SQLITE_BLOB : {
                        auto size = sqlite3_column_bytes(stmt, i);
                        auto blob = sqlite3_column_blob(stmt, i);
                        auto bytes = static_cast<const unsigned char *>(blob);

                        stringstream stream;

                        for (size_t k = 0; k < size; k++) {
//                            if (bytes[k] != '\r')
//                                stream << bytes[k] << " ";
//                            else
//                                stream << "\\x0D" << " ";
                            printf("%02x ", bytes[k]);
                        }

                        //cout << stream.str() << "\t\t\t\t";

                        break;
                    }
                    case SQLITE_NULL : {
                        std::cout << "[null]" << "\t\t\t\t";
                        break;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);

}

void delay(size_t ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

//TEST_CASE("Transformations") {
//
//    using namespace STREAM;
//
//    SECTION("LatLon2XYZ") {
//
//        double lat = Geometry::DegreeToRadian(53.11482);
//        double lon = Geometry::DegreeToRadian(8.20436);
//        double x, y, z;
//
//        Geometry::LatLon2XYZ(lat, lon, x, y, z);
//
//        std::cout << ":::LatLong2XYZ:::" << endl;
//        std::cout << "Lat: " << lat / M_PI * 180 << endl;
//        std::cout << "Lon: " << lon / M_PI * 180 << endl;
//        std::cout << "X: " << x << endl;
//        std::cout << "Y: " << y << endl;
//        std::cout << "Z: " << z << endl;
//        std::cout << endl;
//
//    }
//
//    SECTION("XYZ2LatLon") {
//
//        double x = 3.78589e+06;
//        double y = 545849;
//        double z = 5.09722e+06;
//        double lat, lon;
//
//        Geometry::XYZ2LatLon(x, y, z, lat, lon);
//
//        std::cout << ":::XYZ2LatLon:::" << endl;
//        std::cout << "X: " << x << endl;
//        std::cout << "Y: " << y << endl;
//        std::cout << "Z: " << z << endl;
//        std::cout << "Lat: " << lat << endl;
//        std::cout << "Lon: " << lon << endl;
//        std::cout << endl;
//    }
//
//    SECTION("MetricMBR") {
//
//        double lat = Geometry::DegreeToRadian(53.11482);
//        double lon = Geometry::DegreeToRadian(8.20436);
//        double x, y, z;
//
//        Geometry::LatLon2XYZ(lat, lon, x, y, z);
//
//        double distance = 10000.0; // Meter
//
//        double xDiff1, yDiff1, zDiff1;
//
//        Geometry::Local2Global(lat, lon, distance, 0, xDiff1, yDiff1, zDiff1);
//
//        xDiff1 += x;
//        yDiff1 += y;
//        zDiff1 += z;
//
//        double lat1, lon1;
//
//        Geometry::XYZ2LatLon(xDiff1, yDiff1, zDiff1, lat1, lon1);
//
//        double c1 = lat1 / M_PI * 180.0;
//        double c2 = lon1 / M_PI * 180.0;
//
//
//        std::cout << ":::MetricMBR:::" << endl;
//        std::cout << "lat1: " << std::setprecision(15) << setw(15) << c1 << endl;
//        std::cout << "lon1: " << std::setprecision(15) << setw(15) << c2 << endl;
//        std::cout << endl;
//    }
//
//    SECTION("Distance test") {
//        double latOriginal = 53.11482;
//        double lonOriginal = 8.20436;
//
//        double lat10m = 53.1149099068532;
//        double lon10m = 8.20436;
//
//        double lat100m = 53.1157190769924;
//        double lon100m = 8.20436;
//
//        double lat1000m = 53.1238116161586;
//        double lon1000m = 8.20436;
//
//        double lat10000m = 53.2048209937153;
//        double lon10000m = 8.20436;
//
//        double dist10m = Geometry::haversine(latOriginal, lonOriginal, lat10m, lon10m);
//        double dist100m = Geometry::haversine(latOriginal, lonOriginal, lat100m, lon100m);
//        double dist1000m = Geometry::haversine(latOriginal, lonOriginal, lat1000m, lon1000m);
//        double dist10000m = Geometry::haversine(latOriginal, lonOriginal, lat10000m, lon10000m);
//
//        std::cout << ":::Distance test:::" << endl;
//        std::cout << "dist10m  " << dist10m << endl;
//        std::cout << "dist100m  " << dist100m << endl;
//        std::cout << "dist1000m  " << dist1000m << endl;
//        std::cout << "dist10000m  " << dist10000m << endl;
//
//
//    }
//
//}

TEST_CASE("SQLite extension") {


    SECTION("Create database") {
//remove("~/testdb.sqlite");
        CHECK(SQLITE_OK == sqlite3_open(":memory:", &db));
    }

    SECTION("Load stream extension") {
        char *zErrMsg = 0;

        CHECK(SQLITE_OK ==
              sqlite3_enable_load_extension(db,
                                            1));
        CHECK(SQLITE_OK ==
              sqlite3_load_extension(db,
                                     "./libstreams", nullptr, &zErrMsg));

        if (zErrMsg != nullptr)
            fprintf(stderr,
                    "SQL error: %s\n", zErrMsg);
    }

    SECTION("Create spatial stream") {
        exec("CREATE VIRTUAL TABLE s USING stream(the_geom GEOMETRY);");

        exec("CREATE VIRTUAL TABLE v1 USING streamview(SELECT the_geom FROM s [SLIDE 100 ms]);");
        //exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('LINESTRING(8.205981673199906 53.10468771859567, 8.2133843340883903 53.11456976365428062, 8.21827274164293797 53.11261177245636134)', 6));");
        exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('MULTIPOINT(8.205982 53.104688 125.25, 8.213384 53.114570 124.01, 8.218273 53.112612 122.35, 8.205982 53.104688 125.25)', 6, 2));");
        exec("SELECT asWKT(the_geom) AS wkt FROM v1;");
        exec("SELECT the_geom AS wkt FROM v1;");

//exec("CREATE VIRTUAL TABLE v2 USING streamview(SELECT the_geom FROM s [TILT 100 ms]);");
//exec("CREATE VIRTUAL TABLE v3 USING streamview(SELECT the_geom FROM s [SLIDE 150.0 m ON the_geom]);");
//exec("CREATE VIRTUAL TABLE v4 USING streamview(SELECT the_geom FROM s [TILT 150.0 m ON the_geom]);");
//exec("CREATE VIRTUAL TABLE v5 USING streamview(SELECT the_geom FROM s [WAY 'MULTIPOINT(8.2133843340883903 53.11456976365428062, 8.21827274164293797 53.11261177245636134)' ON the_geom]);");
//exec("CREATE VIRTUAL TABLE v6 USING streamview(SELECT the_geom FROM s [SESSION 80.0 m ON the_geom]);");
//exec("CREATE VIRTUAL TABLE v7 USING streamview(SELECT the_geom FROM s [JUMPING 500.0 m ON the_geom]);");
////exec("CREATE VIRTUAL TABLE v8 USING streamview(SELECT the_geom FROM s [AREA 'POINT()' 'POINT()'  ON the_geom]);");
//
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.205981673199906  53.10468771859567)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.206247082195345 53.105032952930785)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.206578843439642 53.105457852923784)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.20677790018622 53.105803081077326)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.207087544014231 53.106307640317155)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.207463540091101 53.106666139337946)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.207883771000544 53.107210521025699)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.208326119326275 53.107927501027085)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.208591528321714 53.108339095256987)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.208945406982298 53.108737408503039)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.209166581145164 53.109148994981645)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.209387755308027 53.109560577521094)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.209785868801184 53.110091645944955)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.210051277796621 53.110596154872958)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.210272451959487 53.111020999905691)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.210714800285217 53.111538774114365)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.210913857031795 53.111976885882946)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.211422557606385 53.112627407244034)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.211887023348401 53.113145162110008)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.212373606506706 53.11371601281288)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.212572663253283 53.114127551641495)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.212838072248722 53.114459434924449)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.214054530144479 53.114485985476421)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.214872874547078 53.114393058472793)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.21606721502655 53.113994797611035)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.21688555942915 53.11349032855712)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.21790296057833 53.113105335033964)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.218389543736631 53.112375165435473)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.218323191487771 53.111366183404186)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.21790296057833 53.110025262750639)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.216376858854561 53.108060273789718)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (8.21613356727541 53.107330018522653)', 6));");
//exec("SELECT asWKT(the_geom) AS wkt FROM v7;");



//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (7.625752 53.942254)', 6));");
//exec("INSERT INTO s(the_geom) VALUES(geomFromWKT('POINT (7.625752 53.942254 10.175 164.0)', 6, 3, 0));");

//cout << "=====" << endl;
//exec("SELECT rowid, asWKT(the_geom) AS wkt FROM v1;");
//exec("SELECT rowid, asWKT(the_geom) AS wkt FROM v2;");
//exec("SELECT rowid, asWKT(the_geom) AS wkt FROM v2;", 200);
//exec("SELECT rowid, asWKT(the_geom) AS wkt FROM v2;", 200);
//exec("SELECT rowid, asWKT(the_geom) AS wkt FROM v2;");
//exec("SELECT rowid, the_geom FROM v1;", 200);
//        exec("SELECT rowid, the_geom FROM v1;");
//
//exec("SELECT rowid, the_geom FROM v1;", 200);
//        exec("SELECT rowid, the_geom FROM v2;", 200);
//
//exec("SELECT rowid, the_geom FROM v1;", 1000);
//        exec("SELECT rowid, the_geom FROM v2;", 1000);
    }

//    SECTION("Create streamA") {
//        exec("CREATE VIRTUAL TABLE streamA USING stream(int_value INTEGER, real_value REAL, text_value TEXT, blob_value BLOB);");
//    }
//
//    SECTION("Create streamB") {
//        exec("CREATE VIRTUAL TABLE streamB USING stream(int_value INTEGER, real_value REAL, text_value TEXT, blob_value BLOB);");
//    }
//
////    SECTION("Create a Join") {
////        exec("CREATE VIRTUAL TABLE viewA USING streamview(SELECT streamA.text_value FROM streamA JOIN streamB ON streamA.int_value = streamB.int_value [SLIDE 100 ms]);");
////    }
//
//    SECTION("Create a Sliding Window") {
//        exec("CREATE VIRTUAL TABLE viewB USING streamview(SELECT int_value, real_value, text_value FROM streamA [SLIDE 100 ms]);");
//    }
//
//    SECTION("Create a Tilting Window") {
//        exec("CREATE VIRTUAL TABLE viewC USING streamview(SELECT int_value, real_value, text_value FROM streamA [TILT 100 ms]);");
//    }
//
//    SECTION("Insert data streamA") {
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(1, 1.1, 'A_Eins', x'01');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(2, 2.2, 'A_Zwei', x'02');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(3, 3.3, 'A_Drei', x'03');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(4, 4.4, 'A_Vier', x'04');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(5, 5.5, 'A_Fünf', x'05');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(6, 6.6, 'A_Sechs', x'06');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(7, 7.7, 'A_Sieben', x'07');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(8, 8.8, 'A_Acht', x'08');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(9, 9.9, 'A_Neun', x'09');");
//        exec("INSERT INTO streamA(int_value, real_value, text_value, blob_value) VALUES(10, 10.10, 'A_Zehn', x'10');");
//    }
//
//    SECTION("Insert data streamB") {
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(1, 1.1, 'A_Eins', x'01');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(2, 2.2, 'A_Zwei', x'02');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(3, 3.3, 'A_Drei', x'03');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(4, 4.4, 'A_Vier', x'04');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(5, 5.5, 'A_Fünf', x'05');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(6, 6.6, 'A_Sechs', x'06');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(7, 7.7, 'A_Sieben', x'07');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(8, 8.8, 'A_Acht', x'08');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(9, 9.9, 'A_Neun', x'09');");
//        exec("INSERT INTO streamB(int_value, real_value, text_value, blob_value) VALUES(10, 10.10, 'A_Zehn', x'10');");
//    }
//
//    SECTION("Select from Sliding Window") {
//        exec("SELECT int_value, real_value, text_value FROM viewB;");
//        exec("SELECT int_value, real_value, text_value FROM viewB;", 1000);
//    }
//
//    SECTION("Select from Tilting Window") {
//        exec("SELECT int_value, real_value, text_value FROM viewC;");
//        exec("SELECT int_value, real_value, text_value FROM viewC;", 1000);
//    }


    SECTION("Close DB") {
        sqlite3_close(db);
    }
}