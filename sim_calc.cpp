#include <iostream>
#include <cctype>
#include <vector>

enum Ttype {NUMBER, PLUS, MINUS, STAR, SLASH, LPAREN, RPAREN, FACT, END};

class Token {
    public: 
        Ttype ttype; //token type
        double value; // numerical values for number types
};

//global vector for tokens
std::vector<Token> tokens;
size_t pos; //track position in tokens

std::vector<Token> tokenise(const std::string& input) {
    std::vector<Token> result;
    std::string ttext;

    for (char c : input) {
        if (isdigit(c) || c == '.') {
            ttext += c; //build number as string
        }
        else if (isspace(c)) {
            continue; //skip any spaces
        }
        else { //end of number
            if (!ttext.empty()) { //tokenise number found
                Token num;
                num.ttype = NUMBER;
                num.value = std::stod(ttext);
                result.push_back(num);
                ttext.clear();  //clear number string
            }

            Token token;
            token.value = 0; //default value for operators

            switch (c) {
                case '+' : token.ttype = PLUS; break;
                case '-' : token.ttype = MINUS; break;
                case '*' : token.ttype = STAR; break;
                case '/' : token.ttype = SLASH; break;
                case '(' : token.ttype = LPAREN; break;
                case ')' : token.ttype = RPAREN; break;
                case '!' : token.ttype = FACT; break;
                default : throw new std::runtime_error("Invalid char token");
            }

            result.push_back(token);
        }
    }

    if (!ttext.empty()) {
        Token num;
        num.ttype = NUMBER;
        num.value = std::stod(ttext);
        result.push_back(num);
    }

    return result;
}

Token get_token() {
    if (pos < tokens.size()) return tokens[pos];
    //the case that the end of the tokens list is reached
    Token token; 
    token.ttype = END;
    token.value = 0;
    return token;
}

void advance() { ++pos; }

//functions to implement grammar rules
double expression();
double term();
double primary();
double number();

int main() {
    std::cout << "***Simple Calculator***\n";

    while (true) {
        std::cout << "Enter expression(enter 'e' to exit):\n";
        std::string expr;

        std::getline(std::cin, expr);

        if (expr == "e" || expr == "E") 
            break;

        tokens = tokenise(expr);
        try {
            double result = expression();

            std::cout << "Result: " << result << std::endl;
        } catch (std::exception &e) {
            std::cout << "An error occurred: " << e.what() << std::endl;
        }
        tokens.clear();
        pos = 0;
    }

}

double expression() {
    double result = term();

    while (true) {
        Token token = get_token();

        if (token.ttype == PLUS) {
            advance(); //consume the plus token
            result += term(); //add term to the right of operator
        }
        else if (token.ttype == MINUS) {
            advance(); //consume minus token
            result -= term(); //evaluate result
        }
        else {
            break; //end of expression
        }
    }

    return result;
}

double term() {
    double result = primary();

    while (true) {
        Token token = get_token();

        if (token.ttype == STAR) {
            advance(); //consume star token
            result *= primary();
        }
        else if (token.ttype == SLASH) {
            advance();
            double right = primary();

            if (right == 0) throw std::runtime_error("Error: Division by zero");

            result /= right;
        }
        else {
            break;
        }
    }

    return result;
}

double primary() {
    Token token = get_token();

    if (token.ttype == NUMBER && (tokens[pos + 1]).ttype == FACT) {
        double result = number();

        if (result < 0 || result / (int) result != 1) {
            throw std::runtime_error("Syntax error!");
        }
        advance(); //consume factorial token

        for (int i = result - 1; i > 0; --i) {
            result *= i;
        }

        return result;
    }

    if (token.ttype == NUMBER) {
        return number();
    }

    else if (token.ttype == LPAREN) {
        advance(); //consume parenthesis

        double result = expression(); //evaluate expression in brackets

        if (get_token().ttype != RPAREN) {
            throw std::runtime_error("Expected : )");
        }

        advance(); //consume rparen
        return result;
    }

    else { 
        throw std::runtime_error("Syntax error");
    }
}

double number() {
    Token token = get_token();

    if (token.ttype == NUMBER) {
        advance(); //consume number snd move to next token
        return token.value;  //return the floating point value
    } else {
        throw std::runtime_error("Syntax error: expected numerical value");
    }
}
