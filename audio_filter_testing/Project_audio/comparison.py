import numpy as np
import scipy.io.wavfile as wav
from scipy.signal import butter, lfilter
import matplotlib.pyplot as plt

# Load the input audio file
input_file = "input.wav"
sample_rate, data = wav.read(input_file)

# Define the filter parameters
low_freq = 500  # Hz
high_freq = 4000  # Hz
cutoff_freq = 2000  # Hz
order = 5  # Filter order

# Calculate the FFT of the audio data
fft_data = np.fft.fft(data)

# Calculate the frequency values for each FFT sample
freqs = np.fft.fftfreq(len(data), 1.0/sample_rate)

# Find the indices of the FFT samples within the frequency range of interest
idx_band = np.where((freqs >= low_freq) & (freqs <= high_freq))[0]
idx_low = np.where(freqs < cutoff_freq)[0]
idx_high = np.where(freqs > cutoff_freq)[0]

# Create the filters
b_band, a_band = butter(order, [low_freq/(sample_rate/2), high_freq/(sample_rate/2)], btype='band')
b_low, a_low = butter(order, cutoff_freq/(sample_rate/2), btype='low')
b_high, a_high = butter(order, cutoff_freq/(sample_rate/2), btype='high')

# Apply the filters to the selected FFT data to remove noise
filtered_data_band = lfilter(b_band, a_band, data)
filtered_data_low = lfilter(b_low, a_low, data)
filtered_data_high = lfilter(b_high, a_high, data)

# Plot the original waveform and the filtered waveforms
time_array = np.arange(0, len(data)) / sample_rate
plt.figure(figsize=(10,8))
plt.subplot(4, 1, 1)
plt.plot(time_array, data)
plt.title('Original Signal')
plt.xlabel('Time (seconds)')
plt.ylabel('Amplitude')

plt.subplot(4, 1, 2)
plt.plot(time_array, filtered_data_band)
plt.title('Bandpass Filtered Signal')
plt.xlabel('Time (seconds)')
plt.ylabel('Amplitude')

plt.subplot(4, 1, 3)
plt.plot(time_array, filtered_data_low)
plt.title('Lowpass Filtered Signal')
plt.xlabel('Time (seconds)')
plt.ylabel('Amplitude')

plt.subplot(4, 1, 4)
plt.plot(time_array, filtered_data_high)
plt.title('Highpass Filtered Signal')
plt.xlabel('Time (seconds)')
plt.ylabel('Amplitude')

plt.tight_layout()
plt.show()

# Save the filtered audio data to new files
wav.write("output_bandpass.wav", sample_rate, filtered_data_band.astype(np.int16))
wav.write("output_lowpass.wav", sample_rate, filtered_data_low.astype(np.int16))
wav.write("output_highpass.wav", sample_rate, filtered_data_high.astype(np.int16))