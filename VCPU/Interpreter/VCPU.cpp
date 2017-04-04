//
// Created by svuatoslav on 4/4/17.
//

#include "VCPU.h"

VCPU::VCPU ()
{
    instruction_vector_.push_back (0);
    ip_ = instruction_vector_.cbegin ();
    sign = -1;
}

VCPU::~VCPU ()
{
    instruction_vector_.clear ();
    ip_ = instruction_vector_.cbegin ();
    sign = POISON;
}

bool VCPU::load (std::ifstream &in)
{
    if (!in.is_open () || !in.good ())
        return false;
    instruction_vector_.clear ();
    while (in.good ()) {
        int val;
        in.read ((char *) &val, 4);
        if (in.good ())
            instruction_vector_.push_back (val);
    }
    ip_ = instruction_vector_.cbegin ();
    reset ();
    return true;
}

void VCPU::setInstructions (std::vector<int> instructions)
{
    instruction_vector_ = instructions;
    ip_ = instruction_vector_.cbegin ();
}

void VCPU::reset ()
{
    ip_ = instruction_vector_.cbegin ();
    data_stack_ = std::stack<int> ();
    call_stack_ = std::stack<int> ();
}

int VCPU::execute ()
{
    int ret;
    while ((ret = executeOne ()) == -1);
    return ret;
}

void VCPU::push (int val)
{
    data_stack_.push (val);
}

int VCPU::pop ()
{
    int ret = 0;
    if (data_stack_.size () > 0) {
        ret = data_stack_.top ();
        data_stack_.pop ();
    }
    return ret;
}

int VCPU::executeOne ()
{
    int first;
    int second;
    switch (*(ip_++)) {
        case 0:
            return 0;
        case 1:
            if (*ip_ >= regnum_)
                return 2;
            push (registers[*ip_]);
            ++ip_;
            break;
        case 2:
            push (*(ip_++));
            break;
        case 3:
            if (*ip_ >= regnum_)
                return 2;
            if (data_stack_.empty ())
                return 3;
            registers[*ip_] = pop ();
            ++ip_;
            break;
        case 4:
            if (data_stack_.empty ())
                return 3;
            pop ();
            break;
        case 5:
            if (data_stack_.size () < 2)
                return 3;
            first = pop ();
            second = pop ();
            push (first);
            push (second);
            break;
        case 6:
            if (data_stack_.empty ())
                return 3;
            first = pop ();
            push (first);
            push (first);
            break;
        case 7:
            if (data_stack_.size () < 2)
                return 3;
            first = pop ();
            second = pop ();
            push (first + second);
            break;
        case 8:
            first = pop ();
            second = pop ();
            if (first == second)
                sign = 0;
            else if (first < second)
                sign = 1;
            else
                sign = 2;
            push (first - second);
            break;
        case 9:
            first = pop ();
            second = pop ();
            if (first == second)
                sign = 0;
            else if (first < second)
                sign = 1;
            else
                sign = 2;
            push (second);
            push (first);
            break;
        case 10:
            first = pop ();
            second = pop ();
            push (first * second);
            break;
        case 11:
            first = pop ();
            second = pop ();
            push (first / second);
            break;
        case 12:
            ip_ = instruction_vector_.cbegin () + *ip_;
            break;
        case 13:
            if (sign == 0)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 14:
            if (sign == 1 || sign == 2)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 15:
            if (sign == 2)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 16:
            if (sign == 1)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 17:
            if (sign == 0 || sign == 2)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 18:
            if (sign == 0 || sign == 1)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 19:
            call_stack_.push (ip_ + 1 - instruction_vector_.cbegin ());
            ip_ = instruction_vector_.cbegin () + *ip_;
            break;
        case 20:
            if (call_stack_.empty ())
                return 4;
            ip_ = instruction_vector_.cbegin () + call_stack_.top ();
            call_stack_.pop ();
            break;
        default:
            return 5;

    }
    if (ip_ >= instruction_vector_.cend () || ip_ < instruction_vector_.cbegin ())
        return 1;
    return -1;
}
