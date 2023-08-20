struct Student {
    int sid;
    int grade[4];
    int average;      // this is computed by your program
};

int n;              // number of students
int m;              // you store the median student's id here
struct Student* s;  // a dynamic array of n students
