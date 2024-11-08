#include <cstring>
#include <fstream>
#include <iostream>
#define LENGTH_MAX 7

using namespace std;

int get_num(int charOrder, int depth)
{
    int num = 0;
    if (depth > 1)
    {
        for (int i = charOrder + 1; i <= 26; i++)
            num += get_num(i, depth - 1);
    }
    else if (1 == depth)
        return 1;
    else if (0 == depth)
        return 0;
    return num;
}

int get_sum(char *ch, int depth)
{
    int charOrder = ch[0] - 'a' + 1;
    int sum = 0;
    for (int i = 1; i < charOrder; i++)
        for (int j = 0; j < depth; j++)
            sum += get_num(i, depth - j);
    for (int i = 1; i < depth; i++)
    {
        int l = ch[i] - 'a' + 1;
        int lastl = ch[i - 1] - 'a' + 1;
        for (int j = lastl + 1; j < l; j++)
        {
            sum += get_num(j, depth - i);
        }
    }
    for (int i = charOrder; i <= 26; i++)
        for (int j = 1; j < depth; j++)
            sum += get_num(i, depth - j);
    return sum + 1;
}

int main()
{
    /*
    ifstream fp_read("input.txt");
    ofstream fp_write("output.txt");
    if (fp_read.fail() || fp_write.fail())
    {
        cout << "打开文件错误!" << endl;
        exit(0);
    }
    int num = 0;
    fp_read >> num;
    */
    int num = 0;
    cin >> num;
    cout << num << endl;
    for (int i = 0; i < num; i++)
    {
        char input[LENGTH_MAX];
        // fp_read >> input;
        cin >> input;
        cout << input << " : ";
        int depth = strlen(input);
        int sum = get_sum(input, depth);
        // fp_write << sum << endl;
        cout << sum << endl;
    }
    return 0;
}
