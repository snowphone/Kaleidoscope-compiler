extern foo();
extern bar();

def cond(int _) -> int
	if _ > 1 then
		foo()
	else if _ then
		foo() + foo()
	else
		bar();

cond(4);
