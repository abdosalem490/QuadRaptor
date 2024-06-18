import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Load the data from a CSV file
file_path = 'HMC5883L/raw_data_1.csv'
data = pd.read_csv(file_path, header=None)

# Assuming the CSV file has columns: X, Y, Z
x_raw = data[0].values
y_raw = data[1].values

# Plot the raw data
plt.figure(1)
plt.scatter(x_raw, y_raw, label='Raw Data')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Raw Magnetometer Data')
plt.legend()
plt.axis('equal')
plt.show()

# Convert x_raw and y_raw to numpy arrays of type int
x_raw = x_raw.astype(int)
y_raw = y_raw.astype(int)

# Calculate offsets (center of the ellipse)
x_offset = (np.max(x_raw) + np.min(x_raw)) / 2
y_offset = (np.max(y_raw) + np.min(y_raw)) / 2

# Apply offsets to raw data
x_calibrated = x_raw - x_offset
y_calibrated = y_raw - y_offset


# Calculate scale factors
x_scale = (np.max(x_calibrated) - np.min(x_calibrated)) / 2
y_scale = (np.max(y_calibrated) - np.min(y_calibrated)) / 2
scale = max(x_scale, y_scale)

# Apply scale factors
x_calibrated /= scale
y_calibrated /= scale

# Plot calibrated data
plt.figure(2)
plt.scatter(x_calibrated, y_calibrated, label='Calibrated Data')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Calibrated Magnetometer Data')
plt.legend()
plt.axis('equal')
plt.show()


print('Offsets: ', x_offset, y_offset)
print('Scale: ', scale)