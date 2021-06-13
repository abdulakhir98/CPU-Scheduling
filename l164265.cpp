#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main() {
	string arr;
	char b;
	int c;
	int gap;
	int avg1;
	int t = 1;
	int avg = 0;
	char name[4];
	char n[3];
	int ln;
	char pro[3];
	int prol[3];
	char prof[3];
	int prolf[3];
	int wtime[100];
	int lastcputime[3];
	char event[3];
	int elen[3];
	char eventf[3];
	int elenf[3];
	int len;
	int exe = 0;
	int i = 0;
	int k = 0;
	int q = 0;
	char f[3] = { '1','2','3' };
	int fl[3];
	char oprof[100];
	ifstream in;
	in.open("input.txt");

	if (in.fail()) {

		cout << "error";
		return 1;
	}
	else {
		getline(in, arr);
		if (in.eof() != true)
		{
			while (i < 3) {							//cpu burst input
				in >> name;
				in >> n;
				in >> ln;
				len = ln;
				pro[i] = name[2];
				prol[i] = len;
				oprof[q] = name[2];
				in >> n;
				in >> n;
				in >> n;
				in >> n;
				i++;
				k++;
				q++;
			}

			for (int i = 0; i < 3; i++) {					//cpu swap according to order
				b = f[i];
				if (b == '1') {
					prof[i] = pro[0];
					prolf[i] = prol[0];
				}
				else if (b == '2') {
					prof[i] = pro[1];
					prolf[i] = prol[1];
				}
				else if (b == '3') {
					prof[i] = pro[2];
					prolf[i] = prol[2];
				}
			}

			wtime[0] = 0;							//first cpu burst waiting time
			while (t < 3) {
				wtime[t] = wtime[t - 1] + prolf[t-1];
				t++;
			}

			for (int i = 0; i < 3; i++) {					//cpu burst time calculate
				c = prolf[i];
				c = exe + c;
				prolf[i] = c;
				exe = c;
			}
		}

		while (!in.eof()) {
			for (int i = 0; i < 3; i++) {					//I/O input
				in >> name;
				in >> n;
				in >> ln;
				len = ln;
				event[i] = name[2];
				elen[i] = len;
				in >> n;
				in >> n;
				in >> n;
				in >> n;
			}

			if(in.eof()) {
				break;
			}

			for (int i = 0; i < 3; i++) {					//I/O swap according to order
				b = prof[i];
				if (b == '1') {
					eventf[i] = event[0];
					elenf[i] = elen[0];
				}
				else if (b == '2') {
					eventf[i] = event[1];
					elenf[i] = elen[1];
				}
				else if (b == '3') {
					eventf[i] = event[2];
					elenf[i] = elen[2];
				}
			}

			for (int i = 0; i < 3; i++) {					//I/O time calculate
				int a = 0;
				a = prolf[i];
				fl[i] = a + elenf[i];
			}

			for (int i = 0; i < 3; i++) {					//I/O burst copy in new array
				f[i] = prof[i];
			}

			for (int i = 0; i < 3; i++) {					//next cpu order
				for (int j = i + 1; j < 3; j++) {
					if (fl[j] < fl[i]) {
						swap(fl[i], fl[j]);
						swap(f[i], f[j]);
					}
				}
			}
			i = 0;

			while (i < 3) {							//cpu burst input
				in >> name;
				in >> n;
				in >> ln;
				len = ln;
				pro[i] = name[2];
				prol[i] = len;
				in >> n;
				in >> n;
				in >> n;
				in >> n;
				i++;
				k++;
			}

			for (int i = 0; i < 3; i++) {					//cpu burst swap according to order
				b = f[i];
				if (b == '1') {
					prof[i] = pro[0];
					prolf[i] = prol[0];
				}
				else if (b == '2') {
					prof[i] = pro[1];
					prolf[i] = prol[1];
				}
				else if (b == '3') {
					prof[i] = pro[2];
					prolf[i] = prol[2];
				}
			}

			for (int i = 0; i < 3; i++) {					//cpu burst time calculate
				c = prolf[i];
				lastcputime[i] = exe;
				if ((exe - fl[i]) < 0) {
					gap = (-1)*(exe - fl[i]);
					exe = exe + gap;
					c = exe + c;
				}
				else {
					c = exe + c;
				}
				exe = c;
				prolf[i] = exe;
			}

			for (int i = 0; i < 3; i++) {					//waiting time calculation
				wtime[t] = lastcputime[i] - fl[i];
				if (wtime[t] < 0) {
					
					wtime[t] = 0;

				}
				t++;
			}

			for (int i = 0; i < 3; i++) {
				oprof[q] = f[i];
				q++;
			}
		}

		for (int i = 0; i < k; i++) {						//avg waiting time calculation
			avg = avg + wtime[i];
		}
		avg1 = avg / k;

	}
	in.close();

	ofstream my;
	my.open("output.txt");

	my << "Order of Processes: ";
	for (int i = 0; i < k; i++) {
		my << "P_";
		my << oprof[i];
		if (i < k - 1) {
			my << " ,";
		}
	}
	my << endl;
	my << "Total Execution Time: " << exe <<endl;
	my << "Average Waiting Time: " << avg << "/" << k;
	
	my.close();

	return 0;
}
