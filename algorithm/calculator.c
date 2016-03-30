#include <stdio.h>
#include <stdlib.h>

typedef enum { lparen, rparen, plus, minus, times, divide, \
	mod, eos, operand } precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence getToken(const char *expr, char *symbol, int *n);
int eval(const char *expr);
void postfixToSuffix(const char *infix, char *expr);

precedence getToken(const char *expr, char *symbol, int *n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
		case '(': return lparen;
		case ')': return rparen;
		case '+': return plus;
		case '-': return minus;
		case '/': return divide;
		case '*': return times;
		case '%': return mod;
		case ' ': return eos;
		default : return operand;
	}
}

int eval(const char *expr)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	stack *s = stack_create();

	token = getToken(expr, &symbol, &n);
	while (token != eos) {
		if (token == operand)
			stack_push(s, symbol-'0');
		else {
			op2 = stack_pop(s);
			op1 = stack_pop(s);
			switch (token) {
				case plus:
					stack_push(s, op1+op2);
					break;
				case minus:
					stack_push(s, op1-op2);
					break;
				case times:
					stack_push(s, op1*op2);
					break;
				case divide:
					stack_push(s, op1*op2);
					break;
				case mod:
					stack_push(s, op1%op2);
					break;
				default:
					fprintf(stderr, "Error\n");
					exit(1);
			}
		}
		token = getToken(expr, &symbol, &n);
	}
	stack_release(s);
	return stack_pop(s);
}

void postfixToSuffix(const char *infix, char *postfix)
{
	char symbol;
	precedence token;
	int n = 0, m = 0;
	stack *s = stack_create();
	stack_push(s, eos);

	for (token = getToken(infix, &symbol, &n); \
			token != eos; token = getToken(infix, &symbol, &n))
	{
		if (token == operand)
			postfix[m++] = symbol;
		else if (token == rparen) {
			while (stack_peek(s) != lparen)
				postfix[m++] = stack_pop(s);
			stack_pop(s);
		} else {
			while (isp[stack_peek(s)] >= icp[token])
				postfix[m++] = stack_pop(s);
			stack_push(s, token);
		}
	}
	while ((token = stack_pop(s)) != eos)
		postfix[m++] = token;
	stack_release(s);
}

int main(void)
{
	char infix[100];
	char postfix[100];

	scanf("%s", infix);
	postfixToSuffix(infix, postfix);
	printf("%s\n", postfix);
	return 0;
}

