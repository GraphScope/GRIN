import sys 

from pathlib import Path

def get_macros(fn):
    with open(fn) as f:
        lines = f.readlines()
    macros = []
    for line in lines:
        if line.startswith('#define') and 'NULL' not in line:
            macros.append(line.split()[1])
    return macros

def valid(expr, macros):
    expr = expr.strip()
    if expr == '*':
        return True
    elif '||' in expr:
        segs = expr.split('||')
        for s in segs:
            if valid(s, macros):
                return True
        return False
    elif '&&' in expr:
        segs = expr.split('&&')
        for s in segs:
            if not valid(s, macros):
                return False
        return True
    elif expr[0] == '!':
        if valid(expr[1:], macros):
            return False
        return True
    elif expr.startswith('defined('):
        return valid(expr[len('defined('): -1], macros)
    elif expr.startswith('GRIN'):
        return (expr in macros)
    else:
        assert False, expr

def get_apis_with_expr(fn):
    with open(fn) as f:
        lines = f.readlines()

    expr = '*'
    for line in lines[27:]:
        if line.startswith('#ifdef'):
            assert expr == '*', 'nested macros'
            expr = line.split(' ')[1].strip()
        elif line.startswith('#if '):
            assert expr == '*', 'nested macros'
            expr = line.strip()[4:]
        elif line.startswith('#endif'):
            expr = '*'
        elif line.startswith('#ifndef'):
            assert expr == '*', 'nested macros'
            expr = '!'+line.split(' ')[1].strip()
        elif not line.startswith((' ', '*/', '}', '/', '#', 'type')):
            if line.strip():
                yield line.strip(), expr


def get_enabled_apis(prefix, macros, target):
    for item in Path(prefix).rglob('*'):
        if item.is_file():
            print(item)
            apis = []
            for api, expr in get_apis_with_expr(item):
                if valid(expr, macros):
                    apis.append(api[:api.find('(')])
            print(apis)
            print()
                


if __name__ == '__main__':
    macros = get_macros(sys.argv[1])
    get_enabled_apis(sys.argv[2], macros, sys.argv[3])
