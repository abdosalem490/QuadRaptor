from pydub import AudioSegment

# Replace 'your_audio_file.m4a' with the path to your audio file
file_path = 'Propeller-1.m4a'

# Convert .m4a to .wav using pydub
audio = AudioSegment.from_file(file_path, format='m4a')


audio.export('Propeller-1.wav', format='wav')
