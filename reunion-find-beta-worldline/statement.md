## Statement

**ふたりの誕生**
(The two's birth)

*From Harumakigohan's song "Birth": https://www.youtube.com/watch?v=KJWek21tuyA*

---

[Last year](https://codeforces.com/gym/507096/problem/H), Nana and Lili, residents of the Blue Planet, made a grand plan to reunite -- they would fly away to the next planet on the back of a sky whale. Unfortunately, their plan failed since they weren't able to reach the sky whale!

*Is all hope lost?*

Surely this can't be it. Surely *this can't be the end*!

Maybe... if Nana and Lili waited for long enough, more roads and cities would be built that would allow them to find a place to reunite.

Maybe... in an *alternate worldline*, they could've reunited.

One day, a [D-mail](https://steins-gate.fandom.com/wiki/D-Mail) arrives explaining to Nana the secrets of time travel and multiversal manipulation. Using this information, Nana builds a [phonewave](https://steins-gate.fandom.com/wiki/PhoneWave_(name_subject_to_change)) with the goal of escaping the [alpha attractor field](https://steins-gate.fandom.com/wiki/Attractor_Field/Alpha). It is only in a worldline outside the alpha attractor field -- one that Nana dubs a "beta worldline" -- that they could hope to reunite.

With newfound hope, Nana uses the phonewave to traverse various worldlines in search of the one where she and Lili could reunite.



For this problem, there will be a number of queries.

Initially, there are no cities on the Blue Planet. However, some cities could be built over time.

The query `EXPAND k` creates $k$ new cities. The cities are numbered in the order they were built, starting from `1`.

For example, `EXPAND 3` creates cities `1`, `2`, and `3`. Then, another query `EXPAND 2` creates cities `4` and `5`.

The query `BUILD u v` creates a bidirectional bridge between cities `u` and `v`. If a bridge already exists between cities `u` and `v`, a new bridge will be built. For example, `BUILD 1 2` will build a bridge between cities `1` and `2`.

Next, the query `TIMEWARP k` will send Nana $k$ years back into the past and allow her to explore a new worldline. Specifically, `TIMEWARP k` will undo the last $k$ BUILD and EXPAND queries. No other queries are undone.

Finally, when you encounter the query `SAIKAI u v`, you must determine whether Nana and Lili could reunite. Specifically, if Nana and Lili start at cities $u$ and $v$, respectively, determine if Nana and Lili could reach a common city simply by walking through the cities and the bridges between them.

The time limit bell rings. Help Nana find a worldline where she and Lili could reunite!

## Input

The first line of input contains $q$, the number of queries.

Then, $q$ lines follow, representing each of the queries.

Each of these lines starts with a string consisting of one word -- the query type $q_t$. The query type could be `SAIKAI`, `BUILD`, `EXPAND`, or `TIMEWARP`.

If $q_t = \text{SAIKAI}$, then two integers $u$ and $v$ follow, representing the starting cities of Nana and Lili, respectively.

If $q_t = \text{BUILD}$, then two integers $u$ and $v$ follow, representing the endpoints of the bridge.

If $q_t = \text{EXPAND}$, then one integer $k$ follows, representing the number of new cities to be built.

Finally, if $q_t = \text{TIMEWARP}$, one integer $k$ follows, representing the number of BUILD and EXPAND queries to undo.

## Constraints

Let $n$ be the maximum number of cities on the Blue Planet in any worldline.

**For all Subtasks:**

$1 \le n \le 10^9$,
$2 \le q \le 2 \cdot 10^5$

At any point, $1 \le u, v \le \text{the number of cities}$

**Subtask 1** (5 points): $n \le 3, q \le 2000$, no TIMEWARP queries.

**Subtask 2** (5 points): $n \le 3, q \le 2000$  

**Subtask 3** (10 points): $n, q \le 2000$, no TIMEWARP queries.

**Subtask 4** (10 points): $n, q \le 2000$

**Subtask 5** (15 points): $n, q \le 200000$, no TIMEWARP queries, all BUILD queries happen before SAIKAI queries

**Subtask 6** (20 points): $n, q \le 200000$, no TIMEWARP queries

**Subtask 7** (25 points): $n, q \le 200000$

**Subtask 8** (10 points): No additional constraints  

## Output

For each SAIKAI query, output one line. Print `SAIKAI` if Nana and Lili could reach a common city by traveling only through the cities and the bridges connecting them. Otherwise, print `KONAI SAIKAI`.


## Sample Input 1

    12
    EXPAND 5
    BUILD 1 2
    BUILD 2 3
    SAIKAI 1 3
    SAIKAI 3 4
    TIMEWARP 1
    BUILD 3 4
    SAIKAI 1 3
    SAIKAI 3 4
    BUILD 2 3
    SAIKAI 1 3
    SAIKAI 3 4


## Sample Output 1

    SAIKAI
    KONAI SAIKAI
    KONAI SAIKAI
    SAIKAI
    SAIKAI
    SAIKAI

![center](sample-tcase1.png)

The first query is an expand query. This creates $5$ new cities, as seen in Figure 1.a.

Then, two bridges are built: First, a bridge between cities $1$ and $2$ are built. Then, a bridge between cities $2$ and $3$ are built. This is seen in Figures 1.b and 1.c.

As seen in Figure 1.c., cities $1$ and $3$ are connected, so the answer is "SAIKAI" for this query. Then, for the next query, cities $3$ and $4$ are not connected, so the answer is "KONAI SAIKAI".

Then, Nana performs a timewarp. This timewarp undoes the creation of one bridge (in this case, the bridge between cities $2$ and $3$ since this is the latest bridge built). This is shown in Figure 1.d.

A bridge between cities $3$ and $4$ is subsequently built. This is shown in Figure 1.e.

This time, no path between cities $1$ and $3$ exist, so the answer is "KONAI SAIKAI" for this test case. However, a path *does* exist between cities $3$ and $4$, so the answer is "SAIKAI" for this test case.

Another bridge is built, this time between cities $2$ and $3$. This is shown in Figure 1.f.

This time, there is a path from $1$ to $3$, so the answer for this test case is "SAIKAI". Similarly, there is also a path from $3$ to $4$, so the answer for this test case is "SAIKAI".

## Sample Input 2

    8
    EXPAND 3
    BUILD 1 2
    SAIKAI 1 3
    BUILD 2 3
    SAIKAI 1 3
    TIMEWARP 1
    SAIKAI 1 2
    SAIKAI 1 3

## Sample Output 2

    KONAI SAIKAI
    SAIKAI
    SAIKAI
    KONAI SAIKAI

![center](sample-tcase2.png)

3 cities are created (Figure 2.a.).

Then, a bridge between cities $1$ and $2$ is built (Figure 2.b.).

Cities $1$ and $3$ are not connected, so the answer for this test case is "KONAI SAIKAI".

Another bridge between cities $2$ and $3$ is built (Figure 2.c.).

This time, cities $1$ and $3$ are connected, so the answer for this test case is "SAIKAI".

Then, Nana performs a TIMEWARP, which undoes the creation of the bridge from cities $2$ to $3$, since it is the latest bridge built (Figure 2.d.).

Cities $1$ and $2$ are still connected, so the answer for this test case is "SAIKAI".

Finally, cities $1$ and $3$ are no longer connected due to the TIMEWARP query, so the answer for this test case is "KONAI SAIKAI".