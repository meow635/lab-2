import matplotlib.pyplot as plt
import csv

sizes = []
threads = []
times = []

with open('results.csv', 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        sizes.append(int(row['size']))
        threads.append(int(row['threads']))
        times.append(float(row['time']))

unique_sizes = sorted(set(sizes))
unique_threads = sorted(set(threads))

plt.figure()

for t in unique_threads:
    x = []
    y = []
    for i in range(len(sizes)):
        if threads[i] == t:
            x.append(sizes[i])
            y.append(times[i])
    plt.plot(x, y, marker='o', label=f'{t} threads')

plt.xlabel("Matrix size (N)")
plt.ylabel("Time (seconds)")
plt.title("Execution time vs matrix size")
plt.legend()
plt.grid()

plt.savefig("time_plot.png")
plt.show()


plt.figure()

for size in unique_sizes:
    t1 = None
    x = []
    y = []

    for i in range(len(sizes)):
        if sizes[i] == size and threads[i] == 1:
            t1 = times[i]

    for i in range(len(sizes)):
        if sizes[i] == size:
            x.append(threads[i])
            y.append(t1 / times[i])

    plt.plot(x, y, marker='o', label=f'N={size}')

plt.xlabel("Number of threads")
plt.ylabel("Speedup")
plt.title("Speedup vs threads")
plt.legend()
plt.grid()

plt.savefig("speedup_plot.png")
plt.show()