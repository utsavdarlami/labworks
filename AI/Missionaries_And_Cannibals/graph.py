from collections import defaultdict


class Graph():
    """
    For representing the state space
    it's edges will be the actions
    the neighbours of a node(state) will be the next state
    """

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
