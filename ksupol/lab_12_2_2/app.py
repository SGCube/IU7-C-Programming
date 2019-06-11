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

print("What function do you want to choose?")
print("1 - fill array with fibbonachi numbers\n2 - fill "
      "array with first entered numbers from another array")
choice = int(input("Enter your choice: "))
if choice < 1 or choice > 2:
    print("Wrong code of choice!")
else:
    if choice == 1:
        n = int(input("Enter number of elements in array: "))
        if n <= 0:
            print("Wrong number of elements!")
        else:
            arr = fibon(n)
            print("Array: ")
            for i in range(n):
                print(arr[i], end = ' ')
    else:
        arr = list(map(int, input("Enter elements of first array: ").split()))
        arr_2, n_2 = first_entry(arr)
        print("New array: ")
        for i in range(n_2):
            print(arr_2[i], end = ' ')
    
