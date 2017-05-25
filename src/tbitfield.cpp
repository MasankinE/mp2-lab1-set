#include "tbitfield.h"

TBitField::TBitField(int len)
{    if (len < 0)
         throw "error, len < 0";

     else 
	 {
		 BitLen = len;
         MemLen = (len - 1) / (8 * sizeof(TELEM)) + 1;
         pMem   = new TELEM[MemLen];
         if (pMem != NULL)
             for (int i = 0; i < MemLen; i++)
				 pMem[i] = 0;
     }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem   = new TELEM[MemLen];
    if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	    delete [] pMem ;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{ 
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
   return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0)
        throw "error n<0";
 
    if (BitLen < n)
        throw "error n<BitLen";
 
    if ((-1 < n) && (n < BitLen))
         pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{  
	if (n < 0)
         throw "error n<0";
 
     if (BitLen < n)
         throw "error n<BitLen";
 
     if ((-1 < n) && (n < BitLen))
         pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	 if (n < 0)
         throw "error n<0";
 
     if (BitLen < n)
         throw "error n<BitLen";
 
    if ((-1 < n) && (n < this->BitLen))
        return pMem[GetMemIndex(n)] & GetMemMask(n);
    else
        return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{  
	BitLen = bf.BitLen;
 
     delete [] pMem;
     pMem = NULL;
     pMem = new TELEM[MemLen];
 
     if(pMem != NULL)
         for (int i = 0; i < MemLen; i++)
             pMem[i] = bf.pMem[i];
 
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
     int result  = 1;
 
    if (BitLen == bf.BitLen)
	{
        for (int i = 0; i < MemLen; i++)
             if (pMem[i] != bf.pMem[i]) {
                 result = 0;
                 break;
             }
     }
     else
         result = 0;
 
     return result ;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int result = 0;
 
     if (BitLen == bf.BitLen) {
         for (int i = 0; i < MemLen; i++)
             if (pMem[i] != bf.pMem[i]) {
                 result = 1;
                 break;
             }
     }
     else
       result = 1;
 
     return result;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{    int len = BitLen;
 
     if (len < bf.BitLen)
        len = bf.BitLen;
 
     TBitField disjunction(len);
    for (int i = 0; i < MemLen; i++)
         disjunction.pMem[i] = pMem[i];
 
     for (int i = 0; i < bf.MemLen; i++)
         disjunction.pMem[i] |= bf.pMem[i];
 
     return disjunction;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	   int len = BitLen;
 
    if (len < bf.BitLen)
        len = bf.BitLen;
 
    TBitField conjunction(len);
    for (int i = 0; i < MemLen; i++)
        conjunction.pMem[i] = pMem[i];
 
     for (int i = 0; i < bf.MemLen; i++)
        conjunction.pMem[i] &= bf.pMem[i];
 
     return conjunction;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField negation(*this);
 
    for (int i = 0; i < MemLen - 1; i++)
        negation.pMem[i] = ~negation.pMem[i];

     for (int i = (MemLen - 1) << 5; i < BitLen; i++)
         if (negation.GetBit(i))
             negation.ClrBit(i);
       else
            negation.SetBit(i);
 
     return negation;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	  char ts = 0;
     do {
         istr >> ts;
    } while (ts != ' ');
 
     int i = 0;
     while (1) {
        istr >> ts;
        if (ts == '0')
            bf.ClrBit(i++);
        else
            if (ts == '1')
                 bf.SetBit(i++);
             else
               break;
     }
 
     return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
 
    for (int i = 0; i < len; i++)
         if (bf.GetBit(i))
             ostr << '0';
         else
             ostr << '1';


     return ostr;

}
