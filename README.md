# GStream

GStream is a lightweight SQLite extension for processing spatio-temporal datastreams on embedded systems.

## Installation
The extension can be installed via from source or via a precompiled binary.

#### From source
First, prepare the environment by calling the following script. It will download and install all dependencies and tools for compiling.
```
tools/setupEnvironment.sh 
```
Run the following commands in a shell. It will clone the repo and install the shared library and a testing program.
```
git clone https://github.com/Tobias-Werner/GStream.git
cd GStream/
cmake . -Bbuild
cd build
make
sudo make install
```

#### Precompiled binaries

Precompiled binaries for different cpu architectures can be downloaded via following links. 

* Ubuntu x64 (...) 
* ARM6 (...)

Install the DEB file via double click or via console with:
```
sudo dpkg -i <DEB-file>
```
#### Testing (optional)
After installing the functionalities of the extension can be tested via a testing program. Call it in a shell with
```
libstream-tests
```
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
[SLIDE <distance> m ON the_geom]

-- Tilting distance window
[TILT <distance> m ON the_geom]

-- Waypoint window
[WAY '<Multipoint-as-WKT>' ON the_geom]

-- Session distance window
[SESSION <distance> m ON the_geom]

-- Jumping distance window
[JUMPING <distance> m ON the_geom]
```
A more detailed description of how to use the extension can be found in test/src/tests.cpp.

### References
Werner, T.; Brinkhoff, T. (2018): Managing Spatio-Temporal Data Streams on AUVs. Proceedings of the IEEE/OES Autonomous Underwater Vehicles Workshop (AUV), Porto, Portugal , doi: 10.1109/AUV.2018.8729817 