def binarySearch(arr, v):
    left = 0
    right = len(arr) - 1

    while True:
        if left > right:
            return -1

        mid = (left + right) // 2

        if arr[mid] == v:
            return mid
        elif arr[mid] < v:
            left = mid + 1
        else:
            right = mid - 1


data = [1, 5, 7, 8, 10, 11, 13, 16]
print("Search for 1:", binarySearch(data, 1))
print("Search for 6:", binarySearch(data, 6))

