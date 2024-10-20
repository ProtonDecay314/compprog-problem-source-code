"""Checks whether the input file is valid."""

from utils import * ### @import
from collections import deque
from sys import *
from kg.validators import * ### @import

bounds = {
    'n': 1 <= +Var <= 10**9,
    'q': 0 <= +Var <= 2 * (10**5),
}

subtasks = {
    '1': {},
    '2': {},
    '3': {},
    '4': {},
    '5': {},
    '6': {},
    '7': {},
    '8': {},
}

@validator(bounds=bounds, subtasks=subtasks)
def validate(stream, subtask=None, *, lim):
    ... # write your validator here

    poss_queries = set(["SAIKAI", "BUILD", "EXPAND", "TIMEWARP"])

    s = deque()

    s.append(0)

    maxn = 0

    # example:
    [q] = stream.read.int(lim.q).eoln
    for _ in range(q):
        [qtype] = stream.read.token().space

        ensure(qtype in poss_queries)

        cur_n = back(s) 
        if(qtype == "SAIKAI"):
            # u and v
            [u] = stream.read.int(cur_n + 1).space
            [v] = stream.read.int(cur_n + 1).eoln
        elif(qtype == "BUILD"):
            # u and v
            [u] = stream.read.int(cur_n + 1).space
            [v] = stream.read.int(cur_n + 1).eoln
            s.append(cur_n)
            maxn = max(maxn, cur_n)
        elif(qtype == "EXPAND"):
            # k
            [k] = stream.read.int(lim.n).eoln
            s.append(cur_n + k)
            maxn = max(maxn, back(s))
        else:
            # k
            [k] = stream.read.int(len(s)).eoln

            for i in range(k):
                if(len(s) > 1):
                    s.pop()
                else:
                    break
        
        ensure(maxn in lim.n)
    [] = stream.read.eof

    # other possibilities
    # [x, y, z] = stream.read.real(lim.x).space.real(lim.y).space.int(lim.z).eoln
    # [line] = stream.read.line(lim.s).eoln
    # [name] = stream.read.token(lim.name).eoln


if __name__ == '__main__':
    validate_or_detect_subtasks(validate, subtasks, stdin)
