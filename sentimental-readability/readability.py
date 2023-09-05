import re


text = input("Text: ")

letters = 0
for c in text:
    if c.isalpha():
        letters += 1

words = len(text.split())
sentences = len(re.split(r'[.!?]+', text)) - 1

letters_per_word = letters / words * 100
sentences_per_word = sentences / words * 100
level = 0.0588 * letters_per_word - 0.296 * sentences_per_word - 15.8

if level < 1:
    print("Before Grade 1")
elif level < 16:
    print(f"Grade {round(level)}")
else:
    print("Grade 16+")
    