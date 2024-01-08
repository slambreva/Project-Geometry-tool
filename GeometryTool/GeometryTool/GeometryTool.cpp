// GeometryTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
void define_line(double& A, double& B, double& C)
{
    std::cout << "Enter coeficients: ";
    std::cin >> A >> B >> C;
    
    std::cout<<"line: " << A << "x + " << B << "y + " << C << " = 0" << std::endl;
}

void define_point(double& x, double& y)
{
    std::cout << "Enter coordinates: ";
    std::cin >> x >> y;
    std::cout<<"point: " << "(" << x << ";" << y << ")" << std::endl;
}
bool isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}
bool isLetter(char ch)
{
    return((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}
bool is_(char ch)
{
    return ch == '_';
}


bool isValidName(const char* name)
{
    if (!name)
        return false;
    while (*name)
    {
        if ((!isDigit(*name) && (!isLetter(*name)) && (!is_(*name))))
            return false;
        name++;
    }
    return true;
}
void name_line(double& A, double& B, double& C, const char* name)
{
    
    if (!isValidName(name)) {
        std::cout << "Name is not valid!"<<std::endl;
        return;
    }
    std::cout << "Valid name! Enter coeficients: ";
    std::cin >> A >> B >> C;
    std::cout << "equation of " << name << ":" << std::endl;
    std::cout << A << "x + " << B << "y + " << C << " = 0"<<std::endl;
    return;
}

void name_point(double& x, double& y, const char* name)
{
    if (!isValidName(name)) {
        std::cout << "Name is not valid! Enter a valid name!";
        return;
    }
    std::cout << "Valid name! Enter coordinates: ";
    std::cin >> x >> y;
    std::cout << "Coordinates of " << name << " (" << x << " ; " << y << ")"<<std::endl;
    
}

bool isPointOnTheLine(double& A, double& B, double& C, double& x, double& y) 
{
    define_line(A, B, C);
    define_point(x, y);

    if (abs(A * x + B * y + C) <= 0.0001)
    {
        std::cout << "The given point is on the line"<<std::endl;
        return true;
    }
    std::cout << "The given point is not on the line"<<std::endl;
    return false;
}

void parallelLine(double& A, double& B, double& C, double& x, double& y) //coordinates of line g and point P
{
    define_line(A, B, C);
    define_point(x, y);
    double A_p = A;
    double B_p = B;
    double C_p = -A_p * x - B_p * y;
    std::cout << A_p << "x + " << B_p << "y + " << C_p << " = 0"<<std::endl;
    return;
}
void perpendicularLine(double& A, double& B, double& C, double& x, double& y) //main func
{
    
    define_line(A, B, C);
    define_point(x, y);
    double k_g = -A / B;
    double k_p = -1 / k_g;
    double C_p = -k_p * x + y; //y=kx + C -> kx -y + C = 0 -> C = -k*x+1*y
    std::cout<< k_p << "x + " << "-y + " << C_p << " = 0"<<std::endl;
    return;
}
void intersectionalPoint(double& A1, double& B1, double& C1, double& A2, double& B2, double& C2) //main func
{
    define_line(A1, B1, C1);
    define_line(A2, B2, C2);
    // if A1/A2 = B1/B2, the lines intersect
    double quotientA = A1 / A2;
    double quotientB = B1 / B2;
    if (abs(quotientA - quotientB) <= 0.0001)
    {
        std::cout << "There is no intersectional point!";
        return;
    }
    double x = (-C1 * B2 + C2 * B1) / (A1 * B2 - A2 * B1);
    double y = (-A1 * C2 + A2 * C1) / (A1 * B2 - A2 * B1);
    std::cout << "Coordinates of intersectional point: " << "(" << x << " ; " << y << ")";
    return;
}
double findMiddleX(double x1, double x2)
{
    double x_M = (x1 + x2) / 2;
    return x_M;

}
double findMiddleY(double y1, double y2)
{
    double y_M = (y1 + y2) / 2;
    return y_M;
}
void equationOfLineWith2Points(double x1, double y1, double x2, double y2, double& k, double& b)
{
    k = (y2 - y1) / (x2 - x1); //uglov koef
    b = y1 - k * x1; // y=kx + b -> kx - y + b = 0
    //std::cout << k << "x - y + " << b << " = 0";
    return;
}

void h_inTriangle(double A, double B, double C, double x, double y) //priema koef na prawa i tochka
{
    double k = -A / B;
    double k_h = -1 / k;
    double m_h = y - k_h * x; //y=kx+m
    std::cout << k_h << "x - y + " << m_h << " = 0"<<std::endl;
    return;

}
void allHeightsInTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double k_a, k_b, k_c;
    double m_a, m_b, m_c;
    equationOfLineWith2Points(x2, y2, x3, y3, k_a, m_a); //we calculate coef of segment a which is opposite point A(x1, y1)
    h_inTriangle(k_a, -1, m_a, x1, y1); //coeficients of segment a and coordinates of point A
    equationOfLineWith2Points(x1, y1, x3, y3, k_b, m_b); //coef of segment b
    h_inTriangle(k_b, -1, m_b, x2, y2);
    equationOfLineWith2Points(x1, y1, x2, y2, k_c, m_c);
    h_inTriangle(k_c, -1, m_c, x3, y3);
    return;
}
void med_inTriangle(double x, double y, double x_M, double y_M)
{
    double k_med = (y_M - y) / (x_M - x);
    double m_med = y - k_med * x;
    std::cout << k_med << "x - y + " << m_med << " = 0" << std::endl;
    return;
}
void allMedsInTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double x_M_a = findMiddleX(x2, x3); //middle of segment a which is opposite point A(x1,y1)
    double y_M_a = findMiddleY(y2, y3);
    med_inTriangle(x1, y1, x_M_a, y_M_a);
    double x_M_b = findMiddleX(x1, x3);
    double y_M_b = findMiddleY(y1, y3);
    med_inTriangle(x2, y2, x_M_b, y_M_b);
    double x_M_c = findMiddleX(x1, x2);
    double y_M_c = findMiddleY(y1, y2);
    med_inTriangle(x3, y3, x_M_c, y_M_c);
    return;
}
void middlePoint(double x1, double y1, double x2, double y2, double& x_M, double& y_M)
{
    x_M = findMiddleX(x1, x2);
    y_M = findMiddleY(y1, y2);
    return;
}
void simetral_inTriangle(double A, double B, double C, double x_M, double y_M)
{
    double k_g = -A / B;
    double k_s = -1 / k_g;
    double C_s = -k_s * x_M + y_M;
    std::cout << k_s << "x + " << "-y + " << C_s << " = 0" << std::endl;

    return;
}
void allSimetralsInTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double x_m_a, x_m_b, x_m_c;
    double y_m_a, y_m_b, y_m_c;
    middlePoint(x2, y2, x3, y3, x_m_a, y_m_a); //middle of a 
    middlePoint(x1, y1, x3, y3, x_m_b, y_m_b); //middle of b
    middlePoint(x1, y1, x2, y2, x_m_c, y_m_c); //middle of c

    double k_a, k_b, k_c;
    double m_a, m_b, m_c;
    equationOfLineWith2Points(x2, y2, x3, y3, k_a, m_a); //coef of a
    equationOfLineWith2Points(x1, y1, x3, y3, k_b, m_b); //coef of b
    equationOfLineWith2Points(x1, y1, x2, y2, k_c, m_c); //coef of c
    
    simetral_inTriangle(k_a, -1, m_a, x_m_a, y_m_a); //simetral of a
    simetral_inTriangle(k_b, -1, m_b, x_m_b, y_m_b); //simetral of b
    simetral_inTriangle(k_c, -1, m_c, x_m_c, y_m_c); //simetral of c
}
void triangle(double& x1, double& y1, double& x2, double& y2, double& x3, double& y3) //main func
{
    define_point(x1, y1);
    define_point(x2, y2);
    define_point(x3, y3);
  
    std::cout << "Heights in triangle: " << std::endl;
    allHeightsInTriangle(x1, y1, x2, y2, x3, y3);
    std::cout << "Medians in triangle: " << std::endl;
    allMedsInTriangle(x1, y1, x2, y2, x3, y3);
    std::cout << "Simetrals in triangle: " << std::endl;
    allSimetralsInTriangle(x1, y1, x2, y2, x3, y3);
    return;
}
//2 за параболи
bool areTwoLinesParallel(double A1, double B1, double C1, double A2, double B2, double C2)
{
    if ((abs(A1 / A2 - B1 / B2) <= 0.0001) && (abs(A1 / A2 - C1 / C2) > 0.001)) //A1/A2 = B1/B2 != C1/C2
    {
        return true;
    }
        
    return false;
}
bool areTwoLinesPerpendicular(double A1, double B1, double C1, double A2, double B2, double C2)
{
    double k1 = -A1 / B1;
    double k2 = -A2 / B2;
    if (abs(k1 * k2 + 1) <= 0.0001) //we check if k1*k2=-1
    {
        return true;
    }
    return false;
}
bool areTwoLinesCrossed(double A1, double B1, double C1, double A2, double B2, double C2)
{
    if (abs(A1 / A2 - B1 / B2) > 0.001) //if A1/A2 != B1/B2 they cross each other
        return true;
    return false;
}

void quadrangleType(double& A1, double& B1, double& C1, double& A2, double& B2, double& C2,
                    double& A3, double& B3, double& C3, double& A4, double& B4, double& C4)
{
    define_line(A1, B1, C1);
    define_line(A2, B2, C2);
    define_line(A3, B3, C3);
    define_line(A4, B4, C4);
    if (!areTwoLinesCrossed(A1, B1, C1, A3, B3, C3) || !areTwoLinesCrossed(A1, B1, C1, A4, B4, C4)
        || !areTwoLinesCrossed(A3, B3, C3, A2, B2, C2) || !areTwoLinesCrossed(A4, B4, C4, A2, B2, C2))
    {//da dobavq oshte proverki?
        std::cout << "There is no quadrangle" << std::endl;;
        return;
    }
    if (areTwoLinesParallel(A1, B1, C1, A2, B2, C2)) //trapezoid
    {
        if (areTwoLinesParallel(A3, B3, C3, A4, B4, C4)) //-> parallelogram
        {
            if (areTwoLinesPerpendicular(A1, B1, C1, A3, B3, C3)) 
            {
                std::cout << "rectangle" << std::endl;
                return;
            }
            else
            {
                std::cout << "parallelogram" << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "trapezoid" << std::endl;
            return;
        }
    }
    else if (areTwoLinesParallel(A1, B1, C1, A3, B3, C3))
    {
        if (areTwoLinesParallel(A2, B2, C2, A4, B4, C4)) 
        {
            if (areTwoLinesPerpendicular(A1, B1, C1, A2, B2, C2)) 
            {
                std::cout << "rectangle" << std::endl;
                return;
            }
            else
            {
                std::cout << "parallelogram" << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "trapezoid" << std::endl;
            return;
        }
    }
    else if (areTwoLinesParallel(A1, B1, C1, A4, B4, C4))
    {
        if (areTwoLinesParallel(A2, B2, C2, A3, B3, C3)) 
        {
            if (areTwoLinesPerpendicular(A1, B1, C1, A2, B2, C2)) 
            {
                std::cout << "rectangle" << std::endl;
                return;
            }
            else
            {
                std::cout << "parallelogram" << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "trapezoid" << std::endl;
            return;
        }
    }
    else if (areTwoLinesParallel(A2, B2, C2, A3, B3, C3))
    {
        std::cout << "trapezoid" << std::endl;
        return;
    }
    else if (areTwoLinesParallel(A2, B2, C2, A4, B4, C4))
    {
        std::cout << "trapezoid" << std::endl;
        return;
    }
    else if (areTwoLinesParallel(A3, B3, C3, A4, B4, C4))
    {
        std::cout << "trapezoid" << std::endl;
        return;
    }
    else
    {
        std::cout << "A random quadrangle" << std::endl;
        return;
    }
}
int main()
{
    std::cout << "Hello! Enter a number depending on your choice: " << std::endl;
    std::cout << "1 - define a line; " << std::endl << "2 - define a point; " << std::endl <<
        "3 - name a line; " << std::endl << "4 - name a point; " << std::endl << 
        "5 - check whether a point is on a line" <<
        std::endl << "6 - find the equation of a parallel line via point; " << std::endl <<
        "7 - find the equation of a perpendicular line via point; " << std::endl <<
        "8 - find intersectional point of two lines if it exists; " << std::endl <<
        "9 - find equations of heights, medians and simetrals in triangle" << std::endl <<
        "10 - find tangent of parabola; " << std::endl << "11 - find intersectual points of line and parabola" <<
        std::endl << "12 - find type of quadrangle; " << std::endl << "0 - exit the programme" << std::endl;
    int answer;
    std::cout << "Enter a number: ";
    std::cin >> answer;
    while (answer != 0)
    {
        switch (answer)
        {
        case 1: double A, B, C; define_line(A, B, C); std::cout << "Enter a number: "; std::cin >> answer; break;
        case 2: double x, y; define_point(x, y); std::cout << "Enter a number: ";  std::cin >> answer; break;
        case 3: char name[100]; std::cout << "Enter a valid name: "; std::cin >> name; name_line(A, B, C, name);
            std::cout << "Enter a number: ";  std::cin >> answer; break;
        case 4: std::cout << "Enter a valid name: "; std::cin >> name; name_point(x, y, name); 
            std::cout << "Enter a number: "; std::cin >> answer; break;
        case 5: isPointOnTheLine(A, B, C, x, y); std::cout << "Enter a number: "; std::cin >> answer; break;
        case 6: parallelLine(A, B, C, x, y); std::cout << "Enter a number: "; std::cin >> answer; break;
        case 7: perpendicularLine(A, B, C, x, y); std::cout << "Enter a number: "; std::cin >> answer; break;
        case 8: double A1, B1, C1, A2, B2, C2; intersectionalPoint(A1, B1, C1, A2, B2, C2); 
            std::cout << "Enter a number: "; std::cin >> answer; break;
        case 9: double x1, y1, x2, y2, x3, y3; triangle(x1, y1, x2, y2, x3, y3);
            std::cout << "Enter a number: "; std::cin >> answer; break;
        case 10: break; //tbi
        case 11: break; //tbi
        case 12: double A3, B3, C3, A4, B4, C4; quadrangleType(A1, B1, C1, A2, B2, C2, A3, B3, C3, A4, B4, C4);
            std::cout << "Enter a number: "; std::cin >> answer; break;


        
            
        }
    }
    return 0;

    
}

