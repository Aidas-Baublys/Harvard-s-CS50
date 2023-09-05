import sys
import math


number = 0

while int(number) <= 0:
    try:
        number = input("Number: ")
    except:
        continue

l = len(number)

if l != 15 and l != 16 and l != 13:
    print("INVALID")
    sys.exit()

cardNum = int(number)
cardNumDigits = int(number)
checkSum = 0
i = 1

while cardNumDigits > 0:
    digit = cardNumDigits % 10

    if i % 2 != 0:
        checkSum += digit
    else:
        digitDigit = digit * 2
        if digitDigit > 9:
            checkSum += digitDigit % 10
            checkSum += math.floor(digitDigit / 10)
        else:
            checkSum += digitDigit

    cardNumDigits = math.floor(cardNumDigits / 10)
    i += 1

if checkSum % 10 != 0:
    print("INVALID")
    sys.exit()

if l == 15:
    firstDigits = math.floor(cardNum / 10000000000000)
    if firstDigits == 34 or firstDigits == 37:
        print("AMEX")
        sys.exit()

if l == 16:
    firstDigits = math.floor(cardNum / 100000000000000)
    if firstDigits == 51 or firstDigits == 52 or firstDigits == 53 or firstDigits == 54 or firstDigits == 55:
        print("MASTERCARD")
        sys.exit()
    firstDigits = math.floor(cardNum / 1000000000000000)
    if firstDigits == 4:
        print("VISA")
        sys.exit()

if l == 13:
    firstDigits = math.floor(cardNum / 1000000000000)
    if firstDigits == 4:
        print("VISA")
        sys.exit()

print("INVALID")
