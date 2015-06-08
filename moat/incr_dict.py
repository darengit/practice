def incr_dict(to_incr, keys):
    # call a helper function which contains an index into keys
    return incr_dict_idx(to_incr, keys, 0)

# idx is between 0 and len(keys)-1 inclusive
def incr_dict_idx(to_incr, keys, idx):

    # base cases
    if len(keys) == 0:
        return

    if idx == len(keys)-1:
        if keys[idx] in to_incr:
            to_incr[keys[idx]] += 1
        else: # keys[idx] not in to_incr
            to_incr[keys[idx]] = 1
        return

    #recursive case using tail recursion
    if keys[idx] not in to_incr:
        to_incr[keys[idx]] = {}

    return incr_dict_idx(to_incr[keys[idx]], keys, idx+1)
