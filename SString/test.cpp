#include <time.h>
#include "SString.h"
#include "Token.h"

using namespace std;

void main()
{
    SString R = "SString";
    SString T = "sString";
	char * t = "true";
	char * f = "false";
    int u, v;
    srand((unsigned)time(NULL));

	/* Test for boolean operators */

	cout << "Boolean operator testing\n\n";
	cout << "Less than: " << R << " < " << T << ": ";
	if(R < T) cout << t;
	else cout << f;
	cout << endl;
	
	cout << "Greater than: " << R << " > " << T << ": ";
	if(R > T) cout << t;
	else cout << f;
	cout << endl;

	cout << "Less than equal: " << R << " <= " << T << ": ";
	if(R <= T) cout << t;
	else cout << f;
	cout << endl;

	cout << "Greater than equal: " << R << " >= " << T << ": ";
	if(R >= T) cout << t;
	else cout << f;
	cout << endl;

	cout << "Equal: " << R << " == " << T << ": ";
	if(R == T) cout << t;
	else cout << f;
	cout << endl;

	cout << "Not equal: " << R << " != " << T << ": ";
	if(R != T) cout << t;
	else cout << f;
	cout << endl; cout << endl;

	/* Test cast to a const char * */

    printf("\nString length using strlen: %i\n\n", strlen(R));

	/* Test cast to a char * */

	printf("Type cast to char * for standard C functions: %s\n\n", R);

    printf("Extraction/substring\n\n");

    R = "<html><img src=\"image.gif\"></html>";
    u = abs(rand()) % R.length();
    v = abs(rand()) % R.length();
    if(u < v) { int t = v; v = u; u = t; }

	cout << "Left " << u << ": " << R << "\t" << R.left(u) << endl;
	cout << "Right " << u << ": " << R << "\t" << R.right(u) << endl;
	cout << "Mid " << v << ", " << u << ": " << R << "\t" << R.substring(v, u) << endl;

    printf("\nStream test \n\n");
    cout << "Name: ";
    cin >> R;
    cout << R << endl;

    printf("\nTrim test\n");
    R = "  United We Stand  ";
    R.trim();
    printf("%s\n%i\n", R, R.length());
}

