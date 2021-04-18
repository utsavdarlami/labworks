"""
Represent the state space for the well-known Missionaries and Cannibals Game
and generate it.

M = Missionaries
C = Cannibals
B = Boat/Canoe
"""

import numpy as np
from graphviz import Digraph
# self defined imports
from graph import Graph


INITIAL_STATE = [3, 3, 1]  # M, C and B
GOAL = [0, 0, 0]  # Final Goal State

"""
 List of ACTIONS That Can be performed
"""
ACTIONS = [
    [1, 0, 1],
    [2, 0, 1],
    [0, 1, 1],
    [0, 2, 1],
    [1, 1, 1],
    ]


def illegal_state(state):
    """
    which states are illegal in this problems
    if C > M
    """
    # if sata
    if state[1] > state[0]:
        return True
    if state[0] < 0 or state[0] > 3:
        return True
    if state[1] < 0 or state[1] > 3:
        return True

    return False


def get_new_state(state, action):
    """
    vector subtraction/addition to get the new state
    """
    if state[2] == 1:  # boat is in the initial side
        return list(np.asarray(state) - np.asarray(action))
    return list(np.asarray(state) + np.asarray(action))


def node_name(state):
    """
    Converting list state to string
    eg. [3, 3, 1] == 3M3C1B
    """
    nm = ""
    nm += str(state[0]) + "M"
    nm += str(state[1]) + "C"
    nm += str(state[2]) + "B"
    return nm


def add_to_graph_with_action(state):
    """
    Add the state and the new state to the graph,
    obtained from the actions only if it is legal
    """
    global GRAPH
    # GRAPH[''.join(state)] = []
    for action in ACTIONS:
        n1 = node_name(state)
        n2 = get_new_state(state, action)
        if not(illegal_state(n2)):
            GRAPH.add_edges(n1, n2, node_name(action))


def generate_the_digraph(GRAPH):
    """
    Generating the state space diagram
    """

    vertices = list(GRAPH.graph.keys())
    f = Digraph('M_And_C', filename='MCB.gv')
    f.attr(size='20,20')  # for vertical
    # f.attr(rankdir='LR', size='20,18')  # for horizontal

    # double circle for initial state representation
    f.attr('node', shape='doublecircle', style='filled', color='pink')
    f.node(vertices[0])

    # normal circle for other state
    f.attr('node', shape='circle', style='', color='',)

    for vertex in vertices:
        edge_name, neighbours = GRAPH.get_nodes_and_edge_name(vertex)
        for en, n in zip(edge_name, neighbours):
            if n == GOAL:
                # f.attr('node', style='filled', color='lightgreen')
                f.attr('node', shape='doublecircle',
                       style='filled', color='lightgreen')
                f.edge(vertex, node_name(n), label=en)
                f.attr('node', shape='circle', style='', color='',)
            else:
                f.edge(vertex, node_name(n), label=en)

    # f
    # f.save()
    # $ dot -Tpng MCB.gv -o MCB_vertical.png
    f.view()


if __name__ == "__main__":

    GRAPH = Graph()  # For representing the state space

    print("Generating the State Space")

    # Implemented the Depth First Search
    # So used STACK
    STACK = [INITIAL_STATE]
    VISITED = []
    while STACK != []:

        current_state = STACK[-1]

        if current_state not in VISITED:
            """
            Performing actions on the current state adding to the graph
            Also keeping the track of the visited state in VISITED
            """
            VISITED.append(current_state)
            add_to_graph_with_action(current_state)
            _ = STACK.pop()  # poping the current state from the stack

            # node_data = GRAPH.get_nodes(node_name(current_state))
            # print(node_data)
            STACK.extend(GRAPH.get_nodes(node_name(current_state)))
        else:
            """
            it looks like the current state is already traversed so,
            poping it
            """
            _ = STACK.pop()
        # STACK = []
    print("The State Space is Generated ")

    generate_the_digraph(GRAPH)
