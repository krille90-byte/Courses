#!/usr/bin/env python3

# Christer Linde

#
# Recommended order to get started:
# 1) AdjacencyList.{add_node,node_cardinality}
# 2) AdjacencyList._add_edge, Edge.add - note: if you run in debug mode, you
# will get all edges printed when selecting 'v: view' in the menu.
# 3) AdjacencyList.find_edge, Edge.find
#

import sys
import logging

log = logging.getLogger(__name__)

from math import inf

class AdjacencyList:
    '''
    A linked-list implementation of an adjacency list that keeps its nodes and
    edges lexicographically ordered at all times.
    '''
    def __init__(self, name=None, info=None):
        '''
        Initializes a new adjacency list.  It is considered empty if no head
        node is provided.  Optionally, a node can also have associated info.
        '''
        self._name = name # head node name
        self._info = info # head node info
        if not self.get_head().is_empty():
            self._tail = AdjacencyList() # empty tail
            self._edges = Edge() # empty list of edges

    def is_empty(self):
        '''
        Returns true if this adjacency list is empty.
        '''
        return self._name is None

    def get_head(self):
        '''
        Returns the head of this adjacency list.
        '''
        return self

    def get_tail(self):
        '''
        Returns the tail of this adjacency list.
        '''
        return self._tail

    def get_name(self):
        '''
        Returns the node name.
        '''
        return self._name

    def get_info(self):
        '''
        Returns auxilirary node info.
        '''
        return self._info

    def get_edges(self):
        '''
        Returns the edge head.
        '''
        return self._edges

    def cons(self, tail):
        '''
        Returns the head of this adjacency list with a newly attached tail.
        '''
        self._tail = tail
        return self.get_head()

    def set_tail(self, tail):
        '''
        Returns the head of this adjacency list with a newly attached tail.
        Alias for cons().
        '''
        return self.cons(tail)

    def set_name(self, name):
        '''
        Sets the node name to `name`.

        Returns an adjacency list head.
        '''
        self._name = name
        return self.get_head()

    def set_info(self, info):
        '''
        Sets the auxilirary info of this node to `info`.

        Returns an adjacency list head.
        '''
        self._info = info
        return self.get_head()

    def set_edges(self, edges):
        '''
        Sets the edge head of this node to `edges`.

        Returns an adjacency list head.
        '''
        self._edges = edges
        return self.get_head()

    ###
    # Node operations
    ###
    def add_node(self, name, info=None):
        '''
        Adds a new node named `name` in lexicographical order.  If node `name`
        is a member, its info-field is updated based on `info`.

        Returns an adjacency list head.
        '''
        #log.info("TODO: add_node()")
        node = self.get_head()
        if node.is_empty():
            return node.set_name(name).set_info(info).cons(AdjacencyList()).set_edges(Edge())
        while not node.is_empty() and node.get_name() <= name:
            node = node.get_tail()
        if self.find_node(name):
            node.set_info(info)
            return self.get_head()
        if not node.is_empty():
            node.cons(AdjacencyList(node.get_name(), node.get_info()).set_edges(node.get_edges()).cons(node.get_tail()))
        else:
            node.cons(AdjacencyList())
        node.set_edges(Edge())
        node.set_name(name)
        node.set_info(info)
        return self.get_head()

    def delete_node(self, name):
        '''
        Deletes the node named `name` if it is a member.

        Returns an adjacency list head.
        '''
        #log.info("TODO: delete_node()")
        node = self.get_head()
        last_node = node
        if node.is_empty():
            return self.get_head()
        while node.get_name() != name:
            if node.get_tail().is_empty():
                return self.get_head()
            last_node = node
            node = node.get_tail()
        
        if node is last_node:
            self = node.get_tail()
        else:
            last_node.cons(node.get_tail())
        return self.get_head()

    def find_node(self, name):
        '''
        Returns True if the node named `name` is a member.
        '''
        if self.is_empty():
            return False
        if name == self.get_head().get_name():
            return True
        return self.get_tail().find_node(name)

    def node_cardinality(self):
        '''
        Returns the number of nodes.
        '''
        #log.info("TODO: node_cardinality()")
        nums, node = 0, self.get_head()
        while not node.is_empty():
            node = node.get_tail()
            nums += 1
        return nums

    ###
    # Edge operations
    ###
    def add_edge(self, src, dst, weight=1):
        '''
        Adds or updates an edge from node `src` to node `dst` with a given
        weight `weight`.  If either of the two nodes are non-members, the same
        adjacency list is returned without any modification.

        Returns an adjacency list head.
        '''
        if not self.find_node(dst):
            return self.get_head()
        return self._add_edge(src, dst, weight)

    def _add_edge(self, src, dst, weight):
        '''
        Adds a new (or updates an existing) edge from node `src` to node `dst`,
        setting the weight to `weight`.

        Returns an adjacency list head.

        Pre: `dst` is a member of this adjacency list.
        '''
        #log.info("TODO: _add_edge()")
        src_node = self.get_head()

        while src_node.get_name() != src:
            if src_node.get_tail().is_empty():
                print(f"Source node {src} not found.")
                return self.get_head()  # Kunde inte hitta src.
            src_node = src_node.get_tail()
        

        print(f"Adding edge from {src} to {dst} with weight {weight}.")
        src_node.get_edges().add(dst, weight)
        return self.get_head()

    def delete_edge(self, src, dst):
        '''
        Deletes an edge from node `src` to node `dst` if it exists.

        Returns an adjacency list head.
        '''
        #log.info("TODO: delete_edge()")
        if not self.get_head().is_empty():
            src_node = self.get_head()
            while src_node.get_name() != src:
                if src_node.get_tail().is_empty():
                    return self.get_head()
                src_node = src_node.get_tail()
            
            # Nu har vi vår käll-nod
            src_edge = src_node.get_edges()
            latest_edge = src_edge
            if src_edge.is_empty():
                return self.get_head()
            while src_edge.get_dst() != dst:
                if src_edge.get_tail().is_empty():
                    return self.get_head() # is a Non-member
                latest_edge, src_edge = src_edge, src_edge.get_tail()
            

            if src_edge is latest_edge:
                src_node.set_edges(src_edge.get_tail())
            else:
                latest_edge.cons(src_edge.get_tail())
        return self.get_head()

    def delete_edges(self, name):
        '''
        Deletes all edges towards the node named `name`.

        Returns an adjacency list head.
        '''
        #log.info("TODO: delete_edges()")
        src_node = self.get_head()
        while not src_node.is_empty():
            src_edge = src_node.get_edges()
            while not src_edge.is_empty():
                if src_edge.get_dst() == name:
                    self.delete_edge(src_node.get_name(), name)
                src_edge = src_edge.get_tail()
            src_node = src_node.get_tail()
        return self.get_head()

    def find_edge(self, src, dst):
        '''
        Returns True if there's an edge from node `src` to node `dst`.
        '''
        #log.info("TODO: find_edge()")
        src_node = self.get_head()
        while src_node.get_name() != src:
            if src_node.is_empty():
                return False
            src_node = src_node.get_tail()
        return src_node.get_edges().find(dst)

    def edge_cardinality(self):
        '''
        Returns the number of edges.
        '''
        #log.info("TODO: edge_cardinality()")
        edge_total, src_node = 0, self.get_head()

        while not src_node.is_empty():
            edge_total += src_node.get_edges().cardinality()
            src_node = src_node.get_tail()
        return edge_total

    def self_loops(self):
        '''
        Returns the number of loops in this adjacency list.  Note that a loop is
        defined as a node that has an edge towards itself, e.g., A->A.
        '''
        #log.info("TODO: self_loops()")
        loop_total, src_node = 0, self.get_head()

        while not src_node.is_empty():
            loop_total += 1 if src_node.get_edges().find(src_node.get_name()) else 0
            src_node = src_node.get_tail()
        return loop_total

    def adjacency_matrix(self):
        '''
        Returns this adjacency list as an adjacency matrix.  For example,
        consider the following adjacency list where all edges have weight=1.
        
        a: a->b->c
        |
        v
        b: a->b
        |
        v
        c: c

        Then we would expect the following 3x3 adjacency matrix:

          a b c
        -+-----
        a|1 1 1
        b|1 1 *
        c|* * 1

        Where the corresponding python-matrix is:

        [ [1,1,1], [1,1,inf], [inf,inf,1] ]

        Note that inf indicates that there is no path between two nodes.  Also,
        all rows and columns are lexicographically ordered based on node names.

        Hint: depending on your solution, you may need to add a helper method
        that maps a node's name to it's numeric position in the adjacency list.
        '''
        #log.info("TODO: adjacency_matrix()")
        if self.is_empty():
            return [[]]

        # [Lab comment] In case you'd like to create an inf-initialized n x n matrix
        n = self.node_cardinality()
        node_pos = [""] * n
        present_node = self.get_head()
        for i in range(n):
            node_pos[i] = present_node.get_name()
            present_node = present_node.get_tail()

        matrix = [ [inf]*n for i in range(n) ]
        present_node = self.get_head()

        for i in range(n):
            present_edge = present_node.get_edges()
            for j in range(n):
                for k in range(n):
                    if present_edge.get_dst() == node_pos[k]:
                        matrix[i][k] = present_edge.get_weight()
                        present_edge = present_edge.get_tail()
            present_node = present_node.get_tail()
        return matrix

    def list_nodes(self):
        '''
        Returns a list of node names in lexicographical order.
        '''
        head, node_names = self.get_head(), []
        while not head.is_empty():
            node_names += [ head.get_name() ]
            head = head.get_tail()
        return node_names

    def list_edges(self):
        '''
        Returns a list of edges in lexicographical order.
        '''
        if self.get_head().is_empty():
            return []
        return self.get_head().get_edges().list(self.get_head().get_name()) +\
            self.get_tail().list_edges()
    
    # Help to solve algorithm problems.
    def list_local_edges(self):
        '''
        Returns an array of tuples containing data on all edges of a node.
        '''
        edge, edges = self.get_edges(), []
        while not edge.is_empty():
            edges += [ (self.get_name(), edge.get_dst(), edge.get_weight()) ]
            edge = edge.get_tail()
        return edges

    def get_node(self, name=None):
        '''
        Returns a node if the node named `name` is a member.
        If `name` is None, it returns the next node in the list.
        '''
        if self.is_empty():
            return None  # Inte hittad
        if name is None:
            return self
        if name == self.get_name():
            return self  # Hittad
        return self.get_tail().get_node(name)  # Fortsatt leta

class Edge:
    '''
    A linked-list implementation of edges that originate from an implicit source
    node.  Each edge has a weight and goes towards a given destination node.
    '''
    def __init__(self, dst=None, weight=1):
        '''
        Initializes a new edge sequence.  It is considered empty if no head edge
        is provided, i.e., dst is set to None.
        '''
        self._dst = dst # where is this edge's destination
        self._weight = weight # what is the weight of this edge
        if not self.get_head().is_empty():
            self._tail= Edge() # empty edge tail

    def is_empty(self):
        '''
        Returns true if this edge is empty.
        '''
        return self._dst is None
    
    def get_head(self):
        '''
        Returns the head of this edge.
        '''
        return self

    def get_tail(self):
        '''
        Returns the tail of this edge.
        '''
        return self._tail
        
    def get_dst(self):
        '''
        Returns the node name that this edge goes towards.
        '''
        return self._dst

    def get_weight(self):
        '''
        Returns the weight of this edge.
        '''
        return self._weight
        
    def cons(self, tail):
        '''
        Returns the head of this sequence with a newly attached tail.
        '''
        self._tail = tail
        return self.get_head()
        
    def set_tail(self, tail):
        '''
        Returns the head of this sequence with a newly attached tail.
        '''
        self._tail = tail
        return self.get_head()

    def set_dst(self, dst):
        '''
        Sets the destination of this edge to `dst`.

        Returns an edge head.
        '''
        self._dst = dst
        return self.get_head()

    def set_weight(self, weight):
        '''
        Sets the weight of this edge to `weight`.

        Returns an edge head.
        '''
        self._weight = weight
        return self.get_head()
    
    ###
    # Operations
    ###
    def add(self, dst, weight=1):
        '''
        Adds a new edge towards `dst` in lexicographical order.  If such an
        edge exists already, the associated weight-field is updated instead.

        Returns an edge head.
        '''
        #log.info("TODO: add()")
        if not self.get_head().is_empty():
            while not self.is_empty() and self.get_dst() <= dst:
                if self.get_dst() == dst:
                    self.set_weight(weight)
                    return self.get_head()
                self = self.get_tail()
            self.cons(Edge(self.get_dst(), self.get_weight()).cons(Edge() if self.is_empty() else self.get_tail()))
        else:
            self.cons(Edge())
        self.set_weight(weight)
        self.set_dst(dst)
        return self.get_head()

    def delete(self, dst):
        '''
        Deletes the edge that goes towards `dst` if it exists.

        Returns an edge head.
        '''
 
        return self.get_head()

    def find(self, dst):
        '''
        Returns True if there is an edge towards `dst` in this sequence.
        '''
        #log.info("TODO: edge find()")
        while not self.is_empty():
            if self.get_dst() == dst:
                return True
            self = self.get_tail()
        return False

    def cardinality(self):
        '''
        Returns the number of edges in this sequence.
        '''
        #log.info("TODO: edge cardinality()")
        edge_total = 0

        while not self.is_empty():
            edge_total += 1
            self = self.get_tail()
        return edge_total

    def list(self, src):
        '''
        Returns a list of edges in lexicographical order, e.g., if `src`
        goes to nodes A and B, the returned list would be:
            [ (src, A), (src, B) ]
        '''
        if self.get_head().is_empty():
            return []
        return [(src, self.get_head().get_dst(), self.get_weight())] + self.get_tail().list(src)

if __name__ == "__main__":
    log.critical("module contains no main method")
    sys.exit(1)
