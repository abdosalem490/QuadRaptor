import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Function to calculate and plot linear regression
def plot_regression(ax, x, y, xlabel, ylabel, title):
    slope, intercept = np.polyfit(x, y, 1)  # Calculate slope and intercept
    ax.scatter(x, y, color='b', label=f'{ylabel} vs {xlabel}')  # Scatter plot
    ax.plot(x, slope * x + intercept, color='r', label=f'Regression line: y = {slope:.2f}x + {intercept:.2f}')  # Regression line
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    ax.legend()

file_path = 'thrust_current.csv'
df = pd.read_csv(file_path)

df['Efficiency'] = df['Thrust'] / df['Current']

df['Efficiency'] = df['Efficiency'].fillna(0)


# Create subplots
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 18))

plot_regression(ax1, df['Throttle'], df['Thrust'], 'Throttle', 'Thrust', 'Thrust vs Throttle')

plot_regression(ax2, df['Throttle'], df['Current'], 'Throttle', 'Current', 'Current vs Throttle')

plot_regression(ax3, df['Throttle'], df['Efficiency'], 'Throttle', 'Efficiency', 'Efficiency vs Throttle')

plt.tight_layout()
plt.show()
