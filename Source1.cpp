#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<direct.h>
#include<cstdlib>
#include<filesystem>

using namespace std;

class Person;
class Employee;
class Director;
class Supervisor;
class Guard;

void getInputDate(int& d, int& m, int& y) {
	cout << "Please enter date (i.e. dd): ";
	do {
		do {
			cin >> d;
			if (cin.fail())
				cout << "Invalid input!\nEnter Again: ";
		} while (cin.fail());
		if (d < 1 || d > 31)
			cout << "Invalid date!\nEnter Again: ";
	} while (d < 1 || d > 31);
	cout << "Please enter month (i.e. mm): ";
	do {
		do {
			cin >> m;
			if (cin.fail())
				cout << "Invalid input!\nEnter Again: ";
		} while (cin.fail());
		if (m < 1 || m > 12)
			cout << "Invalid month!\nEnter Again: ";
	} while (m < 1 || m > 12);
	cout << "Please enter year (i.e. yyyy): ";
	do {
		do {
			cin >> y;
			if (cin.fail())
				cout << "Invalid input!\nEnter Again: ";
		} while (cin.fail());
		if (y < 1)
			cout << "Invalid year!\nEnter Again: ";
	} while (y < 1);
}

int dayofweek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
	//0->Sunday, 1->Monday, 2->Tuesday, 3->Wednesday, 4->Thursday, 5->Friday, 6->Sunday
}

bool checkLeapYear(int y) {
	if (y % 400 == 0) {
		return true;
	}

	// not a leap year if divisible by 100
	// but not divisible by 400
	else if (y % 100 == 0) {
		return false;
	}

	// leap year if not divisible by 100
	// but divisible by 4
	else if (y % 4 == 0) {
		return true;
	}

	// all other years are not leap years
	else {
		return false;
	}
}

int daysinmonth(int m, int y) {
	//Number of days in January, February, March, April, May, June, July, August, September, October, November, December respectively!
	static int arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	//For checking leap year
	if (m == 2 && checkLeapYear(y)) //If true return 28 + 1 = 29 (Days in February in leap year)
		return arr[m - 1] + 1;
	else
		return arr[m - 1];
}

class Date {
private:
	int date;
	int month;
	int year;
public:
	friend Date backToDate(string date);
	Date() = default;
	Date(int date, int month, int year)
	{
		this->date = date;
		this->month = month;
		this->year = year;
	}
	int getDate() { return date; }
	int getMonth() { return month; }
	int getYear() { return year; }
	void setDate(int d, int m, int y) {
		this->date = d;
		this->month = m;
		this->year = y;
	}
	string toDate() { return to_string(date) + "-" + to_string(month) + "-" + to_string(year); }
	int toMonths() { return (year * 12) + month; }
	int toDays() { return (year * 360) + (month * 30) + date; }
	void Display() { cout << date << " / " << month << " / " << year; }
	bool operator == (const Date& d) {
		if ((this->date == d.date) && (this->month = d.month) && (this->year == d.year))
			return true;
		else
			return false;
	}
	bool operator <= (const Date& d) {
		if (this->year <= d.year) {
			if (this->year < d.year) {
				return true;
			}
			else {
				if (this->month <= d.month) {
					if (this->month < d.month) {
						return true;
					}
					else {
						if (this->date <= d.date) {
							return true;
						}
						else
							return false;
					}
				}
				else
					return false;
			}
		}
		else
			return false;
	}
	bool operator >= (const Date& d) {
		if (this->year >= d.year) {
			if (this->year > d.year) {
				return true;
			}
			else {
				if (this->month >= d.month) {
					if (this->month > d.month) {
						return true;
					}
					else {
						if (this->date >= d.date)
							return true;
						else
							return false;
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	void operator++(int) {
		this->date += 1;
		if (this->date > daysinmonth(this->month, this->year)) {
			this->date = 1;
			this->month += 1;
			if (this->month > 12) {
				this->month = 1;
				this->year += 1;
			}
		}
	}
};

Date backToDate(string date)
{
	string d, m, y;
	int i = 0;
	while (date[i] != '-') {
		d += date[i];
		i++;
	}
	i++;
	while (date[i] != '-') {
		m += date[i];
		i++;
	}
	i++;
	while (i < date.length()) {
		y += date[i];
		i++;
	}
	Date temp(stoi(d), stoi(m), stoi(y));
	return temp;
}

int getWorkingDays(Date d1, Date d2) {
	//To include the both start date and end date
	int count = (d2.toDays() - d1.toDays()) + 1;
	int workindays = 0, weekday;
	for (int i = 0; i < count; i++) {
		weekday = dayofweek(d1.getDate(), d1.getMonth(), d1.getYear());
		//Check if day is not Saturday or Sunday (i.e. non-working day)
		if (weekday != 0 && weekday != 6) {
			workindays++;
		}
		d1++;
	}
	return workindays;
}

class Time {
private:
	int hour;
	int min;
public:
	friend Time backToTime(string);
	Time() = default;
	Time(int hour, int min)
	{
		this->hour = hour;
		this->min = min;
	}
	void setTime(const Time& t) {
		this->hour = t.hour;
		this->min = t.min;
	}
	string toTime()
	{
		return to_string(hour) + ":" + to_string(min);
	}
	bool operator <= (const Time& t) {
		if (this->hour <= t.hour) {
			if (this->min <= t.min) {
				return true;
			}
		}
		return false;
	}
	bool operator >= (const Time& t) {
		if (this->hour >= t.hour) {
			if (this->min >= t.min) {
				return true;
			}
		}
		return false;
	}
	int operator-(const Time& t)
	{
		float m, h;
		//if mins of exit time is less than mins of entry time
		if (this->min < t.min) {
			m = (this->min + 60) - min;
			h = (this->hour - 1) - hour;
		}
		//if mins of exit time is greater than or equal to mins of entry time
		else {
			m = this->min - min;
			h = this->hour - hour;
		}
		//Convert mins to hour
		h += (m / 60);
		//Convert to int and round off
		int hours = static_cast<int>(round(h));
		return hours;
	}
};

Time backToTime(string time) {
	string h, m;
	int i = 0;
	while (time[i] != ':') {
		h += time[i];
		i++;
	}
	i++;
	while (i < time.length()) {
		m += time[i];
		i++;
	}
	Time temp(stoi(h), stoi(m));
	return temp;
}

void getInputTime(int& hr, int& min) {
	cout << "Please enter hours (i.e. hh): ";
	do {
		do {
			cin >> hr;
			if (cin.fail())
				cout << "Invalid input!\nEnter Again: ";
		} while (cin.fail());
		if (hr < 0 || hr > 23)
			cout << "Invalid hour!\nEnter Again: ";
	} while (hr < 0 || hr > 23);
	cout << "Please enter minutes (i.e. mm): ";
	do {
		do {
			cin >> min;
			if (cin.fail())
				cout << "Invalid input!\nEnter Again: ";
		} while (cin.fail());
		if (min < 0 || min > 59)
			cout << "Invalid minute!\nEnter Again: ";
	} while (min < 0 || min > 59);
}

class IViewAttendance {
public:
	virtual void ViewAttendance(int, string) = 0;
};

class IMarkAttendance {
public:
	virtual bool MarkEntryTime(int, string, Date, Time) = 0;
	virtual bool MarkExitTime(int, string, Date, Time) = 0;
};

class IPendingLeaves {
public:
	virtual int getID() = 0;
	virtual int getEmployeeID() = 0;
	virtual string getEmployeeName() = 0;
	virtual string getApplyDate() = 0;
	virtual string getLeaveStartDate() = 0;
	virtual string getLeaveEndDate() = 0;
	virtual string getLeaveType() = 0;
	virtual string getReason() = 0;
	virtual string getStatus() = 0;
	virtual void setStatus(string) = 0;
};

class IApplyLeave {
public:
	virtual void DisplayLeave(IPendingLeaves*) = 0;
};

class IReviewLeaveDirector {
public:
	virtual void ApproveLeaveasDirector(IPendingLeaves*&, Date&) = 0;
	virtual void RejectLeaveasDirector(IPendingLeaves*&, Date&) = 0;
	virtual void DisplayLeave(IPendingLeaves*) = 0;
};

class IReviewLeaveSupervisor {
public:
	virtual void ApproveLeaveasSupervisor(IPendingLeaves*&, Date&) = 0;
	virtual void RejectLeaveasSupervisor(IPendingLeaves*&, Date&) = 0;
	virtual void DisplayLeave(IPendingLeaves*) = 0;
};

class IHandleEmployeeSupervisor {
public:
	virtual void AddEmployee(int, string, int, int, vector<Employee*>&) = 0;
	virtual void DisplayEmployees(vector<Employee*>) = 0;
};

class IHandleEmployeeDirector {
public:
	virtual void AddEmployee(int, string, int, int, vector<Employee*>&) = 0;
	virtual void RemoveEmployee(int, vector<Employee*>&) = 0;
	virtual void DisplayEmployees(vector<Employee*>) = 0;
};

class IGenerateReports {
public:
	virtual void AttendanceBelowPercenatge(vector<Employee*>) = 0;
	virtual void LeaveDetailsForEmployee(vector<Employee*>) = 0;
	virtual void AttendanceDetailsForEmployee(vector<Employee*>) = 0;
};

class LeaveApplication : public IPendingLeaves {
private:
	int LeaveID;
	int EmployeeID;
	string* EmployeeName;
	Date ApplyDate;
	Date LeaveStartDate;
	Date LeaveEndDate;
	string* LeaveType;
	string* Reason;
	string* Status;
public:
	LeaveApplication() = default;
	//Overload Constructor
	LeaveApplication(int LeaveID, int EmployeeID, string EmployeeName, Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) {
		this->LeaveID = LeaveID;
		this->EmployeeID = EmployeeID;
		this->EmployeeName = new string(EmployeeName);
		this->ApplyDate = ApplyDate;
		this->LeaveStartDate = LeaveStartDate;
		this->LeaveEndDate = LeaveEndDate;
		this->LeaveType = new string(LeaveType);
		this->Reason = new string(Reason);
		this->Status = new string(Status);
	}

	//Getters
	int getID() override { return LeaveID; }
	int getEmployeeID() override { return EmployeeID; }
	string getEmployeeName() override { return *EmployeeName; }
	string getApplyDate() override { return ApplyDate.toDate(); }
	string getLeaveStartDate() override { return LeaveStartDate.toDate(); }
	string getLeaveEndDate() override { return LeaveEndDate.toDate(); }
	string getLeaveType() override { return *LeaveType; }
	string getReason() override { return *Reason; }
	string getStatus() override { return *Status; }

	//Setter
	void setStatus(string newStatus) override { this->Status = new string(newStatus); }
};

class LeaveApprovedBySupervisor : virtual public LeaveApplication {
private:
	Date SupervisorReviewDate;
	bool SupervisorReviewStatus;
public:
	LeaveApprovedBySupervisor() = default;
	LeaveApprovedBySupervisor(bool SupervisorStatus, Date SupervisorDate, int LeaveID, int EmployeeID, string EmployeeName, \
		Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) : \
		LeaveApplication(LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status) {
		SupervisorReviewDate = SupervisorDate;
		SupervisorReviewStatus = SupervisorStatus;
	}
	bool getSupervisorReviewStatus() { return SupervisorReviewStatus; }
	string getSupervisorReviewDate() { return SupervisorReviewDate.toDate(); }
	void setSupervisorReviewStatus(bool status) { SupervisorReviewStatus = status; }
	void setSupervisorReviewDate(Date date) { SupervisorReviewDate = date; }
	~LeaveApprovedBySupervisor() = default;
};

class LeaveApprovedByDirector : virtual public LeaveApplication {
private:
	Date DirectorReviewDate;
	bool DirectorReviewStatus;
public:
	LeaveApprovedByDirector() = default;
	LeaveApprovedByDirector(bool DirectorStatus, Date DirectorDate, int LeaveID, int EmployeeID, string EmployeeName, \
		Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) : \
		LeaveApplication(LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status) {
		DirectorReviewDate = DirectorDate;
		DirectorReviewStatus = DirectorStatus;
	}
	bool getDirectorReviewStatus() { return DirectorReviewStatus; }
	string getDirectorReviewDate() { return DirectorReviewDate.toDate(); }
	void setDirectorReviewStatus(bool status) { DirectorReviewStatus = status; }
	void setDirectorReviewDate(Date date) { DirectorReviewDate = date; }
	~LeaveApprovedByDirector() = default;
};

class CasualLeave : public LeaveApprovedBySupervisor {
public:
	CasualLeave() = default;
	CasualLeave(bool SupervisorStatus, Date SupervisorDate, int LeaveID, int EmployeeID, string EmployeeName, \
		Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) : \
		LeaveApplication(LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status), \
		LeaveApprovedBySupervisor(SupervisorStatus, SupervisorDate, LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status) {}
	~CasualLeave() = default;
};

class EarnedLeave : public LeaveApprovedBySupervisor, public LeaveApprovedByDirector {
public:
	EarnedLeave() = default;
	EarnedLeave(bool SupervisorStatus, Date SupervisorDate, bool DirectorStatus, Date DirectorDate, int LeaveID, int EmployeeID, string EmployeeName, \
		Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) : \
		LeaveApplication(LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status), \
		LeaveApprovedBySupervisor(SupervisorStatus, SupervisorDate, LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status), \
		LeaveApprovedByDirector(DirectorStatus, DirectorDate, LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status) {}
	~EarnedLeave() = default;
};

class OfficialLeave : public LeaveApprovedBySupervisor {
public:
	OfficialLeave() = default;
	OfficialLeave(bool SupervisorStatus, Date SupervisorDate, int LeaveID, int EmployeeID, string EmployeeName, Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) : \
		LeaveApplication(LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status), \
		LeaveApprovedBySupervisor(SupervisorStatus, SupervisorDate, LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status) {}
	~OfficialLeave() = default;
};

class UnpaidLeave : public LeaveApprovedBySupervisor, public LeaveApprovedByDirector {
public:
	UnpaidLeave() = default;
	UnpaidLeave(bool SupervisorStatus, Date SupervisorDate, bool DirectorStatus, Date DirectorDate, int LeaveID, int EmployeeID, string EmployeeName, Date ApplyDate, Date LeaveStartDate, Date LeaveEndDate, string LeaveType, string Reason, string Status) : \
		LeaveApplication(LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status), \
		LeaveApprovedBySupervisor(SupervisorStatus, SupervisorDate, LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status), \
		LeaveApprovedByDirector(DirectorStatus, DirectorDate, LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status) {}
	~UnpaidLeave() = default;
};

class FileHandlerLeave {
public:
	void AddLeavetoFile(LeaveApplication& leave) {
		ofstream fw;
		fw.open("Leave.txt", ios::app);
		fw << leave.getID() << " " << leave.getEmployeeID() << " " << leave.getEmployeeName() << " " \
			<< leave.getApplyDate() << " " << leave.getLeaveStartDate() << " " << leave.getLeaveEndDate() << " " \
			<< leave.getLeaveType() << " " << leave.getReason() << " " << leave.getStatus() << endl;
		fw.close();
	}
	void UpdateNextUsableLeaveID() {
		ifstream fr;
		fr.open("Leave.txt");
		string prevID;
		fr >> prevID;
		int nextID = stoi(prevID) + 1;
		ofstream fw;
		fw.open("temp.txt");
		fw << nextID << endl;
		string LeaveID, EmployeeID, EmployeeName, ApplyDate, StartDate, EndDate, Type, Reason, Status, SupervisorReviewDate, DirectorReviewDate;
		while (!fr.eof()) {
			fr >> LeaveID;
			if (LeaveID != "") {
				fr >> EmployeeID >> EmployeeName >> ApplyDate >> StartDate >> EndDate >> Type >> Reason >> Status;
				fw << LeaveID << " " << EmployeeID << " " << EmployeeName << " " << ApplyDate << " " \
					<< StartDate << " " << EndDate << " " << Type << " " << Reason << " " << Status;
				if (Status == "Pending_for_Director_Approval" || Status == "Rejected_by_Supervisor" || \
					(Status == "Leave_Approved" && (Type == "Casual" || Type == "Official"))) {
					fr >> SupervisorReviewDate;
					fw << " " << SupervisorReviewDate;
				}
				else if (Status == "Rejected_by_Director" || (Status == "Leave_Approved" && (Type == "Earned" || Type == "Unpaid"))) {
					fr >> SupervisorReviewDate >> DirectorReviewDate;
					fw << " " << SupervisorReviewDate << " " << DirectorReviewDate;
				}
				fw << endl;
			}
			else
				break;
			LeaveID = "";
		}
		fr.close();
		fw.close();
		//Now delete previous file and rename the temp.txt
		if (remove("Leave.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Leave.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
	bool CheckDuplicateLeave(Date current, Date start, Date end, string LT, int EID) {
		ifstream fr_leave;
		fr_leave.open("Leave.txt");
		//First input is leave count
		string count;
		fr_leave >> count;
		string LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status, SupervisorReviewDate, DirectorReviewDate;
		//Read remaining data of leave from file
		while (!fr_leave.eof()) {
			fr_leave >> LeaveID;
			if (LeaveID != "") {
				fr_leave >> EmployeeID >> EmployeeName >> ApplyDate >> LeaveStartDate >> LeaveEndDate >> LeaveType >> Reason >> Status;
				if (Status == "Pending_for_Director_Approval" || Status == "Rejected_by_Supervisor" || \
					(Status == "Leave_Approved" && (LeaveType == "Casual" || LeaveType == "Official"))) {
					fr_leave >> SupervisorReviewDate;
				}
				else if (Status == "Rejected_by_Director" || (Status == "Leave_Approved" && (LeaveType == "Earned" || LeaveType == "Unpaid"))) {
					fr_leave >> SupervisorReviewDate >> DirectorReviewDate;
				}

				if (EID == stoi(EmployeeID)) {
					//If exact same leave is applied before
					if (backToDate(ApplyDate) == current && backToDate(LeaveStartDate) == start && backToDate(LeaveEndDate) == end && LeaveType == LT) {
						cout << "Leave has been already applied!\n";
						cout << "Leave's status is: " << Status << endl;
						return false;
					}
					//If an already applied leave intersects with the mentioned time period
					else if ((backToDate(LeaveStartDate) <= end && backToDate(LeaveEndDate) >= end) || (backToDate(LeaveStartDate) <= start && backToDate(LeaveEndDate) >= start)) {
						if (Status != "Rejected_by_Supervisor" || Status != "Rejected_by_Director") {
							//If type is same
							if (LeaveType == LT) {
								cout << "A same type of leave has been alreday applied during this phase!\n";
								return false;
							}
							//IF typpe is different
							else {
								cout << "A different type of leave has been alreday applied during this phase!\n";
								return false;
							}
						}
						else
							return true;
					}
				}
			}
			else
				break;
			LeaveID = "";
		}
		fr_leave.close();
		return true;
	}
	int getID() {
		ifstream fr_leave;
		fr_leave.open("Leave.txt");
		string NextUsableID;
		fr_leave >> NextUsableID;
		fr_leave.close();
		return stoi(NextUsableID);
	}
	void UpdateStatus(int ID, string newStatus, Date newDate) {
		ifstream fr;
		fr.open("Leave.txt");
		string count;
		fr >> count;
		ofstream fw;
		fw.open("temp.txt");
		fw << count << endl;
		string LeaveID, EmployeeID, EmployeeName, ApplyDate, StartDate, EndDate, Type, Reason, Status, SupervisorReviewDate = "", DirectorReviewDate = "";
		while (!fr.eof()) {
			fr >> LeaveID;
			if (LeaveID != "") {
				//Read other data members
				fr >> EmployeeID >> EmployeeName >> ApplyDate >> StartDate >> EndDate >> Type >> Reason >> Status;
				if (Status == "Pending_for_Director_Approval" || Status == "Rejected_by_Supervisor" || \
					(Status == "Leave_Approved" && (Type == "Casual" || Type == "Official"))) {
					fr >> SupervisorReviewDate;
				}
				else if (Status == "Rejected_by_Director" || (Status == "Leave_Approved" && (Type == "Earned" || Type == "Unpaid"))) {
					fr >> SupervisorReviewDate >> DirectorReviewDate;
				}

				if (stoi(LeaveID) != ID) {
					fw << LeaveID << " " << EmployeeID << " " << EmployeeName << " " << ApplyDate << " " \
						<< StartDate << " " << EndDate << " " << Type << " " << Reason << " " << Status;
					if (SupervisorReviewDate != "")
						fw << " " << SupervisorReviewDate;
					if (DirectorReviewDate != "")
						fw << " " << DirectorReviewDate;
				}
				else {
					fw << LeaveID << " " << EmployeeID << " " << EmployeeName << " " << ApplyDate << " " \
						<< StartDate << " " << EndDate << " " << Type << " " << Reason << " " << newStatus;
					if (Status == "Pending_for_Director_Approval")
						fw << " " << SupervisorReviewDate;
					fw << " " << newDate.toDate();
				}
				fw << endl;
			}
			else
				break;
			LeaveID = "", SupervisorReviewDate = "", DirectorReviewDate = "";
		}
		fr.close();
		fw.close();
		//Now delete previous file and rename the temp.txt
		if (remove("Leave.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Leave.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
	void RemoveLeavefromFile(int EID) {
		ifstream fr;
		fr.open("Leave.txt");
		string count;
		fr >> count;
		ofstream fw;
		fw.open("temp.txt");
		fw << count;
		string LeaveID, EmployeeID, EmployeeName, ApplyDate, StartDate, EndDate, Type, Reason, Status, SupervisorReviewDate, DirectorReviewDate;
		while (!fr.eof()) {
			fr >> LeaveID;
			if (LeaveID != "") {
				fr >> EmployeeID >> EmployeeName >> ApplyDate >> StartDate >> EndDate >> Type >> Reason >> Status;
				if (EID != stoi(EmployeeID))
					fw << LeaveID << " " << EmployeeID << " " << EmployeeName << " " << ApplyDate << " " \
					<< StartDate << " " << EndDate << " " << Type << " " << Reason << " " << Status;
				if (Status == "Pending_for_Director_Approval" || Status == "Rejected_by_Supervisor" || \
					(Status == "Leave_Approved" && (Type == "Casual" || Type == "Official"))) {
					fr >> SupervisorReviewDate;
					if (EID != stoi(EmployeeID))
						fw << " " << SupervisorReviewDate;
				}
				else if (Status == "Rejected_by_Director" || (Status == "Leave_Approved" && (Type == "Earned" || Type == "Unpaid"))) {
					fr >> SupervisorReviewDate >> DirectorReviewDate;
					if (EID != stoi(EmployeeID))
						fw << " " << SupervisorReviewDate << " " << DirectorReviewDate;
				}
				fw << endl;
			}
			else
				break;
			LeaveID = "";
		}
		fr.close();
		fw.close();
		//Now delete previous file and rename the temp.txt
		if (remove("Leave.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Leave.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
};

class FileHandlerEmployee {
public:
	void AddEmployeetoFile(int ID, string name, int ccount, int ecount) {
		ofstream fw;
		fw.open("Employee.txt", ios::app);
		fw << to_string(ID) << " " << name << " " << to_string(ccount) << " " << to_string(ecount) << "\n";
		fw.close();
		string empcount;
		ifstream fr;
		fr.open("Employee.txt");
		fr >> empcount;
		int new_empcount = stoi(empcount) + 1;
		fw.open("temp.txt");
		fw << to_string(new_empcount) << "\n";
		string id, c, e;
		for (int i = 0; i < new_empcount; i++) {
			fr >> id >> name >> c >> e;
			fw << id << " " << name << " " << c << " " << e << "\n";
		}
		fr.close();
		fw.close();

		if (remove("Employee.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Employee.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
	void UpdateCasualLeaveinFile(int EmployeeID, int newCasualCount) {
		ifstream fr;
		fr.open("Employee.txt");
		string empCount;
		fr >> empCount;
		ofstream fw;
		fw.open("temp.txt");
		fw << empCount << "\n";
		string ID, name, ccount, ecount;
		for (int i = 0; i < stoi(empCount); i++) {
			fr >> ID >> name >> ccount >> ecount;
			if (stoi(ID) != EmployeeID)
				fw << ID << " " << name << " " << ccount << " " << ecount << "\n";
			else
				fw << ID << " " << name << " " << to_string(newCasualCount) << " " << ecount << "\n";
		}
		fr.close();
		fw.close();

		if (remove("Employee.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Employee.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
	void UpdateEarnedLeaveinFile(int EmployeeID, int newEarnedCount) {
		ifstream fr;
		fr.open("Employee.txt");
		string empCount;
		fr >> empCount;
		ofstream fw;
		fw.open("temp.txt");
		fw << empCount << "\n";
		string ID, name, ccount, ecount;
		for (int i = 0; i < stoi(empCount); i++) {
			fr >> ID >> name >> ccount >> ecount;
			if (stoi(ID) != EmployeeID)
				fw << ID << " " << name << " " << ccount << " " << ecount << "\n";
			else
				fw << ID << " " << name << " " << ccount << " " << to_string(newEarnedCount) << "\n";
		}
		fr.close();
		fw.close();

		if (remove("Employee.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Employee.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
	void RemoveEmployeefromFile(int EmployeeID) {
		ifstream fr;
		fr.open("Employee.txt");
		string empCount;
		fr >> empCount;
		int new_count = stoi(empCount) - 1;
		ofstream fw;
		fw.open("temp.txt");
		fw << to_string(new_count) << endl;
		string ID, name, ccount, ecount;
		for (int i = 0; i < stoi(empCount); i++) {
			fr >> ID >> name >> ccount >> ecount;
			if (stoi(ID) != EmployeeID)
				fw << ID << " " << name << " " << ccount << " " << ecount << endl;
		}
		fr.close();
		fw.close();

		if (remove("Employee.txt") != 0)
			cout << "An error has occured while deleting the file!\n";
		if (rename("temp.txt", "Employee.txt") != 0)
			cout << "An error has occured while renaming the file!\n";
	}
	void CreateEmployeeDirectory(int ID, string Name) {
		string folder = "Employee\\" + to_string(ID) + "-" + Name;
		_mkdir(folder.c_str());
		string filePath = "Employee\\" + to_string(ID) + "-" + Name + "\\Attendance";
		_mkdir(filePath.c_str());
	}
	void RemoveEmployeeDirectory(int ID, string Name) {
		string folderPath = "Employee\\" + to_string(ID) + "-" + Name;
		string command = "rd /s /q \"" + folderPath + "\"";
		system(command.c_str());
	}
	void AddNotificationtoFile(int ID, string Name, string Notification) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Notifications.txt";
		ofstream fw(filePath, ios::app);
		fw << Notification << endl;
		fw.close();
	}
	void RemoveNotificationsFromFile(int ID, string Name) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Notifications.txt";
		ofstream fw(filePath);
		fw.clear();
		fw.close();
	}
};

class FileHandlerAttendance {
public:
	bool CheckDuplicateEntryTime(int ID, string Name, Date date) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear()) + "/" + to_string(date.getMonth()) + ".txt";
		ifstream file_r;
		file_r.open(filePath, ios::_Nocreate);
		if (file_r.is_open()) {
			string fileDate, entryTime, exitTime;
			while (!file_r.eof()) {
				file_r >> fileDate;
				if (fileDate != "") {
					file_r >> entryTime >> exitTime;
					if (fileDate == date.toDate()) {
						file_r.close();
						return false;
					}
				}
				else {
					file_r.close();
					return true;
				}
			}
		}
		return true;
	}
	bool CheckDuplicateExitTime(int ID, string Name, Date date) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear()) + "/" + to_string(date.getMonth()) + ".txt";
		ifstream file_r(filePath, ios::_Nocreate);
		if (file_r.is_open()) {
			string fileDate, entryTime, exitTime;
			while (!file_r.eof()) {
				file_r >> fileDate;
				if (fileDate != "") {
					file_r >> entryTime >> exitTime;
					if (fileDate == date.toDate() && exitTime != "00:00") {
						file_r.close();
						return false;
					}
					else if (fileDate == date.toDate() && exitTime == "00:00") {
						file_r.close();
						return true;
					}
				}
				else
					break;
				fileDate = "", entryTime = "", exitTime = "";
			}
			file_r.close();
		}
		return false;
	}
	void AddEntryTimetoFile(int ID, string Name, Date date, Time entryTime) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear());
		_mkdir(filePath.c_str());
		filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear()) + "/" + to_string(date.getMonth()) + ".txt";
		ofstream file_w;
		file_w.open(filePath, ios::app);
		string data = date.toDate() + " " + entryTime.toTime() + " 00:00";
		file_w << data << endl;
		file_w.close();
	}
	bool AddExitTimetoFile(int ID, string Name, Date date, Time exitTime) {
		Time t1;
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear()) + "/" + to_string(date.getMonth()) + ".txt";
		ifstream file_r(filePath, ios::_Nocreate);
		if (file_r.is_open()) {
			string tempfilePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear()) + "/temp.txt";
			ofstream file_w(tempfilePath);
			string fileDate, fileEntryTime, fileExitTime;
			while (!file_r.eof()) {
				file_r >> fileDate;
				if (fileDate != "") {
					file_r >> fileEntryTime >> fileExitTime;
					if (fileDate == date.toDate()) {
						t1.setTime(backToTime(fileEntryTime));
						if (!(exitTime <= backToTime(fileEntryTime)) && fileExitTime == "00:00") {
							file_w << fileDate << " " << fileEntryTime << " " << exitTime.toTime();
						}
						else {
							file_w << fileDate << " " << fileEntryTime << " " << fileExitTime;
						}
					}
					else {
						file_w << fileDate << " " << fileEntryTime << " " << fileExitTime;
					}
					file_w << endl;
				}
				else {
					break;
				}
				fileDate = "", fileEntryTime = "", fileExitTime = "";
			}
			file_r.close();
			file_w.close();
			//Now delete previous file and rename the temp.txt
			if (remove(filePath.c_str()) != 0)
				cout << "An error has occured while deleting the file!\n";
			if (rename(tempfilePath.c_str(), filePath.c_str()) != 0)
				cout << "An error has occured while renaming the file!\n";
			if (t1 >= exitTime) {
				cout << "Invalid Exit Time!\nAttendance not updated!\n";
				return false;
			}
			return true;
		}
		else {
			cout << "The record does not exists!\n";
			return false;
		}
	}
	void DisplayAttendanceforDate(int ID, string Name, Date date) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(date.getYear()) + "/" + to_string(date.getMonth()) + ".txt";
		ifstream file_r(filePath, ios::_Nocreate);
		if (file_r.is_open()) {
			string fileDate, fileEntryTime, fileExitTime;
			bool status = false;
			while (!(file_r.eof())) {
				file_r >> fileDate;
				if (fileDate != "") {
					if (fileDate == date.toDate()) {
						status = true;
						file_r >> fileEntryTime >> fileExitTime;
						cout << "Attendance for " << date.toDate() << " is as follows:-\n";
						cout << "Entry time: " << fileEntryTime << "\nExit time: " << fileExitTime << endl;
					}
					else {
						file_r >> fileEntryTime >> fileExitTime;
					}
				}
				else
					break;
				fileDate = "", fileEntryTime = "", fileExitTime = "";
			}
			if (!status)
				cout << "Attendance for " << date.toDate() << " does not exists!\n";
			file_r.close();
		}
		else {
			cout << "The attendance record for ";
			date.Display();
			cout << " does not exists!\n";
		}
	}
	void DisplayAttendanceforMonth(int ID, string Name, int month, int year) {
		string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(year) + "/" + to_string(month) + ".txt";
		ifstream file_r(filePath, ios::_Nocreate);
		if (file_r.is_open()) {
			string fileDate, fileEntryTime, fileExitTime;
			cout << "Attendance for " << month << " is as follows:-\n";
			bool Status = false;
			while (!(file_r.eof())) {
				file_r >> fileDate;
				if (fileDate != "") {
					Status = true;
					file_r >> fileEntryTime >> fileExitTime;
					cout << "Attendance for " << fileDate << endl;
					cout << "Entry time: " << fileEntryTime << "\nExit time: " << fileExitTime << endl;
				}
				else
					break;
				fileDate = "", fileEntryTime = "", fileExitTime = "";
			}
			if (!Status) {
				cout << "The attendance for " << month << " does not exists!\n";
			}
			file_r.close();
		}
		else {
			cout << "The attendance record for " << month << ", " << year << " does not exists!\n";
		}
	}
	int getAttendanceHours(int ID, string Name, Date d1, Date d2) {
		string filePath;
		ifstream file_r;
		string fileDate, fileEntryTime, fileExitTime;
		int workingHours = 0;
		while (d1 <= d2) {
			filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(d1.getYear()) + "/" + to_string(d1.getMonth()) + ".txt";
			file_r.open(filePath, ios::_Nocreate);
			if (file_r.is_open()) {
				while (!(file_r.eof())) {
					file_r >> fileDate;
					if (fileDate != "") {
						file_r >> fileEntryTime >> fileExitTime;
						if (backToDate(fileDate) == d1) {
							workingHours += backToTime(fileExitTime) - backToTime(fileEntryTime);
						}
					}
					else
						break;
					fileDate = "", fileEntryTime = "", fileExitTime = "";
				}
				file_r.close();
			}
			d1++;
		}
		return workingHours;
	}
	void MarkPresent(int ID, string Name, Date d1, Date d2) {
		string entryTime = "9:00", exitTime = "5:00";
		string filePath, data;
		ofstream file_w;

		while (d1 <= d2) {
			if (dayofweek(d1.getDate(), d1.getMonth(), d1.getYear()) != 6 && dayofweek(d1.getDate(), d1.getMonth(), d1.getYear()) != 0) {
				filePath = "Employee\\" + to_string(ID) + "-" + Name + "\\Attendance\\" + to_string(d1.getYear());
				_mkdir(filePath.c_str());
				filePath = "Employee/" + to_string(ID) + "-" + Name + "/Attendance/" + to_string(d1.getYear()) + "/" + to_string(d1.getMonth()) + ".txt";
				file_w.open(filePath, ios::app);
				data = d1.toDate() + " " + entryTime + " " + exitTime;
				file_w << data << endl;
				file_w.close();
			}
			d1++;
		}
	}
};

class LeaveService : public IApplyLeave, public IReviewLeaveDirector, public IReviewLeaveSupervisor {
public:
	void ApproveLeaveasSupervisor(IPendingLeaves*& leave, Date& SupervisorApprovalDate) override {
		if (leave->getStatus() == "Pending_for_Supervisor_Approval") {
			auto getsupervisorApproval = dynamic_cast<LeaveApprovedBySupervisor*>(leave);
			getsupervisorApproval->setSupervisorReviewStatus(true);
			getsupervisorApproval->setSupervisorReviewDate(SupervisorApprovalDate);
			FileHandlerLeave fhl;
			if (leave->getLeaveType() == "Casual" || leave->getLeaveType() == "Official") {
				fhl.UpdateStatus(leave->getID(), "Leave_Approved", SupervisorApprovalDate);
				leave->setStatus("Leave_Approved");
			}
			else {
				fhl.UpdateStatus(leave->getID(), "Pending_for_Director_Approval", SupervisorApprovalDate);
				leave->setStatus("Pending_for_Director_Approval");
			}
		}
	}
	void RejectLeaveasSupervisor(IPendingLeaves*& leave, Date& SupervisorRejectionDate) override {
		if (leave->getStatus() == "Pending_for_Supervisor_Approval") {
			auto getsupervisorRejection = dynamic_cast<LeaveApprovedBySupervisor*>(leave);
			getsupervisorRejection->setSupervisorReviewStatus(true);
			getsupervisorRejection->setSupervisorReviewDate(SupervisorRejectionDate);
			FileHandlerLeave fhl;
			fhl.UpdateStatus(leave->getID(), "Rejected_by_Supervisor", SupervisorRejectionDate);
			leave->setStatus("Rejected_by_Supervisor");
		}
	}
	void ApproveLeaveasDirector(IPendingLeaves*& leave, Date& DirectorApprovalDate) override {
		if (leave->getStatus() == "Pending_for_Director_Approval") {
			auto getDirectorApproval = dynamic_cast<LeaveApprovedByDirector*>(leave);
			getDirectorApproval->setDirectorReviewStatus(true);
			getDirectorApproval->setDirectorReviewDate(DirectorApprovalDate);
			FileHandlerLeave fhl;
			fhl.UpdateStatus(leave->getID(), "Leave_Approved", DirectorApprovalDate);
			leave->setStatus("Leave_Approved");
		}
	}
	void RejectLeaveasDirector(IPendingLeaves*& leave, Date& DirectorRejectionDate) override {
		if (leave->getStatus() == "Pending_for_Director_Approval") {
			auto getDirectorRejection = dynamic_cast<LeaveApprovedByDirector*>(leave);
			getDirectorRejection->setDirectorReviewStatus(true);
			getDirectorRejection->setDirectorReviewDate(DirectorRejectionDate);
			FileHandlerLeave fhl;
			fhl.UpdateStatus(leave->getID(), "Rejected_by_Director", DirectorRejectionDate);
			leave->setStatus("Rejected_by_Director");
		}
	}
	void DisplayLeave(IPendingLeaves* leave) override {
		cout << "Leave ID: " << leave->getID() << "\n";
		cout << "Employee ID: " << leave->getEmployeeID() << "\n";
		string name = leave->getEmployeeName();
		cout << "Employee Name: ";
		for (int i = 0; i < name.size(); i++) {
			if (name[i] != '_')
				cout << name[i];
			else
				cout << " ";
		}
		cout << "\n";
		cout << "Apply Date: " << leave->getApplyDate() << "\n";
		cout << "Leave Start Date: " << leave->getLeaveStartDate() << "\n";
		cout << "Leave End Date: " << leave->getLeaveEndDate() << "\n";
		string reason = leave->getReason();
		cout << "Reason for Leave: ";
		for (int i = 0; i < reason.size(); i++) {
			if (reason[i] != '_') {
				cout << reason[i];
			}
			else
				cout << " ";
		}
		cout << "\n";
		string status = leave->getStatus();
		cout << "Leave Status: ";
		for (int i = 0; i < status.size(); i++) {
			if (status[i] != '_')
				cout << status[i];
			else
				cout << " ";
		}
		cout << "\n";
		cout << "Leave Type: " << leave->getLeaveType() << "\n";
		auto leave_supervisor = dynamic_cast<LeaveApprovedBySupervisor*>(leave);
		if (leave_supervisor->getSupervisorReviewStatus())
			cout << "Supervisor Review Date: " << leave_supervisor->getSupervisorReviewDate() << "\n";
		if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
			auto leave_director = dynamic_cast<LeaveApprovedByDirector*>(leave);
			if (leave_director->getDirectorReviewStatus()) {
				cout << "Director Review Date: " << leave_director->getDirectorReviewDate() << "\n";
			}
		}
		cout << "--------------------------------------\n";
	}
};

class Attendance : public IViewAttendance, public IMarkAttendance {
public:
	Attendance() = default;
	bool MarkEntryTime(int ID, string Name, Date date, Time entryTime) override {
		FileHandlerAttendance fha;
		bool flag = fha.CheckDuplicateEntryTime(ID, Name, date);
		if (flag) {
			fha.AddEntryTimetoFile(ID, Name, date, entryTime);
			cout << "Entry time has been marked!\n";
			return true;
		}
		else {
			cout << "The attendance of ";
			date.Display();
			cout << " already exists!\n";
			return false;
		}
	}
	bool MarkExitTime(int ID, string Name, Date date, Time exitTime) override {
		FileHandlerAttendance fha;
		bool flag = fha.CheckDuplicateExitTime(ID, Name, date);
		if (flag) {
			if (fha.AddExitTimetoFile(ID, Name, date, exitTime)) {
				cout << "Exit time has been marked!\n";
				return true;
			}
			else
				return false;
		}
		else {
			cout << "The attendance for ";
			date.Display();
			cout << " already/does not exists!\n";
			return false;
		}
	}
	void ViewAttendance(int ID, string Name) override
	{
		FileHandlerAttendance fha;
		int input;
		cout << "1-Attendance of a specific date" << endl;
		cout << "2-Attendance of a specific month" << endl;
		do {
			cout << "Your choice: ";
			do {
				cin >> input;
				if (cin.fail())
					cout << "Wrong Input!\nEnter Again: ";
			} while (cin.fail());
			if (input < 1 || input > 2)
				cout << "Invalid Input!\nEnter Again: ";
		} while (input < 1 || input > 2);
		if (input == 1)
		{
			int date, month, year;
			cout << "Please enter date:- \n";
			getInputDate(date, month, year);
			Date tempDate(date, month, year);
			fha.DisplayAttendanceforDate(ID, Name, tempDate);
		}
		else if (input == 2)
		{
			int month, year;
			cout << "Please enter month: ";
			do {
				do {
					cin >> month;
					if (cin.fail())
						cout << "Wrong Input!\nEnter again: ";
				} while (cin.fail());
				if (month < 1 || month > 12)
					cout << "Invalid month!\nEnter again: ";
			} while (month < 1 || month > 12);
			cout << "Please enter year: ";
			do {
				do {
					cin >> year;
					if (cin.fail())
						cout << "Wrong Input!\nEnter again: ";
				} while (cin.fail());
				if (year < 1)
					cout << "Invalid year!\nEnter again: ";
			} while (month < 1);
			FileHandlerAttendance fha;
			fha.DisplayAttendanceforMonth(ID, Name, month, year);
		}
	}
};

class Person {
private:
	int ID;
	string* Name;
public:
	Person() = default;
	Person(int ID, string Name) {
		this->ID = ID;
		this->Name = new string(Name);
	}
	int getID() { return ID; }
	string getName() { return *Name; }
	~Person() = default;
};

void LoadNotifications(vector<string>& Notifications, int ID, string Name) {
	string filePath = "Employee/" + to_string(ID) + "-" + Name + "/Notifications.txt";
	ifstream fr(filePath);
	string FileNotification;
	while (getline(fr, FileNotification))
	{
		Notifications.push_back(FileNotification);
	}
	fr.close();
}

void LoadPendingLeaves(vector<IPendingLeaves*>& PendingLeaves, int ID) {
	ifstream fr_leave;
	fr_leave.open("Leave.txt");
	//First input is leave count
	string count;
	fr_leave >> count;
	string LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status, \
		SupervisorReviewDate = "00-00-0000", DirectorReviewDate = "00-00-0000";
	while (!fr_leave.eof()) {
		//Read remaining data of leave from file
		fr_leave >> LeaveID;
		if (LeaveID != "") {
			fr_leave >> EmployeeID >> EmployeeName >> ApplyDate >> LeaveStartDate >> LeaveEndDate >> LeaveType >> Reason >> Status;
			if (Status == "Pending_for_Director_Approval" || Status == "Rejected_by_Supervisor" || \
				(Status == "Leave_Approved" && (LeaveType == "Casual" || LeaveType == "Official"))) {
				fr_leave >> SupervisorReviewDate;
			}
			else if (Status == "Rejected_by_Director" || (Status == "Leave_Approved" && (LeaveType == "Earned" || LeaveType == "Unpaid"))) {
				fr_leave >> SupervisorReviewDate >> DirectorReviewDate;
			}
			if (ID == stoi(EmployeeID)) {
				if (LeaveType == "Casual") {
					PendingLeaves.push_back(new CasualLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), stoi(LeaveID), \
						stoi(EmployeeID), EmployeeName, backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
				else if (LeaveType == "Earned") {
					PendingLeaves.push_back(new EarnedLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), \
						(DirectorReviewDate != "00-00-0000"), backToDate(DirectorReviewDate), stoi(LeaveID), stoi(EmployeeID), EmployeeName, \
						backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
				else if (LeaveType == "Official") {
					PendingLeaves.push_back(new OfficialLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), stoi(LeaveID), \
						stoi(EmployeeID), EmployeeName, backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
				else if (LeaveType == "Unpaid") {
					PendingLeaves.push_back(new UnpaidLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), \
						(DirectorReviewDate != "00-00-0000"), backToDate(DirectorReviewDate), stoi(LeaveID), stoi(EmployeeID), EmployeeName, \
						backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
			}
		}
		else
			break;
		SupervisorReviewDate = "00-00-0000", DirectorReviewDate = "00-00-0000", LeaveID = "";
	}
	fr_leave.close();
}

class Employee : public Person {
private:
	vector<IPendingLeaves*> PendingLeaves;
	vector<string> Notifications;
	IApplyLeave* ial;
	IViewAttendance* iva;
	int CasualLeaveCount;
	int EarnedLeaveCount;
public:
	Employee() = default;

	Employee(int ID, string Name, int CasualCount, int EarnedCount) : Person(ID, Name) {
		CasualLeaveCount = CasualCount;
		EarnedLeaveCount = EarnedCount;
		ial = new LeaveService();
		iva = new Attendance();
		LoadPendingLeaves(PendingLeaves, ID);
		LoadNotifications(Notifications, ID, Name);
	}
	void UpdateLeaveStatusinEmployee(int LeaveID, string status, string ReviewDate) {
		for (int i = 0; i < PendingLeaves.size(); i++) {
			if (PendingLeaves[i]->getID() == LeaveID) {
				string LeaveType = PendingLeaves[i]->getLeaveType();
				if (status == "Pending_for_Director_Approval" || status == "Rejected_by_Supervisor" || (status == "Leave_Approved" && (LeaveType == "Casual" || LeaveType == "Official"))) {
					auto leave_supervisor = dynamic_cast<LeaveApprovedBySupervisor*>(PendingLeaves[i]);
					leave_supervisor->setSupervisorReviewStatus(true);
					leave_supervisor->setSupervisorReviewDate(backToDate(ReviewDate));
				}
				else if (status == "Rejected_by_Director" || (status == "Leave_Approved" && (LeaveType == "Earned" || LeaveType == "Unpaid"))) {
					auto leave_director = dynamic_cast<LeaveApprovedByDirector*>(PendingLeaves[i]);
					leave_director->setDirectorReviewStatus(true);
					leave_director->setDirectorReviewDate(backToDate(ReviewDate));
				}
				PendingLeaves[i]->setStatus(status);
			}
		}
	}

	int getCasualLeaveCount() { return CasualLeaveCount; }

	int getEarnedLeaveCount() { return EarnedLeaveCount; }

	bool CheckCasualLeave(int c) { if (CasualLeaveCount >= c) return true; else return false; }

	bool CheckEarnedLeave(int e) { if (EarnedLeaveCount >= e) return true; else return false; }

	void UpdateCasualLeaveCount(int c) { CasualLeaveCount -= c; }

	void UpdateEarnedLeaveCount(int e) { EarnedLeaveCount -= e; }

	void ShowLeaves() {
		int choice;
		cout << "Please enter:-\n1-Display all leaves\n2-Display approved leaves\n3-Display rejected leaves\n4-Display pending leaves\nYout choice: ";
		do {
			do {
				cin >> choice;
				if (cin.fail())
					cout << "Invalid Input\nEnter again: ";
			} while (cin.fail());
			if (choice < 1 || choice > 4)
				cout << "Invalid Input\nEnter again: ";
		} while (choice < 1 || choice > 4);
		int size = PendingLeaves.size();
		if (choice == 1) {
			for (int i = 0; i < size; i++)
				ial->DisplayLeave(PendingLeaves[i]);
		}
		else if (choice == 2) {
			for (int i = 0; i < size; i++)
				if (PendingLeaves[i]->getStatus() == "Leave_Approved")
					ial->DisplayLeave(PendingLeaves[i]);
		}
		else if (choice == 3) {
			for (int i = 0; i < size; i++)
				if (PendingLeaves[i]->getStatus() == "Rejected_by_Supervisor" || PendingLeaves[i]->getStatus() == "Rejected_by_Director")
					ial->DisplayLeave(PendingLeaves[i]);
		}
		else {
			for (int i = 0; i < size; i++)
				if (PendingLeaves[i]->getStatus() == "Pending_for_Supervisor_Approval" || PendingLeaves[i]->getStatus() == "Pending_for_Director_Approval")
					ial->DisplayLeave(PendingLeaves[i]);
		}
	}
	void ShowAttendance() {
		iva->ViewAttendance(this->getID(), this->getName());
	}
	void AppendLeave(IPendingLeaves*& leave) {
		if (leave->getLeaveType() == "Casual") PendingLeaves.push_back(new CasualLeave(*dynamic_cast<CasualLeave*>(leave)));
		else if (leave->getLeaveType() == "Unpaid") PendingLeaves.push_back(new UnpaidLeave(*dynamic_cast<UnpaidLeave*>(leave)));
		else if (leave->getLeaveType() == "Official") PendingLeaves.push_back(new OfficialLeave(*dynamic_cast<OfficialLeave*>(leave)));
		else if (leave->getLeaveType() == "Earned") PendingLeaves.push_back(new EarnedLeave(*dynamic_cast<EarnedLeave*>(leave)));
	}
	void AddNotification(string Notification)
	{
		this->Notifications.push_back(Notification);
	}
	void ViewNotifications() // Reads Notifications from Notifications.txt and erase all Notifications from file.
	{
		bool flag = false;
		for (int i = 0; i < Notifications.size(); i++) {
			flag = true;
			cout << Notifications[i] << endl;
		}
		if (!flag)
			cout << "No notifications to display!\n";
		Notifications.clear();
	}
	~Employee() = default;
};

class EmployeeHandler : public IHandleEmployeeDirector, public IHandleEmployeeSupervisor {
public:
	void AddEmployee(int ID, string name, int ccount, int ecount, vector<Employee*>& e) override {
		e.push_back(new Employee(ID, name, ccount, ecount));
		FileHandlerEmployee addemp;
		addemp.AddEmployeetoFile(ID, name, ccount, ecount);
		addemp.CreateEmployeeDirectory(ID, name);
		cout << "Employee " << ID << " has been added!\n";
	}
	void RemoveEmployee(int ID, vector<Employee*>& e) override {
		string name;
		for (int i = 0; i < e.size(); i++) {
			if (e[i]->getID() == ID) {
				name = e[i]->getName();
				e.erase(e.begin() + i);
			}
		}
		FileHandlerLeave removeLeave;
		removeLeave.RemoveLeavefromFile(ID);
		FileHandlerEmployee removeEmp;
		removeEmp.RemoveEmployeefromFile(ID);
		removeEmp.RemoveEmployeeDirectory(ID, name);
		cout << "Employee " << ID << " has been removed!\n";
	}
	void DisplayEmployees(vector<Employee*> e) override {
		cout << "Employees:-\n";
		bool flag = false;
		for (int i = 0; i < e.size(); i++) {
			flag = true;
			cout << "ID: " << e[i]->getID() << " , Name: ";
			string name = e[i]->getName();
			for (int i = 0; i < name.size(); i++) {
				if (name[i] != '_')
					cout << name[i];
				else
					cout << " ";
			}
			cout << endl;
		}
		if (!flag)
			cout << "No employees to display!\n";
		cout << "-------------------------------------\n";
	}
};

void LoadPendingLeaves(vector<IPendingLeaves*>& PendingLeaves, string StatusCondition) {
	ifstream fr_leave;
	fr_leave.open("Leave.txt");
	//First input is leave count
	string count;
	fr_leave >> count;
	string LeaveID, EmployeeID, EmployeeName, ApplyDate, LeaveStartDate, LeaveEndDate, LeaveType, Reason, Status, \
		SupervisorReviewDate = "00-00-0000", DirectorReviewDate = "00-00-0000";
	while (!fr_leave.eof()) {
		//Read remaining data of leave from file
		fr_leave >> LeaveID;
		if (LeaveID != "") {
			fr_leave >> EmployeeID >> EmployeeName >> ApplyDate >> LeaveStartDate >> LeaveEndDate >> LeaveType >> Reason >> Status;
			if (Status == "Pending_for_Director_Approval" || Status == "Rejected_by_Supervisor" || \
				(Status == "Leave_Approved" && (LeaveType == "Casual" || LeaveType == "Official"))) {
				fr_leave >> SupervisorReviewDate;
			}
			else if (Status == "Rejected_by_Director" || (Status == "Leave_Approved" && (LeaveType == "Earned" || LeaveType == "Unpaid"))) {
				fr_leave >> SupervisorReviewDate >> DirectorReviewDate;
			}
			if (Status == StatusCondition) {
				if (LeaveType == "Casual") {
					PendingLeaves.push_back(new CasualLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), stoi(LeaveID), \
						stoi(EmployeeID), EmployeeName, backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
				else if (LeaveType == "Earned") {
					PendingLeaves.push_back(new EarnedLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), \
						(DirectorReviewDate != "00-00-0000"), backToDate(DirectorReviewDate), stoi(LeaveID), stoi(EmployeeID), EmployeeName, \
						backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
				else if (LeaveType == "Official") {
					PendingLeaves.push_back(new OfficialLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), stoi(LeaveID), \
						stoi(EmployeeID), EmployeeName, backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
				else if (LeaveType == "Unpaid") {
					PendingLeaves.push_back(new UnpaidLeave((SupervisorReviewDate != "00-00-0000"), backToDate(SupervisorReviewDate), \
						(DirectorReviewDate != "00-00-0000"), backToDate(DirectorReviewDate), stoi(LeaveID), stoi(EmployeeID), EmployeeName, \
						backToDate(ApplyDate), backToDate(LeaveStartDate), backToDate(LeaveEndDate), LeaveType, Reason, Status));
				}
			}
		}
		else
			break;
		SupervisorReviewDate = "00-00-0000", DirectorReviewDate = "00-00-0000", LeaveID = "";
	}
	fr_leave.close();
}

class MenuHandler {
public:
	void DisplayDirectorMenu() {
		cout << "Please Enter what you want to do :-\n"
			<< "1-Show Pending Leaves\n2-Approve a Leave\n3-Reject a Leave\n4-Add an Employee\n5-Remove an Employee\n6-Display list of employees\n7-Generate Report\n8-Return to Main Menu\n";
	}
	void DisplaySupervisorMenu() {
		cout << "Please Enter what you want to do :-\n"
			<< "1-Show Pending Leaves\n2-Approve a Leave\n3-Reject a Leave\n4-Add an Employee\n5-Display list of employees\n6-Generate Report\n7-Return to Main Menu\n";
	}
	void DisplayGuardMenu() {
		cout << "Please Enter what you want to do :-\n"
			<< "1-Mark Entry Time\n2-Mark Exit Time\n3-Return to Main Menu\n";
	}
	void DisplayEmployeeMenu() {
		cout << "Please Enter what you want to do :-\n"
			<< "1-Apply for Leave\n2-View Leaves\n3-View Remaining Leaves\n4-View Attendance\n5-View Notifications\n6-Return to Main Menu\n";
	}
	int GetChoice(int LowerLimit, int UpperLimit) {
		int choice;
		cout << "Your choice: ";
		do {
			do {
				cin >> choice;
				if (cin.fail())
					cout << "Invalid input!\nEnter again: ";
			} while (cin.fail());
			if (choice < LowerLimit || choice > UpperLimit)
				cout << "Invalid input!\nEnter again: ";
		} while (choice < LowerLimit || choice > UpperLimit);
		return choice;
	}
};

class Report : public IGenerateReports {
public:
	void AttendanceBelowPercenatge(vector<Employee*> e) override {
		int percentage;
		cout << "Enter percentage(in whole numbers only): ";
		do {
			do {
				cin >> percentage;
				if (cin.fail())
					cout << "Invalid Input!\nEnter again: ";
			} while (cin.fail());
			if (percentage < 0 || percentage > 100)
				cout << "Invalid Input!\nEnter again: ";
		} while (percentage < 0 || percentage > 100);
		int d1, m1, y1, d2, m2, y2;
		cout << "Please enter the start date to calculate attendance from:- \n";
		getInputDate(d1, m1, y1);
		Date start(d1, m1, y1);
		cout << "Please enter the end date to calculate attendance from:- \n";
		getInputDate(d2, m2, y2);
		Date end(d2, m2, y2);
		//Check if second date is greater than first date
		if (end <= start) {
			do {
				cout << "Invalid date!\nEnter again:- \n";
				getInputDate(d2, m2, y2);
				end.setDate(d2, m2, y2);
			} while (end <= start);
		}
		//Total working days between the given range of dates
		int days = getWorkingDays(start, end);
		//Total 8 hours in each working day
		int totalWorkingHours = days * 8;
		int employeeWorkingHours = 0;
		FileHandlerAttendance fha;
		cout << "Employees having attendance percentage less than " << percentage << "% are:- \n";
		for (int i = 0; i < e.size(); i++) {
			employeeWorkingHours = fha.getAttendanceHours(e[i]->getID(), e[i]->getName(), start, end);
			if (((employeeWorkingHours / totalWorkingHours) * 100) < percentage) {
				cout << "Employee ID: " << e[i]->getID() << ", Employee Name: " << e[i]->getName() << endl;
			}
		}
		if (employeeWorkingHours == 0)
			cout << "No employees to display!\n";
	}
	void LeaveDetailsForEmployee(vector<Employee*> e) override {
		int ID;
		cout << "Please enter the ID of employee: ";
		do {
			cin >> ID;
			if (cin.fail())
				cout << "Invalid Input!\nEnter again: ";
		} while (cin.fail());
		bool flag = false;
		for (int i = 0; i < e.size(); i++) {
			if (e[i]->getID() == ID) {
				flag = true;
				cout << "Remaining Casual Leaves: " << e[i]->getCasualLeaveCount() << endl;
				cout << "Remaining Earned Leaves: " << e[i]->getEarnedLeaveCount() << endl;
				e[i]->ShowLeaves();
			}
		}
		if (!flag)
			cout << "Employee with ID " << ID << " does not exists!\n";
	}
	void AttendanceDetailsForEmployee(vector<Employee*> e) override {
		int ID;
		cout << "Please enter the ID of employee: ";
		do {
			cin >> ID;
			if (cin.fail())
				cout << "Invalid Input!\nEnter again: ";
		} while (cin.fail());
		bool flag = false;
		for (int i = 0; i < e.size(); i++) {
			if (e[i]->getID() == ID) {
				flag = true;
				e[i]->ShowAttendance();
			}
		}
		if (!flag)
			cout << "Employee with ID " << ID << " does not exists!\n";
	}
};

class Supervisor : public Person {
private:
	vector<IPendingLeaves*> PendingLeaves;
	IReviewLeaveSupervisor* irls;
	IHandleEmployeeSupervisor* ihes;
	IGenerateReports* igr;
public:
	Supervisor() = default;
	Supervisor(int ID, string Name) : Person(ID, Name) {
		irls = new LeaveService();
		ihes = new EmployeeHandler();
		igr = new Report();
		LoadPendingLeaves(PendingLeaves, "Pending_for_Supervisor_Approval");
	}
	void DisplayLeaves() {
		bool flag = false;
		for (int i = 0; i < PendingLeaves.size(); i++) {
			flag = true;
			irls->DisplayLeave(PendingLeaves[i]);
		}
		if (!flag)
			cout << "No leave to display!\n";
	}
	IPendingLeaves* ApproveLeave(vector<Employee*>& e) {
		int ID;
		int toReturn;
		bool flag = false;
		cout << "Please enter the leave ID to approve: ";
		do {
			do {
				cin >> ID;
				if (cin.fail())
					cout << "Wrong Input!\nEnter again: ";
			} while (cin.fail());
			for (int i = 0; i < PendingLeaves.size(); i++) {
				if (PendingLeaves[i]->getID() == ID) {
					flag = true;
					int d, m, y;
					cout << "Please enter the date of approval:- \n";
					getInputDate(d, m, y);
					Date Approvaldate(d, m, y);
					toReturn = i;
					irls->ApproveLeaveasSupervisor(PendingLeaves[i], Approvaldate);
				}
			}
			if (!flag) {
				cout << "The leave does not exists!\nEnter again: ";
			}
		} while (!flag);
		return PendingLeaves[toReturn];
	}
	IPendingLeaves* RejectLeave(vector<Employee*>& e) {
		int ID;
		int toReturn;
		bool flag = false;
		cout << "Please enter the leave ID to reject: ";
		do {
			do {
				cin >> ID;
				if (cin.fail())
					cout << "Wrong Input!\nEnter again: ";
			} while (cin.fail());
			for (int i = 0; i < PendingLeaves.size(); i++) {
				if (PendingLeaves[i]->getID() == ID) {
					flag = true;
					int d, m, y;
					cout << "Please enter the date of rejection:- \n";
					getInputDate(d, m, y);
					Date Rejectiondate(d, m, y);
					toReturn = i;
					irls->RejectLeaveasSupervisor(PendingLeaves[i], Rejectiondate);
				}
			}
			if (!flag) {
				cout << "The leave does not exists!\nEnter again: ";
			}
		} while (!flag);
		return PendingLeaves[toReturn];
	}
	void AppendLeave(IPendingLeaves*& leave) {
		if (leave->getLeaveType() == "Casual") PendingLeaves.push_back(new CasualLeave(*dynamic_cast<CasualLeave*>(leave)));
		else if (leave->getLeaveType() == "Unpaid") PendingLeaves.push_back(new UnpaidLeave(*dynamic_cast<UnpaidLeave*>(leave)));
		else if (leave->getLeaveType() == "Official") PendingLeaves.push_back(new OfficialLeave(*dynamic_cast<OfficialLeave*>(leave)));
		else if (leave->getLeaveType() == "Earned") PendingLeaves.push_back(new EarnedLeave(*dynamic_cast<EarnedLeave*>(leave)));
	}
	void RemoveLeave(IPendingLeaves*& leave) {
		int RemoveID = leave->getID();
		for (int i = 0; i < PendingLeaves.size(); i++)
			if (PendingLeaves[i]->getID() == RemoveID)
				PendingLeaves.erase(PendingLeaves.begin() + i);
	}
	void RemoveLeavewithEmployeeID(int ID) {
		for (int i = 0; i < PendingLeaves.size(); i++)
			if (PendingLeaves[i]->getEmployeeID() == ID)
				PendingLeaves.erase(PendingLeaves.begin() + i);
	}
	void AddEmployee(int ID, string Name, int ccount, int ecount, vector<Employee*>& e) {
		ihes->AddEmployee(ID, Name, ccount, ecount, e);
	}
	void GenerateReports(vector<Employee*> e) {
		int choice;
		cout << "Please Enter what you want to do :-\n"
			<< "1-Show Employees having attendance below than a given percentage\n2-Show leave details for a given employee\n3-Show Attendance details for a given employee\nYour choice: ";
		do {
			do {
				cin >> choice;
				if (cin.fail())
					cout << "Invalid Input!\nEnter again: ";
			} while (cin.fail());
			if (choice < 1 || choice > 3)
				cout << "Invalid Input!\nEnter again: ";
		} while (choice < 1 || choice > 3);
		if (choice == 1)
			igr->AttendanceBelowPercenatge(e);
		else if (choice == 2)
			igr->LeaveDetailsForEmployee(e);
		else if (choice == 3)
			igr->AttendanceDetailsForEmployee(e);
	}
	void DisplayEmployees(vector<Employee*> e) {
		ihes->DisplayEmployees(e);
	}
	~Supervisor() = default;
};

class Director : public Person {
private:
	vector<IPendingLeaves*> PendingLeaves;
	IReviewLeaveDirector* irld;
	IHandleEmployeeDirector* ihed;
	IGenerateReports* igr;
public:
	Director() = default;
	Director(int ID, string Name) : Person(ID, Name) {
		LoadPendingLeaves(PendingLeaves, "Pending_for_Director_Approval");
		irld = new LeaveService();
		ihed = new EmployeeHandler();
		igr = new Report();
	}
	IPendingLeaves* ApproveLeave(vector<Employee*>& e) {
		int ID;
		int toReturn;
		bool flag = false;
		cout << "Please enter the leave ID to approve: ";
		do {
			do {
				cin >> ID;
				if (cin.fail())
					cout << "Wrong Input!\nEnter again: ";
			} while (cin.fail());
			for (int i = 0; i < PendingLeaves.size(); i++) {
				if (PendingLeaves[i]->getID() == ID) {
					flag = true;
					int d, m, y;
					cout << "Please enter the date of approval:- \n";
					getInputDate(d, m, y);
					Date Approvaldate(d, m, y);
					toReturn = i;
					irld->ApproveLeaveasDirector(PendingLeaves[i], Approvaldate);
				}
			}
			if (!flag) {
				cout << "The leave does not exists!\nEnter again: ";
			}
		} while (!flag);
		return PendingLeaves[toReturn];
	}
	IPendingLeaves* RejectLeave(vector<Employee*>& e) {
		int ID;
		int toReturn;
		bool flag = false;
		cout << "Please enter the leave ID to reject: ";
		do {
			do {
				cin >> ID;
				if (cin.fail())
					cout << "Wrong Input!\nEnter again: ";
			} while (cin.fail());
			for (int i = 0; i < PendingLeaves.size(); i++) {
				if (PendingLeaves[i]->getID() == ID) {
					flag = true;
					int d, m, y;
					cout << "Please enter the date of rejection:- \n";
					getInputDate(d, m, y);
					Date Rejectiondate(d, m, y);
					toReturn = i;
					irld->RejectLeaveasDirector(PendingLeaves[i], Rejectiondate);
				}
			}
			if (!flag) {
				cout << "The leave does not exists!\nEnter again: ";
			}
		} while (!flag);
		return PendingLeaves[toReturn];
	}
	void AppendLeave(IPendingLeaves*& leave) {
		if (leave->getLeaveType() == "Earned") PendingLeaves.push_back(new EarnedLeave(*dynamic_cast<EarnedLeave*>(leave)));
		else if (leave->getLeaveType() == "Unpaid") PendingLeaves.push_back(new UnpaidLeave(*dynamic_cast<UnpaidLeave*>(leave)));
	}
	void RemoveLeave(IPendingLeaves*& leave) {
		int RemoveID = leave->getID();
		for (int i = 0; i < PendingLeaves.size(); i++)
			if (PendingLeaves[i]->getID() == RemoveID)
				PendingLeaves.erase(PendingLeaves.begin() + i);
	}
	void RemoveLeavewithEmployeeID(int ID) {
		for (int i = 0; i < PendingLeaves.size(); i++)
			if (PendingLeaves[i]->getEmployeeID() == ID)
				PendingLeaves.erase(PendingLeaves.begin() + i);
	}
	void AddEmployee(int ID, string Name, int ccount, int ecount, vector<Employee*>& e) {
		ihed->AddEmployee(ID, Name, ccount, ecount, e);
	}
	void RemoveEmployee(int ID, vector<Employee*>& e) {
		ihed->RemoveEmployee(ID, e);
	}
	void DisplayLeaves() {
		bool flag = false;
		for (int i = 0; i < PendingLeaves.size(); i++) {
			flag = true;
			irld->DisplayLeave(PendingLeaves[i]);
		}
		if (!flag)
			cout << "No leave to display!\n";
	}
	void GenerateReports(vector<Employee*> e) {
		int choice;
		cout << "Please Enter what you want to do :-\n"
			<< "1-Show Employees having attendance below than a given percentage\n2-Show leave details for a given employee\n3-Show Attendance details for a given employee\nYour choice: ";
		do {
			do {
				cin >> choice;
				if (cin.fail())
					cout << "Invalid Input!\nEnter again: ";
			} while (cin.fail());
			if (choice < 1 || choice > 3)
				cout << "Invalid Input!\nEnter again: ";
		} while (choice < 1 || choice > 3);
		if (choice == 1)
			igr->AttendanceBelowPercenatge(e);
		else if (choice == 2)
			igr->LeaveDetailsForEmployee(e);
		else if (choice == 3)
			igr->AttendanceDetailsForEmployee(e);
	}
	void DisplayEmployees(vector<Employee*> e) {
		ihed->DisplayEmployees(e);
	}
	~Director() = default;
};

class Guard : public Person {
	IMarkAttendance* ima;
public:
	Guard() = default;
	Guard(int ID, string Name) : Person(ID, Name) { ima = new Attendance(); }
	bool MarkEntryTime(int ID, string Name, Date date, Time time) {
		return ima->MarkEntryTime(ID, Name, date, time);
	}
	bool MarkExitTime(int ID, string Name, Date date, Time time) {
		return ima->MarkExitTime(ID, Name, date, time);
	}
	~Guard() = default;
};

void DirectorFunc(int opt, Director& d, Supervisor& s, vector<Employee*>& e) {
	if (opt == 1) {
		d.DisplayLeaves();
	}
	else if (opt == 2) {
		IPendingLeaves* leave = d.ApproveLeave(e);
		string notificationString;
		auto leave_director = dynamic_cast<LeaveApprovedByDirector*>(leave);
		notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
			+ leave->getLeaveEndDate() + " has been approved by director on " + leave_director->getDirectorReviewDate() + ".";
		if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
			for (int i = 0; i < e.size(); i++) {
				if (leave->getEmployeeID() == e[i]->getID()) {
					FileHandlerEmployee fhe;
					if (leave->getLeaveType() == "Earned") {
						//Update Earned leave count in employee
						e[i]->UpdateEarnedLeaveCount(getWorkingDays(backToDate(leave->getLeaveStartDate()), backToDate(leave->getLeaveEndDate())));
						//Update Earned leave count in file
						fhe.UpdateEarnedLeaveinFile(e[i]->getID(), e[i]->getEarnedLeaveCount());
					}
					//Send notification to employee about director approval
					e[i]->AddNotification(notificationString);
					fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
					notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
						+ leave->getLeaveEndDate() + " has been approved.";
					e[i]->AddNotification(notificationString);
					fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
					//Update leave status in employee
					e[i]->UpdateLeaveStatusinEmployee(leave->getID(), "Leave_Approved", leave_director->getDirectorReviewDate());
					//Update Attdence for the next days of leave
					FileHandlerAttendance fha;
					fha.MarkPresent(e[i]->getID(), e[i]->getName(), backToDate(leave->getLeaveStartDate()), backToDate(leave->getLeaveEndDate()));
				}
			}
			//Remove leave from director
			d.RemoveLeave(leave);
			cout << leave->getLeaveType() << " leave has been approved!\n";
		}
	}
	else if (opt == 3) {
		IPendingLeaves* leave = d.RejectLeave(e);
		string notificationString;
		auto leave_director = dynamic_cast<LeaveApprovedByDirector*>(leave);
		notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
			+ leave->getLeaveEndDate() + " has been rejected by director on " + leave_director->getDirectorReviewDate() + ".";
		for (int i = 0; i < e.size(); i++) {
			if (leave->getEmployeeID() == e[i]->getID()) {
				FileHandlerEmployee fhe;
				//Send notification to employee
				e[i]->AddNotification(notificationString);
				fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
				notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
					+ leave->getLeaveEndDate() + " has been rejected.";
				e[i]->AddNotification(notificationString);
				fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
				//Update leave status in employee
				e[i]->UpdateLeaveStatusinEmployee(leave->getID(), "Rejected_by_Director", leave_director->getDirectorReviewDate());
			}
		}
		//Remove leave from director
		d.RemoveLeave(leave);
		cout << leave->getLeaveType() << " leave has been rejected!\n";
	}
	else if (opt == 4) {
		int ID;
		string name;
		cout << "Please enter ID of new employee: ";
		do {
			cin >> ID;
			if (cin.fail())
				cout << "Invalid Input!\nEnter again: ";
		} while (cin.fail());
		bool flag = true;
		for (int i = 0; i < e.size(); i++)
			if (e[i]->getID() == ID) {
				flag = false;
			}
		if (flag) {
			cout << "Please enter name of new employee: ";
			cin.ignore();
			getline(cin, name);
			string temp = "";
			for (int i = 0; i < name.size(); i++) {
				if (name[i] != ' ')
					temp += name[i];
				else
					temp += "_";
			}
			name = temp;
			d.AddEmployee(ID, name, 15, 21, e);
		}
		else {
			cout << "The employee with ID " << ID << " already exists!\n";
		}
	}
	else if (opt == 5) {
		int ID;
		cout << "Please enter ID of employee to remove: ";
		do {
			cin >> ID;
			if (cin.fail())
				cout << "Invalid Input!\nEnter again: ";
		} while (cin.fail());
		bool flag = false;
		for (int i = 0; i < e.size(); i++)
			if (e[i]->getID() == ID) {
				flag = true;
			}
		if (flag) {
			d.RemoveEmployee(ID, e);
			//Remove all leaves of the employee in Director
			d.RemoveLeavewithEmployeeID(ID);
			//Remove all leaves of the employee in Supervior
			s.RemoveLeavewithEmployeeID(ID);
		}
		else {
			cout << "The employee does not exists!\n";
		}
	}
	else if (opt == 6) {
		d.DisplayEmployees(e);
	}
	else if (opt == 7) {
		d.GenerateReports(e);
	}
}

void SupervisorFunc(int opt, Supervisor& s, Director& d, vector<Employee*>& e) {
	if (opt == 1) {
		s.DisplayLeaves();
	}
	else if (opt == 2) {
		IPendingLeaves* leave = s.ApproveLeave(e);
		string notificationString;
		auto leave_supervisor = dynamic_cast<LeaveApprovedBySupervisor*>(leave);
		notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
			+ leave->getLeaveEndDate() + " has been approved by supervisor on " + leave_supervisor->getSupervisorReviewDate() + ".";
		if (leave->getLeaveType() == "Casual" || leave->getLeaveType() == "Official") {
			for (int i = 0; i < e.size(); i++) {
				if (leave->getEmployeeID() == e[i]->getID()) {
					FileHandlerEmployee fhe;
					if (leave->getLeaveType() == "Casual") {
						//Update Casual leave count in employee
						e[i]->UpdateCasualLeaveCount(getWorkingDays(backToDate(leave->getLeaveStartDate()), backToDate(leave->getLeaveEndDate())));
						//Update Casual leave count in file
						fhe.UpdateCasualLeaveinFile(e[i]->getID(), e[i]->getCasualLeaveCount());
					}
					//Update leave status in employee
					e[i]->UpdateLeaveStatusinEmployee(leave->getID(), "Leave_Approved", leave_supervisor->getSupervisorReviewDate());
					//Send notification to employee about supervisor approval
					e[i]->AddNotification(notificationString);
					fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
					//Send notification that leave has been approved
					notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
						+ leave->getLeaveEndDate() + " has been approved.";
					e[i]->AddNotification(notificationString);
					fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
					//Update Attendance for the next days of leave
					FileHandlerAttendance fha;
					fha.MarkPresent(e[i]->getID(), e[i]->getName(), backToDate(leave->getLeaveStartDate()), backToDate(leave->getLeaveEndDate()));
				}
			}
			//Remove leave from supervisor
			s.RemoveLeave(leave);
			cout << leave->getLeaveType() << " has been approved!\n";
		}
		else {
			for (int i = 0; i < e.size(); i++) {
				if (leave->getEmployeeID() == e[i]->getID()) {
					FileHandlerEmployee fhe;
					//Update Leave Status in Employee
					e[i]->UpdateLeaveStatusinEmployee(leave->getID(), "Pending_for_Director_Approval", leave_supervisor->getSupervisorReviewDate());
					//Send notification to employee about supervisor approval
					e[i]->AddNotification(notificationString);
					fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
					//Send notification to employee about leave forwared to director for approval
					notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
						+ leave->getLeaveEndDate() + " has been sent to director.";
					e[i]->AddNotification(notificationString);
					fhe.AddNotificationtoFile(e[i]->getID(), e[i]->getName(), notificationString);
				}
			}
			//Remove leave from supervisor
			s.RemoveLeave(leave);
			cout << leave->getLeaveType() << " leave has been approved!\n";
			//Add leave to director
			d.AppendLeave(leave);
		}
	}

	else if (opt == 3) {
		IPendingLeaves* leave = s.RejectLeave(e);
		string notificationString;
		auto leave_supervisor = dynamic_cast<LeaveApprovedBySupervisor*>(leave);
		notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
			+ leave->getLeaveEndDate() + " has been rejected by supervisor on " + leave_supervisor->getSupervisorReviewDate() + ".";
		for (int i = 0; i < e.size(); i++) {
			if (leave->getEmployeeID() == e[i]->getID()) {
				//Update status in employee
				e[i]->UpdateLeaveStatusinEmployee(leave->getID(), "Rejected_by_Supervisor", leave_supervisor->getSupervisorReviewDate());
				//Send Notification to employee about supervisor rejection
				e[i]->AddNotification(notificationString);
				//Send notification to employee about rejection
				notificationString = "Your " + leave->getLeaveType() + " leave from " + leave->getLeaveStartDate() + " to " \
					+ leave->getLeaveEndDate() + " has been rejected.";
				e[i]->AddNotification(notificationString);
			}
		}
		//Remove leave from supervisor
		s.RemoveLeave(leave);
		cout << leave->getLeaveType() << " leave has been rejected!\n";
	}
	else if (opt == 4) {
		int ID;
		string name;
		cout << "Please enter ID of new employee: ";
		do {
			cin >> ID;
			if (cin.fail())
				cout << "Invalid Input!\nEnter again: ";
		} while (cin.fail());
		bool flag = true;
		for (int i = 0; i < e.size(); i++)
			if (e[i]->getID() == ID) {
				flag = false;
			}
		if (flag) {
			cout << "Please enter name of new employee: ";
			cin.ignore();
			getline(cin, name);
			string temp = "";
			for (int i = 0; i < name.size(); i++) {
				if (name[i] != ' ')
					temp += name[i];
				else
					temp += "_";
			}
			name = temp;
			d.AddEmployee(ID, name, 15, 21, e);
		}
		else {
			cout << "The employee with ID " << ID << " already exists!\n";
		}
	}
	else if (opt == 5) {
		s.DisplayEmployees(e);
	}
	else if (opt == 6) {
		s.GenerateReports(e);
	}
}

void GuardFunc(int opt, Guard& g, vector<Employee*>& e) {
	if (opt == 1) {
		int ID;
		cout << "Please enter ID of Employee to mark entry time for: ";
		do {
			cin >> ID;
			if (cin.fail()) {
				cout << "Invalid Input!\nEnter again: ";
			}
		} while (cin.fail());
		bool flag = false;
		for (int i = 0; i < e.size(); i++) {
			if (e[i]->getID() == ID) {
				flag = true;
				int d, m, y;
				//Get attendance date
				cout << "Please enter date to mark entry time for:-\n";
				getInputDate(d, m, y);
				Date date(d, m, y);
				int weekday = dayofweek(date.getDate(), date.getMonth(), date.getYear());
				if (weekday != 0 && weekday != 6) {
					int hr, min;
					//Get entry time
					cout << "Please enter time of entry(in 24 hr format):-\n";
					getInputTime(hr, min);
					if (!(hr == 23 && min == 59)) {
						Time time(hr, min);
						if (g.MarkEntryTime(ID, e[i]->getName(), date, time)) {
							FileHandlerEmployee fhe;
							string notification = time.toTime() + " has been marked as entry time for " + date.toDate();
							e[i]->AddNotification(notification);
							fhe.AddNotificationtoFile(ID, e[i]->getName(), notification);
						}
					}
					else
						cout << "You cannot mark the last minute of day as entry time!\n";
				}
				else
					cout << "The entered day is not a working day!\n";
			}
		}
		if (!flag) {
			cout << "The employee with ID " << ID << " does not exists!\n";
		}
	}
	else if (opt == 2) {
		int ID;
		cout << "Please enter ID of Employee to mark exit time for: ";
		do {
			cin >> ID;
			if (cin.fail()) {
				cout << "Invalid Input!\nEnter again: ";
			}
		} while (cin.fail());
		bool flag = false;
		for (int i = 0; i < e.size(); i++) {
			if (e[i]->getID() == ID) {
				flag = true;
				int d, m, y;
				//Get attendance date
				cout << "Please enter date to mark exit time for:-\n";
				getInputDate(d, m, y);
				Date date(d, m, y);
				int weekday = dayofweek(date.getDate(), date.getMonth(), date.getYear());
				if (weekday != 0 && weekday != 6) {
					int hr, min;
					//Get entry time
					cout << "Please enter time of exit(in 24 hr format):-\n";
					getInputTime(hr, min);
					Time time(hr, min);
					if (g.MarkExitTime(ID, e[i]->getName(), date, time)) {
						FileHandlerEmployee fhe;
						string notification = time.toTime() + " has been marked as exit time for " + date.toDate();
						e[i]->AddNotification(notification);
						fhe.AddNotificationtoFile(ID, e[i]->getName(), notification);
					}
				}
				else
					cout << "The entered day is not a working day!\n";
			}
		}
		if (!flag) {
			cout << "The employee with ID " << ID << " does not exists!\n";
		}
	}
}

void EmployeeFunc(int opt, Employee& e, Supervisor& s) {
	if (opt == 1) {
		int d, m, y;
		cout << "Please Enter today's date:- \n";
		getInputDate(d, m, y);
		Date current(d, m, y);

		cout << "Please enter the leave start date:- \n";
		getInputDate(d, m, y);
		Date start(d, m, y);
		if (!(start >= current)) {
			while (!(start >= current)) {
				cout << "Invalid Date!\n";
				cout << "Please enter the leave start date:- \n";
				getInputDate(d, m, y);
				start.setDate(d, m, y);
			}
		}

		cout << "Please enter the leave end date:- \n";
		getInputDate(d, m, y);
		Date end(d, m, y);
		if (!(end >= current)) {
			while (!(end >= current)) {
				cout << "Invalid Date!\n";
				cout << "Please enter the leave end date:- \n";
				getInputDate(d, m, y);
				end.setDate(d, m, y);
			}
		}

		//Get the number of working days between leave start date and end date to get the total number of leave days!
		int DaysofLeave = getWorkingDays(start, end);

		if (DaysofLeave != 0) {
			string LeaveType;
			cout << "Please enter leave type:-\nCasual\nEarned\nOfficial\nUnpaid\n";
			cout << "Your choice: ";
			do {
				cin >> LeaveType;
			} while (!(LeaveType == "Casual" || LeaveType == "Earned" || LeaveType == "Official" || LeaveType == "Unpaid"));

			string reason;
			cout << "Please enter the reason for leave: ";
			cin.ignore();
			getline(cin, reason);
			string temp = "";
			for (int i = 0; i < reason.size(); i++) {
				if (reason[i] != ' ')
					temp += reason[i];
				else
					temp += "_";
			}
			reason = temp;

			//Check remaining leaves if type == Casual or Earned
			bool LeaveFlag = true, countFlag = true;
			if (LeaveType == "Casual") {
				LeaveFlag = e.CheckCasualLeave(DaysofLeave);
				if (DaysofLeave > 4)
					countFlag = false;
			}
			else if (LeaveType == "Earned")
				LeaveFlag = e.CheckEarnedLeave(DaysofLeave);
			else
				LeaveFlag = true;
			FileHandlerLeave fhl;

			if (LeaveFlag && countFlag) {
				if (fhl.CheckDuplicateLeave(current, start, end, LeaveType, e.getID())) { //Proceed if true means no duplicate leave exists
					//Get leave ID from file
					int LeaveID = fhl.getID();

					//Update next usuable ID in Leave.txt
					fhl.UpdateNextUsableLeaveID();

					//Add leave to employee, supervisor
					string status = "Pending_for_Supervisor_Approval";
					LeaveApplication* new_leave = new LeaveApplication();
					Date date(0, 0, 0);
					if (LeaveType == "Casual") new_leave = new CasualLeave(false, date, LeaveID, e.getID(), e.getName(), current, start, end, LeaveType, reason, status);
					else if (LeaveType == "Earned") new_leave = new EarnedLeave(false, date, false, date, LeaveID, e.getID(), e.getName(), current, start, end, LeaveType, reason, status);
					else if (LeaveType == "Official") new_leave = new OfficialLeave(false, date, LeaveID, e.getID(), e.getName(), current, start, end, LeaveType, reason, status);
					else if (LeaveType == "Unpaid") new_leave = new UnpaidLeave(false, date, false, date, LeaveID, e.getID(), e.getName(), current, start, end, LeaveType, reason, status);
					IPendingLeaves* new_pending_leave = dynamic_cast<IPendingLeaves*>(new_leave);
					e.AppendLeave(new_pending_leave);
					s.AppendLeave(new_pending_leave);
					fhl.AddLeavetoFile(*new_leave);
					cout << LeaveType << " leave has been applied!\n";
				}
			}
			else if (LeaveFlag)
				cout << "You can apply for maximum 4 casual leaves at a time!\n";
			else
				cout << "Insufficient Leaves!\n";
		}
		else {
			cout << "There is no working day between ";
			start.Display();
			cout << " and ";
			end.Display();
			cout << ".\n";
		}
	}
	else if (opt == 2) {
		e.ShowLeaves();
	}
	else if (opt == 3) {
		cout << "Remaining Casual Leaves: " << e.getCasualLeaveCount() << endl;
		cout << "Remaining Earned Leaves: " << e.getEarnedLeaveCount() << endl;
	}
	else if (opt == 4) {
		e.ShowAttendance();
	}
	else if (opt == 5) {
		e.ViewNotifications();
		FileHandlerEmployee fhe;
		fhe.RemoveNotificationsFromFile(e.getID(), e.getName());
	}
}

int DisplayMainMenu(Director& d, Supervisor& s, Guard& g, vector<Employee*>& e) {
	int choice;
	cout << "Please select your role :-\n"
		<< "1-Director\n2-Supervisor\n3-Guard\n4-Employee\n5-Exit\n";
	cout << "Your choice: ";
	do {
		do {
			cin >> choice;
			if (cin.fail())
				cout << "Invalid input!\nEnter again: ";
		} while (cin.fail());
		if (choice < 1 || choice > 5)
			cout << "Invalid input!\nEnter again: ";
	} while (choice < 1 || choice > 5);

	if (choice >= 1 && choice <= 4) {
		int ID;
		cout << "Please enter your ID for verification: ";
		do {
			cin >> ID;
			if (cin.fail())
				cout << "Invalid input!\nEnter again: ";
		} while (cin.fail());
		MenuHandler menu;
		int option;
		//Director
		if (choice == 1) {
			if (d.getID() == ID) {
				do {
					cout << "Successfully logged in as Director!\n";
					menu.DisplayDirectorMenu();
					option = menu.GetChoice(1, 8);
					if (option != 8) {
						DirectorFunc(option, d, s, e);
						system("pause");
						system("cls");
					}
				} while (option != 8);
			}
			else {
				cout << "Invalid ID!\nAccess Denied!\n";
			}
			system("pause");
			system("cls");
			DisplayMainMenu(d, s, g, e);
		}
		//Supervisor
		else if (choice == 2) {
			if (s.getID() == ID) {
				do {
					cout << "Successfully logged in as Supervisor!\n";
					menu.DisplaySupervisorMenu();
					option = menu.GetChoice(1, 7);
					if (option != 7) {
						SupervisorFunc(option, s, d, e);
						system("pause");
						system("cls");
					}
				} while (option != 7);
			}
			else {
				cout << "Invalid ID!\nAccess Denied!\n";
			}
			system("pause");
			system("cls");
			DisplayMainMenu(d, s, g, e);
		}
		//Guard
		else if (choice == 3) {
			if (g.getID() == ID) {
				do {
					cout << "Successfully logged in as Guard!\n";
					menu.DisplayGuardMenu();
					option = menu.GetChoice(1, 3);
					if (option != 3) {
						GuardFunc(option, g, e);
						system("pause");
						system("cls");
					}
				} while (option != 3);
			}
			else {
				cout << "Invalid ID!\nAccess Denied!\n";
			}
			system("pause");
			system("cls");
			DisplayMainMenu(d, s, g, e);
		}
		//Employee
		else {
			bool status = false;
			for (int i = 0; i < e.size(); i++)
				if (e[i]->getID() == ID) {
					status = true;
					do {
						cout << "Successfully logged in as Employee " << e[i]->getID() << "!\n";
						menu.DisplayEmployeeMenu();
						option = menu.GetChoice(1, 6);
						if (option != 6) {
							EmployeeFunc(option, *e[i], s);
							system("pause");
							system("cls");
						}
					} while (option != 6);
				}
			if (status == false) {
				cout << "The employee does not exist!\n";
			}
			system("pause");
			system("cls");
			DisplayMainMenu(d, s, g, e);
		}
	}
	else {
		system("cls");
		return 0;
	}
}

int main() {
	string ID;
	string Name;
	//Read Director File
	ifstream fr_director;
	fr_director.open("Director.txt");
	fr_director >> ID;
	fr_director >> Name;
	fr_director.close();
	if (ID == "" || Name == "") {
		cout << "Error in reading the director file!\n";
		return 0;
	}
	Director director(stoi(ID), Name);

	ID = "", Name = "";
	//Read Supervisor File
	ifstream fr_supervisor;
	fr_supervisor.open("Supervisor.txt");
	fr_supervisor >> ID;
	fr_supervisor >> Name;
	fr_supervisor.close();
	if (ID == "" || Name == "") {
		cout << "Error in reading the supervisor file!\n";
		return 0;
	}
	Supervisor supervisor(stoi(ID), Name);

	string CountOfEmployees, CasualCount, EarnedCount;
	vector<Employee*> employee;
	//Read Employee File
	FileHandlerEmployee addEmp;
	string folder = "Employee";
	_mkdir(folder.c_str());
	ifstream fr_employee;
	fr_employee.open("Employee.txt");
	fr_employee >> CountOfEmployees;
	for (int i = 0; i < stoi(CountOfEmployees); i++) {
		ID = "", Name = "";
		fr_employee >> ID;
		fr_employee >> Name;
		fr_employee >> CasualCount;
		fr_employee >> EarnedCount;
		if (ID == "" || Name == "") {
			cout << "Error in reading the employee file!\n";
			return 0;
		}
		employee.push_back(new Employee(stoi(ID), Name, stoi(CasualCount), stoi(EarnedCount)));
		addEmp.CreateEmployeeDirectory(stoi(ID), Name);
	}
	fr_employee.close();

	ID = "", Name = "";
	//Read Guard File
	ifstream fr_guard;
	fr_guard.open("Guard.txt");
	fr_guard >> ID;
	fr_guard >> Name;
	fr_guard.close();
	if (ID == "" || Name == "") {
		cout << "Error in reading the guard file!\n";
		return 0;
	}
	Guard guard(stoi(ID), Name);

	DisplayMainMenu(director, supervisor, guard, employee);

	return 0;
}
