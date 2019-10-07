[![Build Status](https://travis-ci.org/Tobias-Werner/GStream.svg?branch=master)](https://travis-ci.org/Tobias-Werner/GStream)

# GStream

GStream is a lightweight SQLite extension for processing spatio-temporal datastreams on embedded systems.


### Basic Usage
The following usage examples are based on sql commands. This commands can be passed via sqlite console or directly in a program as raw string.

```
-- Loading the extension
SELECT load_extension('libstreams');

-- Create a stream (accepts insert statements only)
CREATE VIRTUAL TABLE <streamName> USING stream(<attributeName> <attributeType>);

-- Create a view (accepts select statements only)
CREATE VIRTUAL TABLE <viewName> USING stream_view(SELECT <attributeList> FROM <streamName> <window>);
```

The following window types can be used in a stream view.
```
-- Sliding time window
[SLIDE <duriation> ms]

-- Tilting time window
[TILT <duriation> ms]

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
A more detailed description of how to use the extension can be found in test/src/tests.cpp.

### Citing
Werner, T.; Brinkhoff, T. (2018): Managing Spatio-Temporal Data Streams on AUVs. Proceedings of the IEEE/OES Autonomous Underwater Vehicles Workshop (AUV), Porto, Portugal , doi: 10.1109/AUV.2018.8729817 