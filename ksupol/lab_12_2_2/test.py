import ctypes

lib = ctypes.CDLL('arr.dll')

_fibon = lib.fibon
_fibon.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_fibon.restype = None

_first_entry = lib.first_entry
_first_entry.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int,
                         ctypes.POINTER(ctypes.c_int),
                         ctypes.POINTER(ctypes.c_int))
_first_entry.restype = None

def fibon(am):
    arr = (ctypes.c_int * am)()
    _fibon(arr, am)

    return list(arr)

def first_entry(a):
    am = len(a)
    arr = (ctypes.c_int * am)(*a)
    arr_2 = (ctypes.c_int * am)()
    am_2 = ctypes.c_int()
    _first_entry(arr, am, arr_2, am_2)

    return list(arr_2), am_2.value

def test_fibon():
    print("test_fibon:")
    size = [1, 2, 4, 8, 10, 15, 20]
    res = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144,
           233, 377, 610, 987, 1597, 2584, 4181]
    for i in range(len(size)):
        arr = fibon(size[i])
        if arr == res[:size[i]]:
            print(i+1, "OK")
        else:
            print(i+1, "FAILED")

def test_first_entry():
    print("test_firts_entry:")
    arr = [[1], [2, 2], [1, 2, 3, 3, 4], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
           [1, 2, 1, 2, 3, 4, 3, 4, 5]]
    res = [[1], [2, 0], [1, 2, 3, 4, 0], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
           [1, 2, 3, 4, 5, 0, 0, 0, 0]]
    for i in range(5):
        a = first_entry(arr[i])[0]
        if a == res[i]:
            print(i+1, "OK")
        else:
            print(i+1, "FAILED")

test_fibon()
print()
test_first_entry()
