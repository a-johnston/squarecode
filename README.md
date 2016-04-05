# squarecode
### Adam Johnston

A personal experiment in FEC algorithms. Originally intended to be a wannabe
fountain code but instead a bit of practice in graph theory.

Data intended for transfer on a lossy but not corrupting channel is divided
into blocks that represent nodes in a directed and fully-connected graph.
Each block is then augmented with encoding symbols formed by the data symbols
of the in-edges. In order to maximize recoverability, the graph is made then to
have no single node that can be removed and break the fully-connectedness of
the graph.

The name squarecode comes from the construction of this graph as a square with
edges going up and left, and wrapping around the square. This would then make
the actual shape of the graph a torus. Possible future names for this include
toruscode, boxcode, or whatever else sounds interesting and doesn't come up
already on Google.
