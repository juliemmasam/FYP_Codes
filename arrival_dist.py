import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('data_points.csv')

plt.hist(data["Transmission_Duration"], bins=100)
plt.xlabel("Inter-arrival times in seconds")
plt.ylabel("Relative number of Generations")
plt.title("The Distribution of Inter-arrival times")
plt.savefig("trans_dist.png")
plt.show()
