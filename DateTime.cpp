#include "DateTime.h"


DateTime::DateTime(int16_t _year,int8_t _month,int8_t _day,int8_t _hour,int8_t _min,int8_t _sec)
{
	setDateTime(_year,_month,_day,_hour,_min,_sec);
	LHour = LMinute = 0;
	DayofWeek = 1;
}

void DateTime::setCurrentDateTime(RTC_HandleTypeDef *_hrtc)
{
	RTC_DateTypeDef _date;
	RTC_TimeTypeDef _time;
	_date.Year = Year - 2000;
	_date.Month = Month;
	_date.Date = Day;
	HAL_RTC_SetDate(_hrtc,&_date,RTC_FORMAT_BIN);
	_time.Hours = Hour;
	_time.Minutes = Minute;
	_time.Seconds = Second;
	HAL_RTC_SetTime(_hrtc,&_time,RTC_FORMAT_BIN);
}

void DateTime::getCurrentDateTime(RTC_HandleTypeDef *_hrtc)
{
	RTC_DateTypeDef _date;
	RTC_TimeTypeDef _time;
	HAL_RTC_GetDate(_hrtc,&_date,RTC_FORMAT_BIN);
	osDelay(1);
	HAL_RTC_GetTime(_hrtc,&_time,RTC_FORMAT_BIN);
	setDateTime(_date.Year,_date.Month,_date.Date,_time.Hours,_time.Minutes,_time.Seconds);
	setDayOfWeek(_date.WeekDay);
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

void DateTime::setUnixTime(uint64_t _UnixtTime)
{
	UnixDateTime = _UnixtTime;
	UnixToDateTime();
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

const char *DateTime::getDayOfWeekStr(StrinDyOfWeekSize _SDOWS)
{
	switch(DayofWeek)
	{
		case 0:
			if(_SDOWS == Full)
				return "Sunday";
			else
				return "Su";
		case 1:
			if(_SDOWS == Full)
				return "Monday";
			else
				return "Mo";
		case 2:
			if(_SDOWS == Full)
				return "Tuesday";
			else
				return "Tu";
		case 3:
			if(_SDOWS == Full)
				return "Wednesday";
			else
				return "We";
		case 4:
			if(_SDOWS == Full)
				return "Thursday";
			else
				return "Th";
		case 5:
			if(_SDOWS == Full)
				return "Friday";
			else
				return "Fr";
		case 6:
			if(_SDOWS == Full)
				return "Saturday";
			else
				return "Sa";
		default:
			if(_SDOWS == Full)
				return "Not In Day's";
			else
				return "NA";
	}
}

uint64_t DateTime::getUnixTime(void)
{
	DateTimeToUnix();
	return UnixDateTime;
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

void DateTime::DateTimeToUnix(void)
{
	uint16_t y;
	uint16_t m;
	uint16_t d;

	//Year
	y = Year;
	//Month of year
	m = Month;
	//Day of month
	d = Day;

	//January and February are counted as months 13 and 14 of the previous year
	if(m <= 2)
	{
		 m += 12;
		 y -= 1;
	}
	
	//Convert years to days
	UnixDateTime = (365 * y) + (y / 4) - (y / 100) + (y / 400);
	//Convert months to days
	UnixDateTime += (30 * m) + (3 * (m + 1) / 5) + d;
	//Unix time starts on January 1st, 1970
	UnixDateTime -= 719561;
	//Convert days to seconds
	UnixDateTime *= 86400;
	//Add hours, minutes and seconds
	UnixDateTime += (3600 * Hour) + (60 * Minute) + Second;
}

void DateTime::UnixToDateTime(void)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;

	//Negative Unix time values are not supported
	if(UnixDateTime < 1)
		 UnixDateTime = 0;

	//Retrieve hours, minutes and seconds
	Second = UnixDateTime % 60;
	UnixDateTime /= 60;
	Minute = UnixDateTime % 60;
	UnixDateTime /= 60;
	Hour = UnixDateTime % 24;
	UnixDateTime /= 24;

	//Convert Unix time to date
	a = (uint32_t) ((4 * UnixDateTime + 102032) / 146097 + 15);
	b = (uint32_t) (UnixDateTime + 2442113 + a - (a / 4));
	c = (20 * b - 2442) / 7305;
	d = b - 365 * c - (c / 4);
	e = d * 1000 / 30601;
	f = d - e * 30 - e * 601 / 1000;

	//January and February are counted as months 13 and 14 of the previous year
	if(e <= 13)
	{
		 c -= 4716;
		 e -= 1;
	}
	else
	{
		 c -= 4715;
		 e -= 13;
	}

	//Retrieve year, month and day
	Year = c;
	Month = e;
	Day = f;
}
