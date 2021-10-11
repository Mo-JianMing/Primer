#ifndef SALESITEM_H
#define SALESITEM_H
#include <iostream>
#include <string>

/*
 * ������Ʒ��¼������
 */
class Sales_item
{
public:
// ���⺯��
	Sales_item() { Sales_item(""); }
	Sales_item(const std::string book) :isbn(book), units_sold(0), revenue(0.0){}
	Sales_item(std::istream &is){ is >> *this; }
public:
// ����������
	friend std::istream & operator>>(std::istream &, Sales_item &);
	friend std::ostream & operator<<(std::ostream &, const Sales_item &);
	Sales_item & operator+=(const Sales_item &);
public:
// ��Ա����
	double avg_price() const;
	bool same_isbn(const Sales_item &rhs) const
	{
		return isbn == rhs.isbn;
	}
// ��Ա����
public:
	std::string isbn;
	unsigned units_sold;
	double revenue;
};

using std::istream;
using std::ostream;
inline istream & operator>>(istream &in, Sales_item &s)
{
	double price;
	in >> s.isbn >> s.units_sold >> price;
	if (in)
		s.revenue = s.units_sold * price;
	return in;
}
inline ostream & operator<<(ostream &out, const Sales_item &s)
{
	out << s.isbn << "\t" << s.units_sold << "\t" << s.revenue;
	return out;
}
inline double Sales_item::avg_price() const
{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
inline Sales_item operator+(const Sales_item &lhs, const Sales_item &rhs)
{
	Sales_item ret(lhs);
	ret += rhs;
	return ret;
}
inline Sales_item & Sales_item::operator +=(const Sales_item &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
inline bool operator==(const Sales_item &lhs, const Sales_item &rhs)
{
	return lhs.same_isbn(rhs) && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}
inline bool operator!=(const Sales_item &lhs, const Sales_item &rhs)
{
	return !(lhs == rhs);
}
#endif