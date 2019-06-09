import ctypes

lib = ctypes.CDLL('arr.dll');


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

def main():
    print("1 - fill with prime numbers",
          "2 - copy from one to other with additional number", sep = '\n')
    action = int(input("Enter action: "))
    if action == 1:
        n1 = int(input("Enter array size: "))
        if n1 <= 0:
            print("Non-positive input!")
        else:
            print("Array with prime numbers:", arr_fill_prime(n1))
    elif action == 2:
        arr1 = list(map(int, input('Enter array: ').split()))
        num = int(input("Enter number to add after each even number: "))
        print("New array: ", arr_copy_spec(arr1, num))
    else:
        print("Invalid action!")

if __name__ == '__main__':
    main()
