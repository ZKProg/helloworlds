import os
import sys
import re

stack = "I have been studying hard since 1970 to become a better programmer."

needle_simple = r"st(u)+dy"
needle_all = r"e"
# Mind the syntax of the group search => inside the parentheses! 
needle_group = r"I have (?P<verb>\w+) studying hard (.)*"

result_simple = re.search(needle_simple, stack)
result_all = re.findall(needle_all, stack)
needle_group = re.search(needle_group, stack)

print(result_simple)
print(result_all)

if needle_group is not None:
    print(needle_group.group('verb'))