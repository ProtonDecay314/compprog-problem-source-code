def pref_sum(a):
    ap = [0]
    for v in a:
        ap.append(ap[-1] + v)
    return ap

def sample(ap, rand):
    rnd = rand.randint(0, ap[-1] - 1)

    n = len(ap) - 1

    for i in range(n):
        if(ap[i] <= rnd and rnd < ap[i + 1]):
            return i

def sample_pair(mn, mx, rand):
    i = 0
    j = 0
    while(i == j):
        i = rand.randint(mn, mx)
        j = rand.randint(mn, mx)
    
    return (min(i, j), max(i, j))

def back(d):
    ans = d.pop()
    d.append(ans)
    return ans


def ipw(n, pw):
    if(n == 1): return 1
    l = 0
    r = n

    while(r - l > 1):
        m = (l + r) >> 1

        if(m ** pw <= n): l = m
        else: r = m
    return l

def sqrt_dist(mx, pw, rand):
    return mx + 1 - ipw(rand.randint(1, max(1, ((mx + 1) ** pw) - 1)), pw)