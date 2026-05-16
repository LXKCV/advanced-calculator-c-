#pragma once

#include <string>
#include <optional>

struct EvalResult {
    bool ok{false};
    double value{0.0};
    std::string error;
};

class ExpressionParser {
public:
    EvalResult evaluate(const std::string &expr, bool radians = true) const;
};
