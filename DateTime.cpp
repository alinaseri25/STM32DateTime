#include "DateTime.h"


DateTime::DateTime(uint16_t _year,uint8_t _month,uint8_t _day,uint8_t _hour,uint8_t _min,uint8_t _sec)
{
	setDateTime(_year,_month,_day,_hour,_min,_sec);
	this->LocalOffset = 0;
	this->DayofWeek = 1;
}

#ifdef HAL_RTC_MODULE_ENABLED
void DateTime::setCurrentDateTime(RTC_HandleTypeDef *_hrtc)
{
	RTC_DateTypeDef _date;
	RTC_TimeTypeDef _time;
	
	_date.Year = this->Year - 2000;
	_date.Month = this->Month;
	_date.Date = this->Day;
	HAL_RTC_SetDate(_hrtc,&_date,RTC_FORMAT_BIN);
	
	_time.Hours = this->Hour;
	_time.Minutes = this->Minute;
	_time.Seconds = this->Second;
	HAL_RTC_SetTime(_hrtc,&_time,RTC_FORMAT_BIN);
}
#endif

#ifdef HAL_RTC_MODULE_ENABLED
void DateTime::getCurrentDateTime(RTC_HandleTypeDef *_hrtc)
{
	RTC_DateTypeDef _date;
	RTC_TimeTypeDef _time;
	
	HAL_RTC_GetDate(_hrtc,&_date,RTC_FORMAT_BIN);
	
	HAL_Delay(1);
	HAL_RTC_GetTime(_hrtc,&_time,RTC_FORMAT_BIN);
	
	setDayOfWeek(_date.WeekDay);
	setDateTime(_date.Year + 2000,_date.Month,_date.Date,_time.Hours,_time.Minutes,_time.Seconds);
}
#endif

void DateTime::setDateTime(uint16_t _year,uint8_t _month,uint8_t _day,uint8_t _hour,uint8_t _min,uint8_t _sec)
{
	if(_sec >= 60) _sec = 0;
	this->Second = _sec;
	if(_min >= 60) _min = 0;
	this->Minute = _min;
	if(_hour >= 24) _hour = 0;
	this->Hour = _hour;
	
	this->Year = _year;
	if(_month > 12 || _month < 1) _month = 1;
	this->Month = _month;
	if(_day > 31 || _day < 1) _day = 1;
	this->Day = _day;
	
	DateTimeToUnix();
}

void DateTime::setDate(uint16_t _year,uint8_t _month,uint8_t _day)
{
	this->Year = _year;
	this->Month = _month;
	this->Day = _day;
	
	DateTimeToUnix();
}

void DateTime::setTime(uint8_t _hour,uint8_t _min,uint8_t _sec)
{
	this->Hour = _hour;
	this->Minute = _min;
	this->Second = _sec;
	
	DateTimeToUnix();
}

void DateTime::setUnixTime(uint64_t _UnixtTime,bool _IsUTCTime)
{
	if(_IsUTCTime)
	{
		_UnixtTime += LocalOffset;
	}
	this->UnixDateTime = _UnixtTime;
	UnixToDateTime();
}

uint16_t DateTime::getYear()
{
	return this->Year;
}

int8_t DateTime::getYearFrom2000()
{
	return this->Year - 2000;
}

uint8_t DateTime::getMonth()
{
	return this->Month;
}

uint8_t DateTime::getDay()
{
	return this->Day;
}

uint8_t DateTime::getHour()
{
	return this->Hour;
}

uint8_t DateTime::getMinute()
{
	return this->Minute;
}

uint8_t DateTime::getSecond()
{
	return this->Second;
}

void DateTime::setYear(uint16_t _year)
{
	this->Year = _year;
	
	DateTimeToUnix();
}

void DateTime::setMonth(uint8_t _month)
{
	if(_month > 12 || _month < 1) _month = 1;
	this->Month = _month;
	
	DateTimeToUnix();
}

void DateTime::setDay(uint8_t _day)
{
	if(_day > 31 || _day < 1) _day = 1;
	this->Day = _day;
	
	DateTimeToUnix();
}

void DateTime::setHour(uint8_t _hour)
{
	if(_hour >= 24) _hour = 0;
	this->Hour = _hour;
	
	DateTimeToUnix();
}

void DateTime::setMinute(uint8_t _min)
{
	if(_min >= 60) _min = 0;
	this->Minute = _min;
	
	DateTimeToUnix();
}

void DateTime::setSecond(uint8_t _sec)
{
	if(_sec >= 60) _sec = 0;
	this->Second = _sec;
	
	DateTimeToUnix();
}

void DateTime::setDayOfWeek(uint8_t _dow)
{
  if(_dow > 6) _dow = 0;
	this->DayofWeek = _dow;
}

uint8_t DateTime::getDayOfWeek()
{
	return this->DayofWeek;
}

const char *DateTime::getDayOfWeekStr(StringDyOfWeekSize _SDOWS)
{
	switch(this->DayofWeek)
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

uint64_t DateTime::getUnixTime(bool _IsUTCTime)
{
	uint64_t TempTime;
	TempTime = this->UnixDateTime;
	if(_IsUTCTime)
	{
		TempTime -= this->LocalOffset;
	}
	return TempTime;
}

void DateTime::setLocalTime(int32_t _LocalOffset)
{
	this->LocalOffset = _LocalOffset;
}

int32_t DateTime::getLocalTime(void)
{
	return this->LocalOffset;
}

void DateTime::addSecond(uint16_t _sec)
{
	uint16_t temp = this->Second + _sec;
	addMinute(temp/60);
	this->Second = temp % 60;
	
	DateTimeToUnix();
}

void DateTime::addMinute(uint16_t _min)
{
	uint16_t temp = this->Minute + _min;
	addHour(temp/60);
	this->Minute = temp % 60;
	
	DateTimeToUnix();
}

void DateTime::addHour(uint16_t _hour)
{
	uint16_t temp = this->Hour + _hour;
	addDay(temp/24);
	this->Hour = temp % 24;
	
	DateTimeToUnix();
}

void DateTime::addDay(uint16_t _day)
{
	uint16_t temp = this->Day + _day;
	while (temp > milmonth[(this->Month - 1)]) {
			temp -= milmonth[(this->Month - 1)];
			addMonth(1);
	}
	this->Day = temp;
	
	DateTimeToUnix();
}

void DateTime::addMonth(uint16_t _month)
{
	uint16_t temp = this->Month + _month;
	addYear(temp/12);
	this->Month = temp % 12;
	
	DateTimeToUnix();
}

void DateTime::addYear(uint16_t _year)
{
	this->Year += _year;
	
	DateTimeToUnix();
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
	
	this->LocalOffset = _dt.getLocalTime();
	
	this->DateTimeToUnix();
	
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
	
	if(this->LocalOffset != _dt.getLocalTime())
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
	
	if(this->LocalOffset != _dt.getLocalTime())
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

void DateTime::setSecInDay(void)
{
	SecsInDay = this->Hour * 3600;
	SecsInDay += (this->Minute * 60);
	SecsInDay += this->Second;
}

uint32_t DateTime::getSecsInDay(void)
{
	return this->SecsInDay;
}

void DateTime::DateTimeToUnix(bool IsUnixTime)
{
	uint16_t y;
	uint16_t m;
	uint16_t d;

	//Year
	y = this->Year;
	//Month of year
	m = this->Month;
	//Day of month
	d = this->Day;

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
	if(IsUnixTime)
	{
		//Unix time starts on January 1st, 1970
		UnixDateTime -= 719561;
	}
	else
	{
		//Unix time starts on January 1st, 1900
		UnixDateTime -= 693994;
	}
	//Convert days to seconds
	UnixDateTime *= 86400;
	//Add hours, minutes and seconds
	UnixDateTime += (3600 * Hour) + (60 * Minute) + Second;
	
	setSecInDay();
}

void DateTime::UnixToDateTime(bool IsUnixTime)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;

	//Negative Unix time values are not supported
	if(this->UnixDateTime < 1)
		 this->UnixDateTime = 0;

	//Retrieve hours, minutes and seconds
	this->Second = this->UnixDateTime % 60;
	this->UnixDateTime /= 60;
	this->Minute = this->UnixDateTime % 60;
	this->UnixDateTime /= 60;
	this->Hour = this->UnixDateTime % 24;
	this->UnixDateTime /= 24;

	//Convert Unix time to date
	a = (uint32_t) ((4 * this->UnixDateTime + 102032) / 146097 + 15);
	b = (uint32_t) (this->UnixDateTime + 2442113 + a - (a / 4));
	c = (20 * b - 2442) / 7305;
	d = b - 365 * c - (c / 4);
	e = d * 1000 / 30601;
	f = d - e * 30 - e * 601 / 1000;

	//January and February are counted as months 13 and 14 of the previous year
	uint32_t TimeToMinus;
	if(IsUnixTime)
	{
		//Unix time starts on January 1st, 1970
		TimeToMinus = 4716;
	}
	else
	{
		//Unix time starts on January 1st, 1900
		TimeToMinus = 4786;
	}
	if(e <= 13)
	{
		 c -= TimeToMinus;
		 e -= 1;
	}
	else
	{
		 c -= (TimeToMinus - 1);
		 e -= 13;
	}

	//Retrieve year, month and day
	this->Year = c;
	this->Month = e;
	this->Day = f;
	
	setSecInDay();
}
