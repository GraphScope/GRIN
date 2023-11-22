import sys 

from pathlib import Path

def get_macros(fn):
    with open(fn) as f:
        lines = f.readlines()
    macros = []
    for line in lines:
        if line.startswith('#define') and 'NULL' not in line and 'PREDEFINE' not in line:
            macros.append(line.split()[1])
    return macros

if __name__ == '__main__':
    correct = set(get_macros(Path('..') / 'template' / 'features.h'))
    for s in sys.argv[1:]:
        x = set(get_macros(Path('..') / 'storage' / s / 'predefine.h'))
        if x - correct:
            print(s, x - correct)
        else:
            print(s, 'OK')