import cs50

while True:
    card_number_str = cs50.get_string("Number: ")
    if card_number_str.isdigit():
        break

length = len(card_number_str)
sum1 = 0
sum2 = 0

# Luhn's Algorithm - Sum of digits multiplied by 2 (from second-to-last)
for i in range(length - 2, -1, -2):
    digit = int(card_number_str[i])
    product = digit * 2
    sum1 += product // 10 + product % 10

# Luhn's Algorithm - Sum of digits not multiplied by 2 (from last)
for i in range(length - 1, -1, -2):
    digit = int(card_number_str[i])
    sum2 += digit

total_sum = sum1 + sum2

if total_sum % 10 == 0:
    if length == 15 and (card_number_str.startswith("34") or card_number_str.startswith("37")):
        print("AMEX")
    elif length == 16 and card_number_str[0:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
    elif (length == 13 or length == 16) and card_number_str.startswith("4"):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
