def precedence(operator):
    if operator == '^':
        return 3
    elif operator in ['*', '/']:
        return 2
    elif operator in ['+', '-']:
        return 1
    else:
        return 0

def infix_to_postfix(expression):
    postfix = []
    stack = []

    for symbol in expression:
        if symbol.isalnum():
            postfix.append(symbol)
        elif symbol == '(':
            stack.append(symbol)
        elif symbol == ')':
            while stack and stack[-1] != '(':
                postfix.append(stack.pop())
            stack.pop()  # Remove the '('
        else:
            while stack and precedence(stack[-1]) >= precedence(symbol):
                postfix.append(stack.pop())
            stack.append(symbol)

    while stack:
        postfix.append(stack.pop())

    return ''.join(postfix)

def evaluate_postfix(expression, values, output_type):
    stack = []

    for symbol in expression:
        if symbol.isalnum():
            stack.append(values[symbol])
        else:
            operand2 = stack.pop()
            operand1 = stack.pop()
            if symbol == '+':
                stack.append(operand1 + operand2)
            elif symbol == '-':
                stack.append(operand1 - operand2)
            elif symbol == '*':
                stack.append(operand1 * operand2)
            elif symbol == '/':
                stack.append(operand1 / operand2)
            elif symbol == '^':
                stack.append(operand1 ** operand2)

    if output_type == float:
        stack = [round(item, 6) if isinstance(item, float) else item for item in stack]

    return stack[0]

infix_expression = "(F-D/(C+A)*B*B-D^E^A)"
values = {'A': 3, 'B': 2, 'C': 2, 'D': 2, 'E': 2, 'F': 1}

# Convert infix expression to postfix
postfix_expression = infix_to_postfix(infix_expression)
print("Symbol\tStack\tPostfix")
print("----------------------------")
stack = []
for symbol in infix_expression:
    if symbol == '(':
        stack.append(symbol)
    elif symbol == ')':
        while stack and stack[-1] != '(':
            print(f"{symbol}\t{' '.join(map(str, stack))}\t{postfix_expression}")
            stack.pop()
        stack.pop()
    elif symbol.isalnum():
        print(f"{symbol}\t{' '.join(map(str, stack))}\t{postfix_expression}")
    else:
        while stack and precedence(stack[-1]) >= precedence(symbol) and stack[-1] != '(':
            print(f"{symbol}\t{' '.join(map(str, stack))}\t{postfix_expression}")
            stack.pop()
        stack.append(symbol)

while stack:
    print(f"\t{' '.join(map(str, stack))}\t{postfix_expression}")
    stack.pop()

print("\nPostfix Expression:", postfix_expression)

print("Enter the postfix expression: ")
print(infix_expression)
# User option for result type
output_option = input("\nDo you want the result as a: 1. Float or 2. Integer?: 1")

output_type = float if output_option == '1' else int

# Evaluate postfix expression
result = evaluate_postfix(postfix_expression, values, output_type)
print("\nSymbol\tStack")
stack = []
for symbol in postfix_expression:
    if symbol.isalnum():
        stack.append(values[symbol])
    else:
        operand2 = stack.pop()
        operand1 = stack.pop()
        if symbol == '+':
            result_str = operand1 + operand2
        elif symbol == '-':
            result_str = operand1 - operand2
        elif symbol == '*':
            result_str = operand1 * operand2
        elif symbol == '/':
            result_str = operand1 / operand2
        elif symbol == '^':
            result_str = operand1 ** operand2

        stack.append(result_str)
    stack_display = ['%.6f' % item if isinstance(item, float) else item for item in stack]
    print(f"{symbol}\t{' '.join(map(str, stack_display))}")

print("\nThe evaluation is:", result)
