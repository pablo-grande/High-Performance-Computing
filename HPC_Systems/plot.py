import pandas as pd

from matplotlib import pyplot as plt
from os import walk

data = {}
# get data from results files
for dirpath, dirnames, filenames in walk("."):
    for filename in filenames:
        if filename.endswith(".txt"):
            key = int(filename.split(".")[0])
            with open(filename, "r") as _file:
                data[key] = [float(i) for i in _file.readlines()]

df = pd.DataFrame(data)
df = df.reindex(sorted(data.keys()), axis=1)

p = df.plot.box()
p.set_title("Sample parametric study")
p.set_xlabel("app parameter")
p.set_ylabel("Time (seconds)")
plt.show()
