from subprocess import Popen, TimeoutExpired, PIPE
import numpy as np
import sys
import time
import math

def is_path_correct(path):
    if len(path) > 0 and min(path) == 2 and max(path) == len(path) + 1:
        if len(path) == len(set(path)):
            return True
    return False

def calc_cost(path, distances):
    d = distances[0][path[0]]
    for i in range(0, len(path)-1):
        d += distances[path[i]][path[i+1]]
    d += distances[path[-1]][1]
    return d

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python run.py dataset_path [exe_path] [timeout_sec]')
        exit(1)
    else:
        datapath = sys.argv[1]
        timeout_sec = 60
        exepath = './a.out'

        if len(sys.argv) > 2:
            exepath = sys.argv[2]
            if len(sys.argv) > 3:
                timeout_sec = int(sys.argv[3])

    proc = Popen([exepath], stdout=PIPE, stdin=open(datapath, 'r'))

    start_time = time.perf_counter()
    try:
        output, error = proc.communicate(timeout=timeout_sec)
    except TimeoutExpired:
        proc.kill()
        output, error = proc.communicate()
    end_time = time.perf_counter()

    print('TIME =', end_time - start_time)

    records = output.decode('utf-8').split('\n')
    if len(records) > 1:
        records = records[0:-1]

    max_tries = min(3, len(records))
    for i in range(max_tries):
        last_record = [int(j) for j in records[-1-i].split(',')[0:-1]]
        if is_path_correct(last_record):
            break
        print('FAIL pass', i+1, 'line:', records[-1-i])
        if i == max_tries-1:
            print('RUN FAILED')
            exit(1)

    data = np.loadtxt(datapath, skiprows=1)
    distances = [[math.sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2) for p1 in data] for p2 in data]

    print('PASS, cost =', calc_cost(last_record, distances))
