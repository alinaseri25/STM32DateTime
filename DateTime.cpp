#include "DateTime.h"


DateTime::DateTime(int16_t _year,int8_t _month,int8_t _day,int8_t _hour,int8_t _min,int8_t _sec)
{
	setDateTime(_year,_month,_day,_hour,_min,_sec);
	LHour = LMinute = 0;
	DayofWeek = 1;
}

void DateTime::setDateTime(int16_t _year,int8_t _month,int8_t _day,int8_t _hour,int8_t _min,int8_t _sec)
{
	if(_sec >= 60 || _sec < 0) _sec = 0;
	Second = _sec;
	if(_min >= 60 || _min < 0) _min = 0;
	Minute = _min;
	if(_hour >= 24 || _hour < 0) _hour = 0;
	Hour = _hour;
	
	Year = _year;
	if(_month > 12 || _month < 1) _month = 1;
	Month = _month;
	if(_day > 31 || _day < 1) _day = 1;
	Day = _day;
}

void DateTime::setDate(uint16_t _year,int8_t _month,int8_t _day)
{
	Year = _year;
	Month = _month;
	Day = _day;
}

void DateTime::setTime(int8_t _hour,int8_t _min,int8_t _sec)
{
	Hour = _hour;
	Minute = _min;
	Second = _sec;
}

uint16_t DateTime::getYear()
{
	return Year;
}

int8_t DateTime::getYearFrom2000()
{
	return Year - 2000;
}

uint8_t DateTime::getMonth()
{
	return Month;
}

uint8_t DateTime::getDay()
{
	return Day;
}

uint8_t DateTime::getHour()
{
	return Hour;
}

uint8_t DateTime::getMinute()
{
	return Minute;
}

uint8_t DateTime::getSecond()
{
	return Second;
}

void DateTime::setYear(int16_t _year)
{
	Year = _year;
}

void DateTime::setMonth(int8_t _month)
{
	if(_month > 12 || _month < 1) _month = 1;
	Month = _month;
}

void DateTime::setDay(int8_t _day)
{
	if(_day > 31 || _day < 1) _day = 1;
	Day = _day;
}

void DateTime::setHour(int8_t _hour)
{
	if(_hour >= 24 || _hour < 0) _hour = 0;
	Hour = _hour;
}

void DateTime::setMinute(int8_t _min)
{
	if(_min >= 60 || _min < 0) _min = 0;
	Minute = _min;
}

void DateTime::setSecond(int8_t _sec)
{
	if(_sec >= 60 || _sec < 0) _sec = 0;
	Second = _sec;
}

void DateTime::setDayOfWeek(int8_t _dow)
{
    if(_dow > 6 || _dow < 0) _dow = 0;
	DayofWeek = _dow;
}

uint8_t DateTime::getDayOfWeek()
{
	return DayofWeek;
}

const char *DateTime::getDayOfWeekStr()
{
	switch(DayofWeek)
	{
		case 0:
			return "Sunday";
		case 1:
			return "Monday";
		case 2:
			return "Tuesday";
		case 3:
			return "Wednesday";
		case 4:
			return "Thursday";
		case 5:
			return "Friday";
		case 6:
			return "Saturday";
		default:
			return "Not In Day's";
	}
}

void DateTime::setLocalTime(int8_t _hour,int8_t _min,bool _sign)
{
	LHour = _hour;
	LMinute = _min;
	LSign = _sign;
}

bool DateTime::getLocalTime(int8_t *_hour,int8_t *_min)
{
	*_hour = LHour;
	*_min = LMinute;
    return LSign;
}

void DateTime::addSecond(int16_t _sec)
{
    int16_t temp = this->Second + _sec;
    addMinute(temp/60);
    this->Second = temp % 60;
}

void DateTime::addMinute(int16_t _min)
{
    int16_t temp = this->Minute + _min;
    addHour(temp/60);
    this->Minute = temp % 60;
}

void DateTime::addHour(int16_t _hour)
{
    int16_t temp = this->Hour + _hour;
    addDay(temp/24);
    this->Hour = temp % 24;
}

void DateTime::addDay(int16_t _day)
{
    int16_t temp = this->Day + _day;
    while (temp > milmonth[(this->Month - 1)]) {
        temp -= milmonth[(this->Month - 1)];
        addMonth(1);
    }
    this->Day = temp;
}

void DateTime::addMonth(int16_t _month)
{
    int16_t temp = this->Month + _month;
    addYear(temp/12);
    this->Month = temp % 12;
}

void DateTime::addYear(int16_t _year)
{
    this->Year += _year;
}

DateTime DateTime::operator=(DateTime _dt)
{
	this->Second = _dt.getSecond();
	this->Minute = _dt.getMinute();
	this->Hour = _dt.getHour();
	
	this->DayofWeek = _dt.getDayOfWeek();
	
	this->Day = _dt.getDay();
	this->Month = _dt.getMonth();
	this->Year = _dt.getYear();
	
	this->LSign = _dt.getLocalTime(&this->LHour,&this->LMinute);
	
    return *this;
}

DateTime DateTime::operator+(DateTime _dt)
{
    DateTime temp = *this;
    temp.addSecond(_dt.getSecond());
    temp.addMinute(_dt.getMinute());
    temp.addHour(_dt.getHour());

    temp.addDay(_dt.getDay());
    temp.addMonth(_dt.getMonth());
    temp.addYear(_dt.getYear());

    return temp;
}

DateTime DateTime::operator+=(DateTime _dt)
{
    this->addSecond(_dt.getSecond());
    this->addMinute(_dt.getMinute());
    this->addHour(_dt.getHour());

    this->addDay(_dt.getDay());
    this->addMonth(_dt.getMonth());
    this->addYear(_dt.getYear());

    return *this;
}

bool DateTime::operator==(DateTime _dt)
{	
	if(this->Second != _dt.getSecond())
		return false;
	if(this->Minute != _dt.getMinute())
		return false;
	if(this->Hour != _dt.getHour())
		return false;
	
	if(this->DayofWeek != _dt.getDayOfWeek())
		return false;
	if(this->Day != _dt.getDay())
		return false;
	if(this->Month != _dt.getMonth())
		return false;
	if(this->Year != _dt.getYear())
		return false;
	
	int8_t h,m;
	if(this->LSign != _dt.getLocalTime(&h,&m))
		return false;
	if(this->LHour != h)
		return false;
	if(this->LMinute != m)
		return false;
	
	return true;
}

bool DateTime::operator!=(DateTime _dt)
{	
	if(this->Second != _dt.getSecond())
		return true;
	if(this->Minute != _dt.getMinute())
		return true;
	if(this->Hour != _dt.getHour())
		return true;
	
	if(this->DayofWeek != _dt.getDayOfWeek())
		return true;
	if(this->Day != _dt.getDay())
		return true;
	if(this->Month != _dt.getMonth())
		return true;
	if(this->Year != _dt.getYear())
		return true;
	
	int8_t h,m;
	if(this->LSign != _dt.getLocalTime(&h,&m))
		return true;
	if(this->LHour != h)
		return true;
	if(this->LMinute != m)
		return true;
	
    return false;
}

bool DateTime::operator<(DateTime _dt)
{
    if(this->Year > _dt.getYear())
        return false;
    else if((this->Year < _dt.getYear()))
        return true;

    if(this->Month > _dt.getMonth())
        return false;
    else if(this->Month < _dt.getMonth())
        return true;

    if(this->Day > _dt.getDay())
        return false;
    else if(this->Day < _dt.getMonth())
        return true;

    if(this->Hour > _dt.getHour())
        return false;
    else if(this->Hour < _dt.getHour())
        return true;

    if(this->Minute > _dt.getMinute())
        return false;
    else if(this->Minute < _dt.getMinute())
        return true;

    if(this->Second > _dt.getSecond())
        return false;
    else if(this->Second < _dt.getSecond())
        return true;

    return false;
}

bool DateTime::operator<=(DateTime _dt)
{
    if(this->Year > _dt.getYear())
        return false;
    else if((this->Year < _dt.getYear()))
        return true;

    if(this->Month > _dt.getMonth())
        return false;
    else if(this->Month < _dt.getMonth())
        return true;

    if(this->Day > _dt.getDay())
        return false;
    else if(this->Day < _dt.getMonth())
        return true;

    if(this->Hour > _dt.getHour())
        return false;
    else if(this->Hour < _dt.getHour())
        return true;

    if(this->Minute > _dt.getMinute())
        return false;
    else if(this->Minute < _dt.getMinute())
        return true;

    if(this->Second > _dt.getSecond())
        return false;
    else if(this->Second < _dt.getSecond())
        return true;

    return true;
}

bool DateTime::operator>(DateTime _dt)
{
    if(this->Year < _dt.getYear())
        return false;
    else if (this->Year > _dt.getYear())
        return true;

    if(this->Month < _dt.getMonth())
        return false;
    else if(this->Month > _dt.getMonth())
        return true;

    if(this->Day < _dt.getDay())
        return false;
    else if(this->Day > _dt.getDay())
        return true;

    if(this->Hour < _dt.getHour())
        return false;
    else if(this->Hour > _dt.getHour())
        return true;

    if(this->Minute < _dt.getMinute())
        return false;
    else if(this->Minute > _dt.getMinute())
        return true;

    if(this->Second < _dt.getSecond())
        return false;
    else if(this->Second > _dt.getSecond())
        return true;

    return false;
}

bool DateTime::operator>=(DateTime _dt)
{
    if(this->Year < _dt.getYear())
        return false;
    else if (this->Year > _dt.getYear())
        return true;

    if(this->Month < _dt.getMonth())
        return false;
    else if(this->Month > _dt.getMonth())
        return true;

    if(this->Day < _dt.getDay())
        return false;
    else if(this->Day > _dt.getDay())
        return true;

    if(this->Hour < _dt.getHour())
        return false;
    else if(this->Hour > _dt.getHour())
        return true;

    if(this->Minute < _dt.getMinute())
        return false;
    else if(this->Minute > _dt.getMinute())
        return true;

    if(this->Second < _dt.getSecond())
        return false;
    else if(this->Second > _dt.getSecond())
        return true;

    return true;
}
