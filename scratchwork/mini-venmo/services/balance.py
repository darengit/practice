from services.service import Service

class Balance(Service):
    """logic to return a user's current balance"""

    def parse_payload(self):
        self.name = self.payload

    def run_service(self):
        balance = self.db.get_balance(self.name)
        return ["-- ${}".format(balance)]

