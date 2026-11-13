G = {
    'E': ['TA'],
    'A': ['+TA', '#'],
    'T': ['FB'],
    'B': ['*FB', '#'],
    'F': ['(E)', 'i']
}
first, follow = {k : set() for k in G}, {k : set() for k in G}

def fs(s):
    r = set()
    for c in s:
        f = first[c] if c in G else {c}
        r.update(f - {"#"})
        if '#' not in f:
            return r
    return r | {'#'}

ch = True
while ch:
    ch = False
    for nt, prod in G.items():
        for p in prod:
            old = len(first[nt])
            first[nt].update(fs(p))
            if(len(first[nt])) != old:
                ch = True

follow['E'].add('$')

ch = True
while ch:
    ch = False
    for nt, prod in G.items():
        for p in prod:
            for i, c in enumerate(p):
                if c in G:
                    old = len(follow[c])
                    b = p[i + 1 : ]
                    f = fs(b) if b else {'#'}
                    follow[c].update(f - {'#'})
                    if not b or '#' in f:
                        follow[c].update(follow[nt])
                    if(len(follow[c])) != old:
                        ch = True

print("\nFIRST SETS")
print("-" * 30)
for nt in G:
    print(f"FIRST({nt})  = {first[nt]}")

print("\nFOLLOW SETS")
print("-" * 30)
for nt in G:
    print(f"FOLLOW({nt}) = {follow[nt]}")

table = {nt : {t: p for p in G[nt] for t in fs(p) - {'#'} | (follow[nt] if '#' in fs(p) else set())} for nt in G}

print("\nPREDICTIVE PARSING TABLE")
print("-" * 40)
for nt in table:
    print(f"{nt} : {table[nt]}")

def parse(s):
    s, st, i = s + '$', ['$', 'E'], 0

    print("\nPARSING PROCESS")
    print("-" * 65)
    print(f"{'STACK':<20}{'INPUT':<20}{'ACTION'}")
    print("-" * 65)

    while st:
        top, curr = st[-1], s[i]

        if top == curr == '$':
            return print("\nACCEPTED")

        if top not in G:
            if top == curr:
                st.pop()
                i += 1
                print(f"{''.join(st):<20}{s[i:]:<20}MATCH {top}")
            else:
                return print("\nREJECTED")

        else:
            p = table[top].get(curr)
            if not p:
                return print("\nREJECTED")

            st.pop()
            if p != '#':
                st.extend(reversed(p))

            print(f"{''.join(st):<20}{s[i:]:<20}{top} -> {p}")

parse(input("\nEnter input string: "))