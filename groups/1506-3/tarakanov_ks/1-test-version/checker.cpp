#include <cstdio> 
#include <cmath> 
#include <string>
#include <iostream>

using namespace std;

/* 
// Checker ������������� ��� �������� 
AC = Accepted(��������� ���������)
WA = Wrong Answer(��������� �����������)
*/

enum verdict { NO = 1, AC, WA};

class Result 
{
private: 
	FILE * res; 
public: 

	enum type { NO = 1, VERDICT, MESSAGE, TIME, MEMORY }; 

	// �-� �� ���������
	Result(bool read = false)
	{ 
		if (read) 
			fopen_s(&res, "result.txt", "r"); 
		else 
			fopen_s(&res,"result.txt", "w"); 
	}
	// �-�
	~Result() { fclose(res); }
	// ������ ���� ���������
	void write_type(type t) { fwrite(&t, sizeof(t), 1, res); }

	// �������� ����������� �������, ��� ���������� ���� �� ���������
	void write_verdict(verdict v) 
	{
		write_type(type::VERDICT); 
		fwrite(&v, sizeof (v), 1, res); 
	}
	
	// �������� ��������� ������������ � ������������ �������
	void write_message(string str)
	{ 
		write_type(type::MESSAGE); 
		int l = str.size (); 
		fwrite(&l, sizeof (l), 1, res);
		fwrite (&str[0], sizeof (str[0]), l, res); 
	}

	// �������� ����������� ������� ����� ������ ��������� ���������,  
	// x ����� ����������� 100 �� = 10 ^ (-7) ��� 
	void write_time(long long x)
	{ write_type(type::TIME); fwrite(&x, sizeof (x), 1, res); }

} checker_result; 


int main() 
{ 
	// ��������� ���� ������� ������,  ����� ��������� 
	FILE * bui;
	fopen_s(&bui, "matr.in", "rb");
	FILE * buo;
	fopen_s(&buo, "matr.out", "rb");
	// ��������� ������
	FILE * perfect;
	fopen_s(&perfect, "answer.out", "rb");
	
	int N; 
	// ��������� ����������� ������ 
	fread(&N, sizeof (N), 1, bui);

	int block_size; 
	// ��������� ������ �����
	fread(&block_size, sizeof(block_size), 1, bui);

	// �������� ������ ��� ������� ������ ���� � ������ ���������
	double **ans = new double*[N];
	for (int count = 0; count < N; count++)
		ans[count] = new double[N];

	double **res = new double*[N];
	for (int count = 0; count < N; count++)
		res[count] = new double[N];

	// ������� ������ ���� � ��������� 
	double ans_time, res_time;
	
	// ��������� ����� ������ ��������� ��������� � ������� ��������� 
	fread(&ans_time, sizeof (int), 1, buo); 
	for (int i = 0; i < N; i++)
	{
		fread(ans[i], sizeof(double), N, buo);
	}
  
	// ��������� ����� ������ ��������� � ������� ���� 
	fread(&res_time, sizeof (int), 1, perfect); 
	for (int i = 0; i < N; i++)
	{
		fread(res[i], sizeof(double), N, perfect);
	}

	bool flag = true;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (res[i][j] != ans[i][j])
			{
				flag = false;
				break;
			}
		}
	}

		   
	// ���� ������ ���, �������� ��� ������� ���������
	if (flag)
	{ 
		checker_result.write_message ("AC. Numbers are equal.");
		checker_result.write_verdict (verdict::AC); 
	} 
	else 
	{ 
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}
		   
	// ���������� ����� � ���������� ����������� (��������� �� 100 �� = 10 ^ (-7) ���). 
	checker_result.write_time (res_time * 1e7);

	fclose(buo);
	fclose(bui);
	fclose(perfect);

	return 0;
}