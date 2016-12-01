from datetime import datetime
import re

from services.service import Service
from utils.exception import InputError

class Pay(Service):
    """logic for one user to pay another from credit card to other's venmo balance"""

    def parse_payload(self):
        (payer, receiver, quantity, self.note) = self.payload.split(" ", 3)
        self.payer_id = self.db.get_user_id(payer)
        self.receiver_id = self.db.get_user_id(receiver)

        self.quantity = re.match("^\$(\d+\.\d+)$", quantity).group(1)
        if (self.payer_id == self.receiver_id):
            raise InputError("user cannot pay themselves")

        self.payer_cc_number = self.db.get_cc_number(payer)

        if (self.payer_cc_number is None):
            raise InputError("this user does not have a credit card")

    def run_service(self):
        #self.db.cursor.execute("BEGIN")
        self.db.new_payment(self.payer_id,
                            self.receiver_id,
                            self.quantity,
                            self.note,
                            datetime.strftime(datetime.now(), "%Y-%m-%d %H:%M:%S"))
        self.db.increment_balance(self.receiver_id, self.quantity)
        #self.db.cursor.execute("COMMIT")
        return []

