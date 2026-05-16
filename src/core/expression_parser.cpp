#include "expression_parser.h"
#include <cctype>
#include <cmath>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace {
int prec(const std::string &op){ if(op=="+"||op=="-") return 1; if(op=="*"||op=="/"||op=="%") return 2; if(op=="^") return 3; return 0; }
bool rightAssoc(const std::string &op){ return op=="^"; }

double toRad(double v,bool r){ return r? v : v*M_PI/180.0; }

double apply(const std::string& op,double a,double b){
    if(op=="+") return a+b; if(op=="-") return a-b; if(op=="*") return a*b;
    if(op=="/") { if (b==0) throw std::runtime_error("Division by zero"); return a/b;}
    if(op=="%") return std::fmod(a,b); if(op=="^") return std::pow(a,b);
    throw std::runtime_error("Unknown operator: "+op);
}
}

EvalResult ExpressionParser::evaluate(const std::string &expr, bool radians) const {
    try {
        std::vector<std::string> out, ops;
        std::string t;
        for(size_t i=0;i<expr.size();++i){
            char c=expr[i];
            if(std::isspace((unsigned char)c)) continue;
            if(std::isdigit((unsigned char)c)||c=='.'){
                t.clear(); while(i<expr.size() && (std::isdigit((unsigned char)expr[i])||expr[i]=='.')) t.push_back(expr[i++]); --i; out.push_back(t); continue;
            }
            if(std::isalpha((unsigned char)c)){
                t.clear(); while(i<expr.size() && std::isalpha((unsigned char)expr[i])) t.push_back(std::tolower(expr[i++])); --i; ops.push_back(t); continue;
            }
            std::string op(1,c);
            if(c=='(') ops.push_back(op);
            else if(c==')') {
                while(!ops.empty() && ops.back()!="(") { out.push_back(ops.back()); ops.pop_back(); }
                if(ops.empty()) throw std::runtime_error("Mismatched parentheses");
                ops.pop_back();
                if(!ops.empty() && std::isalpha((unsigned char)ops.back()[0])) { out.push_back(ops.back()); ops.pop_back(); }
            } else {
                while(!ops.empty() && ops.back()!="(" && ((prec(ops.back())>prec(op)) || (prec(ops.back())==prec(op)&&!rightAssoc(op)))) { out.push_back(ops.back()); ops.pop_back(); }
                ops.push_back(op);
            }
        }
        while(!ops.empty()) { if(ops.back()=="(") throw std::runtime_error("Mismatched parentheses"); out.push_back(ops.back()); ops.pop_back(); }

        std::stack<double> st;
        for (const auto &tk: out) {
            if(!tk.empty() && (std::isdigit((unsigned char)tk[0]) || tk[0]=='.')) st.push(std::stod(tk));
            else if(tk=="pi") st.push(M_PI);
            else if(tk=="e") st.push(M_E);
            else if(tk=="sin"||tk=="cos"||tk=="tan"||tk=="asin"||tk=="acos"||tk=="atan"||tk=="sinh"||tk=="cosh"||tk=="tanh"||tk=="log"||tk=="log10"||tk=="ln"||tk=="sqrt"||tk=="abs"||tk=="exp"||tk=="fact"){
                if(st.empty()) throw std::runtime_error("Stack underflow");
                double v=st.top(); st.pop();
                if(tk=="sin") st.push(std::sin(toRad(v,radians)));
                else if(tk=="cos") st.push(std::cos(toRad(v,radians)));
                else if(tk=="tan") st.push(std::tan(toRad(v,radians)));
                else if(tk=="asin") st.push(std::asin(v));
                else if(tk=="acos") st.push(std::acos(v));
                else if(tk=="atan") st.push(std::atan(v));
                else if(tk=="sinh") st.push(std::sinh(v));
                else if(tk=="cosh") st.push(std::cosh(v));
                else if(tk=="tanh") st.push(std::tanh(v));
                else if(tk=="log"||tk=="ln") st.push(std::log(v));
                else if(tk=="log10") st.push(std::log10(v));
                else if(tk=="sqrt") st.push(std::sqrt(v));
                else if(tk=="abs") st.push(std::fabs(v));
                else if(tk=="exp") st.push(std::exp(v));
                else if(tk=="fact") { if(v<0) throw std::runtime_error("Negative factorial"); double r=1; for(int i=1;i<=(int)v;i++) r*=i; st.push(r); }
            } else {
                if(st.size()<2) throw std::runtime_error("Invalid expression"); double b=st.top(); st.pop(); double a=st.top(); st.pop(); st.push(apply(tk,a,b));
            }
        }
        if(st.size()!=1) throw std::runtime_error("Invalid expression");
        return {true, st.top(), {}};
    } catch (const std::exception &e) { return {false, 0.0, e.what()}; }
}
