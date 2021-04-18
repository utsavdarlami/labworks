import sys
from graphviz import Digraph

def parse_grammar(grammars):
    """
       Grammar Parser
    """
    global G, start, terminals, nonterminals, symbols
    for line in grammars:

        line = " ".join(line.split())
        if line == '\n':
            break
        # head = line[:line.index("->")].strip()
        arrow_index = line.index("->")
        # print(arrow_index)

        # print(line[:arrow_index][1])
        head = line[:arrow_index].strip()  # Before Arrow ->

        after_arrow = line[arrow_index + 2:]  # After Arrow ->
        # print(after_arrow)

        tails = after_arrow.split('|')  # Break each rule seperated by |
        # print(tails)

        prods = [t.strip().split(' ') for t in tails]
        # Get single char from each tails given by the rule

        # print(prods)

        if not start:
            # For S' -> S
            start = head + "'"
            G[start] = [[head]]
            nonterminals.append(start)

        if head not in G:
            G[head] = []

        if head not in nonterminals:
            nonterminals.append(head)

        for prod in prods:
            G[head].append(prod)
            for char in prod:
                if char == EPSILON and char not in terminals:
                    terminals.append(char)

                # Check for small letters i.e terminals
                elif not char.isupper() and char not in terminals:
                    terminals.append(char)

                # Check for capital letters i.e Non terminals
                elif char.isupper() and char not in nonterminals and char not in terminals:
                    nonterminals.append(char)
                    G[char] = []    # non terminals dont produce other symbols

    symbols =  nonterminals+terminals  # Merge all the notations/symbols

def print_grammar():
    print("GRAMMAR:")
    # Grammar without S', Given Grammar Cleaned
    for head in G.keys():
        if head == start:
            continue
        print(f" {head} -> ",end='')
        num_prods = 0
        for prods in G[head]:
            if num_prods > 0:
                print("|",end=' ')
            for prod in prods:
                print(prod,end=' ')
            num_prods += 1
        print()

    print("\nAUGMENTED GRAMMAR:")
    i = 0
    for head in G.keys():
        for prods in G[head]:
            print(f"{str(i)}: {head} ->",end=' ')
            print(' '.join(prods)) # Join Single Production symbols with Space
            i += 1
    print()
    print(f"TERMINALS    : {terminals}")
    print(f"NONTERMINALS : {nonterminals}")
    print(f"SYMBOLS      : {symbols}")

first_seen = []
def FIRST(X):
    global first_seen
    first = []
    # first_seen = []
    first_seen.append(X)
    if X in terminals:  # CASE 1
        first.append(X) # terminal So add

    elif X in nonterminals:  # CASE 2 Found Non terminal is 1st
        non_term_prods = G[X]
        for production in non_term_prods:
            # CASE 2.1, first of non terminal is terminal
            if production[0] in terminals and production[0] not in first:
                # NON terminals
                first.append(production[0])
            else:  # CASE 2.2, first of non terminal is non-terminal
                for_break = False
                for nonterm in production:
                # nonterm = production[0]
                    if for_break or nonterm in terminals:
                        break

                    if nonterm not in first_seen:
                        first_of_nonterm = FIRST(nonterm)

                        for term in first_of_nonterm:
                            if term not in first:
                                first.append(term)

                        if EPSILON not in first_of_nonterm:
                            for_break = True
                                # FIRST(production)
    first_seen.remove(X)
    return first

def print_first():
    print("\nFIRST:")
    for head in G.keys(): # loop through each nonterminals in G
        print(f"{head} = {{",end=' ')
        terms = FIRST(head) # find the first of a single head/non-terminals

        print(' , '.join(terms),end=' ')
        print("}")

follow_seen = []
def FOLLOW(passed_head):
    global follow_seen
    follow = []
    follow_seen.append(passed_head)

    # CASE 1
    if passed_head == start:
        """
        follow of start symbol is $
        """
        follow.append('$')
        follow_seen.remove(passed_head)
        return follow


    for heads in G.keys():
        for prods in G[heads]:
            follow_head = False
            if passed_head in prods:
                next_symbol_pos = prods.index(passed_head) + 1
                # CASE 2
                while next_symbol_pos < len(prods):
                    """
                     Not in last postion, FIRST works for both terminal and
                     non terminal
                    """
                    symbol_first = FIRST(prods[next_symbol_pos])
                    for terms in symbol_first:
                        if terms not in follow:
                            follow.append(terms)
                    if EPSILON in symbol_first:
                        next_symbol_pos +=1
                        follow.remove(EPSILON)
                    else:
                        break

                # CASE 3 - in the last position
                else:
                    follow_head = True

                if follow_head and heads not in follow_seen:
                    for terms in FOLLOW(heads):
                        if terms not in follow:
                            follow.append(terms)

    follow_seen.remove(passed_head)

    return follow

def print_follow() :
    print("\nFOLLOW:")
    for head in G.keys(): # loop through each nonterminals in G
        print(f"{head} = {{",end=' ')
        terms = FOLLOW(head) # find the first of a single head/non-terminals
        print(' , '.join(terms),end=' ')
        print("}")

def closure(I):
    """
      Takes dictionary as input..
      returns the same dictionary by making a copy of it and expanding
    """
    J = I
    all_heads = J.keys() #type dict_keys
    main_heads = list(all_heads) # type change to list

    for heads in main_heads:
        heads_all_prods = J[heads]     #All
        for prods in heads_all_prods:
            dot_pos = prods.index('.')      # checks if final item or not
            if dot_pos + 1 < len(prods):
                sym_after_dot = prods[dot_pos + 1]
                if sym_after_dot in nonterminals : # Non terminals get expansion
#                     main_heads.append(prod_after_dot)
                    nonterminals_productions  = G[sym_after_dot]
#                     J[sym_after_dot/t] = []
                    for prod in nonterminals_productions:
                        item = ["."] + prod
                        if sym_after_dot not in main_heads:
                            main_heads.append(sym_after_dot)
                            J[sym_after_dot] = [item]
                        elif item not in J[sym_after_dot]:
                            J[sym_after_dot].append(item)
    return J # A dictionary

def GOTO(I, X):
    """
      I -> state name,dictionary
      X -> A Symbol
    """
    goto = {} # new state
    for heads in I.keys():
        for prods in I[heads]:
            for i in range(len(prods) - 1):
                if "." == prods[i] and X == prods[i + 1]: # symbol found after dot.
                    temp_prods = prods[:]
                    temp_prods[i], temp_prods[i + 1] = temp_prods[i + 1], temp_prods[i]
                    prod_closure = closure({heads: [temp_prods]}) # closure of changed dot prods
                    for keys in prod_closure:
                        if keys not in goto.keys():
                            goto[keys] = prod_closure[keys]
                        elif prod_closure[keys] not in goto[keys]:
                            for prod in prod_closure[keys]:
                                goto[keys].append(prod)
    return goto # dictionary # new state

def items():
    global C
    i = 1
    start_I0 = {start: [['.'] + G[start][0]]}
    C = {'I0': closure(start_I0)} # called closure for I0 only.
    C_heads = list(C.keys()) # list of I's
    try:
          for I in C_heads: # loop through I's
            for X in symbols:
                goto_i_x = GOTO(C[I], X)
                if goto_i_x and goto_i_x not in C.values():
                    item_name = 'I' + str(i)
                    C_heads.append(item_name)
                    C[item_name] = goto_i_x
                    i += 1
    except Exception as e:
        print(e)
        pass

def print_item() :
    print("\nITEMS:")
    for i in range(len(C)):
        print('I' + str(i) + ':')
        for keys in C['I' + str(i)]:
            for prods in C['I' + str(i)][keys]:
                new_canonical_prods = ' '.join(prods)
                print(f"  {keys} -> {new_canonical_prods}")
        print()

def ACTION(i, a):
    """
        i is state number
        a is symbol
        i -> a , gives what?
        adds at parse_table[i][index(a)]
    """
    global error
    for heads in C['I' + str(i)]: # loop through each i's Head
        for prods in C['I' + str(i)][heads]: # Loop through production array of the i's head
            for j in range(len(prods) - 1):
                if prods[j] == '.' and prods[j + 1] == a:
                    for k in range(len(C)):
                        if GOTO(C['I' + str(i)], a) == C['I' + str(k)]:
                            if a in terminals:
                                if "r" in parse_table[i][terminals.index(a)]:
                                    if error!=1:
                                        print(f"ERROR: Shift-Reduce Conflict at State {str(i)}, Symbol \' {str(terminals.index(a))} \'")
                                    error=1
                                    if "s"+str(k) not in parse_table[i][terminals.index(a)]:
                                        parse_table[i][terminals.index(a)] = parse_table[i][terminals.index(a)]+ "/s" + str(k)
                                    return parse_table[i][terminals.index(a)]
                                else:
                                    parse_table[i][terminals.index(a)] = "s" + str(k)
                            else:
                                parse_table[i][len(terminals) + nonterminals.index(a)] = str(k)
                            return "s" + str(k)
    for heads in C['I' + str(i)]:
        if heads != start:
            for prods in C['I' + str(i)][heads]:
                if prods[-1] == '.':             #final item
                    k = 0
                    for head in G.keys():
                        for Gprods in G[head]:
                            if head == heads and (Gprods == prods[:-1] ) and (a in terminals or a == '$'):
                                for terms in FOLLOW(heads):
                                    if terms == '$':
                                        index = len(terminals)
                                    else:
                                        index = terminals.index(terms)
                                    if "s" in parse_table[i][index]:
                                        if error!=1:
                                            print(f"ERROR: Shift-Reduce Conflict at State {str(i)}, Symbol \' {str(terms)} \'")
                                        error=1
                                        if "r"+str(k) not in parse_table[i][index]:
                                            parse_table[i][index] = parse_table[i][index]+ "/r" + str(k)
                                        return parse_table[i][index]
                                    elif parse_table[i][index] and parse_table[i][index] != "r" + str(k):
                                        if error!=1:
                                            print(f"ERROR: Reduce-Reduce Conflict at State {str(i)}, Symbol \' {str(terms)} \'")
                                        error=1
                                        if "r"+str(k) not in parse_table[i][index]:
                                                parse_table[i][index] = parse_table[i][index]+ "/r" + str(k)
                                        return parse_table[i][index]
                                    else:
                                        parse_table[i][index] = "r" + str(k)
                                return "r" + str(k)
                            k += 1
    if start in C['I' + str(i)] and G[start][0] + ['.'] in C['I' + str(i)][start]:
        parse_table[i][len(terminals)] = "acc"
        return "acc" # Return as accept
    return "" # return no action

def print_table():
    """
        Parsing table print
    """
    for i in range(len(parse_table)):  #row 9      #len gives number of states
        for j in symbols:              # col
            ACTION(i, j)

    print("PARSING TABLE:")
    print("+" + "--------+" * (len(symbols)+ 1))
    print("|{:^8}|".format('STATE'),end=" ")
    for terms in terminals:
        print("{:^7}|".format(terms),end=" ")
    print("{:^7}|".format("$"),end=" ")
    for nonterms in nonterminals:
        if nonterms == start:
            continue
        print("{:^7}|".format(nonterms),end=" ")
    print("\n+" + "--------+" * (len(symbols) + 1))
    for i in range(len(parse_table)):
        print("|{:^8}|".format(i),end=' ')
        for j in range(len(symbols)):
            print("{:^7}|".format(parse_table[i][j]),end=' ')
        print()
    print("+" + "--------+" * (len(symbols) + 1))

def look_at_parse_table(top_stack,curr_symbol):
    """
        top_stack  -> no. of state
    """
    if curr_symbol=="$":
        start_index  = len(terminals) # terminal
        return parse_table[top_stack][start_index]
    elif curr_symbol in terminals:
        term_index = terminals.index(curr_symbol)
        return parse_table[top_stack][term_index]
    elif curr_symbol in nonterminals:
        nonterm_index = len(terminals) + nonterminals.index(curr_symbol)
#         print(nonterm_index)
        return parse_table[top_stack][nonterm_index]
    else:
        return "none"

def process_input():
    get_input = input("\nEnter Input (e.g id = id * id): ")

    to_parse = (get_input + " $").split()

    curr_pointer = 0  # Current input symbol pointer
    stack = ['0']

    print("\n+--------+----------------------------+----------------------------+----------------------------+")
    print("|{:^8}|{:^28}|{:^28}|{:^28}|".format("STEP", "STACK", "INPUT", "ACTION"))
    print("+--------+----------------------------+----------------------------+----------------------------+")

    step = 1
    while True:
        curr_symbol = to_parse[curr_pointer]
        top_stack = int(stack[-1])
#         stack_content = ""
        input_content = ""

        print("|{:^8}|".format(step),end=" ")

        stack_content = "".join(stack)
        print("{:27}|".format(stack_content),end=' ')
#         input_content = "".join(to_parse)
        i = curr_pointer
        while i < len(to_parse):
            input_content += to_parse[i]
            i += 1
        print("{:>26} | ".format(input_content),end=' ')

        step += 1

        get_action = look_at_parse_table(top_stack,curr_symbol)

#         get_action = ACTION(top_stack, curr_symbol)
        if "/" in get_action:
            print("{:^26}|".format(get_action+". So conflict"))
            break
        if "s" in get_action:
            print("{:^26}|".format(get_action))
            stack.append(curr_symbol)
            stack.append(get_action[1:])
            curr_pointer += 1
        elif "r" in get_action:
            print("{:^26}|".format(get_action))
            i = 0
            for head in G.keys():
                for prods in G[head]:
                    if i == int(get_action[1:]):
                        for j in range(2 * len(prods)):
                            stack.pop()
                        state = stack[-1]
                        stack.append(head)
                        stack.append(parse_table[int(state)][len(terminals) + nonterminals.index(head)])
                    i += 1
        elif get_action == "acc":
            print("{:^26}|".format("ACCEPTED"))
            break
        elif get_action == "" :
#             print(f"ERROR: Unrecognized symbol {curr_symbol} |")
            print("{:^26}|".format("Not Accepted "))
            break
        else:
            print(f"Error : Invalid symbol {curr_symbol}  |")
#             print("{:^26}|".format("Not Accepted "))
#             print(f"ERROR: Unrecognized symbol {curr_symbol} |")
            break
    print("+--------+----------------------------+----------------------------+----------------------------+")

def construct_digraph():
    """
        To Construct Diagraph using C and parse_table
    """
    I = {}
    J = {}
    relation = []
    r1 = []
    Z = []
    pd = []
#     print("\nITEMS:")

    for i in range(len(C)):
#         print(f"I{str(i)} :")
        I[i] = 'I' + str(i)
        Z = ""
        for keys in C['I' + str(i)]: # keys = head
            Y = ""
            for prods in C['I' + str(i)][keys]:
                # print(G)
#                 zzz = "{:>{width}} ->".format(keys, width=len(max(G.keys(), key=len)))
                zzz = f" {keys} ->"
                pd = ""

                Z = Z + zzz
#                 print(zzz,end=' ')
                pd = ''.join(prods)
#                 print(pd)

                Z = Z + pd + "\n"
#                 print(f"z {Z}")
#                 print()
            Y = Y + Z
#         print()
#         print("J")
        J[i] = Y
#         print(Y,end=' ')

    for i in range(len(parse_table)):
        for j in symbols:
            ACTION(i, j)

    dot = Digraph()

    for i in range(len(C)):
        for a in symbols:
            rel = look_at_parse_table(i,a)
            if rel:
                # print rel
                if (len(rel) == 1):
                    r = int(rel)
                else:
                    if (rel == 'acc') or (rel[0] == 'r'):
                        continue
                    elif '/' in rel:
                        spos = rel.index('s')
                        rel = rel[spos:spos + 2]
#                         print(rel)
                        r = int(rel[1:3])
                    else:
                        # print rel
                        r = int(rel[1:3])

#                 print("node %d relates to %s for %s" % (i, r, a))
                relation.append(chr(i + 97) + chr(r + 97))
                r1.append(a)

    M = [v for v in I.values()]
    N = [v for v in J.values()]

    for i in range(len(C)):
        dot.node(chr(97 + i), N[i], xlabel=M[i])

    for i in range(len(relation)):
        dot.edge(relation[i][0], relation[i][1], label=r1[i])
#     dot.render('./test.gv.svg', view=True)
    dot.render(filename='g1.dot')

if __name__ == '__main__':
    if len(sys.argv) != 2:
        grammars = open("grammar.txt")
    else:
        try:
            grammars = open(sys.argv[1])
        except Exception as e:
            print(e)
            print("Usage : \n\tpython SLRParser.py grammar_file\n")
            sys.exit(1)

    G = {}              # Store Grammars
    C = {}              # Store state i.e I's
    start = ""          # Start Symbol .e.g S'
    terminals = []      # terminal Symbols, *,id .+
    nonterminals = []   # Variables
    symbols = []        # terminals + nonterminals
    error = 0           # Error Flag
    EPSILON = "/E"      # Epsilon Symbol

    parse_grammar(grammars)
    print_grammar()

    print_first()
    print_follow()

    items()
    print_item()

    global parse_table

    no_of_rows = len(C) # No of States, right side of table
    no_of_cols = len(symbols)  # All symbols plus the state no
    parse_table = [["" for c in range(no_of_cols) ] for r in range(no_of_rows)]

    print_table()

    construct_digraph()

    process_input()
