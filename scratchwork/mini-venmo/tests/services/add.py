import os
import sys
sys.path.append(os.path.abspath(os.path.dirname(os.path.abspath(os.path.dirname(os.path.abspath(os.path.dirname(__file__)))))))

import unittest
from unittest.mock import patch

from services.add import Add

class AddTestCase(unittest.TestCase):
    def setUp(self):
        self.add_to_test = Add("", "")
        pass

    @patch("utils.db.Db")
    def test_run_service(self, mock_db):
        self.add_to_test.db = mock_db
        self.add_to_test.name = "test_name"
        self.add_to_test.cc_number = "test_cc_number"
        self.add_to_test.run_service()
        mock_db.set_cc_number.assert_called_with("test_name", "test_cc_number")

if __name__ == '__main__':
    unittest.main()
