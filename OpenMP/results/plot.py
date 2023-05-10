import pandas as pd

from matplotlib import pyplot as plt
from os import walk

data = {}
# get data from results files
for dirpath, dirnames, filenames in walk("."):
    for filename in filenames:
        if not filename.endswith(".py"):
            fname, threads = filename.split(".")[0].split("_")
            # values with 4 threads are discarded because they do not provide enough values
            if threads == "4":
                continue
            version = fname.split("pmm")[1]
            key = f"v{version}_t{threads}"
            if not key in data:
                data[key] = []
            with open(filename, "r") as _file:
                content = _file.readlines()
                time = content[1].split("\t")[1].strip().split("m")[1].rstrip("s")
                data[key].append(float(time))

df = pd.DataFrame(data)
df = df.reindex(sorted(data.keys()), axis=1)

p = df.plot.box()
p.set_title("Sample parametric study")
p.set_xlabel("code version and threads")
p.set_ylabel("Time (seconds)")
plt.show()
