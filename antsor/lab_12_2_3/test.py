import ctypes

lib = ctypes.CDLL('arr.dll');

is_prime = lib.is_prime
is_prime.argtypes = (ctypes.c_int, )
is_prime.restype = ctypes.c_int

_arr_fill_prime = lib.arr_fill_prime
_arr_fill_prime.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_arr_fill_prime.restype = None

_arr_copy_spec = lib.arr_copy_spec
_arr_copy_spec.argtypes = (ctypes.POINTER(ctypes.c_int),
                           ctypes.POINTER(ctypes.c_int),
                           ctypes.c_int, ctypes.POINTER(ctypes.c_int),
                           ctypes.c_int)
_arr_copy_spec.restype = None


def arr_fill_prime(num):
    arr = (ctypes.c_int * num)()
    
    _arr_fill_prime(arr, num)
    
    return list(arr)

def arr_copy_spec(pylist, num):
    arr1_len = len(pylist)
    arr2_len = ctypes.c_int()
    
    arr1 = (ctypes.c_int * arr1_len)(*pylist)
    arr2 = (ctypes.c_int * (2 * arr1_len))()
    
    _arr_copy_spec(arr1, arr2, arr1_len, arr2_len, num)
    
    return list(arr2)[:arr2_len.value]

def test_is_prime():
    numbers = [ -11, -10, 0, 1, 2, 3, 4, 8, 19 ]
    results = [ 0, 0, 0, 0, 1, 1, 0, 0, 1 ]
    print("is_prime:")
    for i in range(len(numbers)):
        print("#", i + 1, "\t",
              "PASSED" if is_prime(numbers[i]) == results[i] else "FAILED",
              sep = '')
    print()

def test_fill_prime():
    prime = [ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 ]
    sizes = [ 0, 1, 2, 12 ]
    print("arr_fill_prime:")
    for i in range(len(sizes)):
        arr = arr_fill_prime(sizes[i])
        print("#", i + 1, "\t",
              "PASSED" if arr == prime[:sizes[i]] else "FAILED", sep = '')
    print()

def test_copy_spec():
    arrs = [ [ 1 ], [ 2 ], [ 1, 3, 5 ], [ 2, 4, 6 ], [ 1, -2 ],
             [ 1, 0 ], [ 1, 2, 4, 5, 4 ] ]
    ress = [ [ 1 ], [ 2, 9 ], [ 1, 3, 5 ], [ 2, 9, 4, 9, 6, 9 ],
             [ 1, -2, 9 ], [ 1, 0, 9 ], [ 1, 2, 9, 4, 9, 5, 4, 9 ] ]
    print("arr_copy_spec:")
    for i in range(len(arrs)):
        arr = arr_copy_spec(arrs[i], 9)
        print("#", i + 1, "\t",
              "PASSED" if arr == ress[i] else "FAILED",
              sep = '')
    print()

def main():
    test_is_prime()
    test_fill_prime()
    test_copy_spec()
    
if __name__ == '__main__':
    main()
