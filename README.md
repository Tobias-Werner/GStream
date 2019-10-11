[![Build Status](https://travis-ci.org/Tobias-Werner/GStream.svg?branch=master)](https://travis-ci.org/Tobias-Werner/GStream)

# GStream

GStream is a lightweight SQLite extension for processing spatio-temporal datastreams on embedded systems.


### Basic Usage
The following usage examples are based on sql commands. This commands can be passed via sqlite console or directly in a program as raw string.

#### Prerequisites

```
-- Loading the extension
SELECT load_extension('libstreams');

-- Create a stream (accepts insert statements only)
CREATE VIRTUAL TABLE <streamName> USING stream(<attributeName> <attributeType>);

-- Create a view (accepts select statements only)
CREATE VIRTUAL TABLE <viewName> USING stream_view(SELECT <attributeList> FROM <streamName> <window>);
```

#### Window types

The following window types can be used in a stream view.

##### Temporal

```
-- Sliding time window
[SLIDE <duriation> ms]

-- Tilting time window
[TILT <duriation> ms]
```

##### Spatial

```
-- Sliding distance window
[SLIDE <distance> m ON <geometry-column>]

-- Tilting distance window
[TILT <distance> m ON <geometry-column>]

-- Waypoint window
[WAY '<Multipoint-as-WKT>' ON <geometry-column>]

-- Session distance window
[SESSION <distance> m ON <geometry-column>]

-- Jumping distance window
[JUMPING <distance> m ON <geometry-column>]
```

#### Encoding of Geometries

Encoding and decoding of geometries can be done by three functions.
```
-- Encoding 2d geometry (converting from WKT to TWKB)
geomFromWKT('<geometry-as-WKT>', <precisionXY>))

-- Encoding 3d geometry (converting from WKT to TWKB)
geomFromWKT('<geometry-as-WKT>', <precisionXY>, <precisionZ>))

-- Decoding geometry (converting from TWKB to WKT)
asWKT(<geometry-column>)
``` 

The following geometry types (2d and 3d) are available.

* Point
* Linestring
* Polygon
* Multipoint
* Multilinestring
* Multipolygon

### Minimal example

```
-- Create a data stream with a geometry column
CREATE VIRTUAL TABLE a_stream USING stream(the_geom GEOMETRY);

-- Applying a sliding distance window
CREATE VIRTUAL TABLE a_view USING streamview(SELECT the_geom FROM a_stream [SLIDE 100 ms]);

-- Inserting a single location geometry
INSERT INTO a_stream(the_geom) VALUES(geomFromWKT('POINT (8.205981673199906  53.10468771859567)', 6));

-- Querying the sliding distance window
SELECT asWKT(the_geom) AS wkt FROM a_view;
```


A more detailed description of how to use the extension can be found in test/src/tests.cpp.

### Citing
Werner, T.; Brinkhoff, T. (2018): Managing Spatio-Temporal Data Streams on AUVs. Proceedings of the IEEE/OES Autonomous Underwater Vehicles Workshop (AUV), Porto, Portugal , doi: 10.1109/AUV.2018.8729817 