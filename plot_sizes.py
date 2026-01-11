import csv
from collections import Counter
import matplotlib.pyplot as plt

sizes=[]

with open("avalanches.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        s = int (row["size"])
        if s > 0:
            sizes.append(s)

counts = Counter(sizes)

x= list(counts.keys())
y= list (counts.values())

plt.loglog(x, y, 'o')
plt.xlabel("Avalanche Size")
plt.ylabel("Frequency")
plt.title("Sandpile avalanche size distribution")
plt.show()
