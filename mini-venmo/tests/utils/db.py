import os
import sys
sys.path.append(os.path.abspath(os.path.dirname(os.path.abspath(os.path.dirname(os.path.abspath(os.path.dirname(__file__)))))))

import unittest
from unittest.mock import MagicMock

from utils.db import Db

class DbTestCase(unittest.TestCase):
    def setUp(self):
        self.db_to_test = Db()
        pass

    def test_new_user(self):
        self.db_to_test.cursor = MagicMock()
        self.db_to_test.new_user("test_user")
        self.db_to_test.cursor.execute.assert_called_with("INSERT INTO user (name,balance,cc_number) VALUES (?,?,?)", ("test_user",0,None))

if __name__ == '__main__':
    unittest.main()
