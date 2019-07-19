// OJ Problem #1
// GPA

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

class Student {
public:
	Student() { TotalScore = 0; credit = 0; }
	long TotalScore;
	int credit;
};

int stat[41];

int main(){
    ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i<41; i++)
		stat[i] = 0;
	Student *stu = new Student[n];
	
	for (int q = 1; q <= m; q++) {
		int j;
		cin >> j;
		switch (j) {
		case 1: {
			unsigned int k, l; string grade;
			cin >> k >> l >> grade;
			int g;
			if (grade == "A+" || grade == "A=") g = 40;
			else if (grade == "A-") g = 37;
			else if (grade == "B+") g = 33;
			else if (grade == "B=") g = 30;
			else if (grade == "B-") g = 27;
			else if (grade == "C+") g = 23;
			else if (grade == "C=") g = 20;
			else if (grade == "C-") g = 17;
			else if (grade == "D+") g = 13;
			else if (grade == "D=") g = 10;
			else g = 0;
			if (stu[k - 1].credit) {
				int gpa = ceil(10 * (double(stu[k - 1].TotalScore) / stu[k - 1].credit));
				stat[gpa]--;
			}
			stu[k - 1].credit += 10 * l;
			stu[k - 1].TotalScore += (l*g);
			int gpa = ceil(10 * (double(stu[k - 1].TotalScore) / stu[k - 1].credit));
			stat[gpa]++;
			break;
		}
		case 2: {
			int k;
			cin >> k;
			cout << setiosflags(ios_base::fixed) << setprecision(1) << ceil(10 * (double(stu[k - 1].TotalScore) / stu[k - 1].credit)) / 10.0 << '\n';
			break;
		}
		case 3: {
			double g;
			cin >> g;
			int gpa = 10*g;
			cout << stat[gpa] << '\n';
			break;
		}
		}
	}
	delete[] stu;
	return 0;
}