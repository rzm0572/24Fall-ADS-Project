import numpy as np
import cyaron as cy
import dataGen as dg
import os

_n = cy.ati(np.linspace(1000, 15000, 29))
# _m = cy.ati(np.floor(1.2 * np.pow(_n, 1.4)))
_m = cy.ati(np.floor(0.5 * np.pow(_n, 1.8)))

def dataGen(n, m):
    test_data = cy.IO(file_prefix=f"./data/processed/custom", data_id = n, input_suffix=".gr", disable_output=True)
    
    test_data.input_writeln(n, m)

    graph = cy.Graph.DAG(n, m, weight_limit = 1000, self_loop = False, repeated_edges = False)
    test_data.input_writeln(graph)

if __name__ == "__main__":
    for i in range(len(_n)):
        dataGen(_n[i], _m[i])
        dg.queryGenerator(os.path.join("./data/queries", f"custom{_n[i]}_0.qry"), 1000, _n[i])
        print(f"custom{_n[i]} generated")

