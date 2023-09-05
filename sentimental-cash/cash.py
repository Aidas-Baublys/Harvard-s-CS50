import math


def main():
    cents = 0
    while cents <= 0:
        try:
            cents = float(input("Change owed: ")) * 100
        except:
            continue

    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    coins = quarters + dimes + nickels + cents

    print(f"{round(coins)}")


def calculate_quarters(cents):
    return math.floor(cents / 25)


def calculate_dimes(cents):
    return math.floor(cents / 10)


def calculate_nickels(cents):
    return math.floor(cents / 5)


if __name__ == "__main__":
    main()
