from math import sin, pi

def color(r, g, b):
    r = int(r)
    g = int(g)
    b = int(b)
    return f"\x1b[38;2;{r};{g};{b}m"

i = 0;
def rainbow(t):
    i = 0
    for c in t:
        i += 0.1;
        r = sin(i         ) * 127 + 128
        g = sin(i + 2*pi/3) * 127 + 128
        b = sin(i + 4*pi/3) * 127 + 128
        print(color(r, g, b), end = "")
        print(c, end = "")

reset = "\033[m"

print(rainbow("a big bloody ass fox\na"))

print(reset)
