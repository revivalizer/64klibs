#pragma once

class ZMatrixStack : public align16
{
public:
	ZMatrixStack(void);
	~ZMatrixStack(void);

	ZStack<ZMatrix> stack;

	void Reset() { stack.Reset(); stack.Push(IdentityMatrix()); };

	void Push() { stack.Push(stack.Top()); };
	void Push(ZMatrix& mat) { stack.Push(mat); };
	ZMatrix& Pop() { return stack.Pop(); };

	ZMatrix& operator()() { return stack.Top(); };

};