#!/usr/bin/env python3

# Christer Linde

import bt
import sys
import logging

log = logging.getLogger(__name__)

class BST(bt.BT):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(BST(), BST())

    def is_member(self, v):
        '''
        Returns true if the value `v` is a member of the tree.
        '''
        #logging.info("TODO@src/bst.py: implement is_member()")
        if self.is_empty():
            return False
        if self.get_value() == v:
            return True
        return self.get_lc().is_member(v) or self.get_rc().is_member(v)

    def size(self):
        '''
        Returns the number of nodes in the tree.
        '''
        #logging.info("TODO@src/bst.py: implement size()")
        if self.is_empty():
            return 0
        return self.get_lc().size() + self.get_rc().size() + 1

    def height(self):
        '''
        Returns the height of the tree.
        '''
        #logging.info("TODO@src/bst.py: implement height()")
        if self.is_empty():
            return 0
        return max(self.get_lc().height(), self.get_rc().height()) + 1

    def preorder(self):
        '''
        Returns a list of all members in preorder.
        '''
        if self.is_empty():
            return []
        return [self.get_value()] + self.get_lc().preorder() + self.get_rc().preorder()

    def inorder(self):
        '''
        Returns a list of all members in inorder.
        '''
        #log.info("TODO@src/bst.py: implement inorder()")
        if self.is_empty():
            return []
        return self.get_lc().inorder() + [self.get_value()] + self.get_rc().inorder()

    def postorder(self):
        '''
        Returns a list of all members in postorder.
        '''
        #log.info("TODO@src/bst.py: implement postorder()")
        if self.is_empty():
            return []
        return self.get_lc().postorder() + self.get_rc().postorder() + [self.get_value()]

    def bfs_order_star(self):
        '''
        Returns a list of all members in breadth-first search* order, which
        means that empty nodes are denoted by "stars" (here the value None).

        For example, consider the following tree `t`:
                    10
              5           15
           *     *     *     20

        The output of t.bfs_order_star() should be:
        [ 10, 5, 15, None, None, None, 20 ]
        '''
        #log.info("TODO@src/bst.py: implement bfs_order_star()")
        bfs, queue = [], [self]
        while queue:
            if len(bfs) >= (2**self.height())-1:
                break #Blir Klart om trädet är fyllt.
            node = queue.pop(0)
            bfs.append(node.get_value() if node is not None else None)
            queue += [node.get_lc(), node.get_rc()] if node is not None else [None, None]
        return bfs

    def add(self, v):
        '''
        Adds the value `v` and returns the new (updated) tree.  If `v` is
        already a member, the same tree is returned without any modification.
        '''
        if self.is_empty():
            self.__init__(value=v)
            return self
        if v < self.get_value():
            return self.cons(self.get_lc().add(v), self.get_rc())
        if v > self.get_value():
            return self.cons(self.get_lc(), self.get_rc().add(v))
        return self

    def delete(self, v):
        '''
        Removes the value `v` from the tree and returns the new (updated) tree.
        If `v` is a non-member, the same tree is returned without modification.
        '''
        #log.info("TODO@src/bst.py: implement delete()")
        if not BST.is_member(self, v): return self 

        if v < self.get_value(): self.set_lc(BST.delete(self.get_lc(), v))
        if v > self.get_value(): self.set_rc(BST.delete(self.get_rc(), v))
        if v == self.get_value():
            if self.get_lc().is_empty() and self.get_rc().is_empty():
                return self.set_value(None)
            if self.get_rc().is_empty(): #Om den högra noden är tom, använd vänster nod.
                return self.get_lc()
            if self.get_lc().is_empty(): #Om den vänstra noden är tom, använd den högra noden.
                return self.get_rc()

            if self.get_lc().height() >= self.get_rc().height():
                node = self.get_lc()
                while not node.rc().is_empty(): #Letar efter största värdet i Vänster subträd.
                    node = node.rc()
                self.set_value(node.value())
                self.set_lc(BST.delete(self.get_lc(), node.value()))
            else:
                node = self.get_rc()
                while not node.lc().is_empty(): #Letar efter minsta värdet i Höger subträd.
                    node = node.lc()
                self.set_value(node.value())
                self.set_rc(BST.delete(self.get_rc(), node.value()))
        return self

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
