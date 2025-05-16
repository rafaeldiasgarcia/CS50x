import cs50
import math

while True:
    try:
        dollars = cs50.get_float("Change owed: ")
        if dollars >= 0:
            break
    except ValueError:
        pass  # cs50 library handles non-numeric re-prompt

cents = round(dollars * 100)
coin_count = 0

coin_count += cents // 25
cents %= 25

coin_count += cents // 10
cents %= 10

coin_count += cents // 5
cents %= 5

coin_count += cents

print(coin_count)
