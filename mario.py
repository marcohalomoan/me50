height = "start"
while (type(height) != int):
    height = input("Height: ")
    if height.isdigit():
        height = int(height)
        if height < 1 or height > 8:
            height = "start"

count = 1

for i in range(height):
    print(" " * (height - 1), end="")
    print("#" * count, end="")
    print("  ", end="")
    print("#" * count)
    count += 1
    height -= 1