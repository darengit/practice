import abc

from utils.exception import InputError

class Service(object):
    """abstract class to describe high level functionality of all services"""
    def __init__(self, payload, db):
        self.payload = payload
        self.db = db

    def run(self):
        """high level logic of all services"""

        output = []
        try:
            self.parse_payload()
            output = output + self.run_service()
        except InputError as e:
            output.append("ERROR: " + e.message)
        except Exception as e:
            output.append("ERROR: " + str(e))

        for line in output:
            print(line)

    @abc.abstractmethod
    def parse_payload(self):
        """validate the payload"""

    @abc.abstractmethod
    def run_service(self):
        """db updates and any other logic, returns output array"""
