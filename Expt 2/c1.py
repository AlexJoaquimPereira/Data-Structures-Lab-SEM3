def evaluate_postfix(expression, values):
    stack = []

    for symbol in expression:
        if symbol.isalnum():
            stack.append(values[symbol])
        else:
            operand2 = stack.pop()
            operand1 = stack.pop()
            if symbol == '+':
                result = operand1 + operand2
            elif symbol == '-':
                result = operand1 - operand2
            elif symbol == '*':
                result = operand1 * operand2
            elif symbol == '/':
                result = operand1 / operand2
            elif symbol == '^':
                result = operand1 ** operand2
            stack.append(result)

    stack = [round(item, 6) if isinstance(item, float) else item for item in stack]

    return stack[0]

postfix_expression = "FDCA+/B*B*-DEA^^-"
values = {'A': 3, 'B': 2, 'C': 2, 'D': 2, 'E': 2, 'F': 1}


print("Enter the postfix expression: ");
print(postfix_expression);
print("\nDo you want it as a 1. Float or 2. Integer?: 1\n")
print("Symbol\tStack")
#print("------------")
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

print("\nThe evaluation is:", stack[0])
