import re

from services.service import Service
from utils.exception import InputError

class User(Service):
    """logic to add a new user user"""

    def parse_payload(self):
        self.name = self.payload

        if len(self.name)<4 or len(self.name)>15:
            raise InputError("username is not of proper length")

        if not re.match("^[\w-]+$", self.name):
            raise InputError("username has weird characters")

    def run_service(self):
        self.db.new_user(self.name)
        return []
