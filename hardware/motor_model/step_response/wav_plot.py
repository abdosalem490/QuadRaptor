import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile

# Replace 'your_audio_file.m4a' with the path to your audio file
file_path = 'Propeller-1.wav'

sample_rate, data = wavfile.read(file_path)

# If the audio file is stereo, take only one channel
if len(data.shape) == 2:
    data = data[:, 0]

# Create time array
time = np.arange(0, len(data)) / sample_rate

# Plot the amplitude
plt.figure(figsize=(10, 4))
plt.plot(time, data, label='Amplitude')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.title('Sound Wave Amplitude')
plt.legend()
plt.show()
