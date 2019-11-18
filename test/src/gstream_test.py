import sqlite3
import unittest
import time


class Tests(unittest.TestCase):
    db = None
    cursor = None
    stream_name = "aStream"
    data = [[]]

    def setUp(self):
        self.db = sqlite3.connect(':memory:')
        self.assertIsNotNone(self.db)

        self.db.enable_load_extension(True)
        self.cursor = self.db.cursor()
        self.assertIsNotNone(self.cursor)

        self.cursor.execute("SELECT load_extension('../../build/libstreams.so');")

        self.cursor.execute("CREATE VIRTUAL TABLE " + self.stream_name + " " +
                            "USING stream(the_geom GEOMETRY);")
        self.check_table_exists("aStream")

        self.data.append([417599.59366124, 5961901.44477639])
        self.data.append([417599.667241198, 5961901.42335678])
        self.data.append([417599.780203676, 5961901.34758207])
        self.data.append([417599.905072555, 5961901.18439828])
        self.data.append([417599.949403817, 5961901.02934143])
        self.data.append([417599.984886674, 5961900.75370309])
        self.data.append([417599.966244483, 5961900.45889566])
        self.data.append([417600.001018315, 5961900.14302396])
        self.data.append([417600.008079679, 5961899.78068717])
        self.data.append([417600.164546287, 5961899.50291666])
        self.data.append([417600.454862871, 5961899.57158445])
        self.data.append([417600.498854084, 5961899.77874593])
        self.data.append([417600.477050166, 5961900.06755854])
        self.data.append([417600.468452543, 5961900.34272312])
        self.data.append([417600.479073505, 5961900.56388792])
        self.data.append([417600.469412345, 5961900.7787025])
        self.data.append([417600.540052471, 5961900.97197904])
        self.data.append([417600.711275994, 5961901.15006773])
        self.data.append([417600.925176412, 5961901.07922186])
        self.data.append([417601.02268739, 5961900.88968967])
        self.data.append([417601.023972875, 5961900.58111581])
        self.data.append([417601.011579385, 5961900.25936771])
        self.data.append([417601.016868272, 5961899.79644762])
        self.data.append([417601.039735757, 5961899.56798499])
        self.data.append([417601.165431919, 5961899.45174005])
        self.data.append([417601.312828252, 5961899.42231198])
        self.data.append([417601.435820874, 5961899.53417435])
        self.data.append([417601.488069566, 5961899.8283896])
        self.data.append([417601.473695923, 5961900.15731707])
        self.data.append([417601.472055899, 5961900.4457743])
        self.data.append([417601.456500563, 5961900.70764621])
        self.data.append([417601.481391298, 5961900.97551296])
        self.data.append([417601.471375584, 5961901.17021087])
        self.data.append([417601.400868028, 5961901.36597479])
        self.data.append([417601.140509257, 5961901.47117753])
        self.data.append([417600.886753642, 5961901.56955627])
        self.data.append([417600.585830658, 5961901.66205862])
        self.data.append([417600.357069586, 5961901.65267478])
        self.data.append([417600.174885037, 5961901.6156396])
        self.data.append([417600.025598032, 5961901.53777887])
        self.data.append([417599.849898447, 5961901.48721415])
        self.data.append([417599.748960538, 5961901.48228535])
        self.data.append([417599.681747379, 5961901.48346985])
        self.data.append([417599.594488446, 5961901.49171525])

    def tearDown(self):
        self.cursor.close()
        self.db.close()

    def check_table_exists(self, name):
        self.cursor.execute("SELECT count(name) FROM sqlite_master WHERE type='table' AND name=?", (name,))
        result = self.cursor.fetchone()
        self.assertEqual(int(result[0]), 1)

    def insert_data(self, start_idx, stop_idx, dt=0.5):
        for i in range(start_idx, stop_idx):
            wkt = "POINT(" + str(self.data[i][0]) + " " + str(self.data[i][1]) + ")"
            self.cursor.execute("INSERT INTO " + self.stream_name + "(the_geom) VALUES(geomFromWKT(?, 2))", (wkt,))
            time.sleep(dt)

    def count_tuples_in_windw(self, name):
        self.cursor.execute("SELECT count(*) FROM " + name)
        return int(self.cursor.fetchone()[0])

    def test_temporal_sliding_window(self):
        view_name = "temporal_sliding_window"

        self.cursor.execute(
            "CREATE VIRTUAL TABLE  " + view_name + " " +
            "USING streamview("
            "   SELECT the_geom FROM " + self.stream_name + " [SLIDE 10000 ms]);")

        self.check_table_exists(view_name)

        self.assertEqual(0, self.count_tuples_in_windw(view_name))
        self.insert_data(1, 2)
        self.assertEqual(1, self.count_tuples_in_windw(view_name))
        self.insert_data(2, 3)
        self.assertEqual(2, self.count_tuples_in_windw(view_name))

        #self.insert_data(11, 21)
        #self.assertEqual(10, self.count_tuples_in_windw(view_name))

    def test_temporal_tilting_window(self):
        view_name = "temporal_tilting_window"
        self.cursor.execute("CREATE VIRTUAL TABLE " + view_name + " " +
                            "USING streamview("
                            "   SELECT the_geom FROM " + self.stream_name + " [TILT 100 ms]);")

        self.check_table_exists(view_name)

    def test_spatial_sliding_window(self):
        view_name = "spatial_sliding_window"
        self.cursor.execute("CREATE VIRTUAL TABLE " + view_name + " " +
                            "USING streamview("
                            "   SELECT the_geom FROM " + self.stream_name + " [SLIDE 150.0 m ON the_geom]);")

        self.check_table_exists(view_name)

    def test_spatial_tilting_window(self):
        view_name = "spatial_tilting_window"
        self.cursor.execute("CREATE VIRTUAL TABLE " + view_name + " " +
                            "USING streamview("
                            "   SELECT the_geom FROM " + self.stream_name + " [TILT 150.0 m ON the_geom]);")

        self.check_table_exists(view_name)

    def test_spatial_area_window(self):
        view_name = "spatial_area_window"
        self.cursor.execute("CREATE VIRTUAL TABLE " + view_name + " " +
                            "USING streamview("
                            "   SELECT the_geom FROM " + self.stream_name + " [WAY 'MULTIPOINT(8.2133843340883903 53.11456976365428062, 8.21827274164293797 53.11261177245636134)' ON the_geom]);")

        self.check_table_exists(view_name)

    def test_spatial_session_window(self):
        view_name = "spatial_session_window"
        self.cursor.execute("CREATE VIRTUAL TABLE " + view_name + " " +
                            "USING streamview("
                            "   SELECT the_geom FROM " + self.stream_name + " [SESSION 80.0 m ON the_geom]);")

        self.check_table_exists(view_name)

    def test_spatial_jumping_window(self):
        view_name = "spatial_jumping_window"
        self.cursor.execute("CREATE VIRTUAL TABLE " + view_name + " " +
                            "USING streamview("
                            "   SELECT the_geom FROM " + self.stream_name + " [JUMPING 500.0 m ON the_geom]);")

        self.check_table_exists(view_name)


if __name__ == "__main__":
    unittest.main()
