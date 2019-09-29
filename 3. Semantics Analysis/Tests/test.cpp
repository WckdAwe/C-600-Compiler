typedef int a;
typedef a wckd;
typedef wckd wckdawe[300];
typedef wckdawe vasil500[500];
typedef char ar[100];
typedef char multi_lvl[500][200][100][50];
enum days { monday=1, tuesday, wednesday, thursday, friday };
enum enum_verify { monday=1, tuesday=7, wednesday, thursday=32, friday };
class t {
private:
   float a,b;
   int list al;
   days d;
public:
   float zz(int&,ar);
   union {
      int i[2];
      float f[2];
   };
};
class t2 {
public:
   float za(int&,ar);
   float z2(int&,ar);
};
union u {
   int a;
   char b[4];
   days dd;
};

// arz d; TODO: Verify that non existing ids get SEMANTIC_ERRROR

void zz(){}
// void __try_it(int& n, days list d, int z){}
float t2::za(int & a, ar test){}
float t2::z2(int& a, ar test){}
// void test();

int g[3][2];
int i_1;
float f_1;
char c_1;
string s_1;

int expr_test = 3 + 5;

class mystery_class : t {
   void __try_it(int&,days list);
};


void mystery_class::__try_it(int& a, days list b) {
   ar z;
   static t x;
   char str[100];
   str = "another \n\
\tstring!";
   //x.i[0] = u.a = 0x33202036;
   u.a = 0x33202036;
}
// void mystery_class::__try_it() {
// /*
// ** no comment
// **/
//    ar z;
//    static t x;
//    char str[100];
//    str = "another \n\
// \tstring!";
//    if (n <= 0) x.a = 0b1.0;
//    else {
//       x.zz(n-1,z); // call zz of x
//       x.b = -x.a*car(x.al)/.314159E1;
//    }
//    x.i[0] = u.a = 0x33202036;
//    x.i[1] = 0o2762.3;
// }

int main(){}