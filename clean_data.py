import pandas as pd
import csv

data = pd.read_csv("data_points.csv")
data_packets = data["Packets"]

print(data_packets.head())
print(len(data_packets))

with open("clean_data.csv", 'w') as csv_file:
    file_headers = ["packets_1", "packets_2", "packets_3", "packets_4"]
    writer = csv.DictWriter(csv_file, fieldnames=file_headers)
    writer.writeheader()

    for index in range(0, (len(data_packets)-3)):
        writer.writerow({"packets_1": data_packets[index], "packets_2": data_packets[index+1],
                         "packets_3": data_packets[index+2], "packets_4": data_packets[index+3]})
        index += 1