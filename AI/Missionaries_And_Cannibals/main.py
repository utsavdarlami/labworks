import numpy as np
from graphviz import Digraph
from collections import defaultdict

class Graph():
    def __init__(self):
        self.graph = defaultdict(list)

    def add_edges(self, node1, node2, action):
        """ add n1 to n2 edge with its label """
        self.graph[node1].append({action: node2})

    def get_nodes(self, state):
        nodes = []
        node_data = self.graph[state]
        for node in node_data:
            nodes.append(*node.values())
        return nodes

    def get_nodes_and_edge_name(self, state):

        node_data = self.graph[state]
        nodes = []
        edge_names = []

        for n in node_data:
            nodes.append(*n.values())
            edge_names.append(*n.keys())

        return edge_names, nodes

    def show(self):
        print(self.graph)

def illegal_state(state):
    if state[1] > state[0]:
        return True
    if state[0] < 0 or state[0] > 3:
        return True
    if state[1] < 0 or state[1] > 3:
        return True

    return False

def get_new_state(state, action):
    if state[2] == 1:
        return list(np.asarray(state) - np.asarray(action))
    return list(np.asarray(state) + np.asarray(action))

def node_name(state):
    nm = ""
    nm += str(state[0]) + "M"
    nm += str(state[1]) + "C"
    nm += str(state[2]) + "B"
    return nm


def add_to_graph_with_action(state):
    global GRAPH
    for action in ACTIONS:
        n1 = node_name(state)
        n2 = get_new_state(state, action)
        if not(illegal_state(n2)):
            GRAPH.add_edges(n1, n2, node_name(action))


def generate_the_digraph(GRAPH):

    vertices = list(GRAPH.graph.keys())
    f = Digraph('M_And_C', filename='MCB.gv')
    f.attr(rankdir='LR', size='20,20')

    f.node(vertices[0])

    for vertex in vertices:
        edge_name, neighbours = GRAPH.get_nodes_and_edge_name(vertex)
        for en, n in zip(edge_name, neighbours):
            f.edge(vertex, node_name(n), label=en)

    f.view()


INITIAL_STATE = [3, 3, 1]
GOAL = [0, 0, 0]

ACTIONS = [
    [1, 0, 1],
    [2, 0, 1],
    [0, 1, 1],
    [0, 2, 1],
    [1, 1, 1],
    ]


if __name__ == "__main__":

    GRAPH = Graph()

    STACK = [INITIAL_STATE]
    VISITED = []
    while STACK != []:

        current_state = STACK[-1]

        if current_state not in VISITED:
            VISITED.append(current_state)
            add_to_graph_with_action(current_state)
            _ = STACK.pop()

            STACK.extend(GRAPH.get_nodes(node_name(current_state)))
        else:
            _ = STACK.pop()

    generate_the_digraph(GRAPH)
