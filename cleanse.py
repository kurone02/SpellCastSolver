import re

pattern = re.compile(r".*[^(a-z^)].*\n", re.A)

out = open("data.dic", "w")

with open("en_US-large.txt") as f:
    for line in f:
        x = pattern.sub("", line)
        # print(pattern.match(line))
        out.write(f"{x}")

out.close()

