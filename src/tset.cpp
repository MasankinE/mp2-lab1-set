#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(MaxPower)
{}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{ return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{ return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
     return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{ this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{ this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{ this->BitField = s.BitField;
     this->MaxPower = s.GetMaxPower();
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{ return this->BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{ return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{ InsElem(Elem);
   return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{   DelElem(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{  return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{ return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    char ts = 0;
     do {
         istr >> ts;
     }
   while (ts != '{');
 
     int temp = 0;
     do {
         istr >> ts;
         s.InsElem(temp);
 
        do {
             istr >> ts;
         }
         while ((ts != ',') && (ts != '}'));
     }
     while (ts != '}');
 
     return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{ 
	char ts = ' ';
     ostr << "{";
 
     for (int i = 0; i < s.GetMaxPower(); i++)
         if (s.IsMember(i)) {
             ostr << ts << ' ' << i;
             ts = ',';
        }
 
    ostr << "}";
 
     return ostr;
}
