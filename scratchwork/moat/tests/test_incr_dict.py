# i feel like there is a better way to do this, but couldn't find it quickly
import os,sys,inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0,parentdir)

import unittest
from incr_dict import incr_dict

class TestIncrDict(unittest.TestCase):
     
    def setUp(self):
        pass
                 
    def test_incr_dict(self):
        dct = {} 
        incr_dict(dct, ('a', 'b', 'c')) 
        self.assertEquals(dct, {'a': {'b': {'c': 1}}})

        incr_dict(dct, ('a', 'b', 'c')) 
        self.assertEquals(dct, {'a': {'b': {'c': 2}}})

        incr_dict(dct, ('a', 'b', 'f')) 
        self.assertEquals(dct, {'a': {'b': {'c': 2, 'f': 1}}})

        incr_dict(dct, ('a', 'r', 'f'))
        self.assertEquals(dct, {'a': {'r': {'f': 1}, 'b': {'c': 2, 'f': 1}}})

        incr_dict(dct, ('a', 'z')) 
        self.assertEquals(dct, {'a': {'r': {'f': 1}, 'b': {'c': 2,'f': 1}, 'z': 1}})
                                                  
if __name__ == '__main__':
    unittest.main()
