"""Prints the test data in the correct input format."""

from kg.formatters import * ### @import

@formatter
def format_case(stream, queries, *, print, **kwargs):
    ... # write your formatter here

    # example:
    print(len(queries))
    for arr in queries:
        print(" ".join(map(str, arr)))
