extern "C"
{
	typedef unsigned char Byte;
	typedef unsigned short Word;
	typedef unsigned short Address;
	typedef unsigned char Port;

	enum class InterruptType
	{
		None,
		Halted,
		CodeModified,
		UnknownOpcode
	};

	class Memory
	{
	public:
		Byte byte;
		bool isCode;
		bool isStart;
		bool isEnd;
		bool isMethodStart;
		bool isAnchor;

		Memory() :
			byte(),
			isCode(false),
			isStart(false),
			isEnd(false),
			isMethodStart(false),
			isAnchor(false)
		{}

	};

	class State
	{
	public:
		State() :
			a(0), b(0), c(0), d(0), e(0), h(0), l(0), pc(0), parentBlockPc(0), sp(0),
			cf(false), sf(false), zf(false), pf(false), af(false),
			ie(true),
			m(nullptr),
			isInterrupted(false), interruptType(InterruptType::None),
			resumeFromRecordIndex(-1), sideExitIndex(-1),
			interpretedCount(nullptr), nativelyExecutedCount(nullptr)
		{}

		void SetSf()
		{
			sf = ((a & 0x80) == 0x80);
		}

		void SetSf(Byte operand)
		{
			sf = ((operand & 0x80) == 0x80);
		}

		void SetZf()
		{
			zf = (a == 0x00);
		}

		void SetZf(Byte operand)
		{
			zf = (operand == 0x00);
		}

		void SetPf()
		{
			pf = true;
			for (int i = 0; i < 8; ++i)
			{
				if ((a >> i) & 1)
					pf = !pf;
			}
		}

		void SetPf(Byte operand)
		{
			pf = true;
			for (int i = 0; i < 8; ++i)
			{
				if ((operand >> i) & 1)
					pf = !pf;
			}
		}

		void SetCarryDueToSub(Byte operand)
		{
			cf = (a < operand);
		}

		void SetCarryDueToAdd(Byte operand)
		{
			Byte sum = a + operand;
			cf = (sum < a);
		}

		void SetAuxCarryDueToAdd(Byte operand)
		{
			af = (((a & 0x0f) + (operand & 0x0f)) > 0x09);
		}

		void SetAuxCarryDueToAdd(Byte operand1, Byte operand2)
		{
			af = (((operand1 & 0x0f) + (operand2 & 0x0f)) > 0x09);
		}

		void SetAuxCarryDueToSub(Byte operand)
		{
			af = ((a & 0x0f) < (operand & 0x0f));
		}

		void SetAuxCarryDueToSub(Byte operand1, Byte operand2)
		{
			af = ((operand1 & 0x0f) < (operand2 & 0x0f));
		}

		void SetAuxCarryDueToAnd(Byte operand)
		{
			af = (((a & 0x08) | (operand & 0x08)) == 0x08);
		}

		Memory& GetM()
		{
			size_t index = (h << 8) + l;
			return m[index];
		}

		Memory& GetST() // stack top
		{
			size_t index = sp;
			return m[index];
		}

		// registers
		Byte a;
		Byte b;
		Byte c;
		Byte d;
		Byte e;
		Byte h;
		Byte l;
		Address pc;
		Address parentBlockPc;
		Address sp;

		// condition flags
		bool cf;
		bool sf;
		bool zf;
		bool pf;
		bool af;

		// interrupt flag
		bool ie;

		// memory
		Memory* m;

		// interrupted
		bool isInterrupted;
		InterruptType interruptType;

		// compiler
		int resumeFromRecordIndex;
		int sideExitIndex;

		//benchmarking
		int* interpretedCount;
		int* nativelyExecutedCount;
	};

	// data transfer
	// MOVE R,R ---------------------------------------------------------------------------
	void mov_a_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->a;
		s->pc += 1;
	}

	void mov_a_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->b;
		s->pc += 1;
	}

	void mov_a_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->c;
		s->pc += 1;
	}

	void mov_a_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->d;
		s->pc += 1;
	}

	void mov_a_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->e;
		s->pc += 1;
	}

	void mov_a_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->h;
		s->pc += 1;
	}

	void mov_a_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->l;
		s->pc += 1;
	}

	void mov_b_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->a;
		s->pc += 1;
	}

	void mov_b_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->b;
		s->pc += 1;
	}

	void mov_b_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->c;
		s->pc += 1;
	}

	void mov_b_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->d;
		s->pc += 1;
	}

	void mov_b_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->e;
		s->pc += 1;
	}

	void mov_b_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->h;
		s->pc += 1;
	}

	void mov_b_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->l;
		s->pc += 1;
	}

	void mov_c_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->a;
		s->pc += 1;
	}

	void mov_c_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->b;
		s->pc += 1;
	}

	void mov_c_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->c;
		s->pc += 1;
	}

	void mov_c_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->d;
		s->pc += 1;
	}

	void mov_c_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->e;
		s->pc += 1;
	}

	void mov_c_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->h;
		s->pc += 1;
	}

	void mov_c_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->l;
		s->pc += 1;
	}

	void mov_d_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->a;
		s->pc += 1;
	}

	void mov_d_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->b;
		s->pc += 1;
	}

	void mov_d_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->c;
		s->pc += 1;
	}

	void mov_d_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->d;
		s->pc += 1;
	}

	void mov_d_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->e;
		s->pc += 1;
	}

	void mov_d_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->h;
		s->pc += 1;
	}

	void mov_d_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->l;
		s->pc += 1;
	}

	void mov_e_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->a;
		s->pc += 1;
	}

	void mov_e_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->b;
		s->pc += 1;
	}

	void mov_e_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->c;
		s->pc += 1;
	}

	void mov_e_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->d;
		s->pc += 1;
	}

	void mov_e_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->e;
		s->pc += 1;
	}

	void mov_e_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->h;
		s->pc += 1;
	}

	void mov_e_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->l;
		s->pc += 1;
	}

	void mov_h_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->a;
		s->pc += 1;
	}

	void mov_h_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->b;
		s->pc += 1;
	}

	void mov_h_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->c;
		s->pc += 1;
	}

	void mov_h_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->d;
		s->pc += 1;
	}

	void mov_h_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->e;
		s->pc += 1;
	}

	void mov_h_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->h;
		s->pc += 1;
	}

	void mov_h_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->l;
		s->pc += 1;
	}

	void mov_l_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->a;
		s->pc += 1;
	}

	void mov_l_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->b;
		s->pc += 1;
	}

	void mov_l_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->c;
		s->pc += 1;
	}

	void mov_l_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->d;
		s->pc += 1;
	}

	void mov_l_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->e;
		s->pc += 1;
	}

	void mov_l_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->h;
		s->pc += 1;
	}

	void mov_l_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->l;
		s->pc += 1;
	}

	// MOV M,R ----------------------------------------------------------------------------------------------------

	void mov_m_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->a;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void mov_m_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->b;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void mov_m_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->c;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void mov_m_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->d;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void mov_m_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->e;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void mov_m_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->h;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void mov_m_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = s->l;
		s->pc += 1;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	// MOV R,M ---------------------------------------------------------------------------------

	void mov_a_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->GetM().byte;
		s->pc += 1;
	}

	void mov_b_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = s->GetM().byte;
		s->pc += 1;
	}

	void mov_c_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->GetM().byte;
		s->pc += 1;
	}

	void mov_d_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = s->GetM().byte;
		s->pc += 1;
	}

	void mov_e_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->GetM().byte;
		s->pc += 1;
	}

	void mov_h_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = s->GetM().byte;
		s->pc += 1;
	}

	void mov_l_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->GetM().byte;
		s->pc += 1;
	}

	// MVI R/M ----------------------------------------------------------------------------------
	void mvi_a(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = operand;
		s->pc += 2;
	}

	void mvi_b(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->b = operand;
		s->pc += 2;
	}

	void mvi_c(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = operand;
		s->pc += 2;
	}

	void mvi_d(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->d = operand;
		s->pc += 2;
	}

	void mvi_e(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = operand;
		s->pc += 2;
	}

	void mvi_h(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->h = operand;
		s->pc += 2;
	}

	void mvi_l(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = operand;
		s->pc += 2;
	}

	void mvi_m(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->GetM().byte = operand;
		s->pc += 2;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	// LOAD --------------------------------------------------------------------------

	void lda(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->m[(size_t)operand].byte;
		s->pc += 3;
	}

	void ldax_bc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->m[(size_t)((s->b << 8) + s->c)].byte;
		s->pc += 1;
	}

	void ldax_de(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = s->m[(size_t)((s->d << 8) + s->e)].byte;
		s->pc += 1;
	}

	void lhld(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->m[(size_t)operand].byte;
		s->h = s->m[(size_t)((Word)(operand + 0x0001))].byte;
		s->pc += 3;
	}

	void lxi_bc(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = operand;
		s->b = operand >> 8;
		s->pc += 3;
	}

	void lxi_de(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = operand;
		s->d = operand >> 8;
		s->pc += 3;
	}

	void lxi_hl(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = operand;
		s->h = operand >> 8;
		s->pc += 3;
	}

	void lxi_sp(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp = operand;
		s->pc += 3;
	}

	// EXCHANGE -----------------------------------------------------------

	void xchg(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte temp;
		temp = s->d;
		s->d = s->h;
		s->h = temp;
		temp = s->e;
		s->e = s->l;
		s->l = temp;
		s->pc += 1;
	}

	// STORE -----------------------------------------------------------------------------

	void sta(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		size_t index = (size_t)operand;
		s->m[index].byte = s->a;
		s->pc += 3;
		if (s->m[index].isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void stax_bc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		size_t index = (size_t)((s->b << 8) + s->c);
		s->m[index].byte = s->a;
		s->pc += 1;
		if (s->m[index].isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void stax_de(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		size_t index = (size_t)((s->d << 8) + s->e);
		s->m[index].byte = s->a;
		s->pc += 1;
		if (s->m[index].isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	void shld(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		size_t index = (size_t)operand;
		size_t next_index = (size_t)((Word)(operand + 0x0001));
		s->m[index].byte = s->l;
		s->m[next_index].byte = s->h;
		s->pc += 3;
		if (s->m[index].isCode || s->m[next_index].isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
	}

	// logical

	void ana_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->a);
		s->a = s->a & s->a;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->b);
		s->a = s->a & s->b;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->c);
		s->a = s->a & s->c;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->d);
		s->a = s->a & s->d;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->e);
		s->a = s->a & s->e;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->h);
		s->a = s->a & s->h;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->l);
		s->a = s->a & s->l;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ana_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(s->GetM().byte);
		s->a = s->a & s->GetM().byte;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ani(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->SetAuxCarryDueToAnd(operand);
		s->a = s->a & operand;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 2;
	}

	void ora_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->a;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->b;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->c;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->d;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->e;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->h;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->l;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ora_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | s->GetM().byte;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void ori(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a | operand;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void xra_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->a;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->b;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->c;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->d;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->e;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->h;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->l;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xra_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ s->GetM().byte;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}
	void xri(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = false;
		s->af = false;
		s->a = s->a ^ operand;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 2;
	}

	// rotate

	void ral(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = ((s->a & 0x80) == 0x80);
		s->a = (s->a << 1);
		s->pc += 1;
	}
	void rar(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = ((s->a & 0x01) == 0x01);
		s->a = (s->a >> 1);
		s->pc += 1;
	}
	void rlc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = ((s->a & 0x80) == 0x80);
		s->a = (s->a << 1);
		if (s->cf == true)
			s->a = s->a | 0x01; // set bit 0
		s->pc += 1;
	}
	void rrc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = ((s->a & 0x01) == 0x01);
		s->a = (s->a >> 1);
		if (s->cf == true)
			s->a = s->a | 0x80; // set bit 7
		s->pc += 1;
	}

	// complement, carry
	void cma(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = ~(s->a);
		s->pc += 1;
	}
	void cmc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = !(s->cf);
		s->pc += 1;
	}
	void stc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->cf = true;
		s->pc += 1;
	}

	// stack
	void push_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp -= 1;
		s->GetST().byte = s->b;
		s->sp -= 1;
		s->GetST().byte = s->c;
		s->pc += 1;
	}
	void push_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp -= 1;
		s->GetST().byte = s->d;
		s->sp -= 1;
		s->GetST().byte = s->e;
		s->pc += 1;
	}
	void push_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp -= 1;
		s->GetST().byte = s->h;
		s->sp -= 1;
		s->GetST().byte = s->l;
		s->pc += 1;
	}
	void push_psw(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp -= 1;
		s->GetST().byte = s->a;
		s->sp -= 1;
		// condition flag byte
		// S Z 0 A 0 P 1 C
		Byte cfb = 0b00000010;
		if (s->sf == true)
			cfb = cfb | 0b10000000;
		if (s->zf == true)
			cfb = cfb | 0b01000000;
		if (s->af == true)
			cfb = cfb | 0b00010000;
		if (s->pf == true)
			cfb = cfb | 0b00000100;
		if (s->cf == true)
			cfb = cfb | 0b00000001;
		s->GetST().byte = cfb;
		s->pc += 1;
	}
	void pop_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c = s->GetST().byte;
		s->sp += 1;
		s->b = s->GetST().byte;
		s->sp += 1;
		s->pc += 1;
	}
	void pop_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e = s->GetST().byte;
		s->sp += 1;
		s->d = s->GetST().byte;
		s->sp += 1;
		s->pc += 1;
	}
	void pop_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l = s->GetST().byte;
		s->sp += 1;
		s->h = s->GetST().byte;
		s->sp += 1;
		s->pc += 1;
	}
	void pop_psw(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		// condition flag byte
		// S Z 0 A 0 P 1 C
		Byte cfb = s->GetST().byte;
		s->sf = ((cfb & 0b10000000) != 0x00);
		s->zf = ((cfb & 0b01000000) != 0x00);
		s->af = ((cfb & 0b00010000) != 0x00);
		s->pf = ((cfb & 0b00000100) != 0x00);
		s->cf = ((cfb & 0b00000001) != 0x00);
		s->sp += 1;
		s->a = s->GetST().byte;
		s->sp += 1;
		s->pc += 1;
	}
	void xthl(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte oldL = s->l;
		Byte oldH = s->h;
		s->l = s->m[(size_t)s->sp].byte;
		s->h = s->m[(size_t)((Word)(s->sp + 0x0001))].byte;
		s->m[(size_t)s->sp].byte = oldL;
		s->m[(size_t)((Word)(s->sp + 0x0001))].byte = oldH;
		s->pc += 1;
	}
	void sphl(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp = (s->h << 8) + s->l;
		s->pc += 1;
	}

	//arithmetic

	void add_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->a);
		s->SetAuxCarryDueToAdd(s->a);
		s->a += s->a;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->b);
		s->SetAuxCarryDueToAdd(s->b);
		s->a += s->b;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->c);
		s->SetAuxCarryDueToAdd(s->c);
		s->a += s->c;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->d);
		s->SetAuxCarryDueToAdd(s->d);
		s->a += s->d;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->e);
		s->SetAuxCarryDueToAdd(s->e);
		s->a += s->e;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->h);
		s->SetAuxCarryDueToAdd(s->h);
		s->a += s->h;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(s->l);
		s->SetAuxCarryDueToAdd(s->l);
		s->a += s->l;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void add_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte toAdd = s->GetM().byte;
		s->SetCarryDueToAdd(toAdd);
		s->SetAuxCarryDueToAdd(toAdd);
		s->a += toAdd;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adi(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToAdd(operand);
		s->SetAuxCarryDueToAdd(operand);
		s->a += operand;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 2;
	}

	void adc_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->a);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->a);
		s->a += s->a;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->b);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->b);
		s->a += s->b;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->c);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->c);
		s->a += s->c;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->d);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->d);
		s->a += s->d;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->e);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->e);
		s->a += s->e;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->h);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->h);
		s->a += s->h;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(s->l);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(s->l);
		s->a += s->l;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void adc_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		Byte toAdd = s->GetM().byte;
		if (s->cf == false)
			s->SetCarryDueToAdd(toAdd);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(toAdd);
		s->a += toAdd;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void aci(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToAdd(0x01);
			s->SetAuxCarryDueToAdd(0x01);
			s->a += 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToAdd(operand);
		if (s->af == false)
			s->SetAuxCarryDueToAdd(operand);
		s->a += operand;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 2;
	}

	void sub_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->a);
		s->SetAuxCarryDueToSub(s->a);
		s->a -= s->a;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->b);
		s->SetAuxCarryDueToSub(s->b);
		s->a -= s->b;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->c);
		s->SetAuxCarryDueToSub(s->c);
		s->a -= s->c;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->d);
		s->SetAuxCarryDueToSub(s->d);
		s->a -= s->d;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->e);
		s->SetAuxCarryDueToSub(s->e);
		s->a -= s->e;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->h);
		s->SetAuxCarryDueToSub(s->h);
		s->a -= s->h;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->l);
		s->SetAuxCarryDueToSub(s->l);
		s->a -= s->l;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sub_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte toSub = s->GetM().byte;
		s->SetCarryDueToSub(toSub);
		s->SetAuxCarryDueToSub(toSub);
		s->a -= toSub;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void sui(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(operand);
		s->SetAuxCarryDueToSub(operand);
		s->a -= operand;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 2;
	}

	void sbb_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->a = 0xff;
		s->cf = true;
		s->af = true;
		s->zf = false;
		s->sf = true;
		s->pf = true;
		s->pc += 1;
	}

	void sbb_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(s->b);
		if (s->af == false)
			s->SetAuxCarryDueToSub(s->b);
		s->a -= s->b;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbb_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(s->c);
		if (s->af == false)
			s->SetAuxCarryDueToSub(s->c);
		s->a -= s->c;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbb_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(s->d);
		if (s->af == false)
			s->SetAuxCarryDueToSub(s->d);
		s->a -= s->d;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbb_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(s->e);
		if (s->af == false)
			s->SetAuxCarryDueToSub(s->e);
		s->a -= s->e;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbb_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(s->h);
		if (s->af == false)
			s->SetAuxCarryDueToSub(s->h);
		s->a -= s->h;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbb_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(s->l);
		if (s->af == false)
			s->SetAuxCarryDueToSub(s->l);
		s->a -= s->l;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbb_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		Byte toSub = s->GetM().byte;
		if (s->cf == false)
			s->SetCarryDueToSub(toSub);
		if (s->af == false)
			s->SetAuxCarryDueToSub(toSub);
		s->a -= toSub;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 1;
	}

	void sbi(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
		{
			s->SetCarryDueToSub(0x01);
			s->SetAuxCarryDueToSub(0x01);
			s->a -= 0x01;
		}

		if (s->cf == false)
			s->SetCarryDueToSub(operand);
		if (s->af == false)
			s->SetAuxCarryDueToSub(operand);
		s->a -= operand;
		s->SetSf();
		s->SetZf();
		s->SetPf();
		s->pc += 2;
	}

	void inr_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->a, 0x01);
		s->a += 0x01;
		s->SetPf(s->a);
		s->SetSf(s->a);
		s->SetZf(s->a);
		s->pc += 1;
	}

	void inr_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->b, 0x01);
		s->b += 0x01;
		s->SetPf(s->b);
		s->SetSf(s->b);
		s->SetZf(s->b);
		s->pc += 1;
	}

	void inr_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->c, 0x01);
		s->c += 0x01;
		s->SetPf(s->c);
		s->SetSf(s->c);
		s->SetZf(s->c);
		s->pc += 1;
	}

	void inr_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->d, 0x01);
		s->d += 0x01;
		s->SetPf(s->d);
		s->SetSf(s->d);
		s->SetZf(s->d);
		s->pc += 1;
	}

	void inr_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->e, 0x01);
		s->e += 0x01;
		s->SetPf(s->e);
		s->SetSf(s->e);
		s->SetZf(s->e);
		s->pc += 1;
	}

	void inr_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->h, 0x01);
		s->h += 0x01;
		s->SetPf(s->h);
		s->SetSf(s->h);
		s->SetZf(s->h);
		s->pc += 1;
	}

	void inr_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->l, 0x01);
		s->l += 0x01;
		s->SetPf(s->l);
		s->SetSf(s->l);
		s->SetZf(s->l);
		s->pc += 1;
	}

	void inr_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToAdd(s->GetM().byte, 0x01);
		s->GetM().byte += 0x01;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
		s->SetPf(s->GetM().byte);
		s->SetSf(s->GetM().byte);
		s->SetZf(s->GetM().byte);
		s->pc += 1;
	}

	void dcr_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->a, 0x01);
		s->a -= 0x01;
		s->SetPf();
		s->SetSf();
		s->SetZf();
		s->pc += 1;
	}

	void dcr_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->b, 0x01);
		s->b -= 0x01;
		s->SetPf(s->b);
		s->SetSf(s->b);
		s->SetZf(s->b);
		s->pc += 1;
	}

	void dcr_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->c, 0x01);
		s->c -= 0x01;
		s->SetPf(s->c);
		s->SetSf(s->c);
		s->SetZf(s->c);
		s->pc += 1;
	}

	void dcr_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->d, 0x01);
		s->d -= 0x01;
		s->SetPf(s->d);
		s->SetSf(s->d);
		s->SetZf(s->d);
		s->pc += 1;
	}

	void dcr_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->e, 0x01);
		s->e -= 0x01;
		s->SetPf(s->e);
		s->SetSf(s->e);
		s->SetZf(s->e);
		s->pc += 1;
	}

	void dcr_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->h, 0x01);
		s->h -= 0x01;
		s->SetPf(s->h);
		s->SetSf(s->h);
		s->SetZf(s->h);
		s->pc += 1;
	}

	void dcr_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->l, 0x01);
		s->l -= 0x01;
		s->SetPf(s->l);
		s->SetSf(s->l);
		s->SetZf(s->l);
		s->pc += 1;
	}

	void dcr_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetAuxCarryDueToSub(s->GetM().byte, 0x01);
		s->GetM().byte -= 0x01;
		if (s->GetM().isCode)
		{
			s->isInterrupted = true;
			s->interruptType = InterruptType::CodeModified;
		}
		s->SetPf(s->GetM().byte);
		s->SetSf(s->GetM().byte);
		s->SetZf(s->GetM().byte);
		s->pc += 1;
	}

	void inx_bc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->c += 0x01;
		if (s->c == 0x00)
			s->b += 0x01;
		s->pc += 1;
	}

	void inx_de(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->e += 0x01;
		if (s->e == 0x00)
			s->d += 0x01;
		s->pc += 1;
	}

	void inx_hl(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->l += 0x01;
		if (s->l == 0x00)
			s->h += 0x01;
		s->pc += 1;
	}

	void inx_sp(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp += 0x0001;
		s->pc += 1;
	}

	void dcx_bc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->c == 0x00)
		{

			s->b -= 0x01;
			s->c = 0xff;
		}
		else
			s->c -= 0x01;
		s->pc += 1;
	}

	void dcx_de(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->e == 0x00)
		{

			s->d -= 0x01;
			s->e = 0xff;
		}
		else
			s->e -= 0x01;
		s->pc += 1;
	}

	void dcx_hl(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->l == 0x00)
		{

			s->h -= 0x01;
			s->l = 0xff;
		}
		else
			s->l -= 0x01;
		s->pc += 1;
	}

	void dcx_sp(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->sp -= 0x0001;
		s->pc += 1;
	}

	void dad_bc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte sumL = s->l + s->c;
		Byte sumH = s->h + s->b;
		if (sumH < s->h)
			s->cf = true;
		else
		{
			if (sumL < s->l)
			{
				sumH += 0x01;
				if (sumH < 0x01)
					s->cf = true;
				else
					s->cf = false;
			}
			else
			{
				s->cf = false;
			}
		}
		s->l = sumL;
		s->h = sumH;
		s->pc += 1;
	}

	void dad_de(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte sumL = s->l + s->e;
		Byte sumH = s->h + s->d;
		if (sumH < s->h)
			s->cf = true;
		else
		{
			if (sumL < s->l)
			{
				sumH += 0x01;
				if (sumH < 0x01)
					s->cf = true;
				else
					s->cf = false;
			}
			else
			{
				s->cf = false;
			}
		}
		s->l = sumL;
		s->h = sumH;
		s->pc += 1;
	}

	void dad_hl(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte sumL = s->l + s->l;
		Byte sumH = s->h + s->h;
		if (sumH < s->h)
			s->cf = true;
		else
		{
			if (sumL < s->l)
			{
				sumH += 0x01;
				if (sumH < 0x01)
					s->cf = true;
				else
					s->cf = false;
			}
			else
			{
				s->cf = false;
			}
		}
		s->l = sumL;
		s->h = sumH;
		s->pc += 1;
	}

	void dad_sp(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte lower = s->sp;
		Byte upper = Byte(s->sp >> 8);
		Byte sumL = s->l + lower;
		Byte sumH = s->h + upper;
		if (sumH < s->h)
			s->cf = true;
		else
		{
			if (sumL < s->l)
			{
				sumH += 0x01;
				if (sumH < 0x01)
					s->cf = true;
				else
					s->cf = false;
			}
			else
			{
				s->cf = false;
			}
		}
		s->l = sumL;
		s->h = sumH;
		s->pc += 1;
	}

	void daa(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (((s->a & 0x0f) > 0x09) || (s->af == true))
		{
			s->a += 0x06;
			s->af = true;
		}
		if (((s->a & 0xf0) > 0x90) || (s->cf == true))
		{
			s->a += 0x60;
			s->cf = true;
		}
		s->SetZf();
		s->SetSf();
		s->SetPf();
		s->pc += 1;
	}

	// branching
	void jmp(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc = operand;
	}
	void jc(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jnc(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == false)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jm(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->sf == true)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jp(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->sf == false)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jz(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->zf == true)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jnz(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->zf == false)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jpe(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->pf == true)
			s->pc = operand;
		else
			s->pc += 3;
	}
	void jpo(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->pf == false)
			s->pc = operand;
		else
			s->pc += 3;
	}

	void push_pc(State* s)
	{
		s->sp -= 1;
		s->GetST().byte = (s->pc >> 8); // higher bits
		s->sp -= 1;
		s->GetST().byte = (Byte)s->pc; // lower bits
		s->pc += 1;
	}
	void call(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		push_pc(s);
		s->pc = operand;
	}
	void cc(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->cf == true)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cnc(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->cf == false)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cm(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->sf == true)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cp(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->sf == false)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cz(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->zf == true)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cnz(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->zf == false)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cpe(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->pf == true)
		{
			push_pc(s);
			s->pc = operand;
		}
	}
	void cpo(State* s, Word operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 3;
		if (s->pf == false)
		{
			push_pc(s);
			s->pc = operand;
		}
	}

	void pop_pc(State* s)
	{
		Byte c = s->GetST().byte;
		s->sp += 1;
		Byte p = s->GetST().byte;
		s->sp += 1;
		s->pc = (p << 8) + c;
	}
	void ret(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		pop_pc(s);
	}
	void rc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == true)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rnc(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->cf == false)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rm(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->sf == true)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rp(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->sf == false)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rz(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->zf == true)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rnz(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->zf == false)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rpe(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->pf == true)
			pop_pc(s);
		else
			s->pc += 1;
	}
	void rpo(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->pf == false)
			pop_pc(s);
		else
			s->pc += 1;
	}

	// program counter
	void pchl(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc = (s->h << 8) + s->l;
	}
	void rst_0(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0000;
		}
	}
	void rst_1(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0008;
		}
	}
	void rst_2(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0010;
		}
	}
	void rst_3(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0018;
		}
	}
	void rst_4(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0020;
		}
	}
	void rst_5(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0028;
		}
	}
	void rst_6(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0030;
		}
	}
	void rst_7(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		if (s->ie == true)
		{
			s->pc += 1;
			push_pc(s);
			s->pc = 0x0038;
		}
	}

	// machine control
	void hlt(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->isInterrupted = true;
		s->interruptType = InterruptType::Halted;
	}

	void nop(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->pc += 1;
	}

	void ei(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->ie = true;
		s->pc += 1;
	}

	void di(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->ie = false;
		s->pc += 1;
	}

	// compare functions
	void cmp_a(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->a);
		s->SetAuxCarryDueToSub(s->a);
		Byte result = s->a - s->a;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_b(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->b);
		s->SetAuxCarryDueToSub(s->b);
		Byte result = s->a - s->b;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_c(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->c);
		s->SetAuxCarryDueToSub(s->c);
		Byte result = s->a - s->c;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_d(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->d);
		s->SetAuxCarryDueToSub(s->d);
		Byte result = s->a - s->d;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_e(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->e);
		s->SetAuxCarryDueToSub(s->e);
		Byte result = s->a - s->e;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_h(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->h);
		s->SetAuxCarryDueToSub(s->h);
		Byte result = s->a - s->h;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_l(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(s->l);
		s->SetAuxCarryDueToSub(s->l);
		Byte result = s->a - s->l;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cmp_m(State* s)
	{
		++(s->nativelyExecutedCount[s->pc]);
		Byte toSub = s->GetM().byte;
		s->SetCarryDueToSub(toSub);
		s->SetAuxCarryDueToSub(toSub);
		Byte result = s->a - toSub;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 1;
	}

	void cpi(State* s, Byte operand)
	{
		++(s->nativelyExecutedCount[s->pc]);
		s->SetCarryDueToSub(operand);
		s->SetAuxCarryDueToSub(operand);
		Byte result = s->a - operand;
		s->SetPf(result);
		s->SetSf(result);
		s->SetZf(result);
		s->pc += 2;
	}

}