class KeyNotFound(Exception):
    pass

class HashMap:
    """A very basic HashTable implementation with the following interface:
    constructor with optional initial size parameter
    contains()
    get()
    put()
    remove()
    size()
    """

    _sizing_factor = 2

    def __init__(self, size=20):
        """Allow user to pass in initial size,
        use an underlying list to store key value tuples."""
        self._underlying_list = [None]*size*self._sizing_factor
        self._size = 0

    def _index_of(self, key):
        """retrieve the index of a key from _underlying_list,
        or None if it is not in the list."""
        hash_idx = self._hash_idx(key)
        for i in range(0, len(self._underlying_list)):
            idx_to_test = (hash_idx+i)%len(self._underlying_list)
            if (self._underlying_list[idx_to_test] is None):
                return None
            elif (self._underlying_list[idx_to_test] == ("Removed",)):
                pass
            else: # _underlying_list[idx_to_test] is not None and not ("Removed",)
                (curr_key, curr_value) = self._underlying_list[idx_to_test]
                if key == curr_key:
                    return idx_to_test
        return None

    def _hash_idx(self, key):
        """use python's hash function to calculate a index between 0
        and len(_underlying_list)-1.
        note that certain types are not hashable by hash(), TypeError
        will be raised in those cases.
        as a result only immutable types can be keys, and there are not many of them.
        i did it this way for simplicity."""
        return hash(key)%(len(self._underlying_list))

    def _double_underlying_list(self):
        """double the size of the underlying list and move all kv pairs
        from the current list to the new list with double size."""
        curr_underlying_list = self._underlying_list

        self._underlying_list = [None]*len(self._underlying_list)*2
        self._size = 0

        for kv in curr_underlying_list:
            if (kv is not None) and (kv != ("Removed",)):
                (key, value) = kv
                self.put(key, value)

    def contains(self, key):
        """test if a key is in the HashMap."""
        return self._index_of(key) is not None
    
    def get(self, key):
        """retrieves a value from the HashMap according to the key,
        and raise KeyNotFound if key doesn't exist within the HashMap."""
        idx = self._index_of(key)
        if idx is not None:
            return self._underlying_list[idx][1]
        else: # idx is None
            raise KeyNotFound("{} key was not found".format(key))
    
    def put(self, key, value):
        """inserts a key value pair (tuple) into the HashMap, also double the size
        the _underlying_list if necessary."""
        if self._size*self._sizing_factor >= len(self._underlying_list):
            self._double_underlying_list()

        hashed_idx = self._hash_idx(key)

        for i in range(0, len(self._underlying_list)):
            idx_to_test = (hashed_idx+i)%len(self._underlying_list)
            if (self._underlying_list[idx_to_test] is None) or\
               (self._underlying_list[idx_to_test] is ("Removed",)):
                self._underlying_list[idx_to_test] = (key, value)
                self._size += 1
                return

        raise Exception("list underlying HashMap is full.")


    def remove(self, key):
        """remove a key value pair from the HashMap."""
        idx = self._index_of(key)
        if idx is not None:
            self._underlying_list[idx] = ("Removed",)
            self._size -= 1

    def size(self):
        return self._size
