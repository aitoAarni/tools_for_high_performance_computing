import statistics
import sys

# run chmod +x get_freq 
# run ./get_freq 100 > freq_output.txt
# run python3 task1.py
# or
# run python3 task1.py > results.txt


def analyze_frequencies(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()

    # Parse the data: list of lists, where each inner list is a row of core frequencies
    data = []
    for line in lines:
        row = [float(x) for x in line.split()]
        if row: 
            data.append(row)


    num_cores = len(data[0])
    print(f" CPU Frequency Analysis ({len(data)} samples)") 
    print(f"Detected {num_cores} logical cores.\n")

    cores_data = [ [row[i] for row in data] for i in range(num_cores) ]

    for i, core_freqs in enumerate(cores_data):
        avg = statistics.mean(core_freqs)
        stdev = statistics.stdev(core_freqs) if len(core_freqs) > 1 else 0.0
        print(f"Core {i}: Average = {avg:.2f} MHz, Standard Deviation = {stdev:.2f} MHz")

if __name__ == "__main__":
    analyze_frequencies('freq_output.txt')