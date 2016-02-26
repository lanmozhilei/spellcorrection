#ifndef _WD_NONCOPYABLE_H
#define _WD_NONCOPYABLE_H

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

private:
	Noncopyable(const Noncopyable &);
	Noncopyable &operator=(const Noncopyable &);
};

#endif
