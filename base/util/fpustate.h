// RAII FPU state class, sets FTZ and DAZ and rounding, no exceptions 
// Adapted from code by mystran @ kvraudio
// http://www.kvraudio.com/forum/viewtopic.php?t=312228&postdays=0&postorder=asc&start=0

class ZFPUState
{ 
private:
	unsigned int sse_control_store; 

public: 
	enum Rounding 
	{
		kRoundNearest = 0, 
		kRoundNegative, 
		kRoundPositive, 
		kRoundToZero, 
	}; 

	ZFPUState(Rounding mode = kRoundToZero) 
	{
		sse_control_store = _mm_getcsr(); 

		// bits: 15 = flush to zero | 6 = denormals are zero 
		// bitwise-OR with exception masks 12:7 (exception flags 5:0) 
		// rounding 14:13, 00 = nearest, 01 = neg, 10 = pos, 11 = to zero 
		// The enum above is defined in the same order so just shift it up 
		_mm_setcsr(0x8040 | 0x1f80 | ((unsigned int)mode << 13)); 
	} 

	~ZFPUState() 
	{
		// clear exception flags, just in case (probably pointless) 
		_mm_setcsr(sse_control_store & (~0x3f)); 
	} 
}; 