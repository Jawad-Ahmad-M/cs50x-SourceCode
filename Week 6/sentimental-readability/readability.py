def gradeCalculation(letters, sentences, words):
    # Formula of Coleman-Liau index, It is widely used in US American system
    grade = round(0.0588 * ((letters / words) * 100.0) -
                  0.296 * ((sentences / words) * 100.0) - 15.8)
    if grade < 1:
        return 1122  # Return specific integer which shows specific error case i.e Less than grade 1
    elif grade > 16:
        return 1123  # Return specific integer which shows specific error case i.e More than grade 16
    else:
        return grade  # If between 1 and 16 then return an integer

# --------------------Main Function------------------ #


text = input("Text: ")  # Takes the input from the user in the format of string

# Words initialized at 1 because at last of sentence there is no space so we have to add it manually
words = 1
sentences = 0
letters = 0

for i in range(len(text)):
    if text[i] == ' ':  # Check the spaces then adds words
        words += 1
    elif text[i] == '?' or text[i] == '!' or text[i] == '.':  # Check for the sentence endings
        sentences += 1
    elif text[i].isalpha():  # Adds the letter by checking using isalpha function
        letters += 1


# Calculates the grade based on GradeCalculation Function
grade = gradeCalculation(letters, sentences, words)

# --------------------Output Required------------------ #

if grade == 1122:
    print("Before Grade 1")

elif grade == 1123:
    print("Grade 16+")

elif (grade >= 1 and grade <= 16):
    print("Grade", grade)
