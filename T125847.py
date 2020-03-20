from cyaron import *

for i in range(25):
    print("Generating data input #",i)
    test_data = IO(file_prefix="segtree", data_id=i+1)
    test_data.input_writeln(100000, randint(1, 100000000))
    for j in range(100000):
        operation = randint(1, 2)
        x = randint(1, 1000000000)
        y = randint(x, 1000000000)
        if operation == 1:
            test_data.input_writeln(1, x, y, randint(1, 100000000))
        else:
            test_data.input_writeln(2, x, y)
    print("Generating data output #",i)
    test_data.output_gen("T125847.exe")
