#!/usr/bin/env python3

# Christer Linde

import sys
import logging

log = logging.getLogger(__name__)

from math import inf

def warshall(adjlist):
    '''
    Returns an NxN matrix that contains the result of running Warshall's
    algorithm.

    Warshall's algorithm is similar to Floyd's, but gives the transitive closure
    instead of the minimum distances.

    Pre: adjlist is not empty.
    '''
    #log.info("TODO: warshall()")
    warshall_matrix = floyd(adjlist)
    len = adjlist.node_cardinality() # Length
    for i in range(len):
        for j in range(len):
            warshall_matrix[i][j] = warshall_matrix[i][j] != inf
    return warshall_matrix

def floyd(adjlist):
    '''
    Returns an NxN matrix that contains the result of running Floyd's algorithm.

    Floyd's algorithm is similar to Warshall's, but gives the minimum distances
    instead of transitive closure.

    Pre: adjlist is not empty.
    '''
    #log.info("TODO: floyd()")
    len = adjlist.node_cardinality()
    floyd_matrix = adjlist.adjacency_matrix()

    for i in range(len):
        for j in range(len):
            if i == j:
                floyd_matrix[i][j] = 0

    for k in range(len):
        for i in range(len):
            for j in range(len):
                if floyd_matrix[i][j] > floyd_matrix[i][k] + floyd_matrix[k][j]:
                    floyd_matrix[i][j] = floyd_matrix[i][k] + floyd_matrix[k][j]

    return floyd_matrix

def dijkstra(adjlist, start_node):
    '''
    Returns the result of running Dijkstra's algorithm as two N-length lists:
    1) distance d: here, d[i] contains the minimal cost to go from the node
    named `start_node` to the i:th node in the adjacency list.
    2) edges e: here, e[i] contains the node name that the i:th node's shortest
    path originated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: start_node is a member of adjlist.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 *
    b|* * 2
    c|* * *

    For start node "a", the expected output would then be:

    d: [ None, 1, 3]
    e: [ None, 'a', 'b' ]
    '''
    #log.info("TODO: dijkstra()")
    length = adjlist.node_cardinality()
    d = [inf]  * length
    e = [None] * length
    unexplored_nodes, explored_nodes = [], [False] * length

    node = adjlist.get_head()
    for pos in range(length):
        unexplored_nodes.append(node)
        if node.get_name() == start_node:
            d[pos] = 0
        node = node.get_tail()


    while True:
        minimal_node_index = get_min_index(d, explored_nodes)

        if minimal_node_index is None or d[minimal_node_index] == inf:
            break

        for edge in unexplored_nodes[minimal_node_index].list_local_edges():
            v = unexplored_nodes.index(adjlist.get_node(edge[1]))
            if d[v] > d[minimal_node_index] + edge[2]:
                d[v] = d[minimal_node_index] + edge[2]
                e[v] = unexplored_nodes[minimal_node_index].get_name()
        explored_nodes[minimal_node_index] = True

        #[DEBUG] print("Explored Nodes:", explored_nodes)  # Add this line for debugging

    d[:] = [x if x != 0 else None for x in d]
    return d, e

def prim(adjlist, start_node):
    '''
    Returns the result of running Prim's algorithm as two N-length lists:
    1) lowcost l: here, l[i] contains the weight of the cheapest edge to connect
    the i:th node to the minimal spanning tree that started at `start_node`.
    2) closest c: here, c[i] contains the node name that the i:th node's
    cheapest edge orignated from. 

    If the index i refers to the start node, set the associated values to None.

    Pre: adjlist is setup as an undirected graph and start_node is a member.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 3
    b|1 * 1
    c|3 1 *

    For start node "a", the expected output would then be:

    l: [ None, 1, 1]
    c: [ None, 'a', 'b' ]
    '''
    #log.info("TODO: prim()")

    # Maste köras i undirected mode "python3 main.py --mode undirected"

    length = adjlist.node_cardinality()
    l = [inf]  * length
    c = [None] * length
    unexplored_nodes, explored_nodes = [], [False] * length

    node = adjlist.get_head()
    for pos in range(length):
        unexplored_nodes.append(node)
        if node.get_name() == start_node:
            l[pos] = 0
        node = node.get_tail()

    while explored_nodes != [True] * length:
        minimal_node_index = get_min_index(l, explored_nodes)

        for edge in unexplored_nodes[minimal_node_index].list_local_edges():
            v = unexplored_nodes.index(adjlist.get_node(edge[1]))
            if not explored_nodes[v] and (edge[2] < l[v]):
                l[v] = edge[2]
                c[v] = unexplored_nodes[minimal_node_index].get_name()
        explored_nodes[minimal_node_index] = True
    l[:] = [x if x != 0 else None for x in l]
    return l, c

def get_min_index(queue, explored):
    minimal_node = inf
    minimal_node_index = None

    for index in range(len(queue)):
        if type(queue[index]) is not str and (queue[index] < minimal_node) and not explored[index]:
            minimal_node = queue[index]
            minimal_node_index = index

    return minimal_node_index

if __name__ == "__main__":
    logging.critical("module contains no main")
    sys.exit(1)
