import cs50

while True:
    try:
        height = cs50.get_int("Height: ")
        if 1 <= height <= 8:
            break
    except ValueError:
        # Handle non-integer input if get_int doesn't handle it (though cs50 lib usually does)
        pass  # Or print an error message

for i in range(1, height + 1):
    spaces = height - i
    hashes = i
    print(" " * spaces + "#" * hashes)
