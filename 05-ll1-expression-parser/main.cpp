#include <iostream>
#include <regex>

enum tokens {PLUS_TOKEN = 0, MIN_TOKEN = 1, MULT_TOKEN = 2, DIV_TOKEN = 3, LP_TOKEN
= 4, RP_TOKEN = 5, DOUBLE_TOKEN = 6, EOF_TOKEN = 7,
T_NT = 0, t_NT = 1, R_NT = 2, r_NT = 3, V_NT = 4};

tokens next_token;

int main() {
    // ll(1) look-up table for arithmetic with parenthesis
    std::string ll_table[5][8] = {
        //+ - * / ( ) double $
        {"" ,"" ,"" ,"" ,"Rt" ,"" ,"Rt" ,""}, // T->
        {"+Rt" ,"-Rt" ,"" ,"" ,"" ,"e" ,"" ,"e"}, // t->
        {"" ,"" ,"" ,"" ,"Vr" ,"" ,"Vr" ,""}, // R->
        {"e" ,"e" ,"*Vr" ,"/Vr" ,"" ,"e" ,"" ,"e"}, // r->
        {"" ,"" ,"" ,"" ,"(T)" ,"" ,"d" ,""} // V->
    };

    std::string math_exp;
    std::stack<char> stack_machine;
    std::regex double_pattern ("(\\d+\\.?\\d*|\\.\\d+)");

    std::cout << "Enter a mathematical expression: ";
    std::getline(std::cin, math_exp);

    math_exp = std::regex_replace(math_exp, double_pattern, "d");

    math_exp.append("$");

    stack_machine.push('$');
    stack_machine.push('T');

    //checking if the string is valid
    for (long unsigned int i = 0; i < math_exp.length(); i++) {
        if (stack_machine.empty()) {
            std::cout << "String is not valid. \n";
            std::cout <<math_exp.substr(0,i) << " ^ " << math_exp.substr(i);
            return 0;
        }
        std::string push_string = " ";
        int current_nonterminal = 0;
        char string_char = math_exp.at(i);
        char stack_char = stack_machine.top();
        stack_machine.pop();

        switch (string_char) {
            case '+': next_token = PLUS_TOKEN; break;
            case '-': next_token = MIN_TOKEN; break;
            case '*': next_token = MULT_TOKEN; break;
            case '/': next_token = DIV_TOKEN; break;
            case '(': next_token = LP_TOKEN; break;
            case ')': next_token = RP_TOKEN; break;
            case 'd': next_token = DOUBLE_TOKEN; break;
            case '$': next_token = EOF_TOKEN; break;
            default:
                std::cout << "Error in input string. Unidentified input character: " << string_char << std::endl;
            return 1;
        }


        while (string_char != stack_char) {
            int next_token;
            switch (stack_char) {
                case 'T': current_nonterminal = T_NT; break;
                case 't': current_nonterminal = t_NT; break;
                case 'R': current_nonterminal = T_NT; break;
                case 'r': current_nonterminal = r_NT; break;
                case 'V': current_nonterminal = V_NT; break;
                default:
                    std::cout << "String is not valid. \n";
                    std::cout << math_exp.substr(0,i) << " ^ " << math_exp.substr(i);

            }
            push_string = ll_table[current_nonterminal][next_token];


            if (push_string.length() == 0) {
                std::cout << "String is not valid. \n";
                std::cout << math_exp.substr(0,i) << " ^ " << math_exp.substr(i);
                return 2;
        }
if (push_string.at(0) != 'e') {
    for (int j = push_string.length() - 1; j >= 0; j--) {
        stack_machine.push(push_string.at(j));
        }
    stack_char = stack_machine.top();
    stack_machine.pop();
    }
}

        if (stack_machine.empty()) {
            std::cout << "String is not valid. \n";
        }
        else {
            std::cout << "String is not valid. \n";
        }
        return 3;
    }
}



