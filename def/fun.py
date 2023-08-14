import re
import sys

if __name__ == '__main__':
    st = 'LIBRARY '
    alias = sys.argv[1]
    st += alias + '.dll\nEXPORTS\n'
    f = open('1.txt').read()
    pattern = '#pragma comment\(linker,.*'
    for line in re.findall(pattern, f):
        line = str(line).split(':')
        num = line[1].find('=')
        fun = line[1][:num]
        line = line[1].split('@')
        num = line[1].find('"')
        val = line[1][:num]
        st += '    ' + fun + '=' + alias + '.' + fun + ' @' + val + '\n'
    file = open('fun.def', 'w')
    file.write(st)
    file.close()
