import sys
import cmd

from utils.db import Db # there is probably a better way to represent the db

from services.user import User
from services.add import Add
from services.pay import Pay
from services.feed import Feed
from services.balance import Balance

class MiniVenmoCmd(cmd.Cmd):
    """wrapper class for a command line interface"""
    def __init__(self):
        cmd.Cmd.__init__(self)
        self.prompt = "> "
        self.db = Db() # i don't feel great about how this db is created and passed around

    def do_user(self, line):
        """user <username>"""
        User(line, self.db).run()

    def do_add(self, line):
        """add <username> <credit card number>"""
        Add(line, self.db).run()

    def do_pay(self, line):
        """pay <payer> <receiver> $<quantity> <note>"""
        Pay(line, self.db).run()

    def do_feed(self, line):
        """feed <username>"""
        Feed(line, self.db).run()
    
    def do_balance(self, line):
        """balance <username>"""
        Balance(line, self.db).run()

    def do_users(self, line):
        """list user table for debugging purposes"""
        self.db.cursor.execute("SELECT * FROM user")
        for row in self.db.cursor.fetchall():
            print(row)

    def do_payments(self, line):
        """list payment table for debugging purposes"""
        self.db.cursor.execute("SELECT * FROM payment")
        for row in self.db.cursor.fetchall():
            print(row)

    def do_exit(self, line):
        return True
    def do_quit(self, line):
        return True

    def do_EOF(self, line):
        return True
   
    def default(self, line):
        print("ERROR: command not recognized")

    def emptyline(self):
        pass

class MiniVenmoFile(MiniVenmoCmd):
    """wrapper class for interfacing with input file"""
    def __init__(self, file_handler):
        MiniVenmoCmd.__init__(self)
        self.stdin = file_handler
        self.use_rawinput = False
        self.prompt = ""

if __name__ == "__main__":
    try:
        if len(sys.argv) > 1:
            input_file_handler = open(sys.argv[1], "rt")
            MiniVenmoFile(input_file_handler).cmdloop()
            input_file_handler.close()
        else:
            MiniVenmoCmd().cmdloop()
    except Exception as e: 
        print("ERROR: " + str(e))
