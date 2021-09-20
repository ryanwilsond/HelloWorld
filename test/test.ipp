# 1 "test1.cpp"
# 1 "test2.h" 1
int add(int, int);
# 2 "test1.cpp" 2

int main() {
    int num1 = 3;
    int num2 = 4;

    int res = add(num1, num2);

    return 0;
}
# 1 "test2.cpp"
# 1 "test2.h" 1
int add(int, int);
# 2 "test2.cpp" 2

# 1 "test3.h" 1
class c_int {
private:
    int val_;
public:
    c_int(int val) {
        this->val_ = val;
    }
};
# 4 "test2.cpp" 2

int add(int a, int b) {
    return a+b;
}