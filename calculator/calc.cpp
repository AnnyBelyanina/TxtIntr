#include <iostream>
#include <string>
#include <vector>
using namespace std;

void showHelp(){
    cout << "====================================================================" << endl;
    cout << "Мультипликативный калькулятор" << endl;
    cout << "Доступные операции:" << endl;
    cout << "  умножение (multiply) - перемножить все операнды" << endl;
    cout << "  деление (divide)     - разделить первый операнд на все остальные" << endl;
    cout << "Количество операндов: от 2 до 4" << endl;
    cout << "Использование:" << endl;
    cout << "  ./calc -o <операция> <число1> <число2> <число3> <число4>" << endl;
    cout << "  ./calc --operation <операция> <число1> <число2> ..." << endl;
    cout << "Примеры:" << endl;
    cout << "  ./calc -o multiply 45 13 -2" << endl;
    cout << "  ./calc --operation divide 100 2 5" << endl;
    cout << std::endl;
    cout << "====================================================================" << endl;

};

class Calculator{
private:
    vector<double> operands;
    double result;
public:
    Calculator(): result(0) {}
    
    void addOperand(double value){
        operands.push_back(value);
    }
    
    int getOperandCount(){
        return operands.size();
    }
    
    void multiply(){
        result = operands[0];
        for (size_t i = 1; i < operands.size(); i++){
            result *= operands[i];
        }
        cout << "Результат: " << result << endl;
    }
    
    void divide() {
        for (size_t i = 1; i < operands.size(); i++){
            if (operands[i] == 0){
                cout << "Ошибка - деление на ноль!" << endl;
                return;
            }
        }
        
        result = operands[0];
        for (size_t i = 1; i < operands.size(); i++){
            result /= operands[i];
        }
        cout << "Результат: " << result << endl;
    }
};


int main (int argc, char* argv[]){
    if (argc < 2) {
        showHelp();
        return 0;
    }
    
    string operation = "";
    Calculator calc;
    
    for (int i = 1; i < argc; i ++){
        string arg = argv[i];
        if (arg == "-o" || arg == "--operation"){
            if (i + 1 < argc){
                operation = argv[i + 1];
                i++;
            }
        } else {
            calc.addOperand(stod(argv[i]));
        }
    }
    
    if (calc.getOperandCount() < 2 || calc.getOperandCount() > 4){
        cout << "Ошибка: нужно от 2 до 4 чисел! Вы ввели: "  << calc.getOperandCount() << endl;
        return 1;
    }
    
    if (operation != "multiply" && operation != "divide") {
        cout << "Неизвестная операция!" << endl;
        showHelp();
        return 1;
    }
    
    if (operation == "multiply"){
        calc.multiply();
    } else {
        calc.divide();
    }
    
    return 0;
}
