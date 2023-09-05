def is_operand(c):
    return c.isalpha()

def evaluate_operator(op, operand1, operand2):
    if op == '+':
        return operand1 + operand2
    elif op == '-':
        return operand1 - operand2
    elif op == '*':
        return operand1 * operand2
    elif op == '/':
        return operand1 / operand2
    elif op == '^':
        return operand1 ** operand2

def evaluate_prefix(expression, variable_values):
    stack = []
    expression = expression[::-1]  # Reverse the expression to start from the beginning

    for symbol in expression:
        if is_operand(symbol):
            stack.append(variable_values[symbol])
        else:
            operand1 = stack.pop()
            operand2 = stack.pop()
            result = evaluate_operator(symbol, operand1, operand2)
            stack.append(result)
        
        # Display the current step
        stack_display = ['%.6f' % item if isinstance(item, float) else item for item in stack]
        print(f"{symbol}\t{' '.join(map(str, stack_display))}")

    return stack[0]  # The final result is at the top of the stack

# Variable values
variables = {
    'A': 3,
    'B': 2,
    'C': 2,
    'D': 2,
    'E': 2,
    'F': 1
}

expression = "+*A-AE*B^^FB-+ECE"
print("Enter the prefix expression: ", expression)
print("\nDo you want the result as a: 1. Float or 2. Integer?: 2")
print("Symbol\tStack")
result = evaluate_prefix(expression, variables)
print("The evaluation is", result)
