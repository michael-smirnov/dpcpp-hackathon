from subprocess import Popen, TimeoutExpired, PIPE
import numpy as np
import sys
import time
import math
import re

_line_matcher = re.compile(r'^(?:\d+,?)+$')

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

def parse_records(records: str):
    records = records.splitlines()
    records = [x.strip() for x in records]
    records = [x for x in records if x]
    return records

def parse_line(line: str):
    chunks = line.split(',')
    chunks = [x.strip() for x in chunks]
    chunks = [int(x) for x in chunks if x]
    return chunks

def compute_distances(datapath):
    data = np.loadtxt(datapath, skiprows=1)
    return [[math.sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2) for p1 in data] for p2 in data]

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

    records = parse_records(output.decode('utf-8'))
    records.reverse()

    last_path = None
    for i, record in enumerate(records):
        m = _line_matcher.match(record)
        if not m:
            continue
        path = parse_line(record)
        if is_path_correct(path):
            last_path = path
            break
        print(f'FAILED: "{record}"')

    if not last_path:
        print('Cannot parse output:')
        print('\n'.join(records))
        exit(1)

    distances = compute_distances(datapath)
    print('PASS, cost =', calc_cost(last_path, distances))
