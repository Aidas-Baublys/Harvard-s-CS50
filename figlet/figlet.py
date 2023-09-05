from pyfiglet import Figlet
import sys
import random


f = Figlet()
fonts = f.getFonts()
font = "slant"

if len(sys.argv) == 1:
    r = random.randint(0, 418)
    font = fonts[r]

if len(sys.argv) == 3:
    if sys.argv[1] == "-f" or sys.argv[1] == "--font":
        if sys.argv[2] in fonts:
            font = sys.argv[2]
        else:
            sys.exit("0 or 2 command line args.")
    else:
        sys.exit("0 or 2 command line args.")

if len(sys.argv) > 3 or len(sys.argv) == 2:
    sys.exit("0 or 2 command line args.")

text = input("Input: ")
f.setFont(font=font)
print("Output:")
print(f.renderText(text))
