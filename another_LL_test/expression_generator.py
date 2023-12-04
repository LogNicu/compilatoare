#!/home/nicu/Projects/compilatoare/another_LL_test/venv/bin/python3
import random
import subprocess
import re

open_parens = 0
closed_parens = 0
prev = '+'


def generate_expression(depth=3):
    global closed_parens
    global open_parens
    global prev
    if depth == 0:
        str1 = str(random.randint(50, 1000 ))
        if random.random() < 0.3:
            str1 = '!' +str1
        return str1
    else:
        operator = random.choice(['+', '-', '*',')'])
        prev = operator
        if operator == ')':
            if closed_parens < open_parens:
                closed_parens += 1
            else:
                operator = '+'
            return f'({generate_expression(depth-1)}{operator}{generate_expression(depth-1)})'
        else :
            if random.random() < 0.000001:
                operator += '('
                open_parens += 1
        return f'({generate_expression(depth-1)}{operator}{generate_expression(depth-1)})'


def replace_not(match):
    number = match.group(1)
    return "(not {})".format(number)
def main():
    for i in range(0,50):
        global closed_parens
        global open_parens

        expression = generate_expression()
        while open_parens > closed_parens:
            expression = expression + ')'
            closed_parens +=1

        pattern = re.compile(r"!(\d+)")
        pythonExpression = pattern.sub(replace_not, expression)
        value = eval(pythonExpression)
        value = round(value,5)
        # Specify the command as a list of arguments
        command = ["cmake-build-debug/another_LL_test", expression]

        # Run the command and capture its output
        result = subprocess.run(command, stdout=subprocess.PIPE, text=True)

        try:
            valueFromParser = eval(result.stdout)
        except Exception as e:
            print("Exception from my parser")
            print(e)
            print(pythonExpression)
            print(expression)
        if value != valueFromParser:
            print("Expression: ",expression)
            print("Python expression: ",pythonExpression)
            print("from python: ",value)
            print("from program: ",valueFromParser)
        closed_parens = 0
        open_parens = 0

if __name__ == "__main__":
    main()