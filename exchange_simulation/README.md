simulate what an exchange does to handle orders:

* generate a list of orders in memory
* dispatch orders one at a time into a set of N gateways, each of which contains a SPSC FIFO queue
* a sequencer reads the entries from the gateways in realtime and produces a sequence in which the orders should be executed
* the sequencer is connected to a matcher by another SPSC FIFO queue, matcher matches orders and generate trades in realtime

notes:

* the most vexing syntax feature in C++ bites me again, Compi\<unsigned int> comp()
* synchronization is really hard, hard to test
* make the queue connecting sequencer and matcher one which can produce a whole buffer of output
