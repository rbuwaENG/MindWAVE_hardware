import numpy as np
import scipy.io.wavfile as wav
from scipy.signal import butter, lfilter

# Load the input audio file
input_file = "input.wav"
sample_rate, data = wav.read(input_file)

# Define the bandpass filter parameters
low_freq = 500  # Hz
high_freq = 4000  # Hz
order = 5  # Filter order

# Calculate the FFT of the audio data
fft_data = np.fft.fft(data)

# Calculate the frequency values for each FFT sample
freqs = np.fft.fftfreq(len(data), 1.0/sample_rate)

# Find the indices of the FFT samples within the frequency range of interest
idx = np.where((freqs >= low_freq) & (freqs <= high_freq))[0]

# Create the bandpass filter
b, a = butter(order, [low_freq/(sample_rate/2), high_freq/(sample_rate/2)], btype='band')

# Apply the filter to the selected FFT data to remove noise
filtered_data = lfilter(b, a, data)

# Save the filtered audio data to a new file
output_file = "outputbandpass.wav"
wav.write(output_file, sample_rate, filtered_data.astype(np.int16))