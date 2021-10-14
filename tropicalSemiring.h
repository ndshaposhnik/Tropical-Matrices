#pragma once
#include <iostream>
#include <optional>

struct tropical {
    std::optional<int> val;

    tropical& operator += (const tropical& other) {
        if (!val) {
            val = other.val;
        } if (other.val) {
            *val = std::max(*val, *other.val);
        }
        return *this;
    }

    tropical& operator *= (const tropical& other) {
        if (val && other.val) {
            *val += *other.val;
        } else if (val && !other.val) {
            val.reset();
        }
        return *this;
    }
};

std::ostream& operator << (std::ostream& out, const tropical& t) {
    if (t.val) {
        out << *t.val << ' ';
    } else {
        out << "-inf ";
    }
    return out;
}

tropical operator + (const tropical& lhs, const tropical& rhs) {
    tropical res = lhs;
    res += rhs;
    return res;
}

tropical operator * (const tropical& lhs, const tropical& rhs) {
    tropical res = lhs;
    res *= rhs;
    return res;
}

bool operator < (const tropical& lhs, const tropical& rhs) {
    if (!lhs.val && rhs.val) {
        return true;
    }
    if (!rhs.val) {
        return false;
    }
    return *lhs.val < *rhs.val;
}

