//Section 1: Declarations & Prototypes
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <math.h>
using namespace std;
//frequently used variables :
string a, b, c, d, e, ar[100], ar1[100], ar0[100]; int k, w;
//prototypes :
string var_name(string s); //gets get the name of variable from a string ,e.g.:If given -24.344ali,the function returns ali.
float coeff(string s); //gets the coeff of variable from a string ,e.g.:If given -24.344ali,the function returns -24.344.
bool check_str(string a); //checks if the given string contains letters ,e.g.:If given 2633ali,the function returns true.
string ftos(float a); //transforms given float into string.
string abs(string x); //if given 5x1-27x2-92x3=228, the return is 5x1+27x2+92x3=228. 
string proper_form(string a); //makes the given equation (string) on proper form of equations.
void column(string eqn[], string var, float column_i[], int n); //puts coefficients of the given variable name in a 1-d array.
bool IsInArray(string arr[], int x, string var); //checkes if the given variable name is in the given array. 
string equation_i(string a[], string b); //returns the equation of the given index.
string add(string s1, string s2);
string subtract(string s1, string s2); //returns (s1-s2) .
int num_vars(string eqn[], int n); 
double coeff_in_array(string s1, string v); //returns coefficient of the given variable name in the given equation (string),e.g.: if given s1="6x1-5x2=23" & v="x2",the return is -5.
string substitute(string v, string eq2, string eq1); 
void D(int n, string eqn[], string arr[100][100]);
void D_xi(int r, int m, string eqn[], string arr[100][100], string v);
float D_value(int n, float matrix[100][100]); 

//Section 2: Main Program
int main()
{
	string eqn[100], op, arr[100][100]; float column1[100]; float matrix[100][100];
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> eqn[i];
		eqn[i] = proper_form(eqn[i]);
	}
	int m = num_vars(eqn,n); int r = n;
	while (1)
	{
		getline(cin, op);
		if (op == "quit")
		{
			return 0;
		}
		if (op == "num_vars")cout << num_vars(eqn,n) << endl;
		if (op.substr(0, 8) == "equation")cout << equation_i(eqn, op) << endl;
		if (op.substr(0, 6) == "column")
		{
			string x = op.substr(7, op.length());
			column(eqn, x, column1, n);
			for (int p = 0; p < n; p++)
			{
				cout << column1[p] << endl;
			}
		}
		if (op.substr(0, 3) == "add")
		{
			string a = op.substr(4, op.length()), b, c;
			for (int i = 1; i < a.length(); i++)
			{
				if (a.substr(i, 1) == " ")
				{
					b = a.substr(0, i);
					c = a.substr(i + 1, a.length());
					break;
				}
			}
			cout << add(eqn[atoi(b.c_str()) - 1], eqn[atoi(c.c_str()) - 1]) << endl;
		}
		if (op.substr(0, 8) == "subtract")
		{
			string a = op.substr(8, op.length()), b, c;
			for (int i = 1; i < a.length(); i++)
			{
				if (a.substr(i, 1) == " ")
				{
					b = a.substr(0, i);
					c = a.substr(i + 1, a.length());
					break;
				}
			}
			cout << subtract(eqn[atoi(b.c_str()) - 1], eqn[atoi(c.c_str()) - 1]) << endl;
		}
		if (op.substr(0, 10) == "substitute")
		{
			string a = op.substr(11, op.length()), b, c, d, e;
			for (int i = 1; i < a.length(); i++)
			{
				if (a.substr(i, 1) == " ")
				{
					b = a.substr(0, i);
					c = a.substr(i + 1, a.length());
					break;
				}
			}
			for (int i = 1; i < c.length(); i++)
			{
				if (c.substr(i, 1) == " ")
				{
					d = c.substr(0, i);
					e = c.substr(i + 1, c.length());
					break;
				}
			}
			cout << substitute(b, eqn[atoi(d.c_str()) - 1], eqn[atoi(e.c_str()) - 1]) << endl;
		}
		if (op == "D")
		{
			/*int m = num_vars(eqn); int r = n;*/
			D(r,eqn,arr);
			for (int j = 0; j < r; j++)
			{
				for (int i = 0; i < m; i++)
				{
					cout << coeff(arr[j][i]) << "\t";
				}
				cout << endl;
			}
		}
		if (op.substr(0, 2) == "D ")
		{
			string v = op.substr(2);
			/*int m = num_vars(eqn,n); int r = n;*/
			D_xi(r, m, eqn, arr, v);
			for (int j = 0; j < r; j++)
			{
				for (int i = 0; i < m; i++)
				{
					cout << coeff(arr[j][i]) << "\t";
				}
				cout << endl;
			}
		}
		if (op == "D_value")
		{
			/*float matrix[100][100];
			int m = num_vars(eqn,n); int r = n;*/
			D(r, eqn, arr);
			for (int j = 0; j < n; j++)
			{
				for (int i = 0; i < n; i++)
				{
					matrix[j][i] = coeff(arr[j][i]);
				}
			}
			cout << D_value(n,matrix)<<endl;
		}
		if (op == "solve")
		{
			if (m != n)cout << "No Solution" << endl;
			else 
			{
				D(r, eqn, arr);
				for (int j = 0; j < n; j++)
				{
					for (int i = 0; i < n; i++)
					{
						matrix[j][i] = coeff(arr[j][i]);
					}
				}
				float cramer= D_value(n, matrix);
				if (cramer == 0)cout << "No Solution" << endl;
				else
				{
					for (int i = 0; i < 100; i++)
					{
						ar1[i] = "0";
					}
					w = 0;
					string x = "=78";
					for (int j = 0; j < n; j++)
					{
						x = add(abs(x), abs(eqn[j]));
					}

					for (int i = 1; i < x.length(); i++)
					{
						if (x.substr(i, 1) == "=")
						{
							b = x.substr(0, i);
						}
					}

					for (int i = 1; i < b.length(); i++)
					{
						if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
						{
							d = b.substr(0, i);
							b = b.substr(i, b.length());
							i = 0;
							ar1[w] = d;
							w++;
						}
					}
					ar1[w] = b;
					for (int i = 0; i < n; i++)
					{
						D_xi(r, m, eqn, arr, var_name(ar1[i]));
						for (int j = 0; j < n; j++)
						{
							for (int p = 0; p < n; p++)
							{
								matrix[j][p] = coeff(arr[j][p]);
							}
						}
						cout << var_name(ar1[i]) << "=" << D_value(n, matrix) / cramer << endl;
					}
				}
			}
		}
	}

}

//Section 3: Used Functions
string var_name(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 65 && s[i] <= 122)
		{
			return s.substr(i, s.length());
		}
	}
	return s;
}
float coeff(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 65 && s[i] <= 122)
		{
			s = s.substr(0, i);
			if (s == "+")s = "+1";
			if (s == "-")s = "-1";
			if (s.length() == 0)s = "+1";
			return atof(s.c_str());
		}
	}
	return atof(s.c_str());
}
bool check_str(string a)
{
	for (int i = 0; i < a.length(); i++)if (a[i] >= 65 && a[i] <= 122)return true;
	return false;
}
string ftos(float a)
{
	ostringstream ss;
	ss << a;
	return ss.str();
}
string abs(string x)
{
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] == '-')x[i] = '+';
	}
	return x;
}
string proper_form(string a)
{
	if (a.substr(0, 1) != "+" && (a.substr(0, 1) != "-"))a = "+" + a;
	//string b, c, d, e, ar[100], ar1[100];
	for (int i = 0; i < 100; i++)
	{
		ar[i] = ar1[i] = "|";
	}
	int n = 0, m;

	for (int i = 1; i<a.length(); i++)
	{
		if (a.substr(i, 1) == "=")
		{
			b = a.substr(0, i);
			c = a.substr(i + 1, a.length());
			break;
		}
	}
	if (c.find("+") != 0 && c.find("-") != 0)c = "+" + c;

	for (int i = 1; i<b.length(); i++)
	{
		if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
		{
			d = b.substr(0, i);
			b = b.substr(i, b.length());
			i = 0;
			ar[n] = d;
			n++;
		}
	}
	ar[n] = b;
	m = n + 1;
	for (int i = 1; i<c.length(); i++)
	{
		if (c.substr(i, 1) == "+" || c.substr(i, 1) == "-")
		{
			e = c.substr(0, i);
			c = c.substr(i, c.length());
			i = 0;
			if (e.substr(0, 1) == "+")
			{
				e = "-" + e.substr(1, e.length());
			}

			else if (e.substr(0, 1) == "-")
			{
				e = "+" + e.substr(1, e.length());
			}
			ar[m] = e;
			m++;
		}
	}
	if (c.substr(0, 1) == "+")
	{
		c = "-" + c.substr(1, c.length());
	}

	else if (c.substr(0, 1) == "-")
	{
		c = "+" + c.substr(1, c.length());
	}
	ar[m] = c;

	float ar2[100];
	for (int i = 0; i <m + 1; i++)
	{
		if ((var_name(ar[i]) == var_name(ar[i])) && (!check_str(ar[i])))
		{
			ar1[i] = ar[i];
			ar[i] = "|";
		}
	}

	float sum = 0.0;
	for (int i = 0; i <m + 1; i++)
	{
		ar2[i] = atof(ar1[i].c_str());
		sum += ar2[i];
	}

	for (int j = 0; j < m + 1; j++)
	{
		for (int i = j + 1; i < m + 1; i++)
		{
			if ((var_name(ar[j]) == var_name(ar[i])) && check_str(ar[j]) && (ar[j] != "|"))
			{
				float coeff1 = coeff(ar[j]) + coeff(ar[i]);
				ar[j] = ftos(coeff1) + var_name(ar[j]);
				if (coeff1 == 0)ar[j] = "|";
				ar[i] = "|";
			}
		}
	}

	for (int j = 0; j < m + 1; j++)
	{
		for (int i = j + 1; i< m + 1; i++)
		{
			if (var_name(ar[i]) < var_name(ar[j]))
			{
				string swap = ar[j];
				ar[j] = ar[i];
				ar[i] = swap;
			}
		}
	}
	for (int i = 0; i < m + 1; i++)
	{
		if (ar[i].find("+") != 0 && ar[i].find("-") != 0 && ar[i] != "|")ar[i] = "+" + ar[i];
	}
	for (int i = 0; i < m + 1; i++)
	{
		if (ar[i] == "|")ar[i] = "";
	}

	sum = -1 * sum;
	ar[m] = "=" + ftos(sum);

	string proper_eqn = "";
	for (int i = 0; i < m + 1; i++)
	{
		proper_eqn += ar[i];
	}
	return proper_eqn;
}
void column(string eqn[], string var, float column_i[], int n)
{
	//string ar[100];
	for (int j = 0; j < 100; j++)
	{
		int flag = 0; string y = "";
		for (int i = 0; i < eqn[j].length(); i++)
		{
			if (eqn[j].substr(i, var.length()) == var)
			{
				y += eqn[j].substr(0, i); flag = 1;
				if (y.length() == 0){ ar[j] = "1"; }
				if (y.length() == 1){ ar[j] = y; }
				for (int k = y.length() - 1; k > 0; k--)
				{
					if (y.substr(k, 1) == "+" || y.substr(k, 1) == "-")
					{
						ar[j] = y.substr(k, y.length());
						break;
					}
					else if (!(y.substr(k, 1) == "+" || y.substr(k, 1) == "-")){ ar[j] = y; }
				}

				break;
			}

		}
		if (flag == 0)
		{
			ar[j] = "0";
			continue;
		}
	}

	for (int m = 0; m < n; m++)
	{
		int flag1 = 0;
		if (ar[m] == "+")
		{
			column_i[m] = 1; continue;
		}
		if (ar[m] == "-")
		{
			column_i[m] = -1;
			continue;
		}
		string x = ar[m].substr(1, ar[m].length());
		if (ar[m].substr(0, 1) == "+")
		{
			flag1 = 1;
			column_i[m] = atof(x.c_str());
		}
		else if (ar[m].substr(0, 1) == "-")
		{
			column_i[m] = -1 * atof(x.c_str());
		}
		if (ar[m] == "0" || ar[m] == "1" || ar[m] == "2" || ar[m] == "3" || ar[m] == "4" || ar[m] == "5" || ar[m] == "6" || ar[m] == "7" || ar[m] == "8" || ar[m] == "9")
		{
			column_i[m] = atof(ar[m].c_str());
		}
	}
}
bool IsInArray(string arr[], int x, string var)
{
	for (int i = 0; i < x; i++)
	{
		if (var_name(arr[i]) == var)return true;
	}
	return false;
}
string equation_i(string a[], string b)
{
	string c = b.substr(9, 3);
	int numofeqn = atoi(c.c_str());
	return a[numofeqn - 1];
}
string add(string s1, string s2)
{
	//string a, b;
	for (int i = 1; i<s2.length(); i++)
	{
		if (s2.substr(i, 1) == "=")
		{
			a = s2.substr(0, i);
			b = s2.substr(i + 1, s2.length());
			break;
		}
	}
	if (b.find("-") != 0)b = "+" + b;
	s1 = a + s1 + b;
	return proper_form(s1);
}
string subtract(string s1, string s2)
{
	//string a, b;
	for (int i = 1; i<s2.length(); i++)
	{
		if (s2.substr(i, 1) == "=")
		{
			a = s2.substr(0, i);
			b = s2.substr(i + 1, s2.length());
			break;
		}
	}
	s1 = b + s1 + a;
	return proper_form(s1);
}
int num_vars(string eqn[], int n)
{
	string x = "=78"; int num_vars = 0;
	for (int j = 0; j < n; j++)
	{
		x = add(abs(x), abs(eqn[j]));
	}
	x = x.substr(0, x.find("="));
	//cout << x << endl;
	for (int i = 1; i <= x.length(); i++)
	{
		if (x.substr(i, 1) == "+" || x.substr(i, 1) == "-")
		{
			num_vars++;
		}
	}
	return (num_vars + 1);
}
double coeff_in_array(string s1, string v)
{
	//string b, c, d, ar[100];
	for (int i = 0; i < 100; i++)
	{
		ar[i] = "";
	}
	int n = 0; double coeff1;
	for (int i = 1; i<s1.length(); i++)
	{
		if (s1.substr(i, 1) == "=")
		{
			b = s1.substr(0, i);
			c = s1.substr(i + 1, s1.length());
			break;
		}
	}

	for (int i = 1; i<b.length(); i++)
	{
		if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
		{
			d = b.substr(0, i);
			b = b.substr(i, b.length());
			i = 0;
			ar[n] = d;
			n++;
		}
	}
	ar[n] = b;
	ar[n + 1] = c;
	for (int i = 0; i < n + 2; i++)
	{
		if (var_name(ar[i]) == v)
		{
			return coeff1 = coeff(ar[i]);
		}
	}
}
string substitute(string v, string eq2, string eq1)
{
	string b, c, d, e, ar[100], co;
	for (int i = 0; i < 100; i++)
	{
		ar[i] = "";
	}
	int n = 0;
	double coeff1, coeff3;
	for (int i = 1; i<eq1.length(); i++)
	{
		if (eq1.substr(i, 1) == "=")
		{
			b = eq1.substr(0, i);
			c = eq1.substr(i + 1, eq1.length());
			break;
		}
	}

	for (int i = 1; i<b.length(); i++)
	{
		if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
		{
			d = b.substr(0, i);
			b = b.substr(i, b.length());
			i = 0;
			ar[n] = d;
			n++;
		}
	}
	ar[n] = b;
	ar[n + 1] = c;

	coeff1 = coeff_in_array(eq1, v);
	coeff3 = coeff_in_array(eq2, v);

	for (int i = 0; i < n + 2; i++)
	{
		if (var_name(ar[i]) == v)
		{
			ar[i] = "";
			continue;
		}
		if (ar[i].find("-") != 0 && check_str(ar[i]))
		{
			if (ar[i].find("+") == 0)
				ar[i] = "-" + ar[i].substr(1, ar[i].length());
			else ar[i] = "-" + ar[i];
		}
		else if (ar[i].find("-") == 0 && check_str(ar[i]))ar[i] = "+" + ar[i].substr(1, ar[i].length());
		double coeff2 = (coeff(ar[i]) / coeff1)*coeff3;
		if (coeff2>0)co = "+" + ftos(coeff2);
		else co = ftos(coeff2);
		if (check_str(ar[i]))ar[i] = co + var_name(ar[i]);
		else ar[i] = co;
	}

	string sum = "", sum1 = "";
	for (int i = 0; i < n + 2; i++)
	{
		sum += ar[i];
	}
	for (int i = 1; i<eq2.length(); i++)
	{
		if (eq2.substr(i, 1) == "=")
		{
			b = eq2.substr(0, i);
			c = eq2.substr(i, eq2.length());
			break;
		}
	}
	n = 0;
	for (int i = 1; i<b.length(); i++)
	{
		if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
		{
			d = b.substr(0, i);
			b = b.substr(i, b.length());
			i = 0;
			ar[n] = d;
			n++;
		}
	}
	ar[n] = b;
	ar[n + 1] = c;
	for (int i = 0; i < n + 2; i++)
	{
		if (var_name(ar[i]) == v)
		{
			ar[i] = ""; break;
		}
	}
	for (int i = 0; i < n + 2; i++)
	{
		sum1 += ar[i];
	}

	return proper_form(sum + sum1);
}
void D(int n, string eqn[], string arr[100][100])
{
	int m = num_vars(eqn, n); int r = n;
	/*string b, c, d, ar[100], ar1[100], ar0[100]; int k, w;*/
	for (int i = 0; i < 100; i++)
	{
		ar0[i] = ar1[i] = "0";
	}
	w = 0;
	string x = "=78";
	for (int j = 0; j < n; j++)
	{
		x = add(abs(x), abs(eqn[j]));
	}

	for (int i = 1; i < x.length(); i++)
	{
		if (x.substr(i, 1) == "=")
		{
			b = x.substr(0, i);
			c = x.substr(i + 1, x.length());
			break;
		}
	}

	for (int i = 1; i < b.length(); i++)
	{
		if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
		{
			d = b.substr(0, i);
			b = b.substr(i, b.length());
			i = 0;
			ar1[w] = d;
			w++;
		}
	}
	ar1[w] = b;
	for (int j = 0; j < r; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			ar[i] = "0";
		}
		k = 0;
		for (int i = 1; i < eqn[j].length(); i++)
		{
			if (eqn[j].substr(i, 1) == "=")
			{
				b = eqn[j].substr(0, i);
				c = eqn[j].substr(i + 1, eqn[j].length());
				break;
			}
		}
		for (int i = 1; i < b.length(); i++)
		{
			if (b.substr(i, 1) == "+" || b.substr(i, 1) == "-")
			{
				d = b.substr(0, i);
				b = b.substr(i, b.length());
				i = 0;
				ar[k] = d;
				k++;
			}
		}
		ar[k] = b; int q = 0;
		for (int z = 0; z < k + 1; z++)
		{
			for (int i = q; i < w + 1; i++)
			{
				if (var_name(ar[z]) != var_name(ar1[i]))ar0[i] = "0";
				else { ar0[i] = ar[z]; q = i + 1; }
			}
		}
		for (int p = 0; p < m; p++)
		{
			arr[j][p] = ar0[p];
		}
	}
}
void D_xi(int r, int m, string eqn[], string arr[100][100], string v)
{
	string  c;
	D(r, eqn, arr); int t = 0;
	for (int j = 0; j < r; j++)
	{
		for (int i = 0; i < m; i++)
		{
			if (var_name(arr[j][i]) == v)
			{
				t = i; break;
			}
		}
	}
	for (int j = 0; j < r; j++)
	{
		for (int i = 0; i < eqn[j].length(); i++)
		{
			if (eqn[j].substr(i, 1) == "=")
			{
				c = eqn[j].substr(i + 1);
				break;
			}
		}
		for (int i = 0; i < m; i++)
		{
			arr[j][t] = c;
		}
	}
}
float D_value(int n, float matrix[100][100])
{
	float d = 0;
	float submatrix[100][100];
	if (n == 2)
	{
		return((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	}
	else
	{
		for (int c = 0; c < n; c++)
		{
			int subi = 0;
			for (int i = 1; i < n; i++)
			{
				int subj = 0;
				for (int j = 0; j < n; j++)
				{
					if (j == c)
					{
						continue;
					}
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			d = d + (pow(-1, c) * matrix[0][c] * D_value(n - 1, submatrix));
		}
	}
	return d;
}