---
layout:         page
title:          "JS Date日期助手函数"
date:           2020-07-01 19:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
tags:
    - blog
---

时间参数 **sdate** 可为时间格式字符串或者整型时间戳，例如：`'2020-07-01 12:12:12'`，`1656648732000` 。

以下 
```
>   表示输入
<·  表示输出
```

### 初始化
```javascript
var initDate = function(sdate)
{
	if(
		sdate == '' 
		|| typeof (sdate) == 'undefined'
	)
		return new Date();
	else
		return new Date(sdate);
}
```


### 获取年份
```javascript
var getYear = function(sdate)
{
	return initDate(sdate).getFullYear();
}
```

```
>  getYear('2020-07-01');
<· 2020
```

### 获取月份
```javascript
var getMonth = function(sdate)
{
	return initDate(sdate).getMonth() + 1;
}
```

```
>  getMonth('2020-07-01');
<· 7
```

### 获取日期
```javascript
var getDate = function(sdate)
{
	return initDate(sdate).getDate();
}
```

```
>  getDate('2020-07-01');
<· 1
```

### 获取年月日
```javascript
var getDates = function(sdate)
{
	let curdate = initDate(sdate);
	let month = curdate.getMonth() + 1;
	let date = curdate.getDate();
	month = month < 10?'0'+month:month;
	date = date < 10?'0'+date:date;
	return curdate.getFullYear()+'-'+month+'-'+date;
}
```

```
>  getDates('2020-07-01');
<· "2020-07-01"
```

### 获取小时
```javascript
var getHours = function(sdate)
{
	return initDate(sdate).getHours();
}
```

```
>  getHours('2020-07-01 12:12:12');
<· 12
```

### 获取分钟
```javascript
var getMinutes = function(sdate)
{
	return initDate(sdate).getMinutes();
}
```

```
>  getMinutes('2020-07-01 12:12:12');
<· 12
```

### 获取秒钟
```javascript
var getSeconds = function(sdate)
{
	return initDate(sdate).getSeconds();
}
```

```
>  getSeconds('2020-07-01 12:12:12');
<· 12
```

### 获取毫秒
```javascript
var getMilliseconds = function(sdate)
{
	return initDate(sdate).getMilliseconds();
}
```

```
>  getMilliseconds('2020-07-01 12:12:12');
<· 0
```

### 获取时分秒
```javascript
var getTime = function(sdate)
{
	let curdate = initDate(sdate);
	let hours = curdate.getHours();
	let minutes = curdate.getMinutes();
	let seconds = curdate.getSeconds();
	hours = hours < 10?'0'+hours:hours;
	minutes = minutes < 10?'0'+minutes:minutes;
	seconds = seconds < 10?'0'+seconds:seconds;
	return hours+':'+minutes+':'+seconds;
}
```

```
>  getTime('2020-07-01 12:12:12');
<· "12:12:12"
```

### 获取年月日时分秒
```javascript
var getDateTime = function(sdate)
{
	let curdate = initDate(sdate);
	let month = curdate.getMonth() + 1;
	let date = curdate.getDate();
	let hours = curdate.getHours();
	let minutes = curdate.getMinutes();
	let seconds = curdate.getSeconds();
	month = month < 10?'0'+month:month;
	date = date < 10?'0'+date:date;
	hours = hours < 10?'0'+hours:hours;
	minutes = minutes < 10?'0'+minutes:minutes;
	seconds = seconds < 10?'0'+seconds:seconds;
	return curdate.getFullYear()+'-'+month+'-'+date+' '+hours+':'+minutes+':'+seconds;
}
```

```
>  getDateTime('2020-07-01 12:12:12');
<· "2020-07-01 12:12:12"
>  getDateTime(1593576732000);
<· "2020-07-01 12:12:12"
```

### 获取两个日期相差的天数
```javascript
var getDiffDate = function(sdate,edate)
{
	return (getTimeStamp(getDates(edate)) - getTimeStamp(getDates(sdate)))/(24*60*60*1000);
}
```

```
>  getDiffDate('2020-06-01','2020-07-01');
<· 30
```

### 获取星期
```javascript
var getDay = function(sdate)
{
	let day = initDate(sdate).getDay();
	if(day == 0) return 7;
	else return day;
}
```

```
>  getDay('2020-07-01 12:12:12');
<· 3
```

### 获取周序号
```javascript
// 第几周 week of year
var getWof = function(sdate,start)
{
	if(start < 1 || start > 7) return false;
	let end = start - 1;	//	一周的最后一天是星期几
	if(end == 0) end = 7;
	let firstDate = getDates(getYear(sdate)+'');
	let firstDay = getDay(firstDate);	//	当年第一天是星期几
	if(end < firstDay) end += 7;
	let firstWeekDays = end - firstDay + 1;	//	当年的第一周天数
	let date = getDates(sdate);
	let diffDate = getDiffDate(firstDate,date) + 1;
	if(diffDate <= firstWeekDays) return 1;
	let subDate = diffDate - firstWeekDays;
	let weeks = Math.floor(subDate/7);
	if(subDate%7) weeks++;
	return weeks+1;
}
```

```
>  getWof('2020-07-01 12:12:12',6);
<· 27
```

### 获取时间戳
```javascript
var getTimeStamp = function(sdate)
{
	return initDate(sdate).getTime();
}
```

```
>  getTimeStamp('2020-07-01 12:12:12');
<· 1593576732000
```

### 加/减 年份
```javascript
var setYear = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setFullYear(curdate.getFullYear() + nums);
}
```

```
>  setYear('2020-07-01 12:12:12',2);
<· 1656648732000
>  getDateTime(1656648732000);
<· "2022-07-01 12:12:12"
```

### 加/减 月份
```javascript
var setMonth = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setMonth(curdate.getMonth() + nums);
}
```

```
>  setMonth('2020-07-01 12:12:12',2);
<· 1598933532000
>  getDateTime(1598933532000);
<· "2020-09-01 12:12:12"
```

### 加/减 日期
```javascript
var setDate = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setDate(curdate.getDate() + nums);
}
```

```
>  setDate('2020-07-01 12:12:12',2);
<· 1593749532000
>  getDateTime(1593749532000);
<· "2020-07-03 12:12:12"
```

### 加/减 小时
```javascript
var setHours = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setHours(curdate.getHours() + nums);
}
```

```
>  setHours('2020-07-01 12:12:12',2);
<· 1593583932000
>  getDateTime(1593583932000);
<· "2020-07-01 14:12:12"
```

### 加/减 分钟
```javascript
var setMinutes = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setMinutes(curdate.getMinutes() + nums);
}
```

```
>  setMinutes('2020-07-01 12:12:12',2);
<· 1593576852000
>  getDateTime(1593576852000);
<· "2020-07-01 12:14:12"
```

### 加/减 秒钟
```javascript
var setSeconds = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setSeconds(curdate.getSeconds() + nums);
}
```

```
>  setSeconds('2020-07-01 12:12:12',2);
<· 1593576734000
>  getDateTime(1593576734000);
<· "2020-07-01 12:12:14"
```

### JS代码
```javascript
//  date-helper.js

// 实例化，参数为时间格式字符串或者整型时间戳
var initDate = function(sdate)
{
	if(
		sdate == '' 
		|| typeof (sdate) == 'undefined'
	)
		return new Date();
	else
		return new Date(sdate);
}
//	年
var getYear = function(sdate)
{
	return initDate(sdate).getFullYear();
}	
//	月
var getMonth = function(sdate)
{
	return initDate(sdate).getMonth() + 1;
}
//	日
var getDate = function(sdate)
{
	return initDate(sdate).getDate();
}
//	日期
var getDates = function(sdate)
{
	let curdate = initDate(sdate);
	let month = curdate.getMonth() + 1;
	let date = curdate.getDate();
	month = month < 10?'0'+month:month;
	date = date < 10?'0'+date:date;
	return curdate.getFullYear()+'-'+month+'-'+date;
}
//	时
var getHours = function(sdate)
{
	return initDate(sdate).getHours();
}
//	分
var getMinutes = function(sdate)
{
	return initDate(sdate).getMinutes();
}
//	秒
var getSeconds = function(sdate)
{
	return initDate(sdate).getSeconds();
}
//	毫秒
var getMilliseconds = function(sdate)
{
	return initDate(sdate).getMilliseconds();
}
//	时间
var getTime = function(sdate)
{
	let curdate = initDate(sdate);
	let hours = curdate.getHours();
	let minutes = curdate.getMinutes();
	let seconds = curdate.getSeconds();
	hours = hours < 10?'0'+hours:hours;
	minutes = minutes < 10?'0'+minutes:minutes;
	seconds = seconds < 10?'0'+seconds:seconds;
	return hours+':'+minutes+':'+seconds;
}
//	日期 时间
var getDateTime = function(sdate)
{
	let curdate = initDate(sdate);
	let month = curdate.getMonth() + 1;
	let date = curdate.getDate();
	let hours = curdate.getHours();
	let minutes = curdate.getMinutes();
	let seconds = curdate.getSeconds();
	month = month < 10?'0'+month:month;
	date = date < 10?'0'+date:date;
	hours = hours < 10?'0'+hours:hours;
	minutes = minutes < 10?'0'+minutes:minutes;
	seconds = seconds < 10?'0'+seconds:seconds;
	return curdate.getFullYear()+'-'+month+'-'+date+' '+hours+':'+minutes+':'+seconds;
}
// 两个日期相差的天数
var getDiffDate = function(sdate,edate)
{
	return (getTimeStamp(getDates(edate)) - getTimeStamp(getDates(sdate)))/(24*60*60*1000);
}
//	星期
var getDay = function(sdate)
{
	let day = initDate(sdate).getDay();
	if(day == 0) return 7;
	else return day;
}
// 第几周 week of year
var getWof = function(sdate,start)
{
	if(start < 1 || start > 7) return false;
	let end = start - 1;	//	一周的最后一天是星期几
	if(end == 0) end = 7;
	let firstDate = getDates(getYear(sdate)+'');
	let firstDay = getDay(firstDate);	//	当年第一天是星期几
	if(end < firstDay) end += 7;
	let firstWeekDays = end - firstDay + 1;	//	当年的第一周天数
	let date = getDates(sdate);
	let diffDate = getDiffDate(firstDate,date) + 1;
	if(diffDate <= firstWeekDays) return 1;
	let subDate = diffDate - firstWeekDays;
	let weeks = Math.floor(subDate/7);
	if(subDate%7) weeks++;
	return weeks+1;
}
// 时间戳（毫秒）
var getTimeStamp = function(sdate)
{
	return initDate(sdate).getTime();
}
//	加/减 年份
var setYear = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setFullYear(curdate.getFullYear() + nums);
}
//	加/减 月份
var setMonth = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setMonth(curdate.getMonth() + nums);
}
//	加/减 日期
var setDate = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setDate(curdate.getDate() + nums);
}
//	加/减 小时
var setHours = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setHours(curdate.getHours() + nums);
}

//	加/减 分钟
var setMinutes = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setMinutes(curdate.getMinutes() + nums);
}

//	加/减 秒钟
var setSeconds = function(sdate,nums)
{
	let curdate = initDate(sdate);
	return curdate.setSeconds(curdate.getSeconds() + nums);
}
```