import numpy as np
from datetime import datetime
import time
import csv


# data generation function
def data_fn():
    """
    This function specifically generates some data points for processing

    Some generalized considerations:
        Average delay = 350ms; hence a delay between 250 and 400
        Average flows = 19.9k/s; hence 19k abd 25k

    """
    start = time.time()
    start_time = []
    transmission_duration = []
    packets = []

    i = 0
    while (time.time() - start) < 900:
        start_time.append(datetime.now())
        packets.append(np.random.randint(19000, 25000))
        transmission_time = 0.001*np.random.randint(250, 400)
        time.sleep(transmission_time)
        transmission_duration.append(transmission_time)
        i += 1

    print("Generated " + str(i) + " data points")
    return zip(start_time, transmission_duration, packets)


# the main program here
data_points = data_fn()

# writing to a file
with open("data_points.csv", "w", newline='') as csv_file:
    file_headers = ["Start_Time", "Transmission_Duration", "Packets"]
    writer = csv.DictWriter(csv_file, fieldnames=file_headers)
    writer.writeheader()

    for start_time, transmission_duration, packets in data_points:
        writer.writerow({"Start_Time": start_time, "Transmission_Duration": transmission_duration, "Packets": packets})
