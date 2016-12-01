# i feel like there is a better way to do this, but couldn't find it quickly
import os,sys,inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0,parentdir)

import unittest
from hash_map import HashMap,KeyNotFound

class TestHashMap(unittest.TestCase):
     
    def setUp(self):
        pass
                 
    def test_hash_map(self):
        test_map = HashMap()
        for i in range(0,1000):
            if i%2 is 0:
                test_map.put((i,), i)
            else: # i%2 is 1
                test_map.put(str(i), [i])

        # initialize the map with 1001 kv pairs
        self.assertEquals(test_map.size(), 1000)
        for i in range(0,1000):
            if i%2 is 0:
                self.assertEquals(test_map.get((i,)), i)
            else: # i%2 is 1
                self.assertEquals(test_map.get(str(i)), [i])

        with self.assertRaises(KeyNotFound):
            test_map.get("8")

        with self.assertRaises(KeyNotFound):
            test_map.get((991,))

        with self.assertRaises(KeyNotFound):
            test_map.get("test_key")

        with self.assertRaises(KeyNotFound):
            test_map.get((1002,))

        # remove 700 elements
        for i in range(100,800):
            if i%2 is 0:
                test_map.remove((i,))
            else: # i%2 is 1
                test_map.remove(str(i))

        self.assertEquals(test_map.size(), 300)

        self.assertTrue(test_map.contains((80,)))
        self.assertFalse(test_map.contains((120,)))

        # insert 9000 more values
        for i in range(1000,10000):
            if i%2 is 1:
                test_map.put((i,), i)
            else: # i%2 is 0
                test_map.put(str(i), [i])

        self.assertEquals(test_map.size(), 9300)

        for i in range(1000,10000):
            if i%2 is 1:
                self.assertEquals(test_map.get((i,)), i)
            else: # i%2 is 0
                self.assertEquals(test_map.get(str(i)), [i])


if __name__ == '__main__':
    unittest.main()
