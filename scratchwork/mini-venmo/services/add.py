from services.service import Service
from utils import luhn_checksum
from utils.exception import InputError

class Add(Service):
    """logic to add a credit card"""

    def parse_payload(self):
        (self.name, self.cc_number) = self.payload.split(" ")

        if not luhn_checksum(self.cc_number):
            raise InputError("this card number is invalid")

        # there is a case where username is not in the database, not specified in spec so ignored for now

        none_value = self.db.get_cc_number(self.name)
        if none_value is not None:
            raise InputError("this user already has a valid credit card")

        if self.db.cc_number_exists(self.cc_number):
            raise InputError("this card has already been added to another user, reported for fraud!")

    def run_service(self):
        self.db.set_cc_number(self.name, self.cc_number)
        return []

