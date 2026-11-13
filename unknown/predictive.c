# cook your dish here

table = {
    ('E', 'i'): "TR", ('E', '('): "TR",
    ('R', '+'): "+TR", ('R', ')'): "#", ('R', '$'): "#",
    ('T', 'i'): "FY", ('T', '('): "FY",
    ('Y', '*'): "*FY", ('Y', '+'): "#", ('Y', ')'): "#", ('Y', '$'): "#",
    ('F', 'i'): "i", ('F', '('): "(E)"
}

def main():
    st = "$E"
    ip = 0

    input_str = input("Enter the input string (use i for identifier): ")
    input_str += '$'

    print("\nStack\t\tInput\t\tAction")
    print("---------------------------------------------")

    while st:
        X = st[-1]
        a = input_str[ip]

        print(f"{st}\t\t{input_str[ip:]}\t\t", end="")

        if X == '$' and a == '$':
            print("Accept")
            return

        if X == a:
            st = st[:-1]
            ip += 1
            print("Match", a)

        elif X.isupper() and (X, a) in table:
            rhs = table[(X, a)]
            st = st[:-1]

            print(X, "->", "epsilon" if rhs == "#" else rhs)

            if rhs != "#":
                st += rhs[::-1]

        else:
            print("Error")
            return

    print("Rejected")


main()

