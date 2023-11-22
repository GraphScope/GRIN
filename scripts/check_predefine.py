import sys 

from pathlib import Path

def get_macros(fn, prefix='#define'):
    with open(fn) as f:
        lines = f.readlines()
    macros = []
    for line in lines:
        if (line.startswith(prefix) and 
            not any (x in line for x in ['NULL', 'PREDEFINE', '__cplusplus'])):
            macros.append(line.split()[1])
    return macros

if __name__ == '__main__':
    correct = set(get_macros(Path('..') / 'template' / 'features.h'))
    for s in sys.argv[1:]:
        for p in ['#define', '#ifdef']:
            x = set(get_macros(Path('..') / 'storage' / s / 'predefine.h', p))
            if x - correct:
                print(s, p, x - correct)
            else:
                print(s, p, 'OK')