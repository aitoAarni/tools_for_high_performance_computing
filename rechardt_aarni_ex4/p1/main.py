import os
os.environ['OMP_NUM_THREADS'] = '1'

import time
import numpy as np
from scipy.linalg import eig
import matplotlib.pyplot as plt

def main():
    N_values = np.logspace(np.log10(50), np.log10(1000), num=15, dtype=int)
    
    num_trials = 20 

    avg_times = []
    std_times = []

    print("N\tAvg CPU Time (s)\tStd Dev (s)")
    
    for N in N_values:
        times = []
        for _ in range(num_trials):
            A = np.random.rand(N, N)

            start_time = time.process_time()
            eig(A)
            end_time = time.process_time()

            times.append(end_time - start_time)

        avg = np.mean(times)
        std = np.std(times)
        avg_times.append(avg)
        std_times.append(std)
        print(f"{N}\t{avg:.4f}\t\t\t{std:.4f}")

    c = avg_times[-1] / (N_values[-1]**3)
    theoretical_times = c * (N_values**3)

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

    ax1.errorbar(N_values, avg_times, yerr=std_times, fmt='-o', capsize=5, label='Measured Data')
    ax1.set_title('Measured CPU Time (Linear Scale)')
    ax1.set_xlabel('Matrix Size N')
    ax1.set_ylabel('CPU Time (seconds)')
    ax1.grid(True, ls="--")
    ax1.legend()

    ax2.plot(N_values, theoretical_times, 'r--', label='Theoretical $O(N^3)$')
    ax2.set_title('Theoretical $O(N^3)$ Time (Linear Scale)')
    ax2.set_xlabel('Matrix Size N')
    ax2.set_ylabel('CPU Time (seconds)')
    ax2.grid(True, ls="--")
    ax2.legend()

    plt.tight_layout()
    plt.savefig('eigenvalue_linear_comparison.png', dpi=300, bbox_inches='tight')
    print("\nSuccess! Plot saved as 'eigenvalue_linear_comparison.png'")

if __name__ == "__main__":
    main()