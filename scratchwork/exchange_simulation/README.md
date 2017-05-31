simulate what an exchange does to handle orders:

1 generate a list of orders with timestamps and write this list out to a file
2 dispatch orders one at a time into a set of N gateways, each of which contains a SPSC FIFO queue
3 a sequencer reads the entries from the gateways in realtime and produces a sequence in which the orders should be executed
4 the sequencer provides an api which a matcher can use to match orders and generate trades in realtime
5 matcher generates trades and writes them to a file
6 when all orders have been dispatched, a state variable is set to notify the sequencer that once all gateways are empty to complete
7 once the sequencer completes it sets global variables to notify the matcher its complete
8 once the matcher completes it will write the unmatched orders to a file

