import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('data_points.csv')

plt.hist(data["Packets"], bins=100)
plt.xlabel("Number of Packets")
plt.ylabel("Relative number of Generations")
plt.title("The Distribution of Generated Packets")
plt.savefig("hist_dist.png")
plt.show()
