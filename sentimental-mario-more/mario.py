height = 0

while height < 1 or height > 8:
    print("Please provide a number 1-8")
    try:
        height = int(input("Height: "))
    except:
        continue

for i in range(height):
    if (height > 1):
        spaces = " " * (height - i - 1)
        print(spaces, end="")
    bricks = "#" * (i + 1)
    print(bricks, end="")
    print("  ", end="")
    print(bricks, end="")
    if (i == 8):
        print(" ")
    else:
        print()
