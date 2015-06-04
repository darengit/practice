from services.service import Service

class Feed(Service):
    """logic to return a list of a user's transactions"""

    def parse_payload(self):
        self.name = self.payload
        self.user_id = self.db.get_user_id(self.name)

    def run_service(self):
        feed = []
        for row in self.db.get_raw_feeds_for_user(self.user_id):
            feed.append(self._form_output_row(row))
        return feed

    def _form_output_row(self, db_row):
        (payer, payer_id, receiver, receiver_id, quantity, note) = db_row
        if (payer_id == self.user_id):
            payer = "You"
        else: #receiver_id = self.user_id
            receiver = "you"
        return "-- {} paid {} ${} for {}".format(payer, receiver, quantity, note)
