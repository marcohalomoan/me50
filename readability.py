from cs50 import get_string

text = get_string("Text: ")
index = 0
count_letter = 0
count_word = 0
count_sentence = 0

for i in range(len(text)):
    if text[index].isalpha():
        count_letter += 1
    index += 1
    
index = 0

for i in range(len(text)):
    if text[index] == ' ':
        count_word += 1
    index += 1
count_word += 1

index = 0

for i in range(len(text)):
    if text[index] == '.' or text[index] == '?' or text[index] == '!':
        count_sentence += 1
    index += 1
    
L = count_letter / count_word * 100
S = count_sentence / count_word * 100

result = round(0.0588 * L - 0.296 * S - 15.8)

if result < 1:
    print("Before Grade 1")
elif result >= 16:
    print("Grade 16+")
else:
    print(f"Grade {result}")