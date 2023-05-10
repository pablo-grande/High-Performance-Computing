import pandas as pd

from matplotlib import pyplot as plt
from os import walk

data = {}
# get data from results files
for _, dirnames, _ in walk("."):
    for _dir in dirnames:
        for _, _, filenames in walk(_dir):
            for filename in filenames:
                if not filename.endswith(".sge"):
                    _, benchmark, size, trail = filename.split("_")
                    threads = trail.split(".")[0]
                    key = f"{benchmark}.{size}-{threads}"
                    if not key in data:
                        data[key] = []
                    with open(f"{_dir}/{filename}", "r") as _file:
                        content = _file.readlines()
                    # find our time in seconds
                    t_in_seconds_str = [t for t in content if t.strip().startswith("Time in seconds")]
                    t_in_seconds = float(t_in_seconds_str[0].strip().split("=")[-1])
                    data[key].append(float(t_in_seconds))

df = pd.DataFrame(data)
df = df.reindex(sorted(data.keys()), axis=1)

p = df.plot.box()
p.set_title("Performance study")
p.set_xlabel("Benchmark version and threads")
p.set_ylabel("Time (seconds)")
plt.show()
