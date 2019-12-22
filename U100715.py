from cyaron import *
n_s = [9, 14, 23, 37, 60, 97, 157, 254, 411, 665, 1076, 1741, 2817, 4558, 7375, 11933, 19308, 31241, 50549, 81790]
for i in range(20):
    test_data = IO(file_prefix = "st", data_id = i + 1)
    n = n_s[i]
    m = randint(n,min(n*(n-1)//4,100000))
    test_data.input_writeln(n, m)
    graph = Graph.UDAG(n, m, weight_limit = 300, repeated_edges = False, self_loop = False)
    test_data.input_writeln(graph)
    test_data.output_gen("U100715.exe")
