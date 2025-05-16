import cs50
import math

text = cs50.get_string("Text: ")

letter_count = 0
word_count = 1  # Start with 1, assuming non-empty text
sentence_count = 0

for char in text:
    if char.isalpha():
        letter_count += 1
    elif char.isspace():
        word_count += 1
    elif char in ['.', '!', '?']:
        sentence_count += 1

# Adjust word count for texts starting/ending with space or having multiple spaces
# A more Pythonic way to count words:
words = text.split()
word_count = len(words)

# Handle potential division by zero if text is empty or has no words
if word_count == 0:
    L = 0.0
    S = 0.0
else:
    L = (letter_count / word_count) * 100
    S = (sentence_count / word_count) * 100

index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")
