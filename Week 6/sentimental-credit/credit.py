# For this version we don't have to use this library if you want to use
# get_float funtion on line 102 then uncomment below library

# from cs50 import get_int

while (1):
    userInput = input("Number: ")  # Take input from user as string
    try:
        userInput = int(userInput)  # Convert string into int
        if userInput > 0:
            break  # Break the loop

    except ValueError:
        continue

# First of all we have to make a function which validates the card number using Lohn's Alogorithm


def validation(number):
    tempNumber = number
    sum = 0
    position = 0

    while (tempNumber > 0):  # Run the loop till the number divides till 0
        if (position % 2 == 0):  # This check wether the position is even or odd if it i
            # even we don't have to double it while if it odd, we have to double it

            # Adds the last digits of that number which is our required digit
            sum += (tempNumber % 10)
            tempNumber = tempNumber // 10  # Divides the number by 10 so that we reduce the number by one digit

        # This condition check which number have to be doubled like if it is 4 then we have to add 8 in it.
        elif (position % 2 == 1):
            doubled = 2 * (tempNumber % 10)  # Calculates the double of that specific digit.

            # if greater than ten then add it both digits instead the whole number like
            #  if digit is 6 and it's double is 12 we will add 1 + 2 i.e. 3 instead of 12.
            if doubled >= 10:
                sum += 1 + doubled % 10

            else:
                sum += doubled  # if less than ten like digit is 3 and double is 6 so add six in the sum
            tempNumber = tempNumber // 10  # Divides the number by 10 so that we reduce the number by one digit

        position += 1  # increase the position so that we can track which digit
        # we have to double and which one we have to let it single and add it to sum
    # Returns True when when sum is completely divisible
    # by 10 and False when not. We use Xor in it.
    return ((True and (sum % 10 == 0)) ^ (False))


# This function returns the number of digits by simply dividing the number by ten until it becomes 0
def totalDigits(number):
    digits = 0
    while (number > 0):
        digits += 1
        number = number // 10
    return digits

# The result function provides us with which card does the input is.
# It takes card number and gives us Name of Card like AMEX, MASTERCARD, VISA etc.
# And in some cases the card passes the validation test without having actual length,
# so we also provide and INVALID statement for such trespassers which do such things.


def result(number):
    digits = totalDigits(number)  # Retieves the total digits
    # Calculates the first two digits of number based on division principles
    firstTwo = number // (10 ** (digits-2))
    firstOne = firstTwo // 10  # Diving first two with ten to get principal first number

    # Condition for VISA Card, it must have 13 or 16 digits and first digit must be 4
    if ((digits == 13 or digits == 16) and (firstOne == 4)):
        return "VISA"

    # Condition for AMEX Card, it must have 15 digits and first two digit can be 34 or 37 based on question.
    elif ((digits == 15) and (firstTwo == 37 or firstTwo == 34)):
        return "AMEX"

    # Condition for MASTERCARD Card, it must have 16 digits and first two digits can be 51,52,53,54,55.
    elif ((digits == 16) and (firstTwo >= 51 and firstTwo <= 55)):
        return "MASTERCARD"

    # If all other conditions are false meaning this card is a false positive which passed validation
    else:
        return "INVALID"

# Now lets get to all conditions which tell whether a number is valid and of which company is it off.

# These Below Were Test Cases to Check our Validation function.
# print(validation(378282246310005)) # AMEX
# print(validation(371449635398431))
# print(validation(5555555555554444)) # MASTERCARD
# print(validation(5105105105105100))
# print(validation(4111111111111111)) #VISA
# print(validation(4012888888881881))
# print(validation(1234567890))


# ----------------Main Code------------------ #

# userInput = get_int("Number: ")

if (validation(userInput)):  # Validates the card number
    print(result(userInput))  # Prints the name of Card
else:
    print("INVALID")  # Prints INVALID if the card in not valid
