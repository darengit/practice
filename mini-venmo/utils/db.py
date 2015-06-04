import sqlite3

class Db(object):
    def __init__(self):
        self.conn = sqlite3.connect(":memory:")
        self.cursor = self.conn.cursor()

        # for now put balance and cc_number into user table
        self.cursor.execute("""CREATE TABLE user
                               (id INTEGER PRIMARY KEY,
                                name TEXT UNIQUE NOT NULL,
                                balance REAL NOT NULL,
                                cc_number INTEGER UNIQUE)""")

        self.cursor.execute("""CREATE TABLE payment
                               (id INTEGER PRIMARY KEY,
                                datetime TEXT NOT NULL,
                                payer_id INTEGER NOT NULL,
                                receiver_id INTEGER NOT NULL,
                                quantity REAL NOT NULL,
                                note TEXT NOT NULL)""")

    def new_user(self, name):
        self.cursor.execute("INSERT INTO user (name,balance,cc_number) VALUES (?,?,?)", (name,0,None))
        #self.conn.commit()

    def get_cc_number(self, name):
        self.cursor.execute("SELECT cc_number FROM user WHERE name=?", (name,))
        (cc_number,) = self.cursor.fetchone()
        return cc_number

    def set_cc_number(self, name, cc_number):
        self.cursor.execute("UPDATE user SET cc_number=? WHERE name=?", (cc_number, name))

    def get_user_id(self, name):
        self.cursor.execute("SELECT id FROM user WHERE name=?", (name,))
        (user_id,) = self.cursor.fetchone()
        return user_id

    # i don't feel great about this function
    def cc_number_exists(self, cc_number):
        self.cursor.execute("SELECT COUNT(*) FROM user WHERE cc_number=?", (cc_number,))
        (count,) = self.cursor.fetchone()
        return count > 0

    def new_payment(self, payer_id, receiver_id, quantity, note, time):
        self.cursor.execute("INSERT INTO payment (datetime,payer_id,receiver_id,quantity,note)\
                             VALUES (?,?,?,?,?)", (time, payer_id, receiver_id, quantity, note))

    # this function will work in this demo, but shouldn't exist in its current form in a production environment    
    def increment_balance(self, receiver_id, quantity):
        self.cursor.execute("SELECT balance FROM user WHERE id=?", (receiver_id,))
        (balance,) = self.cursor.fetchone()
        self.cursor.execute("UPDATE user SET balance=?+? WHERE id=?", (float(balance), float(quantity), receiver_id))

    def get_raw_feeds_for_user(self, user_id):
        self.cursor.execute("SELECT p.name,p.id,r.name,r.id,t.quantity,t.note\
                             FROM payment t\
                               INNER JOIN user p ON t.payer_id = p.id\
                               INNER JOIN user r ON t.receiver_id = r.id\
                             WHERE payer_id=? OR receiver_id=?\
                             ORDER BY datetime ASC", (user_id, user_id))
        return self.cursor.fetchall()

    def get_balance(self, name):
        self.cursor.execute("SELECT balance FROM user WHERE name=?", (name,))
        (balance,) = self.cursor.fetchone()
        return balance

