"""Generates random tests."""

from collections import deque
from sys import *
from kg.generators import * ### @import
from formatter import * ### @import
from utils import * ### @import

A = 10**9

@listify
def gen_random(rand, *args):
    [n, q, t, has_timewarp_flag, build_before_saikai_flag] = map(str, args[:5])
    n, q, t = map(int, (n, q, t))
    
    """
    SECTIONS

    INITIAL EXPAND
    q - t - 1 queries
    EXPAND to full
    t - 1 SAIKAI or BUILD
    """

    touched = []

    has_timewarp = has_timewarp_flag == "y"
    build_before_saikai = build_before_saikai_flag == "y"

    qtypes = ["SAIKAI", "BUILD", "TIMEWARP", "EXPAND"]

    qry = []

    s = deque()
    s.append(0)
    maxn = 0

    init_e = rand.randint(1, n)
    maxn = max(maxn, init_e)

    qry.append(["EXPAND", init_e])
    s.append(init_e)

    for _ in range(q - t - 1):
        # random queries
        dist = [8 if (back(s) > 1 and not build_before_saikai) else 0, 4 if back(s) > 1 else 0, 2 if has_timewarp and len(s) > 1 else 0, 0 if back(s) == n else 1]
        qtype = qtypes[sample(pref_sum(dist), rand)]

        cur_n = back(s)
        if(qtype == "SAIKAI"):
            # u and v
            u = 0
            v = 0
            touched_sz = len(touched)
            while(u == v or u > cur_n or v > cur_n):
                if(rand.randint(0, 100) <= 95 and touched_sz > 2):
                    u = touched[rand.randint(0, touched_sz - 1)]
                else:
                    u = rand.randint(1, cur_n)
                
                if(rand.randint(0, 100) <= 95 and touched_sz > 2):
                    v = touched[rand.randint(0, touched_sz - 1)]
                else:
                    v = rand.randint(1, cur_n)
            qry.append([qtype, u, v])
        elif(qtype == "BUILD"):
            # u and v
            u = 0
            v = 0
            touched_sz = len(touched)
            while(u == v or u > cur_n or v > cur_n):
                if(rand.randint(0, 100) <= 99 and touched_sz > 2):
                    u = touched[rand.randint(0, touched_sz - 1)]
                    v = touched[rand.randint(0, touched_sz - 1)]
                else:
                    u, v = sample_pair(1, cur_n, rand)
            s.append(cur_n)
            maxn = max(maxn, cur_n)
            qry.append([qtype, u, v])
            touched.append(u)
            touched.append(v)
        elif(qtype == "EXPAND"):
            # k
            k = rand.randint(1, n - cur_n)
            s.append(cur_n + k)
            maxn = max(maxn, back(s))
            qry.append([qtype, k])
        else:
            # k
            k = sqrt_dist(len(s) - 1, 4, rand)
            qry.append([qtype, k])

            touched = []

            for i in range(k):
                if(len(s) > 1):
                    s.pop()
                else:
                    break

    cur_n = back(s)

    if(cur_n < n):
        qry.append(["EXPAND", n - cur_n])
    
    q_left = q - len(qry)

    if(not build_before_saikai):
        touched = []

    for _ in range(q_left):
        # random queries without timewarp
        dist = [2, 1 if not build_before_saikai else 0, 0, 0]

        touched_sz = len(touched)
        u = 0
        v = 0
        while(u == v):
            if(rand.randint(0, 100) <= 80 and touched_sz > 2):
                u = touched[rand.randint(0, touched_sz - 1)]
            else:
                u = rand.randint(1, n)
            
            if(rand.randint(0, 100) <= 80 and touched_sz > 2):
                v = touched[rand.randint(0, touched_sz - 1)]
            else:
                v = rand.randint(1, n)

        qtype = qtypes[sample(pref_sum(dist), rand)]

        qry.append([qtype, u, v])
        if(qtype == "BUILD"):
            touched.append(u)
            touched.append(v)

        pass

    # example:
    # T, N = map(int, args[:2])
    # for cas in range(T):
    #     n = rand.randint(1, N)
    #     yield [rand.randint(-A, A) for i in range(n)]
    return qry


if __name__ == '__main__':
    write_to_file(format_case, gen_random, argv[1:], stdout)
