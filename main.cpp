#include <iostream>
#include <cmath>

#define EPSILON 0.001

using namespace std;

double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double radians_to_degrees(double radians) {
    return radians * 180.0 / M_PI;
}

// ����������� ABC
class Triangle {
    // ����� ������� AB
    double length_AB_;
    // �������� ���� A
    double angle_A_;
    // �������� ���� B
    double angle_B_;

    // ��� ���������� ������ BC � AC ������������ ������� �������
    double sine_theorem_coefficient() const {
        return this->length_AB() / sin(this->angle_C());
    }

public:
    // ������� ��� �����

    bool set_length_AB(double AB) {
        //cout << "- called set_length_AB(" << AB << ")\n";
        if (AB < 0.0)
            return false;
        this->length_AB_ = AB;
        return true;
    }

    bool set_angle_A(double A) {
        //cout << "- called set_angle_A(" << A << ")\n";
        if (A < 0.0 || A + this->angle_B() > M_PI)
            return false;
        this->angle_A_ = A;
        return true;
    }

    bool set_angle_B(double B) {
        //cout << "- called set_angle_B(" << B << ")\n";
        if (B < 0.0 || this->angle_A() + B > M_PI)
            return false;
        this->angle_B_ = B;
        return true;
    }

    // �������, ��������� ��������� ��� ������

    void set_length_AB_printing(double AB) {
        if (!this->set_length_AB(AB))
            cout << "Could not set length AB\n";
    }

    void set_angle_A_printing(double A) {
        if (!this->set_angle_A(A))
            cout << "Could not set angle A\n";
    }

    void set_angle_B_printing(double B) {
        if (!this->set_angle_B(B))
            cout << "Could not set angle B\n";
    }

    // ������� ��� �����

    double angle_A() const {
        return this->angle_A_;
    }

    double angle_B() const {
        return this->angle_B_;
    }

    double angle_C() const {
        return M_PI - this->angle_A() - this->angle_B();
    }


    // ������� ��� ������

    double length_AB() const {
        return this->length_AB_;
    }

    double length_BC() const {
        return this->sine_theorem_coefficient() * sin(this->angle_A());
    }

    double length_AC() const {
        return this->sine_theorem_coefficient() * sin(this->angle_B());
    }


    // ����������� �����

    // ������ ����� ����������� ����������� ���� A �� �������� BC ������ X
    // ����� ����� ����������� AX �������� �������� AX ������������ ABX,
    // ��� ������� AB ����� ������� AB ������������ ABC
    // ��� ���� BAX ����� �������� ���� A ������������ ABC (��� ��� ��������� ������������ ���� A)
    // ��� ���� ABX ����� ���� B ������������ ABC
    //
    // ������������� ����� ����������� ����������� ACX, � �������� AX �� ����, ��������� ���������� ����� ����� ��
    //
    // ���������� ��������� ������� ��� ���� ���������� ������ �����

    double bisector_A() const {
        Triangle ABX(this->length_AB(), this->angle_A() / 2.0, this->angle_B());

        // � ���� ������������ � ���� ����� C ��������� ����� X
        return ABX.length_AC();
    }

    double bisector_B() const {
        Triangle ABY(this->length_AB(), this->angle_A(), this->angle_B() / 2.0);

        // � ���� ������������ � ���� ����� C ��������� ����� Y
        return ABY.length_BC();
    }

    double bisector_C() const {
        // � ������������ � ���� ���������� ����� A -- ����� C ������������ ABC,
        // ����� B -- ����� A ������������ ABC,
        // ����� C -- ����� Z ����������� ���� B ������������ ABC
        Triangle ACZ(this->length_AC(), this->angle_C() / 2.0, this->angle_A());

        // � ���� ������������ � ���� ����� C ��������� ����� Z
        return ACZ.length_AC();
    }

    // ���������� ������� ������������ ����� ������� � ����� ���� ����� ����
    double area() const {
        cout << "- called area()\n";
        return 0.5 * this->length_AB() * this->length_BC() * sin(this->angle_B());
    }

    // �������� ��������� ������� �������������
    bool operator==(const Triangle &other) const {
        return abs(this->area() - other.area()) < EPSILON;
    }

    // �����������
    Triangle(double AB, double A, double B) {
        cout << "- called Triangle(" << AB << ", " << A << ", " << B << ")\n";
        this->set_length_AB(AB);
        this->set_angle_A_printing(A);
        this->set_angle_B_printing(B);
    }

    // ����������� �����������
    Triangle(const Triangle &other) : length_AB_(other.length_AB()), angle_A_(other.angle_A()), angle_B_(other.angle_B()) {
        cout << "- called Triangle() copy constructor\n";
    }

    // ���������� �������� ������������
    Triangle &operator=(const Triangle &other) {
        cout << "- called operator=() copy operator\n";
        this->length_AB_ = other.length_AB_;
        this->angle_A_ = other.angle_A_;
        this->angle_B_ = other.angle_B_;
        return *this;
    }

    // �������� ������ ������������
    friend ostream &operator<<(ostream &stream, Triangle &triangle);

    // �������� ����� ������������
    friend istream &operator>>(istream &stream, Triangle &triangle);

    // ����������
    ~Triangle() {
        cout << "- called ~Triangle()\n";
    }
};

ostream &operator<<(ostream &stream, Triangle &triangle) {
    stream << "Triangle:\n";
    stream << "  AB = " << abs(triangle.length_AB()) << "\n";
    stream << "  BC = " << abs(triangle.length_BC()) << "\n";
    stream << "  AC = " << abs(triangle.length_AC()) << "\n";
    stream << "  A = " << abs(triangle.angle_A()) << "\n";
    stream << "  B = " << abs(triangle.angle_B()) << "\n";
    stream << "  C = " << abs(triangle.angle_C()) << "\n";
    return stream;
}

istream &operator>>(istream &stream, Triangle &triangle) {
    double number;

    stream >> triangle.length_AB_;

    stream >> number;
    triangle.angle_A_ = degrees_to_radians(number);

    stream >> number;
    triangle.angle_B_ = degrees_to_radians(number);

    return stream;
}

int main()
{
    Triangle t1(1.0, 0.1, 0.1);
    Triangle t2(1.0, 0.1, 0.1);

    int input;
    while (true) {
        cout << "Operations:\n";
        cout << "0. Quit\n";
        cout << "1. Input triangle 1\n";
        cout << "2. Input triangle 2\n";
        cout << "3. Output triangle 1\n";
        cout << "4. Output triangle 2\n";

        cout << "5. bisector of angle A of triangle 1\n";
        cout << "6. bisector of angle B of triangle 1\n";
        cout << "7. bisector of angle C of triangle 1\n";
        cout << "8. Set length AB of triangle 1\n";
        cout << "9. Set angle A of triangle 1\n";
        cout << "10. Set angle B of triangle 1\n";
        cout << "11. Print area of triangle 1\n";
        cout << "12. Swap triangle 1 and triangle 2\n";
        cout << "13. Compare areas of triangle 1 and triangle 2\n";

        cout << "Choose operation: ";
        cin >> input;

        if (input == 0)
            break;

        switch (input) {
        case 1:
            cout << "Input triangle (AB, angle A (degrees), angle B (degrees)):\n";
            cin >> t1;
            break;

        case 2:
            cout << "Input triangle (AB, angle A (degrees), angle B (degrees)):\n";
            cin >> t2;
            break;

        case 3:
            cout << t1;
            break;

        case 4:
            cout << t2;
            break;

        case 5:
            cout << t1.bisector_A() << "\n";
            break;

        case 6:
            cout << t1.bisector_B() << "\n";
            break;

        case 7:
            cout << t1.bisector_C() << "\n";
            break;

        case 8:
            double AB;
            cin >> AB;
            t1.set_length_AB_printing(AB);
            break;

        case 9:
            double A;
            cin >> A;
            t1.set_angle_A_printing(A);
            break;

        case 10:
            double B;
            cin >> B;
            t1.set_angle_B_printing(B);
            break;

        case 11:
            cout << "Area: " << t1.area() << "\n";
            break;

        case 12: {
            Triangle t3(t1);
            t1 = t2;
            t2 = t3;
            break;
        }

        case 13:
            if (t1 == t2)
                cout << "true\n";
            else
                cout << "false\n";
            break;
        }

        cin.get();
        cin.get();

        system("cls");
    }

    return 0;
}
